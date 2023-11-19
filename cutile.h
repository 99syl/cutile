#ifndef CUTILE_H
#define CUTILE_H

#ifdef __cplusplus
    #define CUTILE_CPP
#else // !__cplusplus
    #define CUTILE_C
#endif

#ifdef CUTILE_CPP
    // TODO: Check if it's cpp17 at least.
#elif defined(CUTILE_C)
    #if __STDC_VERSION__ < 201112L
        #error "Only C11 and next versions are supported by cutile."
    #endif
#else
    #error "Compiler could not tell if this is C or C++. Please define yourself CUTILE_CPP or CUTILE_C."
#endif // CUTILE_C

#endif
