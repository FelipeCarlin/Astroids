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

#include "opengl_astroids.h"
#include "opengl_astroids.cpp"

global_variable bool32 GlobalRunning;
global_variable win32_offscreen_buffer GlobalBackBuffer;

typedef BOOL WINAPI wgl_swap_interval_ext(int interval);
global_variable wgl_swap_interval_ext *wglSwapInteval;

internal void
Win32LoadOpenGL(HWND Window)
{   
    HDC DeviceContext = GetDC(Window);
    
    PIXELFORMATDESCRIPTOR DesiredPixelFormat = {};
    DesiredPixelFormat.nSize = sizeof(PIXELFORMATDESCRIPTOR);
    DesiredPixelFormat.nVersion = 1;
    DesiredPixelFormat.dwFlags = PFD_DRAW_TO_WINDOW|PFD_SUPPORT_OPENGL|PFD_DOUBLEBUFFER;
    DesiredPixelFormat.iPixelType = PFD_TYPE_RGBA;
    DesiredPixelFormat.cColorBits = 32;
    DesiredPixelFormat.cRedBits = 0;
    DesiredPixelFormat.cGreenBits = 0;
    DesiredPixelFormat.cBlueBits = 0;
    DesiredPixelFormat.cAlphaBits = 0;
    DesiredPixelFormat.cDepthBits = 24;
    DesiredPixelFormat.cStencilBits = 8;
    DesiredPixelFormat.iLayerType = PFD_MAIN_PLANE;

    int SuggestedPixelFormatIndex = ChoosePixelFormat(DeviceContext, &DesiredPixelFormat);
    SetPixelFormat(DeviceContext, SuggestedPixelFormatIndex, &DesiredPixelFormat);
    
    HGLRC OpenGLRC = wglCreateContext(DeviceContext);
    if(wglMakeCurrent(DeviceContext, OpenGLRC))
    {
        if(LoadOpenGL())
        {
            wglSwapInteval = (wgl_swap_interval_ext *)wglGetProcAddress("wglSwapIntervalEXT");
            if(wglSwapInteval)
            {
                wglSwapInteval(1);
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
    
    ReleaseDC(Window, DeviceContext);
}

internal void
Win32ResizeDIBSection(win32_offscreen_buffer *Buffer, int Width, int Height)
{
    // TODO(felipe): Bulletproof this.
    // Maybe don't free first, free after, then free first if that fails.

    if(Buffer->Memory)
    {
        VirtualFree(Buffer->Memory, 0, MEM_RELEASE);
    }

    Buffer->Width = Width;
    Buffer->Height = Height;

    Buffer->BytesPerPixel = 4;

    Buffer->Info.bmiHeader.biSize = sizeof(Buffer->Info.bmiHeader);
    Buffer->Info.bmiHeader.biWidth = Buffer->Width;
    Buffer->Info.bmiHeader.biHeight = -Buffer->Height;
    Buffer->Info.bmiHeader.biPlanes = 1;
    Buffer->Info.bmiHeader.biBitCount = 32;
    Buffer->Info.bmiHeader.biCompression = BI_RGB;

    // NOTE(felipe): Thank you to Chris Hecker of Spy Party fame
    // for clarifying tha deal with StretchDIBBits and BitBlt!
    // No more DC for us.
    
    int BitmapMemorySize = (Buffer->Width*Buffer->Height)*Buffer->BytesPerPixel;
    Buffer->Memory = VirtualAlloc(0, BitmapMemorySize, MEM_COMMIT, PAGE_READWRITE);
    Buffer->Pitch = Width * Buffer->BytesPerPixel;
    
    int Pitch = Width*Buffer->BytesPerPixel;
    uint8 *Row = (uint8 *)Buffer->Memory;
    for(int Y = 0;
        Y < Buffer->Height;
        ++Y)
    {
        uint8 *Pixel = (uint8 *)Row;
        for(int X = 0;
            X < Buffer->Width;
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
Win32UpdateWindow(win32_offscreen_buffer *Buffer,
                  HDC DeviceContext, int WindowWidth, int WindowHeight)
{
    SwapBuffers(DeviceContext);
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
            Win32ResizeDIBSection(&GlobalBackBuffer, Width, Height);
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

            Win32UpdateWindow(&GlobalBackBuffer, DeviceContext, Width, Height);
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
    
    while(PeekMessage(&Message, 0, 0, 0, PM_REMOVE))
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
            Win32LoadOpenGL(Window);

            HDC DeviceContext = GetDC(Window);
            
            GlobalRunning = true;
            
            while(GlobalRunning)
            {
                Win32ProcessPendingMessages();
                
                // \/ MAIN LOOP HERE
                
                RECT clientRect;
                GetClientRect(Window, &clientRect);
                int WindowWidth = clientRect.right - clientRect.left;
                int WindowHeight = clientRect.bottom - clientRect.top;
                
                glViewport(0, 0, WindowWidth, WindowHeight);
    
                glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
                glClear(GL_COLOR_BUFFER_BIT);

                float vertices[] =
                    {
                        -0.5f, -0.5f, 0.0f,
                        0.5f, -0.5f, 0.0f,
                        0.0f,  0.5f, 0.0f
                    };

                unsigned int VBO;
                glGenBuffers(1, &VBO);

                glBindBuffer(GL_ARRAY_BUFFER, VBO);

                glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

                const char *vertexShaderSource =
                    "#version 330 core\n"
                    "layout (location = 0) in vec3 aPos;\n"
                    "void main()\n"
                    "{\n"
                    "   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
                    "}\0";

                unsigned int vertexShader;
                vertexShader = glCreateShader(GL_VERTEX_SHADER);

                glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
                glCompileShader(vertexShader);

                int VertexSuccess;
                char VertexInfoLog[512];
                glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &VertexSuccess);
                if(!VertexSuccess)
                {
                    glGetShaderInfoLog(vertexShader, 512, NULL, VertexInfoLog);
                    Assert(!"Vertex Shader compilation error.");
                }
    
                const char *fragmentShaderSource =
                    "#version 330 core\n"
                    "out vec4 FragColor;\n"
                    "void main()\n"
                    "{\n"
                    "FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);\n"
                    "}\0";

        
                unsigned int fragmentShader;
                fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
                glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
                glCompileShader(fragmentShader);

                int FragmentSuccess;
                char FragmentInfoLog[512];
                glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &FragmentSuccess);
                if(!FragmentSuccess)
                {
                    glGetShaderInfoLog(fragmentShader, 512, NULL, FragmentInfoLog);
                    Assert(!"Fragment Shader compilation error.");
                }
    
                unsigned int shaderProgram;
                shaderProgram = glCreateProgram();

                glAttachShader(shaderProgram, vertexShader);
                glAttachShader(shaderProgram, fragmentShader);
                glLinkProgram(shaderProgram);

                int ProgramSuccess;
                char ProgramInfoLog[512];
                glGetProgramiv(shaderProgram, GL_LINK_STATUS, &ProgramSuccess);
                if(!ProgramSuccess)
                {
                    glGetProgramInfoLog(shaderProgram, 512, NULL, ProgramInfoLog);
                    Assert(!"Program compilation error.");
                }

                glUseProgram(shaderProgram);

                glDeleteShader(vertexShader);
                glDeleteShader(fragmentShader);
    
                glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
                glEnableVertexAttribArray(0);

                unsigned int VAO;
                glGenVertexArrays(1, &VAO);

                // ..:: Initialization code (done once (unless your object frequently changes)) :: ..
                // 1. bind Vertex Array Object
                glBindVertexArray(VAO);
                // 2. copy our vertices array in a buffer for OpenGL to use
                glBindBuffer(GL_ARRAY_BUFFER, VBO);
                glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
                // 3. then set our vertex attributes pointers
                glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
                glEnableVertexAttribArray(0);

                glUseProgram(shaderProgram);
                glBindVertexArray(VAO);
                glDrawArrays(GL_TRIANGLES, 0, 3);

                Win32UpdateWindow(&GlobalBackBuffer, DeviceContext, WindowWidth, WindowHeight);
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
