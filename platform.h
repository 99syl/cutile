#ifndef CUTILE_PLATFORM_H
#define CUTILE_PLATFORM_H

#define WINDOWS   0
#define MAC_OS    0
#define UNIX_LIKE 0

// INCOMPLETE: What happens on Xbox platforms ?
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

#endif // !CUTILE_PLATFORM_H
