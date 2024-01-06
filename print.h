#ifndef CUTILE_PRINT_H
#define CUTILE_PRINT_H

#include "./cutile.h"

typedef struct string string;
CUTILE_C_API void print(const string* str);
CUTILE_C_API void print_cstr(const char* cstr);
CUTILE_C_API void println(const string* str);
CUTILE_C_API void println_cstr(const char* cstr);

#ifdef CUTILE_IMPLEM

    #ifdef _WIN32
        #include <windows.h>
    #elif defined(__unix__) || defined(__APPLE__)
        #include <unistd.h>
    #endif

    #include "./str.h"

    void print(const string* str)
    {
        #ifdef _WIN32
            HANDLE out = GetStdHandle(STD_OUTPUT_HANDLE);
            if (out && out != INVALID_HANDLE_VALUE) 
            {
                DWORD written;
                WriteConsoleA(out, str->data, str->count, &written, NULL);
            }
        #elif defined(__unix__) || defined(__APPLE__)
            write(1, str->data, str->count);
        #else
            #error "Unsupported platform."
        #endif
    }
    void print_cstr(const char* cstr)
    {
        #ifdef _WIN32
            HANDLE out = GetStdHandle(STD_OUTPUT_HANDLE);
            if (out && out != INVALID_HANDLE_VALUE) 
            {
                DWORD written;
                WriteConsoleA(out, cstr, cstr_length(cstr), &written, NULL);
            }
        #elif defined(__unix__) || defined(__APPLE__)
            write(1, cstr, cstr_length(cstr));
        #else
            #error "Unsupported platform."
        #endif
    }
    void println(const string* str)
    {
        print(str);
        print_cstr("\n");
    }
    void println_cstr(const char* cstr)
    {
        print_cstr(cstr);
        print_cstr("\n");
    }

#endif // CUTILE_IMPLEM

#endif // !CUTILE_PRINT_H
