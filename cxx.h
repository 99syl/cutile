// This file aims to add more tools to C/C++ languages.

#ifndef CUTILE_CXX_H
#define CUTILE_CXX_H

#include "./cutile.h"

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
#endif // _MSC_VER

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

#endif // !CUTILE_CXX_H
