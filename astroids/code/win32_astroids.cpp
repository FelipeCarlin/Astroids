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
global_variable bool32 GlobalOpenGLLoaded;

global_variable int Texture01;
global_variable int GlobalShaderProgram01;
global_variable int GlobalVertexArray01;

typedef BOOL WINAPI wgl_swap_interval_ext(int interval);
global_variable wgl_swap_interval_ext *wglSwapInteval;

char *StringCopy(char *Destination, const char *Source, uint32 Size)
{
   char *Temp;
   Temp = Destination;  
   for (uint32 I = 0;
        I < Size;
        ++I)
   {
      *Destination++ = *Source++;
   }

   return Temp;
}

internal bool32
Win32LoadOpenGL(HWND Window)
{
    bool32 Result = 0;
    
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
        Result = LoadOpenGL();
        if(Result)
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

    return Result;
}

internal void
Win32FreeFileMemory(void *Memory)
{
    if(Memory)
    {
        VirtualFree(Memory, 0, MEM_RELEASE);
    }
}

internal win32_read_file_result
Win32ReadEntireFile(char *Filename)
{
    win32_read_file_result Result = {};
    
    HANDLE FileHandle = CreateFileA(Filename, GENERIC_READ, FILE_SHARE_READ, 0, OPEN_EXISTING, 0, 0);
    if(FileHandle != INVALID_HANDLE_VALUE)
    {
        LARGE_INTEGER FileSize;
        if(GetFileSizeEx(FileHandle, &FileSize))
        {
            uint32 FileSize32 = (uint32)FileSize.QuadPart;
            Result.Contents = VirtualAlloc(0, FileSize32, MEM_RESERVE|MEM_COMMIT, PAGE_READWRITE);
            if(Result.Contents)
            {
                DWORD BytesRead;
                if(ReadFile(FileHandle, Result.Contents, FileSize32, &BytesRead, 0) &&
                   (FileSize32 == BytesRead))
                {
                    // NOTE(felipe): File read succesfully.
                    Result.ContentSize = FileSize32;
                }
                else
                {
                    // TODO(felipe): Logging.
                    Win32FreeFileMemory(Result.Contents);
                    Result.Contents = 0;
                }
            }
            else
            {
                // TODO(felipe): Logging.
            }
        }
        else
        {
            // TODO(felipe): Logging.
        }

        CloseHandle(FileHandle);
    }
    else
    {
        // TODO(felipe): Logging.
    }

    return Result;
}

internal bool32
Win32WriteEntireFile(char *Filename, uint32 MemorySize, void *Memory)
{
    bool32 Result = false;
    
    HANDLE FileHandle = CreateFileA(Filename, GENERIC_WRITE, 0, 0, CREATE_ALWAYS, 0, 0);
    if(FileHandle != INVALID_HANDLE_VALUE)
    {
        DWORD BytesWritten;
        if(WriteFile(FileHandle, Memory, MemorySize, &BytesWritten, 0))
        {
            // NOTE(felipe): File read succesfully.
            return BytesWritten == MemorySize;
        }
        else
        {
            // TODO(felipe): Logging.
        }

        CloseHandle(FileHandle);
    }
    else
    {
        // TODO(felipe): Logging.
    }

    return Result;
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

#if 0
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
#endif
}

internal void
RenderBitmap()
{ 
    win32_read_file_result Bitmap = Win32ReadEntireFile("bitmaps/Morado.bmp");
    char Header[54];
    StringCopy(Header, (char *)Bitmap.Contents, 54);
    if(Header[0] == 'B' &&
       Header[1] == 'M')
    {
        uint64 DataPos = *(int*) & (Header[0x0A]);
        uint32 ImageSize = *(int*) & (Header[0x22]);
        uint32 Width = *(int*) & (Header[0x12]);
        uint32 Height = *(int*) & (Header[0x16]);
        uint32 BitsPerPixel = *(int *) & (Header[0x1C]);

        if(ImageSize == 0)
        {
            ImageSize = Width * Height * 3;
        }
        
        if (DataPos == 0)
        {
            DataPos = 54;
        }

        unsigned char *Data;

        Data = ((unsigned char *)Bitmap.Contents + DataPos);
        
        uint32 TextureID;
        glGenTextures(1, &TextureID);
    
        glBindTexture(GL_TEXTURE_2D, TextureID);
        
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, Width, Height, 0, GL_RGB, GL_UNSIGNED_BYTE, Data);
        
        int TextureShaderLocation = glGetUniformLocation(GlobalShaderProgram01, "Bitmap");
        glUseProgram(GlobalShaderProgram01);
        glUniform1i(TextureShaderLocation, 0);

        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, TextureID);
        
        glBindVertexArray(GlobalVertexArray01);
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
        glBindVertexArray(0);
    }
    else
    {
        // TODO(felipe): Logging
    }
}

