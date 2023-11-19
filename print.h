#ifndef CUTILE_PRINT_H
#define CUTILE_PRINT_H

typedef struct string string;
void print(const string* str);
void print_cstr(const char* cstr);
void println(const string* str);
void println_cstr(const char* cstr);
#ifdef CUTILE_CPP
template <typename ...Args>
inline void print(allocator* allocator, const char* fmt, Args ...args);
template <typename ...Args>
inline void print(const char* fmt, Args ...args);
template <typename ...Args>
inline void print(allocator* allocator, const string* fmt, Args ...args);
template <typename ...Args>
inline void print(const string* fmt, Args ...args);
template <typename ...Args> 
inline void println(allocator* allocator, const char* fmt, Args ...args);
template <typename ...Args> 
inline void println(const char* fmt, Args ...args);
template <typename ...Args>
inline void println(allocator* allocator, const string* fmt, Args ...args);
template <typename ...Args>
inline void println(const string* fmt, Args ...args);
#endif // CUTILE_CPP

#ifdef CUTILE_IMPLEM

    #ifdef _WIN32
        #include <windows.h>
    #elif defined(__unix__)
        #include <unistd.h>
    #endif

    void print(const string* str)
    {
        #ifdef _WIN32
            HANDLE stdout = GetStdHandle(STD_OUTPUT_HANDLE);
            if (stdout && stdout != INVALID_HANDLE_VALUE) 
            {
                DWORD written;
                WriteConsoleA(stdout, str->data, str->count, &written, NULL);
            }
        #elif defined(__unix__)
            write(1, str->data, str->count);
        #endif
    }
    void print_cstr(const char* cstr)
    {
        #ifdef _WIN32
            HANDLE stdout = GetStdHandle(STD_OUTPUT_HANDLE);
            if (stdout && stdout != INVALID_HANDLE_VALUE) 
            {
                DWORD written;
                WriteConsoleA(stdout, cstr, cstr_length(cstr), &written, NULL);
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

// Inline implementations:
#ifdef CUTILE_CPP
    template <typename ...Args>
    inline void print(allocator* allocator, const char* fmt, Args ...args)
    {
        string str = format_str(allocator, fmt, args...);
        print(&str);
        deallocate(allocator, &str);
    }
    template <typename ...Args>
    inline void print(const char* fmt, Args ...args)
    {
        print(&basic_heap_allocator, fmt, args...);
    }
    template <typename ...Args>
    inline void print(allocator* allocator, const string* fmt, Args ...args)
    {
        string str = str_format(allocator, fmt, args...);
        print(&str);
        deallocate(allocator, &str);
    }
    template <typename ...Args>
    inline void print(const string* fmt, Args ...args)
    {
        print(&basic_heap_allocator, fmt, args...);
    }
    template <typename ...Args> 
    inline void println(allocator* allocator, const char* fmt, Args ...args) { print(allocator, fmt, args..., '\n'); }
    template <typename ...Args> 
    inline void println(const char* fmt, Args ...args) { println(&basic_heap_allocator, fmt, args...); }
    template <typename ...Args>
    inline void println(allocator* allocator, const string* fmt, Args ...args) { print(allocator, fmt, args..., '\n'); }
    template <typename ...Args>
    inline void println(const string* fmt, Args ...args) { println(&basic_heap_allocator, fmt, args...); }
#endif // CUTILE_CPP

#endif // !CUTILE_PRINT_H
