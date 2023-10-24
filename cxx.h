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

#endif