internal void
GameUpdateAndRender()
{
    RenderBitmap();
}

internal void
Win32UpdateWindow(win32_offscreen_buffer *Buffer,
                  HDC DeviceContext, int WindowWidth, int WindowHeight)
{   
    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    GameUpdateAndRender();
    
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

            if(GlobalOpenGLLoaded)
            {
                glViewport(0, 0, Width, Height);
            }
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
            GlobalOpenGLLoaded = Win32LoadOpenGL(Window);

            HDC DeviceContext = GetDC(Window);

            float vertices[] =
                {
                     0.5f,  0.5f, 0.0f,  1.0f, 1.0f, // top right
                     0.5f, -0.5f, 0.0f,  1.0f, 0.0f, // bottom right
                    -0.5f, -0.5f, 0.0f,  0.0f, 0.0f, // bottom left
                    -0.5f,  0.5f, 0.0f,   0.0f, 1.0f // top left 
                };

            unsigned int indices[] =
                { 
                    0, 1, 3,
                    1, 2, 3
                };
            
            unsigned int VBO;
            glGenBuffers(1, &VBO);
            glBindBuffer(GL_ARRAY_BUFFER, VBO);
            glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

            unsigned int EBO;
            glGenBuffers(1, &EBO);
            glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
            glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW); 
            
            char *vertexShaderSource = (char *)Win32ReadEntireFile("shaders/BitmapVert.glsl").Contents;

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
    
            char *fragmentShaderSource = (char *)Win32ReadEntireFile("shaders/BitmapFrag.glsl").Contents;

        
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

            // ..:: Initialization code :: ..
            // 1. bind Vertex Array Object
            glBindVertexArray(VAO);
            // 2. copy our vertices array in a vertex buffer for OpenGL to use
            glBindBuffer(GL_ARRAY_BUFFER, VBO);
            glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
            // 3. copy our index array in a element buffer for OpenGL to use
            glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
            glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
            // 4. then set the vertex attributes pointers
            glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void *)0);
            glEnableVertexAttribArray(0); 
            glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void *)(3 * sizeof(float)));
            glEnableVertexAttribArray(1);

            // Textures
            //
            
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

            win32_read_file_result Bitmap = Win32ReadEntireFile("bitmaps/mario.bmp");
            char Header[54];
            StringCopy(Header, (char *)Bitmap.Contents, 54);
            if(Header[0] == 'B' &&
               Header[1] == 'M')
            {
                uint64 DataPos = *(int*) & (Header[0x0A]);
                uint32 ImageSize = *(int*) & (Header[0x22]);
                uint32 Width = *(int*) & (Header[0x12]);
                uint32 Height = *(int*) & (Header[0x16]);
                uint32 BitsPerPixel = *(int *) & (Header[0x1C]);

                if(ImageSize == 0)
                {
                    ImageSize = Width * Height * 3;
                }
        
                if (DataPos == 0)
                {
                    DataPos = 54;
                }

                unsigned char *Data;

                Data = ((unsigned char *)Bitmap.Contents + DataPos);
        
                uint32 TextureID;
                glGenTextures(1, &TextureID);
    
                glBindTexture(GL_TEXTURE_2D, TextureID);
        
                glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, Width, Height, 0, GL_RGB, GL_UNSIGNED_BYTE, Data);
        
                int TextureShaderLocation = glGetUniformLocation(GlobalShaderProgram01, "Bitmap");
                glUseProgram(GlobalShaderProgram01);
                glUniform1i(TextureShaderLocation, 0);

                glActiveTexture(GL_TEXTURE0);
                glBindTexture(GL_TEXTURE_2D, TextureID);
        
                glBindVertexArray(GlobalVertexArray01);
                glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
                glBindVertexArray(0);
            }
            else
            {
                // TODO(felipe): Logging
            }
            //
            //
            
            GlobalShaderProgram01 = shaderProgram;
            GlobalVertexArray01 = VAO;
            
            GlobalRunning = true;
            
            while(GlobalRunning)
            {
                Win32ProcessPendingMessages();
                
                // \/ MAIN LOOP HERE
                GameUpdateAndRender();
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
