#pragma once

#ifdef __cplusplus
    #define CUTILE_CPP
#elif defined(__STDC_VERSION__)
    #define CUTILE_C
#else
    #error "cutile could not tell if you are using C or C++."
#endif

#if defined(CUTILE_CPP)
    #if __cplusplus < 202002L
        #error "C++ versions prior to C++20 are not supported."
    #endif
#elif defined(CUTILE_C)
    #if __STDC_VERSION__ < 201112L
        #error "C versions prior to C11 are not supported."
    #endif
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
