#ifndef CUTILE_PROCESS_H
#define CUTILE_PROCESS_H

#include "cxx.h"

CUTILE_C_API void exit_process(unsigned int exit_code);

#ifdef CUTILE_IMPLEM
    #ifdef _WIN32
        #include <processthreadsapi.h>
    #elif defined(__unix__) || defined(__APPLE__)
        #include <unistd.h>
    #endif
    
    void exit_process(unsigned int exit_code)
    {
        #ifdef _WIN32
        {
            ExitProcess(exit_code);
        } // _WIN32
        #elif defined(__unix__) || defined(__APPLE__)
        {
            _exit(exit_code);
        } // __unix__
        #else
            #error "exit_process: Unsupported platform."
        #endif
    }
#endif

#endif // !CUTILE_PROCESS_H
