#ifndef CUTILE_H
#define CUTILE_H

#ifdef __cplusplus
    #define CUTILE_CPP
#else // !__cplusplus
    #define CUTILE_C
#endif

#ifdef CUTILE_CPP
    // TODO: Check if it's cpp20 at least.
#elif defined(CUTILE_C)
    #if __STDC_VERSION__ < 201112L
        #error "Only C11 and next versions are supported by cutile."
    #endif
#else
    #error "cutile could not tell if this is C or C++. Please define yourself CUTILE_CPP or CUTILE_C."
#endif

#ifdef _WIN32
    #define CUTILE_API_SL_EXPORT __declspec(dllexport)
#else
    #define CUTILE_API_SL_EXPORT
#endif

#ifdef _WIN32
    #define CUTILE_API_IMPORT_SL __declspec(dllimport)
#else
    #define CUTILE_API_IMPORT_SL
#endif

#if defined(COMPILE_CUTILE_DLL)
    #ifdef CUTILE_CPP
        #define CUTILE_C_API extern "C" CUTILE_API_SL_EXPORT
        #define CUTILE_CPP_API extern CUTILE_API_SL_EXPORT
    #else
        #define CUTILE_C_API extern CUTILE_API_SL_EXPORT
    #endif
#elif defined(IMPORT_CUTILE_DLL)
    #ifdef CUTILE_CPP
        #define CUTILE_C_API extern "C" CUTILE_API_IMPORT_SL
        #define CUTILE_CPP_API extern CUTILE_API_IMPORT_SL
    #else
        #define CUTILE_C_API extern CUTILE_API_IMPORT_SL
    #endif
#else
    #ifdef CUTILE_CPP
        #define CUTILE_C_API extern "C"
        #define CUTILE_CPP_API extern
    #else
        #define CUTILE_C_API extern
    #endif
#endif

#endif // !CUTILE_H
