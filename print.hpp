#ifndef CUTILE_PRINT_HPP
#define CUTILE_PRINT_HPP

#include "./print.h"
#include "./str.h"

template <typename ...Args>
force_inline void print(allocator* allocator, const char* fmt, Args ...args);
template <typename ...Args>
force_inline void print(const char* fmt, Args ...args);
template <typename ...Args>
force_inline void print(allocator* allocator, const string* fmt, Args ...args);
template <typename ...Args>
force_inline void print(const string* fmt, Args ...args);
template <typename ...Args> 
force_inline void println(allocator* allocator, const char* fmt, Args ...args);
template <typename ...Args> 
force_inline void println(const char* fmt, Args ...args);
template <typename ...Args>
force_inline void println(allocator* allocator, const string* fmt, Args ...args);
template <typename ...Args>
force_inline void println(const string* fmt, Args ...args);

// Implementation:
template <typename ...Args>
force_inline void print(allocator* allocator, const char* fmt, Args ...args)
{
    string str = format_str(allocator, fmt, args...);
    print(&str);
    destroy_str(&str);
}
template <typename ...Args>
force_inline void print(const char* fmt, Args ...args)
{
    print(&basic_heap_allocator, fmt, args...);
}

template <typename ...Args>
force_inline void print(allocator* allocator, const string* fmt, Args ...args)
{
    string str = str_format(allocator, fmt, args...);
    print(&str);
    destroy_str(&str);
}
template <typename ...Args>
force_inline void print(const string* fmt, Args ...args)
{
    print(&basic_heap_allocator, fmt, args...);
}

template <typename ...Args> 
force_inline void println(allocator* allocator, const char* fmt, Args ...args) { print(allocator, fmt, args..., '\n'); }

template <typename ...Args> 
force_inline void println(const char* fmt, Args ...args) { println(&basic_heap_allocator, fmt, args...); }

template <typename ...Args>
force_inline void println(allocator* allocator, const string* fmt, Args ...args) { print(allocator, fmt, args..., '\n'); }

template <typename ...Args>
force_inline void println(const string* fmt, Args ...args) { println(&basic_heap_allocator, fmt, args...); }

#endif // !CUTILE_PRINT_HPP
