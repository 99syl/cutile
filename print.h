#ifndef CUTILE_PRINT_H
#define CUTILE_PRINT_H

typedef struct string string;
void print(const string* str);
void print_cstr(const char* cstr);
void println(const string* str);
void println_cstr(const char* cstr);

#ifdef CUTILE_IMPLEM

    #ifdef _WIN32
        #include <windows.h>
    #elif defined(__unix__)
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
        #elif defined(__unix__)
            write(1, str->data, str->count);
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
        #elif defined(__unix__)
            write(1, cstr, cstr_length(cstr));
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
