#ifndef CUTILE_PRINT_H
#define CUTILE_PRINT_H

#include "./cutile.h"

struct string;
#ifdef CUTILE_C
typedef struct string string;
#endif

void print(const char* cstr);
void print(string* str);

void println(const char* cstr);
void println(string* str);

#ifdef CUTILE_IMPLEM

#ifdef _WIN32
#include <windows.h>
#elif defined(__unix__)
#include <unistd.h>
#endif
#include "./str.h"

void print(const char* cstr)
{
#ifdef _WIN32
    auto stdout = GetStdHandle(STD_OUTPUT_HANDLE);
    if (stdout && stdout != INVALID_HANDLE_VALUE) 
    {
        DWORD written;
        WriteConsoleA(stdout, cstr, cstr_length(cstr), &written, NULL);
    }
#elif defined(__unix__)
    write(1, cstr, cstr_length(cstr));
#endif
}
void print(string* str)
{
#ifdef _WIN32
    auto stdout = GetStdHandle(STD_OUTPUT_HANDLE);
    if (stdout && stdout != INVALID_HANDLE_VALUE) 
    {
        DWORD written;
        WriteConsoleA(stdout, str->data, str->count, &written, NULL);
    }
#elif defined(__unix__)
    write(1, str->data, str->count);
#endif
}

void println(const char* cstr)
{
    print(cstr);
    print("\n");
}
void println(string* str)
{
    print(str);
    print("\n");
}

#endif

#endif