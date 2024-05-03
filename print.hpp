#pragma once

#include "print.h"
#include "str_format.hpp"

template <typename ...Args>
maybe_inline void print(allocator* allocator, const char* fmt, Args ...args);
template <typename ...Args>
maybe_inline void print(const char* fmt, Args ...args);
template <typename ...Args>
maybe_inline void print(allocator* allocator, const string* fmt, Args ...args);
template <typename ...Args>
maybe_inline void print(const string* fmt, Args ...args);
template <typename ...Args> 
maybe_inline void println(allocator* allocator, const char* fmt, Args ...args);
template <typename ...Args> 
maybe_inline void println(const char* fmt, Args ...args);
template <typename ...Args>
maybe_inline void println(allocator* allocator, const string* fmt, Args ...args);
template <typename ...Args>
maybe_inline void println(const string* fmt, Args ...args);

// Implementation:
template <typename ...Args>
maybe_inline void print(allocator* allocator, const char* fmt, Args ...args)
{
    string str = format_str(allocator, fmt, args...);
    print(&str);
    destroy_str(&str);
}
template <typename ...Args>
maybe_inline void print(const char* fmt, Args ...args)
{
    print(&default_allocator, fmt, args...);
}

template <typename ...Args>
maybe_inline void print(allocator* allocator, const string* fmt, Args ...args)
{
    string str = str_format(allocator, fmt, args...);
    print(&str);
    destroy_str(&str);
}
template <typename ...Args>
maybe_inline void print(const string* fmt, Args ...args)
{
    print(&default_allocator, fmt, args...);
}

template <typename ...Args> 
maybe_inline void println(allocator* allocator, const char* fmt, Args ...args) 
{ 
    string str = format_str(allocator, fmt, args...);
    println(&str);
    destroy_str(&str);
}
template <typename ...Args> 
maybe_inline void println(const char* fmt, Args ...args) 
{ 
    println(&default_allocator, fmt, args...); 
}

template <typename ...Args>
maybe_inline void println(allocator* allocator, const string* fmt, Args ...args)
{
    string str = str_format(allocator, fmt, args...);
    println(&str);
    destroy_str(&str);
}

template <typename ...Args>
maybe_inline void println(const string* fmt, Args ...args) 
{ 
    println(&default_allocator, fmt, args...); 
}
