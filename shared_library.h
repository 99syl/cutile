#ifndef CUTILE_SHARED_LIBRARY_H
#define CUTILE_SHARED_LIBRARY_H

#include "./cxx.h"

typedef struct shared_library
{
    void* handle;
} shared_library;

CUTILE_C_API shared_library  load_shared_library(const char* shared_library_path);
CUTILE_C_API void            unload_shared_library(shared_library);

CUTILE_C_API void* get_shared_library_proc(shared_library, const char* proc_name);
#ifdef CUTILE_CPP
    template <typename ProcType>
    CUTILE_CPP_API force_inline ProcType get_shared_library_proc(shared_library, const char* proc_name);
#endif // CUTILE_CPP

#ifdef CUTILE_IMPLEM
    #ifdef _WIN32
        #include <windows.h>
    #endif
    
    shared_library load_shared_library(const char* shared_library_path)
    {
        shared_library result;
        #ifdef _WIN32
            result.handle = LoadLibraryA(shared_library_path);
        #else
            // TODO: Implement for other platforms.
            result.handle = nullptr;
        #endif

        return result;
    }

    void unload_shared_library(shared_library sl)
    {
        #ifdef _WIN32
            FreeLibrary((HMODULE)sl.handle);
        #else
            // TODO: Implement for other platforms.
        #endif
    }

    void* get_shared_library_proc(shared_library sl, const char* proc_name)
    {
        #ifdef _WIN32
            return GetProcAddress((HMODULE)sl.handle, proc_name);
        #else
            // TODO: Implement for other platforms.
            return nullptr;
        #endif
    }

#endif // CUTILE_IMPLEM

#ifdef CUTILE_CPP
    template <typename ProcType>
    force_inline ProcType get_shared_library_proc(shared_library sl, const char* proc_name) { return (ProcType)get_shared_library_proc(sl, proc_name); }
#endif // CUTILE_CPP


#endif // !CUTILE_SHARED_LIBRARY_H
