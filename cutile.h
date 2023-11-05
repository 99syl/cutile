#ifndef CUTILE_H
#define CUTILE_H

#ifdef __cplusplus
#define CUTILE_CPP
#else // !__cplusplus
#define CUTILE_C
#endif

#ifdef CUTILE_C
#if __STDC_VERSION__ < 201112L
#error "Only C11 and next versions are supported by cutile."
#endif
#endif // CUTILE_C

#endif
