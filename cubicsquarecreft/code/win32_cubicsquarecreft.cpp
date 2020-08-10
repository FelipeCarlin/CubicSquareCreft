/* ========================================================================
   $File: $
   $Date: $
   $Revision: $
   $Creator: Felipe Carlin $
   $Notice: $
   ======================================================================== */

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

#include <windows.h>
#include <gl/gl.h>

#if CSC_SLOW
// TODO(felipe): Complete assertion macro.
#define Assert(Expression) if(!(Expression)) {*(int *)0 = 0;}
#else
#define Assert(Expression)
#endif

// TODO(felipe): Should these always be 64-bit?
#define Kilobytes(Value) ((Value)*1024LL)
#define Megabytes(Value) (Kilobytes(Value)*1024LL)
#define Gigabytes(Value) (Megabytes(Value)*1024LL)
#define Terabytes(Value) (Gigabytes(Value)*1024LL)

#define ArrayCount(Array) (sizeof(Array) / sizeof((Array)[0]))


global_variable bool32 globalRunning;


struct win32_window_dimension
{
    int width;
    int height;
};

internal win32_window_dimension
Win32GetWindowDimension(HWND window)
{
    win32_window_dimension result;
    
    RECT clientRect;
    GetClientRect(window, &clientRect);
    result.width = clientRect.right - clientRect.left;
    result.height = clientRect.bottom - clientRect.top;

    return result;
}

internal LRESULT CALLBACK
Win32MainWindowCallback(HWND window, UINT message,
                        WPARAM wParam, LPARAM lParam)
{
    LRESULT result = 0;

    switch(message)
    {
        case WM_CREATE:
        {
        } break;
        
        case WM_SIZE:
        {
        } break;
        
        case WM_DESTROY:
        {
        } break;

        case WM_CLOSE:
        {
            globalRunning = false;
        } break;

        case WM_ACTIVATEAPP:
        {
        } break;

        case WM_PAINT:
        {
            PAINTSTRUCT paint;
            HDC deviceContext = BeginPaint(window, &paint);
            win32_window_dimension dimension = Win32GetWindowDimension(window);           
//            Win32DisplayBufferInWindow(&GlobalBackBuffer, DeviceContext,
//                                       Dimension.Width, Dimension.Height);
            EndPaint(window, &paint);
        } break;

        default:
        {
            result = DefWindowProc(window, message, wParam, lParam);
        } break;
    }
    
    return result;
}

INT
WinMain(HINSTANCE instance,
        HINSTANCE revInstance,
        PSTR commandLine,
        INT commandShow)
{
    HICON cubicIcon =
        (HICON)LoadImageA(NULL,             
                          "Icon.ico",       
                          IMAGE_ICON,       
                          0,                
                          0,  
                          LR_LOADFROMFILE|LR_DEFAULTSIZE|LR_SHARED);
    
    WNDCLASSA windowClass = {};

    windowClass.style = CS_VREDRAW|CS_HREDRAW;
    windowClass.lpfnWndProc = Win32MainWindowCallback;
    windowClass.hInstance = instance;
    windowClass.hIcon = cubicIcon;
    windowClass.lpszClassName = "CubicSquareCreftWindowClass";

    if(RegisterClassA(&windowClass))
    {

        HWND window =
            CreateWindowExA(
                0, //WS_EX_TOPMOST|WS_EX_LAYERED,
                windowClass.lpszClassName,
                "CubicSquareCreft",
                WS_OVERLAPPEDWINDOW|WS_VISIBLE,
                CW_USEDEFAULT,
                CW_USEDEFAULT,
                CW_USEDEFAULT,
                CW_USEDEFAULT,
                0,
                0,
                instance,
                0);
        
        if(window)
        {
            HDC deviceContext = GetDC(window);
            
            PIXELFORMATDESCRIPTOR pfd = {};
            pfd.nSize = sizeof(PIXELFORMATDESCRIPTOR);
            pfd.nVersion = 1;
            pfd.dwFlags = PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER;    // Flags
            pfd.iPixelType = PFD_TYPE_RGBA;        // The kind of framebuffer. RGBA or palette.
            pfd.cColorBits = 32;                   // Colordepth of the framebuffer.
            pfd.cDepthBits = 24;                   // Number of bits for the depthbuffer
            pfd.cStencilBits = 8;                    // Number of bits for the stencilbuffer
            pfd.dwLayerMask = PFD_MAIN_PLANE;

            int pixelFormat = ChoosePixelFormat(deviceContext, &pfd);
            Assert(pixelFormat);
            SetPixelFormat(deviceContext, pixelFormat, &pfd);

            HGLRC openGLContext = wglCreateContext(deviceContext);
            wglMakeCurrent(deviceContext, openGLContext);

            void *getExtension = wglGetProcAddress("wglGetExtensionsStringARB");
            if(getExtension)
            {
                
            }
            else
            {
                // TODO(felipe): Logging.
            }
            
            
            globalRunning = true;
            
            while(globalRunning)
            {
                MSG message;
                BOOL messageResult = GetMessage(&message, 0, 0, 0);
                if(messageResult > 0)
                {
                    TranslateMessage(&message);
                    DispatchMessage(&message);
                }
                else
                {
                    break;
                }
            }

            wglMakeCurrent(0, openGLContext);
            wglDeleteContext(openGLContext);
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
    
    return 0;
}
