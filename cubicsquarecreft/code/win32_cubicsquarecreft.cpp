/* ========================================================================
   $File: $
   $Date: $
   $Revision: $
   $Creator: Felipe Carlin $
   $Notice: $
   ======================================================================== */

// TODO(felipe): Implement Sine myself.
#include <math.h>
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

#include "cubicsquarecreft.h"

#include <windows.h>
#include <stdio.h>
#include <malloc.h>
#include <XInput.h>
#include <dsound.h>
#include <gl/gl.h>

#include "win32_cubicsquarecreft.h"

// TODO(felipe): This is a global for now
global_variable bool32 GlobalRunning;
global_variable bool32 GlobalPause;
global_variable win32_offscreen_buffer GlobalBackBuffer;
global_variable LPDIRECTSOUNDBUFFER GlobalSecondaryBuffer;
global_variable int64 GlobalPerfCountFrequency;

// NOTE(felipe): XInputGetState
#define X_INPUT_GET_STATE(name) DWORD WINAPI name(DWORD dwUserIndex, XINPUT_STATE *pState)
typedef X_INPUT_GET_STATE(x_input_get_state);
X_INPUT_GET_STATE(XInputGetStateStub)
{
        return(ERROR_DEVICE_NOT_CONNECTED);
}
global_variable x_input_get_state *XInputGetState_ = XInputGetStateStub;
#define XInputGetState XInputGetState_

// NOTE(felipe): XInputSetState
#define X_INPUT_SET_STATE(name) DWORD WINAPI name(DWORD dwUserIndex, XINPUT_VIBRATION *pVibration)
typedef X_INPUT_SET_STATE(x_input_set_state);
X_INPUT_SET_STATE(XInputSetStateStub)
{
        return(ERROR_DEVICE_NOT_CONNECTED);
}
global_variable x_input_set_state *XInputSetState_ = XInputSetStateStub;
#define XInputSetState XInputSetState_

// NOTE(felipe): DirectSoundCreate
#define DIRECT_SOUND_CREATE(name) HRESULT WINAPI name(LPCGUID pcGuidDevice, LPDIRECTSOUND *ppDS, LPUNKNOWN pUnkOuter)
typedef DIRECT_SOUND_CREATE(direct_sound_create);

void
CatStrings(size_t SourceACount, char *SourceA,
           size_t SourceBCount, char *SourceB,
           size_t DestCount, char *Dest)
{
    // TODO(felipe): Dest bounds checking!
    
    for(int Index = 0;
        Index < SourceACount;
        ++Index)
    {
        *Dest++ = *SourceA++;
    }
    
    for(int Index = 0;
        Index < SourceBCount;
        ++Index)
    {
        *Dest++ = *SourceB++;
    }

    *Dest++ = 0;
}

internal void
Win32GetEXEFileName(win32_state *State)
{
    // NOTE(felipe): Never use MAX_PATH in code that is user-facing, because it
    // can be dangerous and lead to bad results.
    DWORD SizeOfFileName = GetModuleFileNameA(0, State->EXEFileName, sizeof(State->EXEFileName));
    State->OnePastLastSlashEXEFilnameSlash = State->EXEFileName;
    for(char *Scan = State->EXEFileName;
        *Scan;
        ++Scan)
    {
        if(*Scan == '\\')
        {
            State->OnePastLastSlashEXEFilnameSlash = Scan + 1;
        }
    }
}

internal int
StringLength(char *String)
{
    int Count = 0;
    while(*String++)
    {
        ++Count;
    }
    return Count;
}

internal void
Win32BuildEXEPathFileName(win32_state *State, char* FileName,
                          int DestCount, char *Dest)
{
    CatStrings(State->OnePastLastSlashEXEFilnameSlash - State->EXEFileName, State->EXEFileName,
               StringLength(FileName), FileName,
               DestCount, Dest);      
}

inline uint32
SafeTruncateUInt64(uint64 Value)
{
    // TODO(felipe): Defines for maximum values.
    Assert(Value <= 0xFFFFFFFF);
    uint32 Result = (uint32)Value;
    return Result;
}


DEBUG_PLATFORM_FREE_FILE_MEMORY(DEBUGPlatformFreeFileMemory)
{
    if(Memory)
    {
        VirtualFree(Memory, 0, MEM_RELEASE);
    }
}

