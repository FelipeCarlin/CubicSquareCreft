#if !defined(CUBICSQUARECREFT_H)
/* ========================================================================
   $File: $
   $Date: $
   $Revision: $
   $Creator: Felipe Carlin $
   $Notice: $
   ======================================================================== */

/*
  NOTE(felipe):

  CSC_INTERNAL:
    0 - Build for public release
    1 - Build for developer only

  CSC_SLOW:
    0 - Not slow code allowed!
    1 - Slow code
 */

// TODO(felipe): Implement Sine myself.
#include <math.h>
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
// TODO(felipe): swap, min, max ... macros???

/*
  NOTE(felipe): Services that the platform layer provides to the Game.
*/

#if CSC_INTERNAL
/*
  IMPORTANT(felipe):

  These are NOT for doing anything inthe shipping game - they are
  blocking and the write doesn't protect against lost data!
*/
struct debug_read_file_result
{
    uint32 ContentSize;
    void *Contents;
};

#define DEBUG_PLATFORM_FREE_FILE_MEMORY(name) void name(void *Memory)
typedef DEBUG_PLATFORM_FREE_FILE_MEMORY(debug_platform_free_file_memory);

#define DEBUG_PLATFORM_READ_ENTIRE_FILE(name) debug_read_file_result name(char *Filename)
typedef DEBUG_PLATFORM_READ_ENTIRE_FILE(debug_platform_read_entire_file);

#define DEBUG_PLATFORM_WRITE_ENtIRE_FILE(name) bool32 name(char *Filename, uint32 MemorySize, void *Memory)
typedef DEBUG_PLATFORM_WRITE_ENtIRE_FILE(debug_platform_write_entire_file);

#endif

/*
  NOTE(felipe): Services that the Game provides to the platform layer.
  (this may expand in the future - sound on different thread, etc.)
*/

// FOUR THINGS - timing, controller/keyboard input, bitmap buffer to use, soundbuffer to use.

// TODO(felipe): In the future, rendering _spesifically_ will become a three-tier abstraction!!
struct game_offscreen_buffer
{
    // NOTE(felipe): Pixels are always 32-bit size, memory order GG BB RR XX.
    void* Memory;
    int Width;
    int Height;
    int Pitch;
    int BytesPerPixel;
};

struct game_sound_output_buffer
{
    int SamplesPerSecond;
    int SampleCount;
    int16 *Samples;
};

struct game_button_state
{
    int HalfTransitionCount;
    bool32 EndedDown;
};

struct game_controller_input
{
    bool32 IsConnected;
    bool32 IsAnalog;
    
    real32 StickAverageX;
    real32 StickAverageY;
    
    union
    {
        game_button_state Buttons[12];
        struct
        {
            game_button_state MoveUp;
            game_button_state MoveDown;
            game_button_state MoveLeft;
            game_button_state MoveRight;
            
            game_button_state ActionUp;
            game_button_state ActionDown;
            game_button_state ActionLeft;
            game_button_state ActionRight;

            game_button_state LeftShoulder;
            game_button_state RightShoulder;

            game_button_state Back;
            game_button_state Start;

            // NOTE(felipe): All buttons must be added above this line.
            
            game_button_state Terminator;
        };
    };
};

struct game_input
{
    // TODO(felipe): Insert clock value here.
    game_controller_input Controllers[5];
};
inline game_controller_input *GetController(game_input *Input, int unsigned ControllerIndex)
{
    Assert(ControllerIndex < ArrayCount(Input->Controllers));

    game_controller_input *Result = &Input->Controllers[ControllerIndex];
    return Result;
}

struct game_memory
{
    bool32 IsInitialized;
    
    uint64 PermanentStorageSize;
    void *PermanentStorage; // NOTE(felipe): REQUIRED to be cleared to zero at startup.
    
    uint64 TransientStorageSize;
    void *TransientStorage; // NOTE(felipe): REQUIRED to be cleared to zero at startup.

    debug_platform_free_file_memory *DEBUGPlatformFreeFileMemory;
    debug_platform_read_entire_file *DEBUGPlatformReadEntireFile;
    debug_platform_write_entire_file *DEBUGPlatformWriteEntireFile;
};

#define GAME_UPDATE_AND_RENDER(name) void name(game_memory *Memory, game_input *Input,game_offscreen_buffer *Buffer)
typedef GAME_UPDATE_AND_RENDER(game_update_and_render);

// NOTE(felipe): At the moment this has to be a very fast function, it cannot be
// more than 1 millisecond or so.
// TODO(felipe): Reduce the pressure on this function's performance by measuring it
// or asking about it, etc.
#define GAME_GET_SOUND_SAMPLES(name) void name(game_memory *Memory, game_sound_output_buffer *SoundBuffer)
typedef GAME_GET_SOUND_SAMPLES(game_get_sound_samples);

//
//
//

struct game_state
{
};


#define CUBICSQUARECREFT_H
#endif
