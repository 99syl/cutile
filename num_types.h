#ifndef CUTILE_NUM_TYPES_H
#define CUTILE_NUM_TYPES_H

#include "./cxx.h"

typedef char            s8;
typedef unsigned char   u8;

typedef short           s16;
typedef unsigned short  u16;

////////////// Clang //////////////
#ifdef __clang__

typedef __INT32_TYPE__          s32;
typedef unsigned __INT32_TYPE__ u32;

typedef __INT64_TYPE__          s64;
typedef unsigned __INT64_TYPE__ u64;

#endif // __clang__
///////////////////////////////////


/////// Microsoft Visual C ////////
#ifdef _MSC_VER

typedef __int32             s32;
typedef unsigned __int32    u32;

typedef __int64             s64;
typedef unsigned __int64    u64;

#endif // _MSC_VER
///////////////////////////////////

/////////////// GCC ///////////////
#ifdef __GNUC__

typedef __INT32_TYPE__          s32;
typedef unsigned __INT32_TYPE__ u32;

typedef __INT64_TYPE__          s64;
typedef unsigned __INT64_TYPE__ u64;

#endif // __GNUC__
////////////////////////////////////

typedef float   f32;
typedef double  f64;

typedef u8  bool8;
typedef u8  b8;
typedef u32 bool32;
typedef u32 b32;

#define S8_MIN ~0x7f
#define S8_MAX 0x7f

#define U8_MIN 0x00
#define U8_MAX 0xff

#define S16_MIN ~0x7fff
#define S16_MAX 0x7fff

#define U16_MIN 0x0000
#define U16_MAX 0xffff

#define S32_MIN ~0x7fffffff
#define S32_MAX 0x7fffffff

#define U32_MIN 0x00000000
#define U32_MAX 0xffffffff

#define S64_MIN ~0x7fffffffffffffff
#define S64_MAX 0x7fffffffffffffff

#define U64_MIN 0x0000000000000000
#define U64_MAX 0xffffffffffffffff

#define BOOL8_TRUE  0x01
#define BOOL8_FALSE 0x00

#define BOOL32_TRUE     0x00000001
#define BOOL32_FALSE    0x00000000

CUTILE_C_API const s8 s8_min;
CUTILE_C_API const u8 s8_max;

CUTILE_C_API const u8 u8_min;
CUTILE_C_API const u8 u8_max;

CUTILE_C_API const s16 s16_min;
CUTILE_C_API const s16 s16_max;

CUTILE_C_API const u16 u16_min;
CUTILE_C_API const u16 u16_max;

CUTILE_C_API const s32 s32_min;
CUTILE_C_API const s32 s32_max;

CUTILE_C_API const u32 u32_min;
CUTILE_C_API const u32 u32_max;

CUTILE_C_API const s64 s64_min;
CUTILE_C_API const s64 s64_max;

CUTILE_C_API const u64 u64_min;
CUTILE_C_API const u64 u64_max;

CUTILE_C_API const bool8 bool8_false;
CUTILE_C_API const b8    b8_false;
CUTILE_C_API const bool8 bool8_true;
CUTILE_C_API const b8    b8_true;

CUTILE_C_API const bool32 bool32_false;
CUTILE_C_API const b32    b32_false;
CUTILE_C_API const bool32 bool32_true;
CUTILE_C_API const b32    b32_true;

CUTILE_STATIC_ASSERT(sizeof(s8) == 1);
CUTILE_STATIC_ASSERT(sizeof(u8) == 1);
CUTILE_STATIC_ASSERT(sizeof(s16) == 2);
CUTILE_STATIC_ASSERT(sizeof(u16) == 2);
CUTILE_STATIC_ASSERT(sizeof(s32) == 4);
CUTILE_STATIC_ASSERT(sizeof(u32) == 4);
CUTILE_STATIC_ASSERT(sizeof(s64) == 8);
CUTILE_STATIC_ASSERT(sizeof(u64) == 8);

CUTILE_STATIC_ASSERT(sizeof(f32) == 4);
CUTILE_STATIC_ASSERT(sizeof(f64) == 8);

CUTILE_STATIC_ASSERT(sizeof(bool8) == 1);
CUTILE_STATIC_ASSERT(sizeof(bool32) == 4);

#ifdef CUTILE_IMPLEM
    const s8 s8_min = S8_MIN;
    const u8 s8_max = S8_MAX;
    
    const u8 u8_min = U8_MIN;
    const u8 u8_max = U8_MAX;
    
    const s16 s16_min = S16_MIN;
    const s16 s16_max = S16_MAX;
    
    const u16 u16_min = U16_MIN;
    const u16 u16_max = U16_MAX;
    
    const s32 s32_min = S32_MIN;
    const s32 s32_max = S32_MAX;
    
    const u32 u32_min = U32_MIN;
    const u32 u32_max = U32_MAX;
    
    const s64 s64_min = S64_MIN;
    const s64 s64_max = S64_MAX;

    const u64 u64_min = U64_MIN;
    const u64 u64_max = U64_MAX;
    
    const bool8 bool8_false = BOOL8_FALSE;
    const b8    b8_false = BOOL8_FALSE;
    const bool8 bool8_true = BOOL8_TRUE;
    const b8    b8_true = BOOL8_TRUE;

    const bool32 bool32_false = BOOL32_FALSE;
    const b32    b32_false = BOOL32_FALSE;
    const bool32 bool32_true = BOOL32_TRUE;
    const b32    b32_true = BOOL32_TRUE;
#endif // CUTILE_IMPLEM

#endif // !CUTILE_NUM_TYPES_H