DEBUG_PLATFORM_READ_ENTIRE_FILE(DEBUGPlatformReadEntireFile)
{
    debug_read_file_result Result = {};
    
    HANDLE FileHandle = CreateFileA(Filename, GENERIC_READ, FILE_SHARE_READ, 0, OPEN_EXISTING, 0, 0);
    if(FileHandle != INVALID_HANDLE_VALUE)
    {
        LARGE_INTEGER FileSize;
        if(GetFileSizeEx(FileHandle, &FileSize))
        {
            uint32 FileSize32 = SafeTruncateUInt64(FileSize.QuadPart);
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
                    DEBUGPlatformFreeFileMemory(Result.Contents);
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

DEBUG_PLATFORM_WRITE_ENtIRE_FILE(DEBUGPlatformWriteEntireFile)
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

inline FILETIME
Win32GetLastWriteTime(char *Filename)
{
    FILETIME LastWriteTime = {};

    WIN32_FILE_ATTRIBUTE_DATA Data;
    if(GetFileAttributesExA(Filename, GetFileExInfoStandard, &Data))
    {
        LastWriteTime = Data.ftLastWriteTime;
    }
    
    return LastWriteTime;
}

internal win32_game_code
Win32LoadGameCode(char *SourceDLLName, char *TempDLLName)
{
    win32_game_code Result = {};

    // TODO(felipe): Need to get the proper path here!
    // TODO(felipe): Automatic determination of when updates are necessary.

    Result.DLLLastWriteTime = Win32GetLastWriteTime(SourceDLLName);
    
    CopyFile(SourceDLLName, TempDLLName, FALSE);
    
    Result.GameCodeDLL = LoadLibraryA(TempDLLName);
    if(Result.GameCodeDLL)
    {
        Result.UpdateAndRender = (game_update_and_render *)
            GetProcAddress(Result.GameCodeDLL, "GameUpdateAndRender");
        
        Result.GetSoundSamples = (game_get_sound_samples *)
            GetProcAddress(Result.GameCodeDLL, "GameGetSoundSamples");

        Result.IsValid = (Result.UpdateAndRender &&
                          Result.GetSoundSamples);
    }

    if(!Result.IsValid)
    {
        Result.UpdateAndRender = 0;
        Result.GetSoundSamples = 0;
    }

    return Result;
}

internal void
Win32UnloadGameCode(win32_game_code *GameCode)
{
    if(GameCode->GameCodeDLL)
    {
        FreeLibrary(GameCode->GameCodeDLL);
        GameCode->GameCodeDLL = 0;
    }

    GameCode->IsValid = false;
    GameCode->UpdateAndRender = 0;
    GameCode->GetSoundSamples = 0;
}

internal void Win32LoadXInput()
{
    // TODO(felipe): Test this on Windows 8.
    HMODULE XInputLibrary = LoadLibraryA("xinput1_4.dll");
    if(!XInputLibrary)
    {
        // TODO(felipe): Diagnostics.
        XInputLibrary = LoadLibraryA("xinput9_1_0.dll");
    }

    if(!XInputLibrary)
    {
        // TODO(felipe): Diagnostics
        XInputLibrary = LoadLibraryA("xinput1_3.dll");
    }
    
    if(XInputLibrary)
    {
        XInputGetState = (x_input_get_state *)GetProcAddress(XInputLibrary, "XInputGetState");
        if(!XInputGetState) {XInputGetState = XInputGetStateStub;}
        
        XInputSetState = (x_input_set_state *)GetProcAddress(XInputLibrary, "XInputSetState");
        if(!XInputSetState) {XInputSetState = XInputSetStateStub;}

        // TODO(felipe): Diagnostics.
    }
    else
    {
        // TODO(felipe): Diagnostics.
    }
}

internal void Win32InitDSound(HWND Window, int32 SamplesPerSecond, int32 BufferSize)
{
    // NOTE(felipe): Load the library.
    HMODULE DSoundLibrary = LoadLibraryA("dsound.dll");
    if(DSoundLibrary)
    {
        // NOTE(felipe): Get a DirectSound object! - cooperative
        direct_sound_create *DirectSoundCreate = (direct_sound_create *)
            GetProcAddress(DSoundLibrary, "DirectSoundCreate");

        // TODO(felipe): Double-check that this works on XP - DirectSound8 or 7?
        LPDIRECTSOUND DirectSound;
        if(DirectSoundCreate && SUCCEEDED(DirectSoundCreate(0, &DirectSound, 0)))
        {
            WAVEFORMATEX WaveFormat = {};
            WaveFormat.wFormatTag = WAVE_FORMAT_PCM;
            WaveFormat.nChannels = 2;
            WaveFormat.nSamplesPerSec = SamplesPerSecond;
            WaveFormat.wBitsPerSample = 16;
            WaveFormat.nBlockAlign = (WaveFormat.nChannels * WaveFormat.wBitsPerSample) / 8;
            WaveFormat.nAvgBytesPerSec = WaveFormat.nSamplesPerSec * WaveFormat.nBlockAlign;
            WaveFormat.cbSize = 0;           
            
            if(SUCCEEDED(DirectSound->SetCooperativeLevel(Window, DSSCL_PRIORITY)))
            {
                DSBUFFERDESC BufferDescription = {};
                BufferDescription.dwSize = sizeof(BufferDescription);
                BufferDescription.dwFlags = DSBCAPS_PRIMARYBUFFER;

                // NOTE(felipe): "Create" a primary buffer
                // TODO(felipe): DSBCAPS_GLOBALFOCUS?
                
                LPDIRECTSOUNDBUFFER PrimaryBuffer;
                if(SUCCEEDED(DirectSound->CreateSoundBuffer(&BufferDescription, &PrimaryBuffer, 0)))
                {
                    HRESULT Error = PrimaryBuffer->SetFormat(&WaveFormat); 
                    if(SUCCEEDED(Error))
                    {
                        // NOTE(felipe): We have finally set the format!
                        OutputDebugStringA("Primary buffer format was set\n");
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
            }
            else
            {
                // TODO(felipe): Diagnostics.
            }

            // TODO(felipe): DSBCAPS_GETCURRENTPOSITION2.
            DSBUFFERDESC BufferDescription = {};
            BufferDescription.dwSize = sizeof(BufferDescription);
            BufferDescription.dwFlags = 0;
            BufferDescription.dwBufferBytes = BufferSize;
            BufferDescription.lpwfxFormat = &WaveFormat;
            HRESULT Error = DirectSound->CreateSoundBuffer(&BufferDescription, &GlobalSecondaryBuffer, 0); 
            if(SUCCEEDED(Error))
            {
                OutputDebugStringA("Secondary buffer created successfully\n");
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
}

internal win32_window_dimension
Win32GetWindowDimension(HWND window)
{
    win32_window_dimension result;
    
    RECT clientRect;
    GetClientRect(window, &clientRect);
    result.Width = clientRect.right - clientRect.left;
    result.Height = clientRect.bottom - clientRect.top;

    return result;
}

internal void Win32ResizeDIBSection(win32_offscreen_buffer *Buffer, int Width, int Height)
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

    // NOTE(felipe): When the bHeight field is negative, this is clue to
    // Windows to treat this bitmap as top-down, not bottom-up, meaning that
    // the first three bytes of the image are the color of the top left pixel
    // inthe bitmap, not the bottom left!
    Buffer->Info.bmiHeader.biSize = sizeof(Buffer->Info.bmiHeader);
    Buffer->Info.bmiHeader.biWidth = Buffer->Width;
    Buffer->Info.bmiHeader.biHeight = -Buffer->Height;
    Buffer->Info.bmiHeader.biPlanes = 1;
    Buffer->Info.bmiHeader.biBitCount = 32;
    Buffer->Info.bmiHeader.biCompression = BI_RGB;

    // NOTE(felipe): Thank you to Chris Hecker of Spy Party fame
    // for clarifying the deal with StrechDIBits and BitBlt!
    // No more DC for us!

    int BitmapMemorySize = (Buffer->Width * Buffer->Height) * Buffer->BytesPerPixel;
    Buffer->Memory = VirtualAlloc(0, BitmapMemorySize, MEM_COMMIT, PAGE_READWRITE);
    Buffer->Pitch = Width * Buffer->BytesPerPixel;
    
    // TODO(felipe): Probably clear this to black.
}

internal void Win32DisplayBufferInWindow(win32_offscreen_buffer *Buffer,
                                         HDC DeviceContext, int WindowWidth, int WindowHeight)
{
    // TODO(felipe): Aspect ratio correction.
    // TODO(felipe): Play with stretch modes.
    StretchDIBits(DeviceContext,
                  0, 0, Buffer->Width, Buffer->Height,
                  0, 0, Buffer->Width, Buffer->Height,
                  Buffer->Memory, &Buffer->Info,
                  DIB_RGB_COLORS, SRCCOPY);
}

internal LRESULT CALLBACK
Win32MainWindowCallback(HWND Window, UINT Message,
                        WPARAM WParam, LPARAM LParam)
{
    LRESULT Result = 0;

    switch(Message)
    {
        case WM_CLOSE:
        {
            // TODO(felipe): Handle this with a message to the user?
            GlobalRunning = false;
        } break;

        case WM_ACTIVATEAPP:
        {
#if 0
            if(WParam == TRUE)
            {
                SetLayeredWindowAttributes(Window, RGB(0, 0, 0), 255, LWA_ALPHA);
            }
            else
            {
                SetLayeredWindowAttributes(Window, RGB(0, 0, 0), 64, LWA_ALPHA);
            }
#endif
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
            Assert(!"Keyboard input came through a non-dispatch Message!");   
        } break;
        
        case WM_PAINT:
        {
            PAINTSTRUCT Paint;
            HDC DeviceContext = BeginPaint(Window, &Paint);
            win32_window_dimension Dimension = Win32GetWindowDimension(Window);           
            Win32DisplayBufferInWindow(&GlobalBackBuffer, DeviceContext,
                                       Dimension.Width, Dimension.Height);
            EndPaint(Window, &Paint);
        } break;

        default:
        {
//            OutputDebugStringA("Default\n")
            Result = DefWindowProc(Window, Message, WParam, LParam);
        } break;
    }

    return Result;
}


internal void Win32ClearSoundBuffer(win32_sound_output *SoundOutput)
{
    VOID *Region1;
    DWORD Region1Size;
    VOID *Region2;
    DWORD Region2Size;
    if(SUCCEEDED(GlobalSecondaryBuffer->Lock(0, SoundOutput->SecondaryBufferSize,
                                             &Region1, &Region1Size,
                                             &Region2, &Region2Size,
                                             0)))
    {
        // TODO(felipe): assert that Region1Size/Region2Size is valid
        
        uint8 *DestSample = (uint8 *)Region1;
        for(DWORD ByteIndex = 0; ByteIndex < Region1Size; ++ByteIndex)
        {
            *DestSample++ = 0;
        }
        
        DestSample = (uint8 *)Region2;
        for(DWORD ByteIndex = 0; ByteIndex < Region2Size; ++ByteIndex)
        {
            *DestSample++ = 0;
        }

        GlobalSecondaryBuffer->Unlock(Region1, Region1Size, Region2, Region2Size);
    }
}

internal void Win32FillSoudBuffer(win32_sound_output *SoundOutput, DWORD ByteToLock, DWORD ByteToWrite,
                                  game_sound_output_buffer *Source)
{
    // TODO(felipe): More strenuos test!
    VOID *Region1;
    DWORD Region1Size;
    VOID *Region2;
    DWORD Region2Size;
    if(SUCCEEDED(GlobalSecondaryBuffer->Lock(ByteToLock, ByteToWrite,
                                             &Region1, &Region1Size,
                                             &Region2, &Region2Size,
                                             0)))
    {
        // TODO(felipe): assert that Region1Size/Region2Size is valid
                        
        DWORD Region1SampleCount = Region1Size/SoundOutput->BytesPerSample;
        int16 *DestSample = (int16 *)Region1;
        int16 *SourceSample = Source->Samples;
        for(DWORD SampleIndex = 0;
            SampleIndex < Region1SampleCount;
            ++SampleIndex)
        {
            *DestSample++ = *SourceSample++;
            *DestSample++ = *SourceSample++;

            ++SoundOutput->RunningSampleIndex;
        }
        
        DWORD Region2SampleCount = Region2Size/SoundOutput->BytesPerSample;
        DestSample = (int16 *)Region2;
        for(DWORD SampleIndex = 0;
            SampleIndex < Region2SampleCount;
            ++SampleIndex)
        {
            *DestSample++ = *SourceSample++;
            *DestSample++ = *SourceSample++;

            ++SoundOutput->RunningSampleIndex;
        }

        GlobalSecondaryBuffer->Unlock(Region1, Region1Size, Region2, Region2Size);
    }
}

internal void
Win32ProcessKeyboardMessage(game_button_state *NewState, bool32 IsDown)
{
    Assert(NewState->EndedDown != IsDown);
    NewState->EndedDown = IsDown;
    ++NewState->HalfTransitionCount;
}

internal void
Win32ProcessXInputDigitalButton(DWORD XInputButtonState,
                                game_button_state *OldState, DWORD ButtonBit,
                                game_button_state *NewState)
{
    NewState->EndedDown = (XInputButtonState & ButtonBit);
    NewState->HalfTransitionCount = (OldState->EndedDown != NewState->EndedDown) ? 1 : 0;
}

internal real32
Win32ProcessXInputStickValue(SHORT Value, SHORT DeadZoneThreshold)
{
    real32 Result = 0;
    
    if(Value < -DeadZoneThreshold)
    {
        Result = (real32)((Value + DeadZoneThreshold) / (32768.0f - DeadZoneThreshold));
    }
    else if(Value > DeadZoneThreshold)
    {
        Result = (real32)((Value + DeadZoneThreshold) / (32767.0f - DeadZoneThreshold));
    }

    return Result;
}

internal void
Win32GetInputFileLocation(win32_state *State, int SlotIndex, int DestCount, char *Dest)
{
    Assert(SlotIndex == 1);
    Win32BuildEXEPathFileName(State, "loop_edit.hmi", DestCount, Dest);
}

internal void
Win32BeginRecordingInput(win32_state *State, int InputRecordIndex)
{
// TODO(felipe): Lazily write the giant memory block and use a memory copy instead?

    State->InputRecordingIndex = InputRecordIndex;
    
    char FileName[WIN32_STATE_FILE_NAME_COUNT];
    Win32GetInputFileLocation(State, InputRecordIndex, sizeof(FileName), FileName);
    
    State->RecordingHandle =
        CreateFileA(FileName, GENERIC_WRITE, 0, 0, CREATE_ALWAYS, 0, 0);

    DWORD BytesToWrite = (DWORD)State->TotalSize;
    Assert(State->TotalSize == BytesToWrite);
    DWORD BytesWritten;
    WriteFile(State->RecordingHandle, State->GameMemoryBlock, BytesToWrite, &BytesWritten, 0);
}

internal void
Win32EndRecordingInput(win32_state *State)
{
    CloseHandle(State->RecordingHandle);
    State->InputRecordingIndex = 0;
}


internal void
Win32BeginInputPlayBack(win32_state *State, int InputPlayingIndex)
{
    State->InputPlayingIndex = InputPlayingIndex;
    
    char FileName[WIN32_STATE_FILE_NAME_COUNT];
    Win32GetInputFileLocation(State, InputPlayingIndex, sizeof(FileName), FileName);
    
    State->PlayBackHandle =
        CreateFileA(FileName, GENERIC_READ, FILE_SHARE_READ, 0, OPEN_EXISTING, 0, 0);

    DWORD BytesToRead = (DWORD)State->TotalSize;
    Assert(State->TotalSize == BytesToRead);
    DWORD BytesRead;
    ReadFile(State->PlayBackHandle, State->GameMemoryBlock, BytesToRead, &BytesRead, 0);
}

internal void
Win32EndInputPlayBack(win32_state *State)
{
    CloseHandle(State->PlayBackHandle);
    State->InputPlayingIndex = 0;
}


internal void
Win32RecordInput(win32_state *State, game_input *Input)
{
    DWORD BytesWritten;
    WriteFile(State->RecordingHandle, Input, sizeof(*Input), &BytesWritten, 0);
}

internal void
Win32PlayBackInput(win32_state *State, game_input *Input)
{
    DWORD BytesRead;
    if(ReadFile(State->PlayBackHandle, Input, sizeof(*Input), &BytesRead, 0))
    {
        if(BytesRead == 0)
        {
            // NOTE(felipe): We've hit the end of the stream, go back to the beginning
            int PlayingIndex = State->InputPlayingIndex;
            Win32EndInputPlayBack(State);
            Win32BeginInputPlayBack(State, PlayingIndex);
            ReadFile(State->PlayBackHandle, Input, sizeof(*Input), &BytesRead, 0);
        }
    }
}

internal void
Win32ProcessPendingMessages(win32_state *State, game_controller_input *KeyboardController)
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

                // NOTE(felipe): Since we are comparing WasDown to IsDown,
                // we MUST use == and != to convert this bit tests to actual
                // 0 or 1 values.
                bool WasDown = ((Message.lParam & (1 << 30)) != 0);
                bool IsDown = ((Message.lParam & (1 << 31)) == 0);
                if(IsDown != WasDown)
                {
                    if(VKCode == 'W')
                    {
                        Win32ProcessKeyboardMessage(&KeyboardController->MoveUp, IsDown);
                    }
                    else if(VKCode == 'A')
                    {
                        Win32ProcessKeyboardMessage(&KeyboardController->MoveLeft, IsDown);
                    }
                    else if(VKCode == 'S')
                    {
                        Win32ProcessKeyboardMessage(&KeyboardController->MoveDown, IsDown);
                    }
                    else if(VKCode == 'D')
                    {
                        Win32ProcessKeyboardMessage(&KeyboardController->MoveRight, IsDown);
                    }
                    else if(VKCode == 'Q')
                    {
                        Win32ProcessKeyboardMessage(&KeyboardController->LeftShoulder, IsDown);
                    }
                    else if(VKCode == 'E')
                    {
                        Win32ProcessKeyboardMessage(&KeyboardController->RightShoulder, IsDown);
                    }
                    else if(VKCode == VK_UP)
                    {
                        Win32ProcessKeyboardMessage(&KeyboardController->ActionUp, IsDown);
                    }
                    else if(VKCode == VK_LEFT)
                    {
                        Win32ProcessKeyboardMessage(&KeyboardController->ActionLeft, IsDown);
                    }
                    else if(VKCode == VK_DOWN)
                    {
                        Win32ProcessKeyboardMessage(&KeyboardController->ActionDown, IsDown);
                    }
                    else if(VKCode == VK_RIGHT)
                    {
                        Win32ProcessKeyboardMessage(&KeyboardController->ActionRight, IsDown);
                    }
                    else if(VKCode == VK_ESCAPE)
                    {
                        Win32ProcessKeyboardMessage(&KeyboardController->Start, IsDown);
                    }
                    else if(VKCode == VK_SPACE)
                    {
                        Win32ProcessKeyboardMessage(&KeyboardController->Back, IsDown);
                    }
#if CSC_INTERNAL
                    else if(VKCode == 'P')
                    {
                        if(IsDown)
                        {
                            GlobalPause = !GlobalPause;
                        }
                    }
                    else if(VKCode == 'L')
                    {
                        if(IsDown)
                        {
                            if(State->InputRecordingIndex == 0)
                            {
                                Win32BeginRecordingInput(State, 1);
                            }
                            else
                            {
                                Win32EndRecordingInput(State);
                                Win32BeginInputPlayBack(State, 1);
                            }
                        }
                    }
#endif
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

inline LARGE_INTEGER
Win32GetWallClock()
{
    LARGE_INTEGER Result;
    QueryPerformanceCounter(&Result);
    return Result;
}   

inline real32
Win32GetSecondsElapsed(LARGE_INTEGER Start, LARGE_INTEGER End)
{
    real32 Result = ((real32)(End.QuadPart - Start.QuadPart) /
                             (real32)GlobalPerfCountFrequency);
    return Result;
}

internal void
Window32DebugDrawVertical(win32_offscreen_buffer *BackBuffer,
                          int X, int Top, int Bottom, uint32 Color)
{
    if(Top <= 0)
    {
        Top = 0;
    }

    if(Bottom >= BackBuffer->Height)
    {
        Bottom = BackBuffer->Height;
    }
    
    if((X >= 0) && (X < BackBuffer->Width))
    {
        uint8 *Pixel = ((uint8 *)BackBuffer->Memory +
                        X*BackBuffer->BytesPerPixel +
                        Top*BackBuffer->Pitch);
        for(int Y = Top;
            Y < Bottom;
            ++Y)
        {
            *(uint32 *)Pixel = Color;
            Pixel += BackBuffer->Pitch;
        }
    }
}

inline void
Win32DrawSoundBufferMarker(win32_offscreen_buffer *BackBuffer,
                           win32_sound_output *SoundOutput,
                           real32 C, int PadX, int Top, int Bottom,
                           DWORD Value, uint32 Color)
{
    real32 XReal32 = (C * (real32)Value);
    int X = PadX + (int)XReal32;
    Window32DebugDrawVertical(BackBuffer, X, Top, Bottom, Color);
}
    
internal void
Win32DebugSyncDisplay(win32_offscreen_buffer *BackBuffer,
                      int MarkerCount, win32_debug_time_marker *Markers,
                      int CurrentMarkerIndex,
                      win32_sound_output *SoundOutput, real32 TargetSecondsPerFrame)
{
    int PadX = 16;
    int PadY = 16;

    int LineHeight = 64;
    
    
    real32 C = ((real32)BackBuffer->Width - 2*PadX) / (real32)SoundOutput->SecondaryBufferSize;
    for(int MarkerIndex = 0;
        MarkerIndex < MarkerCount;
        ++MarkerIndex)
    {
        win32_debug_time_marker *ThisMarker = &Markers[MarkerIndex];
        Assert(ThisMarker->OutputPlayCursor < SoundOutput->SecondaryBufferSize);
        Assert(ThisMarker->OutputWriteCursor < SoundOutput->SecondaryBufferSize);
        Assert(ThisMarker->OutputLocation < SoundOutput->SecondaryBufferSize);
        Assert(ThisMarker->OutputByteCount < SoundOutput->SecondaryBufferSize);
        Assert(ThisMarker->FlipPlayCursor < SoundOutput->SecondaryBufferSize);
        Assert(ThisMarker->FlipWriteCursor < SoundOutput->SecondaryBufferSize);
        
        DWORD PlayColor = 0xFFFFFFFF;
        DWORD WriteColor = 0xFFFF0000;
        DWORD ExpectedFlipColor = 0xFFFFFF00;
        DWORD PlayWindowColor = 0xFFFF00FF;

        int Top = PadY;
        int Bottom = PadY + LineHeight;
        if(MarkerIndex == CurrentMarkerIndex)
        {
            Top += LineHeight+PadY;
            Bottom += LineHeight+PadY;

            int FirstTop = Top;
            
            Win32DrawSoundBufferMarker(BackBuffer, SoundOutput, C, PadX, Top, Bottom, ThisMarker->OutputPlayCursor, PlayColor);
            Win32DrawSoundBufferMarker(BackBuffer, SoundOutput, C, PadX, Top, Bottom, ThisMarker->OutputWriteCursor, WriteColor);

            Top += LineHeight+PadY;
            Bottom += LineHeight+PadY;
            
            Win32DrawSoundBufferMarker(BackBuffer, SoundOutput, C, PadX, Top, Bottom, ThisMarker->OutputLocation, PlayColor);
            Win32DrawSoundBufferMarker(BackBuffer, SoundOutput, C, PadX, Top, Bottom, ThisMarker->OutputLocation + ThisMarker->OutputByteCount, WriteColor);

            Top += LineHeight+PadY;
            Bottom += LineHeight+PadY;

            Win32DrawSoundBufferMarker(BackBuffer, SoundOutput, C, PadX, FirstTop, Bottom, ThisMarker->ExpectedFlipPlayCursor, ExpectedFlipColor);
        }
        
        Win32DrawSoundBufferMarker(BackBuffer, SoundOutput, C, PadX, Top, Bottom, ThisMarker->FlipPlayCursor, PlayColor);
        Win32DrawSoundBufferMarker(BackBuffer, SoundOutput, C, PadX, Top, Bottom, ThisMarker->FlipPlayCursor + 488*SoundOutput->BytesPerSample, PlayWindowColor);
        Win32DrawSoundBufferMarker(BackBuffer, SoundOutput, C, PadX, Top, Bottom, ThisMarker->FlipWriteCursor, WriteColor);
    }
}

INT
WinMain(HINSTANCE instance,
        HINSTANCE revInstance,
        PSTR commandLine,
        INT commandShow)
{
    win32_state State = {};
    
    LARGE_INTEGER PerfCountFrecuencyResult;
    QueryPerformanceFrequency(&PerfCountFrecuencyResult);
    GlobalPerfCountFrequency = PerfCountFrecuencyResult.QuadPart;
    
    Win32GetEXEFileName(&State);
    
    char SourceGameCodeDLLFullPath[WIN32_STATE_FILE_NAME_COUNT];
    Win32BuildEXEPathFileName(&State, "cubicsquarecreft.dll",
                              sizeof(SourceGameCodeDLLFullPath), SourceGameCodeDLLFullPath);

    char TempGameCodeDLLFullPath[WIN32_STATE_FILE_NAME_COUNT];
    Win32BuildEXEPathFileName(&State, "cubicsquarecreft_temp.dll",
                              sizeof(TempGameCodeDLLFullPath), TempGameCodeDLLFullPath);

    // NOTE(felipe): Set the Windows scheduler granularity to 1ms
    // so that our Sleep() can be more granular.
    UINT DesiredSchedulerMS = 1;
    bool32 SleepIsGranular = (timeBeginPeriod(DesiredSchedulerMS) == TIMERR_NOERROR);
    
    Win32LoadXInput();
    
    WNDCLASSA windowClass = {};

    Win32ResizeDIBSection(&GlobalBackBuffer, 1280, 720);

    windowClass.style = CS_VREDRAW|CS_HREDRAW|CS_OWNDC;
    windowClass.lpfnWndProc = Win32MainWindowCallback;
    windowClass.hInstance = instance;
    windowClass.hIcon = LoadIcon(instance, MAKEINTRESOURCE(102));
    windowClass.lpszClassName = "CubicSquareCreftWindowClass";

    // TODO(felipe): How do we reliably query on this on Windows?
#define MonitorRefreshHz 60
#define GameUpdateHz (MonitorRefreshHz / 2)
    real32 TargetSecondsPerFrame = 1.0f / (real32)GameUpdateHz;
    if(RegisterClassA(&windowClass))
    {
        HWND Window = CreateWindowExA(0,
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

        if(Window)
        {
            win32_sound_output SoundOutput = {};

            // TODO(felipe): Make this like sixty seconds?
            SoundOutput.SamplesPerSecond = 48000;
            SoundOutput.BytesPerSample = sizeof(int16) * 2;
            SoundOutput.SecondaryBufferSize = SoundOutput.SamplesPerSecond * SoundOutput.BytesPerSample;
            // TODO(felipe): Get rid of LatenySampleCount
            SoundOutput.LatencySampleCount = 3*(SoundOutput.SamplesPerSecond / GameUpdateHz);
            // TODO(felipe): Actually compute this variance and see
            // what the lowest reasonable value is.
            SoundOutput.SafetyBytes = (SoundOutput.SamplesPerSecond*SoundOutput.BytesPerSample / GameUpdateHz)/3;
            Win32InitDSound(Window, SoundOutput.SamplesPerSecond, SoundOutput.SecondaryBufferSize);
            Win32ClearSoundBuffer(&SoundOutput);
            GlobalSecondaryBuffer->Play(0, 0, DSBPLAY_LOOPING);

            GlobalRunning = true;
            
            // TODO(felipe): Pool with bitmap VirtualAlloc.
            int16 *Samples = (int16 *)VirtualAlloc(0, SoundOutput.SecondaryBufferSize,
                                                   MEM_RESERVE|MEM_COMMIT, PAGE_READWRITE);

#if CSC_INTERNAL
            LPVOID BaseAddress = (LPVOID)Terabytes(2);
#else
            LPVOID BaseAddress = 0;
#endif
            
            game_memory GameMemory = {};
            GameMemory.PermanentStorageSize = Megabytes(64);
            GameMemory.TransientStorageSize = Gigabytes(1);
            GameMemory.DEBUGPlatformFreeFileMemory = DEBUGPlatformFreeFileMemory;
            GameMemory.DEBUGPlatformReadEntireFile = DEBUGPlatformReadEntireFile;
            GameMemory.DEBUGPlatformWriteEntireFile = DEBUGPlatformWriteEntireFile;

            
            // TODO(felipe): Handle various memory footprints (USING SYSTEM METRICS).
            // TODO(felipe): Use MEM_LARGE_PAGES and call adjust token
            // privileges when not on Windows XP?
            State.TotalSize = GameMemory.PermanentStorageSize + GameMemory.TransientStorageSize;
            State.GameMemoryBlock = VirtualAlloc(BaseAddress, (size_t)State.TotalSize,
                                                 MEM_RESERVE|MEM_COMMIT,
                                                 PAGE_READWRITE);
            GameMemory.PermanentStorage = State.GameMemoryBlock; 
            GameMemory.TransientStorage = ((uint8 *)GameMemory.PermanentStorage +
                                           GameMemory.PermanentStorageSize);
            
            if(Samples && GameMemory.PermanentStorage && GameMemory.TransientStorage)
            {
                game_input Input[2] = {};
                game_input *NewInput = &Input[0];
                game_input *OldInput = &Input[1];
            
                LARGE_INTEGER LastCounter = Win32GetWallClock();
                LARGE_INTEGER FlipWallClock = Win32GetWallClock();
                
                int DebugTimeMarkerIndex = 0;
                win32_debug_time_marker DebugTimeMarkers[GameUpdateHz / 2] = {};

                DWORD AudioLatencyBytes = 0;
                real32 AudioLatencySeconds = 0;
                bool32 SoundIsValid = false;

                win32_game_code Game = Win32LoadGameCode(SourceGameCodeDLLFullPath,
                                                         TempGameCodeDLLFullPath);
                
                uint64 LastCycleCount = __rdtsc();
                while(GlobalRunning)
                {
                    FILETIME NewDLLWriteTime = Win32GetLastWriteTime(SourceGameCodeDLLFullPath); 
                    if(CompareFileTime(&NewDLLWriteTime, &Game.DLLLastWriteTime) != 0)
                    {
                        Win32UnloadGameCode(&Game);
                        Game = Win32LoadGameCode(SourceGameCodeDLLFullPath,
                                                 TempGameCodeDLLFullPath);
                    }
                    
                    // TODO(felipe): Zeroing macro.
                    // TODO(felipe): We can zero everything because up/down state
                    // will be wrong!
                    game_controller_input *OldKeyboardController = GetController(OldInput, 0);
                    game_controller_input *NewKeyboardController = GetController(NewInput, 0);
                    *NewKeyboardController = {};
                    NewKeyboardController->IsConnected = true;
                    for(int ButtonIndex = 0;
                        ButtonIndex < ArrayCount(NewKeyboardController->Buttons);
                        ++ButtonIndex)
                    {
                        NewKeyboardController->Buttons[ButtonIndex].EndedDown =
                            OldKeyboardController->Buttons[ButtonIndex].EndedDown;
                    }
                    
                    Win32ProcessPendingMessages(&State, NewKeyboardController);

                    if(!GlobalPause)
                    {
                        // TODO(felipe): Need to not poll disconnected controllers to avoid
                        // xinput frame rate hit on older libraries...
                        // TODO(felipe): Should we poll this more frequently.
                        DWORD MaxControllerCount = XUSER_MAX_COUNT;
                        if(MaxControllerCount > ArrayCount(NewInput->Controllers) - 1)
                        {
                            MaxControllerCount = ArrayCount(NewInput->Controllers - 1);
                        }
                
                        for(DWORD ControllerIndex = 0;
                            ControllerIndex < MaxControllerCount;
                            ++ControllerIndex)
                        {
                            DWORD OurController = ControllerIndex + 1;
                            game_controller_input *OldController = GetController(OldInput, OurController);
                            game_controller_input *NewController = GetController(NewInput, OurController);
                    
                            XINPUT_STATE ControllerState;
                    
                            if(XInputGetState(ControllerIndex, &ControllerState) == ERROR_SUCCESS)
                            {
                                NewController->IsConnected = true;
                                NewController->IsAnalog = OldController->IsAnalog;
                            
                                // NOTE(felipe): The controller is plugged in.
                                // TODO(felipe): See if ControllerState.dwPacketNumber increments too rapidly.
                                XINPUT_GAMEPAD *Pad = &ControllerState.Gamepad;

                                // TODO(felipe): This is a square deadzone, check XInput to
                                // verify that tha deadzone is "round" and show how to do
                                // round deadzone processing.
                                NewController->IsAnalog = true;
                                NewController->StickAverageX = Win32ProcessXInputStickValue(
                                    Pad->sThumbLX, XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE);
                                NewController->StickAverageY = Win32ProcessXInputStickValue(
                                    Pad->sThumbLY, XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE);
                                if((NewController->StickAverageX != 0) ||
                                   (NewController->StickAverageY != 0))
                                {
                                    NewController->IsAnalog = true;
                                }
                            
                                if(Pad->wButtons & XINPUT_GAMEPAD_DPAD_RIGHT)
                                {
                                    NewController->StickAverageX = 1.0f;
                                    NewController->IsAnalog = false;
                                }
                                if(Pad->wButtons & XINPUT_GAMEPAD_DPAD_LEFT)
                                {
                                    NewController->StickAverageX = -1.0f;
                                    NewController->IsAnalog = false;
                                }
                                if(Pad->wButtons & XINPUT_GAMEPAD_DPAD_UP)
                                {
                                    NewController->StickAverageY = 1.0f;
                                    NewController->IsAnalog = false;NewController->IsAnalog = false;
                                }
                                if(Pad->wButtons & XINPUT_GAMEPAD_DPAD_DOWN)
                                {
                                    NewController->StickAverageY = -1.0f;
                                    NewController->IsAnalog = false;
                                }
                            
                                real32 Threshold = 0.5f;
                                Win32ProcessXInputDigitalButton((NewController->StickAverageX > Threshold) ? 1 : 0,
                                                                &OldController->MoveRight, 1,
                                                                &NewController->MoveRight);
                                Win32ProcessXInputDigitalButton((NewController->StickAverageX < -Threshold) ? 1 : 0,
                                                                &OldController->MoveLeft, 1,
                                                                &NewController->MoveLeft);
                                Win32ProcessXInputDigitalButton((NewController->StickAverageY > Threshold) ? 1 : 0,
                                                                &OldController->MoveUp, 1,
                                                                &NewController->MoveUp);
                                Win32ProcessXInputDigitalButton((NewController->StickAverageY < -Threshold) ? 1 : 0,
                                                                &OldController->MoveDown, 1,
                                                                &NewController->MoveDown);
                            
                                Win32ProcessXInputDigitalButton(Pad->wButtons,
                                                                &OldController->ActionRight, XINPUT_GAMEPAD_B,
                                                                &NewController->ActionRight);
                                Win32ProcessXInputDigitalButton(Pad->wButtons,
                                                                &OldController->ActionLeft, XINPUT_GAMEPAD_X,
                                                                &NewController->ActionLeft);
                                Win32ProcessXInputDigitalButton(Pad->wButtons,
                                                                &OldController->ActionUp, XINPUT_GAMEPAD_Y,
                                                                &NewController->ActionUp);
                                Win32ProcessXInputDigitalButton(Pad->wButtons,
                                                                &OldController->ActionDown, XINPUT_GAMEPAD_A,
                                                                &NewController->ActionDown);
                                Win32ProcessXInputDigitalButton(Pad->wButtons,
                                                                &OldController->LeftShoulder, XINPUT_GAMEPAD_LEFT_SHOULDER,
                                                                &NewController->LeftShoulder);
                                Win32ProcessXInputDigitalButton(Pad->wButtons,
                                                                &OldController->RightShoulder, XINPUT_GAMEPAD_RIGHT_SHOULDER,
                                                                &NewController->RightShoulder);

                                Win32ProcessXInputDigitalButton(Pad->wButtons,
                                                                &OldController->Back, XINPUT_GAMEPAD_BACK,
                                                                &NewController->Back);
                                Win32ProcessXInputDigitalButton(Pad->wButtons,
                                                                &OldController->Start, XINPUT_GAMEPAD_START,
                                                                &NewController->Start);
                            }
                            else
                            {
                                // NOTE(felipe): The controller is not available.
                                NewController->IsConnected = false;
                            }
                        }

                        game_offscreen_buffer Buffer = {};
                        Buffer.Memory = GlobalBackBuffer.Memory;
                        Buffer.Width = GlobalBackBuffer.Width;
                        Buffer.Height = GlobalBackBuffer.Height;
                        Buffer.Pitch = GlobalBackBuffer.Pitch;
                        Buffer.BytesPerPixel = GlobalBackBuffer.BytesPerPixel;

                        if(State.InputRecordingIndex)
                        {
                            Win32RecordInput(&State, NewInput);
                        }
                        if(State.InputPlayingIndex)
                        {
                            Win32PlayBackInput(&State, NewInput);
                        }
                        if(Game.UpdateAndRender)
                        {
                            Game.UpdateAndRender(&GameMemory, NewInput, &Buffer);
                        }
                        
                        LARGE_INTEGER AudioWallClock = Win32GetWallClock();
                        real32 FromBeginToAudioSeconds = Win32GetSecondsElapsed(FlipWallClock, AudioWallClock);
                    
                        DWORD PlayCursor = 0;
                        DWORD WriteCursor = 0;
                        if(GlobalSecondaryBuffer->GetCurrentPosition(&PlayCursor, &WriteCursor) == DS_OK)
                        {
                            /* NOTE(felipe):

                               Here is how sound output computation works.

                               We define a safety value that is the number
                               of samples we think our game update loop
                               may vary by (let's say up to 2ms).
                       
                               When we wake up to write audio, we will look
                               and see what the play cursor position is and we
                               will forecast ahead where we think the play
                               cursor will be on the next frame boundary.

                               We will then look to see if the write cursor is
                               before that by at least our safety value. If it
                               is, the target fill position is that frame plus
                               one frame. This gives us perfect audio sync in
                               the case of a card that has low enough latency.
                           
                               If the write cursor is _after_ that safety
                               margin, then we assume we can never sync the
                               audio perfectly, so we will write one frame's
                               worth of audio plus the safty margin's worth of
                               guard samples.
                            */
                        
                            if(!SoundIsValid)
                            {
                                SoundOutput.RunningSampleIndex = WriteCursor/SoundOutput.BytesPerSample;
                                SoundIsValid = true;
                            }

                            DWORD ByteToLock = ((SoundOutput.RunningSampleIndex*SoundOutput.BytesPerSample) %
                                                SoundOutput.SecondaryBufferSize);

                            DWORD ExpectedSoundBytesPerFrame =
                                (SoundOutput.SamplesPerSecond*SoundOutput.BytesPerSample) / GameUpdateHz;
                            real32 SecondsLeftUntilFlip = (TargetSecondsPerFrame - FromBeginToAudioSeconds);
                            DWORD ExpectedBytesUntilFlip = (DWORD)((SecondsLeftUntilFlip/TargetSecondsPerFrame)*(real32)ExpectedSoundBytesPerFrame);
                            
                            DWORD ExpectedFrameBoundaryByte = PlayCursor + ExpectedBytesUntilFlip;
                            
                            DWORD SafeWriteCursor = WriteCursor;
                            if(SafeWriteCursor < PlayCursor)
                            {
                                SafeWriteCursor += SoundOutput.SecondaryBufferSize;
                            }
                            Assert(SafeWriteCursor >= PlayCursor);
                            SafeWriteCursor += SoundOutput.SafetyBytes;
                        
                            bool32 AudioCardIsLowLatency = (SafeWriteCursor < ExpectedFrameBoundaryByte);
                        
                            DWORD TargetCursor = 0;
                            if(AudioCardIsLowLatency)
                            {
                                TargetCursor = (ExpectedFrameBoundaryByte + ExpectedSoundBytesPerFrame);
                            }
                            else
                            {
                                TargetCursor = (WriteCursor + ExpectedSoundBytesPerFrame +
                                                SoundOutput.SafetyBytes);
                            }
                            TargetCursor = (TargetCursor % SoundOutput.SecondaryBufferSize);

                            DWORD BytesToWrite = 0;
                            if(ByteToLock > TargetCursor)
                            {
                                BytesToWrite = (SoundOutput.SecondaryBufferSize - ByteToLock);
                                BytesToWrite += TargetCursor;
                            }
                            else
                            {
                                BytesToWrite = TargetCursor - ByteToLock;
                            }

                            game_sound_output_buffer SoundBuffer = {};
                            SoundBuffer.SamplesPerSecond = SoundOutput.SamplesPerSecond;
                            SoundBuffer.SampleCount = BytesToWrite / SoundOutput.BytesPerSample;
                            SoundBuffer.Samples = Samples;
                            if(Game.GetSoundSamples)
                            {
                            Game.GetSoundSamples(&GameMemory, &SoundBuffer);
                            }
                            
#if CSC_INTERNAL
                            win32_debug_time_marker *Marker = &DebugTimeMarkers[DebugTimeMarkerIndex];
                            Marker->OutputPlayCursor = PlayCursor;
                            Marker->OutputWriteCursor = WriteCursor;
                            Marker->OutputLocation = ByteToLock;
                            Marker->OutputByteCount = BytesToWrite;
                            Marker->ExpectedFlipPlayCursor = ExpectedFrameBoundaryByte;
                        
                            DWORD UnwrappedWriteCursor = WriteCursor;
                            if(UnwrappedWriteCursor < PlayCursor)
                            {
                                UnwrappedWriteCursor += SoundOutput.SecondaryBufferSize;
                            }
                            AudioLatencyBytes = UnwrappedWriteCursor - PlayCursor;
                            AudioLatencySeconds =
                                (((real32)AudioLatencyBytes / (real32)SoundOutput.BytesPerSample) /
                                 (real32)SoundOutput.SamplesPerSecond);
                        
                            char TextBuffer[256];
                            _snprintf_s(TextBuffer, sizeof(TextBuffer),
                                        "BTL:%u TC:%u BTW:%u PC:%u WC:%u DELTA:%u (%fs)\n",
                                        ByteToLock, TargetCursor, BytesToWrite,
                                        PlayCursor, WriteCursor, AudioLatencyBytes, AudioLatencySeconds);
                            OutputDebugStringA(TextBuffer);   
#endif
                            Win32FillSoudBuffer(&SoundOutput, ByteToLock, BytesToWrite, &SoundBuffer);
                        }
                        else
                        {
                            SoundIsValid = false;
                        }

                        LARGE_INTEGER WorkCounter = Win32GetWallClock();
                        real32 WorkSecondsElapsed = Win32GetSecondsElapsed(LastCounter, WorkCounter);

                        // TODO(felipe): NOT TESTED YET! PROBABLY BUGGY!!
                        real32 SecondsElapsedForFrame = WorkSecondsElapsed;
                        if(SecondsElapsedForFrame < TargetSecondsPerFrame)
                        {
                            if(SleepIsGranular)
                            {
                                DWORD SleepMS = (DWORD)(1000.0f * (TargetSecondsPerFrame - SecondsElapsedForFrame));
                                if(SleepMS > 0)
                                {
                                    Sleep(SleepMS);
                                }
                            }

                            real32 TestSecondsElapsedForFrame = Win32GetSecondsElapsed(LastCounter, Win32GetWallClock());

                            if(TestSecondsElapsedForFrame < TargetSecondsPerFrame)
                            {
                                // TODO(felipe): LOG MISSED SLEEP HERE
                            }
                        
                            while(SecondsElapsedForFrame < TargetSecondsPerFrame)
                            {
                                SecondsElapsedForFrame = Win32GetSecondsElapsed(LastCounter,
                                                                                Win32GetWallClock());
                            }
                        }
                        else
                        {
                            // TODO(felipe): MISSED FRAME RATE!
                            // TODO(felipe): Logging.
                        }

                        LARGE_INTEGER EndCounter = Win32GetWallClock();
                        real32 MSPerFrame = 1000.0f*Win32GetSecondsElapsed(LastCounter, EndCounter);
                        LastCounter = EndCounter;
                    
                        win32_window_dimension Dimension = Win32GetWindowDimension(Window);
#if CSC_INTERNAL
                        // TODO(felipe): Note, current is wrong no the zero'th index.
//                        Win32DebugSyncDisplay(&GlobalBackBuffer, ArrayCount(DebugTimeMarkers), DebugTimeMarkers,
//                                              DebugTimeMarkerIndex - 1, &SoundOutput, TargetSecondsPerFrame);
#endif
                        HDC DeviceContext = GetDC(Window);
                        Win32DisplayBufferInWindow(&GlobalBackBuffer, DeviceContext,
                                                   Dimension.Width, Dimension.Height);
                        ReleaseDC(Window, DeviceContext);

                        FlipWallClock = Win32GetWallClock();
#if 0
#if CSC_INTERNAL
                        // NOTE(felipe): This is debug code
                        {                  
                            DWORD PlayCursor = 0;
                            DWORD WriteCursor = 0;
                            if(GlobalSecondaryBuffer->GetCurrentPosition(&PlayCursor, &WriteCursor) == DS_OK)
                            {

                                Assert(DebugTimeMarkerIndex < ArrayCount(DebugTimeMarkers));
                                win32_debug_time_marker *Marker = &DebugTimeMarkers[DebugTimeMarkerIndex];
                                Marker->FlipPlayCursor = PlayCursor;
                                Marker->FlipWriteCursor = WriteCursor;
                            }
                        }
#endif
#endif

                        game_input *Temp = NewInput;
                        NewInput = OldInput;
                        OldInput = Temp;
                        // TODO(felipe): Should I clear these here?

                        int64 EndCycleCount = __rdtsc();
                        uint64 CyclesElapsed = EndCycleCount - LastCycleCount;
                        LastCycleCount = EndCycleCount;

                    
                        real64 FPS = 0.0f;
                        real64 MCPF = (CyclesElapsed / (1000.0f * 1000.0f));

                        char FPSBuffer[256];
                        _snprintf_s(FPSBuffer, sizeof(FPSBuffer),
                                    "%0.02fms/f, %0.02ff/s, %0.02fc/f\n", MSPerFrame, FPS, MCPF);
                        OutputDebugStringA(FPSBuffer);

#if CSC_INTERNAL
                        ++DebugTimeMarkerIndex;
                        if(DebugTimeMarkerIndex == ArrayCount(DebugTimeMarkers))
                        {
                            DebugTimeMarkerIndex = 0;
                        }
#endif
                    }
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
    }
    else
    {
        // TODO(felipe): Logging.
    }
    
    return 0;
}
