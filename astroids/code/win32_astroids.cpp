/* ========================================================================
   $File: $
   $Date: $
   $Revision: $
   $Creator: Felipe Carlin $
   $Notice: $
   ======================================================================== */

#include <windows.h>
#include <stdint.h>


#define internal static
#define local_persist static
#define global_variable static

typedef uint8_t uint8;
typedef uint16_t uint16;
typedef uint32_t uint32;
typedef uint64_t uint64;
typedef uint32 bool32;

typedef int8_t int8;
typedef int16_t int16;
typedef int32_t int32;
typedef int64_t int64;

typedef float real32;
typedef double real64;

global_variable bool32 GlobalRunning;

global_variable BITMAPINFO BitmapInfo;
global_variable void *BitmapMemory;
global_variable int BitmapWidth;
global_variable int BitmapHeight;

internal void
Win32ResizeDIBSection(int Width, int Height)
{
    // TODO(felipe): Bulletproof this.
    // Maybe don't free first, free after, then free first if that fails.

    if(BitmapMemory)
    {
        VirtualFree(BitmapMemory, 0, MEM_RELEASE);
    }

    BitmapWidth = Width;
    BitmapHeight = Height;

    BitmapInfo.bmiHeader.biSize = sizeof(BitmapInfo.bmiHeader);
    BitmapInfo.bmiHeader.biWidth = BitmapWidth;
    BitmapInfo.bmiHeader.biHeight = -BitmapHeight;
    BitmapInfo.bmiHeader.biPlanes = 1;
    BitmapInfo.bmiHeader.biBitCount = 32;
    BitmapInfo.bmiHeader.biCompression = BI_RGB;

    // NOTE(felipe): Thank you to Chris Hecker of Spy Party fame
    // for clarifying tha deal with StretchDIBBits and BitBlt!
    // No more DC for us.
    int BytesPerPixel = 4;
    int BitmapMemorySize = (BitmapWidth*BitmapHeight)*BytesPerPixel;
    BitmapMemory = VirtualAlloc(0, BitmapMemorySize, MEM_COMMIT, PAGE_READWRITE);

    int Pitch = Width*BytesPerPixel;
    uint8 *Row = (uint8 *)BitmapMemory;
    for(int Y = 0;
        Y < BitmapHeight;
        ++Y)
    {
        uint8 *Pixel = (uint8 *)Row;
        for(int X = 0;
            X < BitmapWidth;
            ++X)
        {
            // Memory Layout  GG BB RR xx
            
            *Pixel = 76;
            ++Pixel;
            
            *Pixel = 76;
            ++Pixel;
            
            *Pixel = 51;
            ++Pixel;

            *Pixel = 0;
            ++Pixel;
        }

        Row += Pitch;
    }
}

internal void
Win32UpdateWindow(HDC DeviceContext, RECT *WindowRect, int X, int Y, int Width, int Height)
{
    int WindowWidth = WindowRect->right - WindowRect->left;
    int WindowHeight = WindowRect->bottom - WindowRect->top;
    StretchDIBits(DeviceContext,
                  /*
                  X, Y, BitmapWidth, BitmapHeight,
                  X, Y, WindowWidth, WindowHeight,
                  */
                  0, 0, BitmapWidth, BitmapHeight,
                  0, 0, WindowWidth, WindowHeight,
                  BitmapMemory,
                  &BitmapInfo,
                  DIB_RGB_COLORS, SRCCOPY);
}

internal LRESULT CALLBACK
Win32MainWindowCallback(HWND Window, UINT Message,
                        WPARAM WParam, LPARAM LParam)
{
    LRESULT Result = 0;

    switch(Message)
    {
        case WM_SIZE:
        {
            RECT ClientRect;
            GetClientRect(Window, &ClientRect);
            int Width = ClientRect.right - ClientRect.left;
            int Height = ClientRect.bottom - ClientRect.top;
            Win32ResizeDIBSection(Width, Height);
        } break;

        case WM_CLOSE:
        {
            // TODO(felipe): Handle this with a message to the user?
            GlobalRunning = false;
        } break;

        case WM_ACTIVATEAPP:
        {
        } break;

        case WM_DESTROY:
        {
            // TODO(felipe): Handle this as an error - recreate window?
            GlobalRunning = false;
        } break;

        case WM_SYSKEYDOWN:
        case WM_SYSKEYUP:
        case WM_KEYDOWN:
        case WM_KEYUP:
        {
        } break;
        
        case WM_PAINT:
        {
            PAINTSTRUCT Paint;
            HDC DeviceContext = BeginPaint(Window, &Paint);
            int X = Paint.rcPaint.left;
            int Y = Paint.rcPaint.top;
            int Width = Paint.rcPaint.right - Paint.rcPaint.left;
            int Height = Paint.rcPaint.bottom - Paint.rcPaint.top;
            
            RECT ClientRect;
            GetClientRect(Window, &ClientRect);

            Win32UpdateWindow(DeviceContext, &ClientRect, X, Y, Width, Height);
            EndPaint(Window, &Paint);
        } break;

        default:
        {
            Result = DefWindowProc(Window, Message, WParam, LParam);
        } break;
    }

    return Result;
}

internal void
Win32ProcessPendingMessages()
{
    MSG Message;
    
    if(PeekMessageA(&Message, 0, 0, 0, PM_REMOVE) > 0)
    {
        switch(Message.message)
        {
            case WM_CLOSE:
            {
                GlobalRunning = false;
            } break;
            
            case WM_SYSKEYDOWN:
            case WM_SYSKEYUP:
            case WM_KEYDOWN:
            case WM_KEYUP:
            {
                uint32 VKCode = (uint32)Message.wParam;

                bool WasDown = ((Message.lParam & (1 << 30)) != 0);
                bool IsDown = ((Message.lParam & (1 << 31)) == 0);
                if(IsDown != WasDown)
                {
                }

                bool32 AltKeyWasDown = (Message.lParam & (1 << 29));
                if(VKCode == VK_F4 && AltKeyWasDown)
                {
                    GlobalRunning = false;
                }
            } break;

            default:
            {
                TranslateMessage(&Message);
                DispatchMessageA(&Message);                  
            } break;
        }
    }
}

INT WINAPI
WinMain(HINSTANCE Instance,
        HINSTANCE PrevInstance,
        PSTR CommandLine,
        INT CommandShow)
{
    WNDCLASS WindowClass = {};
    WindowClass.style = CS_VREDRAW|CS_HREDRAW|CS_OWNDC;
    WindowClass.lpfnWndProc = Win32MainWindowCallback;
    WindowClass.hInstance = Instance;
    //WindowClass.hIcon
    WindowClass.lpszClassName = "AstroidsWindowClass";

    if(RegisterClass(&WindowClass))
    {
        HWND Window =
            CreateWindowEx(0,
                           WindowClass.lpszClassName,
                           "Astroids",
                           WS_OVERLAPPEDWINDOW|WS_VISIBLE,
                           CW_USEDEFAULT,
                           CW_USEDEFAULT,
                           CW_USEDEFAULT,
                           CW_USEDEFAULT,
                           0,
                           0,
                           Instance,
                           0);

        if(Window)
        {
            GlobalRunning = true;
            
            while(GlobalRunning)
            {
                Win32ProcessPendingMessages();
                
                // \/ MAIN LOOP HERE
                
            }
        }
        else
        {
            // TODO(felipe): Diagnostics.
        }
    }
    else
    {
        // TODO(felipe): Diagnostics.
    }
    
    return 0;
}
