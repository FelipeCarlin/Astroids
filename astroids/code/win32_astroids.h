#if !defined(WIN32_ASTROIDS_H)
/* ========================================================================
   $File: $
   $Date: $
   $Revision: $
   $Creator: Felipe Carlin $
   $Notice: $
   ======================================================================== */

/*
  NOTE(felipe):

  ASTROIDS_INTERNAL:
    0 - Build for public release
    1 - Build for developer only

  ASTROIDS_SLOW:
    0 - Not slow code allowed!
    1 - Slow code
 */

#if ASTROIDS_SLOW
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

struct win32_read_file_result
{
    uint32 ContentSize;
    void *Contents;
};

struct win32_offscreen_buffer
{
    // NOTE(felipe): Pixels are always 32-bit size, memory order GG BB RR XX.
    BITMAPINFO Info;
    void* Memory;
    int Width;
    int Height;
    int Pitch;
    int BytesPerPixel;
};

struct game_state
{
    real32 PlayerVelX;
    real32 PlayerVelY;
    
    real32 PlayerX;
    real32 PlayerY;
};


#define WIN32_ASTROIDS_H
#endif
