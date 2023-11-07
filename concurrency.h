#ifndef CUTILE_CONCURRENCY_H
#define CUTILE_CONCURRENCY_H

#include "./num_types.h"

enum thread_error
{
    thread_ok,
    thread_unknown_error
};

struct thread
{
    u64 handle;
};
#ifdef CUTILE_C
typedef struct thread thread;
#endif // CUTILE_C

// This function cannot fail.
// Returns the thread calling this function.
thread get_current_thread();

thread_error start_thread(thread* t, void* start_address, void* param);

thread_error destroy_thread(thread* t);

thread_error join_thread(thread* t);
bool8        is_thread_joinable(thread* t);

#ifdef CUTILE_IMPLEM

#ifdef _WIN32
    #include <windows.h>
#endif // _WIN32

thread_error start_thread(thread* t, void* start_address, void* param)
{
#ifdef _WIN32
    t->handle = (u64)CreateThread(
        nullptr,        // default security attributes
        0,              // default stack size
        (LPTHREAD_START_ROUTINE) start_address,
        param,
        0,              // default creation flags
        nullptr);       // do not receive thread id
    if (!t->handle)
    {
        return thread_unknown_error;
    }
#endif // _WIN32

    return thread_ok;
}

thread_error destroy_thread(thread* t)
{
#ifdef _WIN32
    if (CloseHandle((HANDLE)t->handle) == 0)
    {
        return thread_unknown_error;
    }
#endif // _WIN32
    return thread_ok;
}

thread_error join_thread(thread* t)
{
#ifdef _WIN32
    DWORD err = WaitForSingleObject((HANDLE)t->handle, INFINITE);
    if (err == WAIT_FAILED)
    {
        return thread_unknown_error;
    }
#endif // _WIN32
    return thread_ok;
}
bool8        is_thread_joinable(thread* t)
{
#ifdef _WIN32
    DWORD exit_code;
    if (GetExitCodeThread((HANDLE)t->handle, &exit_code) == 0)
    {
        return bool8_false;
    }
    if (exit_code == STILL_ACTIVE) return bool8_false;
#endif // _WIN32
    return bool8_true;
}

#endif // CUTILE_IMPLEM

#endif // !CUTILE_CONCURRENCY_H
