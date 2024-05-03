#pragma once

#include "cutile.h"

// Types defined in str.h:
typedef struct string string;
typedef struct string_view string_view;

CUTILE_C_API void print(const string* str);
CUTILE_C_API void print_cstr(const char* cstr);
CUTILE_C_API void print_str_view(string_view* view);
CUTILE_C_API void println(const string* str);
CUTILE_C_API void println_cstr(const char* cstr);
CUTILE_C_API void println_str_view(string_view* view);

#ifdef CUTILE_IMPLEM

    #ifdef _WIN32
        #include <windows.h>
    #elif defined(__unix__) || defined(__APPLE__)
        #include <unistd.h>
    #endif

    #include "str.h"

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

    void print_str_view(string_view* view)
    {
        #ifdef _WIN32
            HANDLE out = GetStdHandle(STD_OUTPUT_HANDLE);
            if (out && out != INVALID_HANDLE_VALUE) 
            {
                DWORD written;
                WriteConsoleA(out, view->data, view->count, &written, NULL);
            }
        #elif defined(__unix__) || defined(__APPLE__)
            write(1, view->data, view->count);
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
    
    void println_str_view(string_view* view)
    {
        print_str_view(view);
        print_cstr("\n");
    }

#endif // CUTILE_IMPLEM
