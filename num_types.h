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
typedef u32 bool32;

#define S8_MIN ~0x7f
#define S8_MAX 0x7f

#define U8_MIN 0x00
#define U8_MAX 0xff

#define BOOL8_TRUE  0x01
#define BOOL8_FALSE 0x00

#define BOOL32_TRUE     0x00000001
#define BOOL32_FALSE    0x00000000

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

#endif