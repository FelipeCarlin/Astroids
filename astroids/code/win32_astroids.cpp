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

#define Pi32 3.14159265359f

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

global_variable uint32 Texture01;
global_variable uint32 GlobalShaderProgram01;
global_variable uint32 GlobalVertexArray01;

typedef BOOL WINAPI wgl_swap_interval_ext(int interval);
global_variable wgl_swap_interval_ext *wglSwapInteval;

internal char *
StringCopy(char *Destination, const char *Source, uint32 Size)
{
   char *Result;

   Assert(Destination && Source && Size);

   Result = Destination;  
   for (uint32 I = 0;
        I < Size;
        ++I)
   {
      *Destination++ = *Source++;
   }

   return Result;
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
RenderQuad(uint32 Texture, real32 X, real32 Y, real32 Rotation, real32 Scale)
{
    glUseProgram(GlobalShaderProgram01);

    real32 AspectRatio = (real32)GlobalBackBuffer.Width/(real32)GlobalBackBuffer.Height;
    int AspectShaderLocation = glGetUniformLocation(GlobalShaderProgram01, "u_Aspect");
    glUniform1f(AspectShaderLocation, AspectRatio);
    
    int TextureShaderLocation = glGetUniformLocation(GlobalShaderProgram01, "u_Texture");
    glUniform1i(TextureShaderLocation, 0);
    int PosShaderLocation = glGetUniformLocation(GlobalShaderProgram01, "u_Pos");
    glUniform2f(PosShaderLocation, X, Y);
    // NOTE(felipe): Rotation is in degrees.
    int RotShaderLocation = glGetUniformLocation(GlobalShaderProgram01, "u_Rot");
    glUniform1f(RotShaderLocation, Rotation);
    int ScaleShaderLocation = glGetUniformLocation(GlobalShaderProgram01, "u_Scale");
    glUniform1f(ScaleShaderLocation, Scale);
    
    
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, Texture);
    
    glBindVertexArray(GlobalVertexArray01);
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
    glBindVertexArray(0);
}

internal void
GameUpdateAndRender(game_state *GameState)
{
    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    local_persist real32 QuadRotation;
    QuadRotation += 0.5f;
    
    RenderQuad(Texture01, GameState->PlayerX, GameState->PlayerY, QuadRotation, 0.05f);

}

