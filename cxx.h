// This file aims to add more tools to C/C++ languages.

#ifndef CUTILE_CXX_H
#define CUTILE_CXX_H

#include "cutile.h"

#define internal static
#define persist static

// CUTILE_STATIC_ASSERT
#ifdef CUTILE_CPP
    #define CUTILE_STATIC_ASSERT(a) static_assert(a)
#else // CUTILE_C
    #if __STDC_VERSION__ >= 202311L // C23
        #define CUTILE_STATIC_ASSERT(a) static_assert(a)
    #elif __STDC_VERSION__ >= 201112L // C11
        #define CUTILE_STATIC_ASSERT(a) _Static_assert(a)
    #endif // __STDC_VERSION__
#endif // CUTILE_CPP

#define maybe_inline inline

// force_inline
#ifdef _MSC_VER
    #define force_inline __forceinline
#else
    #define force_inline inline
#endif

CUTILE_C_API void exit_process(unsigned int);
CUTILE_C_API void println_cstr(const char* cstr);

// CUTILE_ASSERT
#ifdef CUTILE_ENABLE_ASSERT
    #define CUTILE_ASSERT(pred, ...)                                        \
    {                                                                   \
        if (!(pred))                                                    \
        {                                                               \
            println_cstr("Assertion Failed: " #pred ". " __VA_ARGS__);  \
            exit_process(1);                                            \
        }                                                               \
    }
#else
    #define CUTILE_ASSERT(pred, ...)
#endif

// nullptr
#ifdef CUTILE_C
    #define nullptr 0
#endif

#ifdef CUTILE_CPP
    template <typename T, typename U>
    struct duple
    {
        T _1;
        U _2;
    };
#endif

#define stringify_m(x) stringify2_m(x)
#define stringify2_m(x) #x

#define current_line_cstr_m stringify_m(__LINE__)

#endif // !CUTILE_CXX_H
