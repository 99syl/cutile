#ifndef CUTILE_CXX_H
#define CUTILE_CXX_H

#include "./cutile.h"

#define internal static

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

#ifdef _MSC_VER
#define force_inline __forceinline
#else
#define force_inline inline
#endif // _MSC_VER

#ifdef CUTILE_C
#define nullptr 0
#endif

#endif // !CUTILE_CXX_H
