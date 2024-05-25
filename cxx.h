// This file is a collection of basic tools I expect from any modern programming language.
// I named it "cxx.h" because it tries to express my ideal (naive/immature?) C/C++ language.

// This is the API, implementation is below this never-entered #if.
// I separated them because implementation is not easy to read, and it is not likely to be improved in the future.
#if 0

    // Keyword used for variables and functions that must not be visible outside their own compilation unit.
    #define internal

    // Keyword used for function variables that need to keep their value persistent between calls.
    #define persist

    // Suggests to the compiler that a function could be inlined.
    // Since C++17: can also suggest that a variable could be inlined.
    #define maybe_inline

    // Performs assertion at compilation-time. A false assertion means a compilation error.
    #define cutile_compile_time_assert(assertion)

    // Integer explicit sized types. Mostly because int_XX_t is too long for me to write.
    // The number represents the number of bits.
    typedef u8;
    typedef s8;
    typedef u16;
    typedef s16;
    typedef u32;
    typedef s32;
    typedef u64;
    typedef s64;

    // Floating-point explicit sized types. I do not like "float". And mostly for the same reason as above.
    // The number represents the number of bits.
    typedef f32;
    typedef f64;

    // Boolean explicit sized types... Why not ??
    // The number represents the number of bits.
    typedef b8;
    typedef b32;

    #define cutile_b8_true
    #define cutile_b8_false
    #define cutile_b32_true
    #define cutile_b32_false

    // nullptr for C.
    #ifdef CUTILE_C
        #define nullptr
    #endif

    // Returns the offset of a structure field.
    #define cutile_field_offset_m(struct, field)

    // Transforms given token into a cstring literal.
    #define cutile_cstr_m(x)

    // Gets the line where this macro is called as a cstring.
    #define cutile_current_line_cstr_m

    // Swap bytes of the given parameter.
    #define cutile_bswap_u16_m(nb) // -> returns u16
    #define cutile_bswap_u32_m(nb) // -> returns u32
    #define cutile_bswap_u64_m(nb) // -> returns u64

    // Targeted Operating Systems:
    // 0 or 1 according to what operating system you are targeting.
    #define LINUX       0|1
    #define MAC_OS      0|1
    #define UNIX_LIKE   0|1
    #define WINDOWS     0|1

    // Compilers:
    // 0 or 1 according to which compiler you are using.
    #define CLANG       0|1
    #define GCC         0|1
    #define MSVC        0|1

    ///////////////////////////////////
    // Short names for this API.
    // Define CUTILE_API_NO_SHORT_NAMES to disable every short name.

    #define compile_time_assert(assertion)

    #define b8_true
    #define b8_false

    #define b32_true
    #define b32_false

    #define field_offset_m(struct, field)

    #define cstr_m(x)

    #define current_src_line_cstr_m

    // Short names for the bswap API. 
    // Define CUTILE_BSWAP_API_NO_SHORT_NAMES to only disable them.
    // Define CUTILE_BSWAP_API_SHORT_NAMES to force enable them no matter what.
    #define bswap_u16_m(nb)
    #define bswap_u32_m(nb)
    #define bswap_u64_m(nb)

#endif

#ifndef CUTILE_CXX_H

    #include "cutile.h"

    #define internal static
    #define persist static

    #define maybe_inline inline

    // cutile_compile_time_assert
    #ifdef CUTILE_CPP
        #define cutile_compile_time_assert(a) static_assert(a)
    #else // CUTILE_C
        #if __STDC_VERSION__ >= 202311L // C23
            #define cutile_compile_time_assert(a) static_assert(a)
        #elif __STDC_VERSION__ >= 201112L // C11
            #define cutile_compile_time_assert(a) _Static_assert(a)
        #endif // __STDC_VERSION__
    #endif // CUTILE_CPP

    // explicit sized numeric types:
    ///////////////////////////////////////////////////////
    typedef char            s8;
    typedef unsigned char   u8;

    typedef short           s16;
    typedef unsigned short  u16;

    ////////////// Clang | GCC //////////////
    #if defined(__clang__) || defined(__GNUC__)

        typedef __INT32_TYPE__          s32;
        typedef unsigned __INT32_TYPE__ u32;

        typedef __INT64_TYPE__          s64;
        typedef unsigned __INT64_TYPE__ u64;

    #endif // __clang__ || __GNUC__
    /////////////////////////////////////////

    /////// Microsoft Visual C ////////
    #ifdef _MSC_VER

        typedef __int32             s32;
        typedef unsigned __int32    u32;

        typedef __int64             s64;
        typedef unsigned __int64    u64;

    #endif // _MSC_VER
    ///////////////////////////////////

    typedef float   f32;
    typedef double  f64;

    typedef u8  bool8;
    typedef u8  b8;
    typedef u32 bool32;
    typedef u32 b32;

    #define cutile_b8_true  0x01
    #define cutile_b8_false 0x00

    #define cutile_b32_true  0x00000001
    #define cutile_b32_false 0x00000000

    #ifndef CUTILE_API_NO_SHORT_NAMES
        #define b8_true  cutile_b8_true
        #define b8_false cutile_b8_false

        #define b32_true  cutile_b32_true
        #define b32_false cutile_b32_false
    #endif
    ///////////////////////////////////////////////////////

    // nullptr
    #ifdef CUTILE_C
        #define nullptr 0
    #endif

    // field_offset
    // Gets the offset (in bytes) of a field inside a structure.
    #define cutile_field_offset_m(structure, field) ((u64)(&((structure*)0x0)->field))

    #define cutile_cstr_m(x)  cutile_cstr2_m(x)
    #define cutile_cstr2_m(x) #x

    #define cutile_current_line_cstr_m cutile_cstr_m(__LINE__)

    #ifndef CUTILE_API_NO_SHORT_NAMES
        #define field_offset_m(structure, field)    cutile_field_offset_m(structure, field)
        #define cstr_m(x)                           cutile_cstr_m(x)
        #define current_src_line_cstr_m             cutile_current_line_cstr_m
    #endif

    #if defined(__GNUC__)
        #define cutile_bswap_u16_m(val) __builtin_bswap16(val)
        #define cutile_bswap_u32_m(val) __builtin_bswap32(val)
        #define cutile_bswap_u64_m(val) __builtin_bswap64(val)
    #endif

    #if (!defined(CUTILE_API_NO_SHORT_NAMES) && !defined(CUTILE_BSWAP_API_NO_SHORT_NAMES)) || defined(CUTILE_BSWAP_API_SHORT_NAMES)
        #define bswap_u16_m(nb) cutile_bswap_u16_m(nb)
        #define bswap_u32_m(nb) cutile_bswap_u32_m(nb)
        #define bswap_u64_m(nb) cutile_bswap_u64_m(nb)
    #endif

    #ifdef __linux__
        #undef  LINUX
        #define LINUX     1
        #undef  UNIX_LIKE
        #define UNIX_LIKE 1
    #endif

    #ifdef _WIN32
        #undef  WINDOWS
        #define WINDOWS 1
    #endif

    #ifdef __APPLE__
        #include <TargetConditionals.h>
    
        #if TARGET_OS_MAC
            #undef  MAC_OS
            #define MAC_OS    1
            #undef  UNIX_LIKE
            #define UNIX_LIKE 1
        #endif
    #endif

    #if defined(__GNUC__) && !defined(__clang__)
        #undef  GCC
        #define GCC 1
    #elif defined(__clang__)
        #undef  CLANG
        #define CLANG 1
    #elif defined(_MSC_VER)
        #undef  MSVC
        #define MSVC 1
    #endif

    #define CUTILE_CXX_H

#endif