internal void
Win32UpdateWindow(win32_offscreen_buffer *Buffer,
                  HDC DeviceContext, int WindowWidth, int WindowHeight)
{   
//    GameUpdateAndRender();
    
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

struct game_button_state
{
    int HalfTransitionCount;
    bool32 EndedDown;
};

struct game_input
{
    game_button_state W;
    game_button_state S;
    game_button_state A;
    game_button_state D;
};

internal void
Win32ProcessPendingMessages(game_state *GameState, game_input *Input)
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

                bool32 WasDown = ((Message.lParam & (1 << 30)) != 0);
                bool32 IsDown = ((Message.lParam & (1 << 31)) == 0);

                if(IsDown != WasDown)
                {
                    if(VKCode == 'W')
                    {
                        if(Input->W.EndedDown != IsDown)
                        {
                            Input->W.EndedDown = IsDown;
                            ++Input->W.HalfTransitionCount;
                        }
                    }
                    else if(VKCode == 'S')
                    {
                        if(Input->S.EndedDown != IsDown)
                        {
                            Input->S.EndedDown = IsDown;
                            ++Input->S.HalfTransitionCount;
                        }
                    }
                    else if(VKCode == 'A')
                    {
                        if(Input->A.EndedDown != IsDown)
                        {
                            Input->A.EndedDown = IsDown;
                            ++Input->A.HalfTransitionCount;
                        }
                    }
                    else if(VKCode == 'D')
                    {
                        if(Input->D.EndedDown != IsDown)
                        {
                            Input->D.EndedDown = IsDown;
                            ++Input->D.HalfTransitionCount;
                        }
                    }
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

internal uint32
OpenGLLoadImageTexure(char *Filepath)
{
    // TODO(felipe): Fix Alpha.
    uint32 Result = 0;
    
    win32_read_file_result Bitmap = Win32ReadEntireFile(Filepath);
    char Header[54];
    StringCopy(Header, (char *)Bitmap.Contents, 54);
    if(Header[0] == 'B' &&
       Header[1] == 'M')
    {
        uint32 DIBHeaderSize = *(uint32 *) & (Header[0xE]);
        uint16 ColorPlanes = *(uint16 *) & (Header[0x1A]);
        uint32 Compression = *(uint32 *) & (Header[0x1E]);
        uint32 DataPos = *(uint32 *) & (Header[0x0A]);
        uint32 ImageSize = *(uint32 *) & (Header[0x22]);
        uint32 Width = *(uint32 *) & (Header[0x12]);
        uint32 Height = *(uint32 *) & (Header[0x16]);
        uint16 BitsPerPixel = *(uint16 *) & (Header[0x1C]);

        if(DIBHeaderSize =< 40)
        {
            if(ImageSize == 0)
            {
                ImageSize = Width * Height * 3;
            }
        
            if (DataPos == 0)
            {
                DataPos = 54;
            }

            uint32 Format;
            uint32 InternalFormat;
            if(BitsPerPixel == 24)
            {
                Format = GL_BGR;
                InternalFormat = GL_RGB8;
            }
            else if(BitsPerPixel == 32)
            {
                Format = GL_BGRA;
                InternalFormat = GL_RGBA8;
            }
            else
            {
                // TODO(felipe): Logging.
                Assert(!"Could not load bitmap.");
            
                Format = GL_BGR;
                InternalFormat = GL_RGB8;
            }

            unsigned char *Data;

            Data = ((unsigned char *)Bitmap.Contents + DataPos);

            glGenTextures(1, &Result);
            glBindTexture(GL_TEXTURE_2D, Result);

            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);   
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

            glTexImage2D(GL_TEXTURE_2D, 0, InternalFormat, Width, Height, 0, Format, GL_UNSIGNED_BYTE, (void *)Data);
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

    return Result;
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
                     1.0f,  1.0f, 0.0f,  1.0f, 1.0f, // top right
                     1.0f, -1.0f, 0.0f,  1.0f, 0.0f, // bottom right
                    -1.0f, -1.0f, 0.0f,  0.0f, 0.0f, // bottom left
                    -1.0f,  1.0f, 0.0f,  0.0f, 1.0f // top left 
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
            
            char *vertexShaderSource = (char *)Win32ReadEntireFile("shaders/TextureVert.glsl").Contents;

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
    
            char *fragmentShaderSource = (char *)Win32ReadEntireFile("shaders/TextureFrag.glsl").Contents;

        
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

            glBindVertexArray(VAO);
            glBindBuffer(GL_ARRAY_BUFFER, VBO);
            glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
            glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
            glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
            glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void *)0);
            glEnableVertexAttribArray(0); 
            glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void *)(3 * sizeof(float)));
            glEnableVertexAttribArray(1);

            // Textures
            //
            
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

            Texture01 = OpenGLLoadImageTexure("bitmaps/astroidBraker.bmp");
            
            GlobalShaderProgram01 = shaderProgram;
            GlobalVertexArray01 = VAO;

            {
                RECT ClientRect;
                GetClientRect(Window, &ClientRect);
                int Width = ClientRect.right - ClientRect.left;
                int Height = ClientRect.bottom - ClientRect.top;
                Win32ResizeDIBSection(&GlobalBackBuffer, Width, Height);
            
                glViewport(0, 0, Width, Height);
            }

            game_state GameState = {};
            game_input Input = {};
            
            GlobalRunning = true;
            
            while(GlobalRunning)
            {
                // \/ MAIN LOOP HERE
                
                Win32ProcessPendingMessages(&GameState, &Input);
                
                RECT ClientRect;
                GetClientRect(Window, &ClientRect);
                int Width = ClientRect.right - ClientRect.left;
                int Height = ClientRect.bottom - ClientRect.top;
                glViewport(0, 0, Width, Height);

                real32 PlayerAcceleration = 0.001f;

                if(GameState.PlayerVelX < 0.0f)
                {
                    GameState.PlayerVelX += (-GameState.PlayerVelX*0.01f) + 0.0001f;
                }
                else if(GameState.PlayerVelX > 0)
                {
                    GameState.PlayerVelX -= (GameState.PlayerVelX*0.01f) + 0.0001f;
                }
                if(GameState.PlayerVelY < 0.0f)
                {
                    GameState.PlayerVelY += (-GameState.PlayerVelY*0.01f) + 0.0001f;
                }
                else if(GameState.PlayerVelY > 0)
                {
                    GameState.PlayerVelY -= (GameState.PlayerVelY*0.01f) + 0.0001f;
                }
                
                if(Input.W.EndedDown)
                {
                    GameState.PlayerVelY += PlayerAcceleration;
                }
                if(Input.S.EndedDown)
                {
                    GameState.PlayerVelY -= PlayerAcceleration;
                }
                if(Input.A.EndedDown)
                {
                    GameState.PlayerVelX -= PlayerAcceleration;
                }
                if(Input.D.EndedDown)
                {
                    GameState.PlayerVelX += PlayerAcceleration;
                }
                
                if(GameState.PlayerVelX > 0.0005f ||
                   GameState.PlayerVelX < -0.0005f)
                {
                    GameState.PlayerX += GameState.PlayerVelX;
                }
                if(GameState.PlayerVelY > 0.0005f ||
                   GameState.PlayerVelY < -0.0005f)
                {
                    GameState.PlayerY += GameState.PlayerVelY;
                }

                // NOTE(felipe): Force player to be on the screen.
                if(GameState.PlayerX > 1.0f)
                {
                    GameState.PlayerX = -1.0f;
                }
                else if(GameState.PlayerX < -1.0f)
                {
                    GameState.PlayerX = 1.0f;
                }
                if(GameState.PlayerY > 1.0f)
                {
                    GameState.PlayerY = -1.0f;
                }
                else if(GameState.PlayerY < -1.0f)
                {
                    GameState.PlayerY = 1.0f;
                }

                
                GameUpdateAndRender(&GameState);

                Win32UpdateWindow(&GlobalBackBuffer, DeviceContext, Width, Height);
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
