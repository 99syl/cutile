#pragma once

#include "str.hpp"

template <typename ...Args>
maybe_inline string format_str(allocator* allocator, const char* fmt, Args ...args);

template <typename ...Args>
maybe_inline string format_str(const char* fmt, Args ...args);

template <typename ...Args>
maybe_inline void   format_str(string* out, const char* fmt, Args ...args);

template <typename ...Args>
maybe_inline string format_str(allocator* allocator, const string* fmt, Args ...args);

template <typename ...Args>
maybe_inline string format_str(const string* fmt, Args ...args);

template <typename ...Args>
maybe_inline void   format_str(string* out, const string* fmt, Args ...args);

struct format_memory_to_str
{
    u8* buffer;
    u64 size;
};

// Implement this function if you want to be able to format other types.
template <typename Arg>
CUTILE_CPP_API void format_arg_into_str(string* out, Arg);
template <> CUTILE_CPP_API void format_arg_into_str<u8>(string*, u8);
template <> CUTILE_CPP_API void format_arg_into_str<s8>(string*, s8);
template <> CUTILE_CPP_API void format_arg_into_str<u16>(string*, u16);
template <> CUTILE_CPP_API void format_arg_into_str<s16>(string*, s16);
template <> CUTILE_CPP_API void format_arg_into_str<u32>(string*, u32);
template <> CUTILE_CPP_API void format_arg_into_str<s32>(string*, s32);
template <> CUTILE_CPP_API void format_arg_into_str<u64>(string*, u64);
template <> CUTILE_CPP_API void format_arg_into_str<s64>(string*, s64);
template <> CUTILE_CPP_API void format_arg_into_str<const char*>(string*, const char*);
template <> CUTILE_CPP_API void format_arg_into_str<string>(string*, string);
template <> CUTILE_CPP_API void format_arg_into_str<string*>(string*, string*);
template <> CUTILE_CPP_API void format_arg_into_str<const string*>(string*, const string*);
template <> CUTILE_CPP_API void format_arg_into_str<string_view>(string*, string_view);
template <> CUTILE_CPP_API void format_arg_into_str<const string_view*>(string*, const string_view*);
template <> CUTILE_CPP_API void format_arg_into_str<format_memory_to_str>(string*, format_memory_to_str);

// IMPLEMENTATION BELOW:

template <typename Arg>
maybe_inline void format_next_arg_into_str(const char* fmt, string* out, Arg arg, u32* i, u32 len)
{
    while (*i < len)
    {
        char c = fmt[*i];
        if (c == '%')
        {
            format_arg_into_str(out, arg);
            ++(*i);
            return;
        }
        else
        {
            str_push_back(out, c);
            ++(*i);
        }
    }
}

template <typename ...Args>
maybe_inline string format_str(allocator* allocator, const char* fmt, Args ...args)
{
    string str = create_empty_str(allocator);
    format_str(&str, fmt, args...);
    return str;
}

template <typename ...Args>
maybe_inline string format_str(const char* fmt, Args ...args)
{
    return format_str(default_allocator, fmt, args...);
}

template <typename ...Args>
maybe_inline void format_str(string* out, const char* fmt, Args ...args)
{
    u32 i = 0;
    u32 fmt_len = cstr_length(fmt);
    (format_next_arg_into_str(fmt, out, args, &i, fmt_len), ...);
    if (i < fmt_len)
    {
        str_push_back_buf(out, (u8*)fmt + i, fmt_len - i);
    }
}

template <typename ...Args>
maybe_inline string format_str(allocator* allocator, const string* fmt, Args ...args)
{
    string str = create_empty_str(allocator);
    format_str(&str, fmt, args...);
    return str;
}

template <typename ...Args>
maybe_inline string format_str(const string* fmt, Args ...args)
{
    return format_str(default_allocator, fmt, args...);
}

template <typename ...Args>
maybe_inline void format_str(string* out, const string* fmt, Args ...args)
{
    u32 i = 0;
    (format_next_arg_into_str((const char*)fmt->data, out, args, &i, fmt->count), ...);
}

#ifdef CUTILE_IMPLEM
    template <>
    void format_arg_into_str<u64>(string* out, u64 arg)
    {
        nb_into_str(arg, out);
    }
    template <>
    void format_arg_into_str<s64>(string* out, s64 arg)
    {
        nb_into_str(arg, out);
    }
    template <>
    void format_arg_into_str<u32>(string* out, u32 arg)
    {
        nb_into_str(arg, out);
    }
    template <>
    void format_arg_into_str<s32>(string* out, s32 arg)
    {
        nb_into_str(arg, out);
    }
    template <>
    void format_arg_into_str<u16>(string* out, u16 arg)
    {
        nb_into_str(arg, out);
    }
    template <>
    void format_arg_into_str<s16>(string* out, s16 arg)
    {
        nb_into_str(arg, out);
    }
    template <>
    void format_arg_into_str<u8>(string* out, u8 arg)
    {
        nb_into_str(arg, out);
    }
    template <>
    void format_arg_into_str<s8>(string* out, s8 arg)
    {
        nb_into_str(arg, out);
    }
    template <>
    void format_arg_into_str<const char*>(string* out, const char* arg)
    {
        str_push_back_cstr(out, arg);
    }
    template <>
    void format_arg_into_str<char*>(string* out, char* arg)
    {
        str_push_back_cstr(out, arg);
    }
    template <>
    void format_arg_into_str<string>(string* out, string arg)
    {
        format_arg_into_str(out, &arg);
    }
    template <>
    void format_arg_into_str<string*>(string* out, string* arg)
    {
        str_push_back_str(out, arg);
    }
    template <>
    void format_arg_into_str<const string*>(string* out, const string* arg)
    {
        str_push_back_str(out, arg);
    }
    template <> 
    void format_arg_into_str<string_view>(string* out, string_view sv)
    {
        str_push_back_buf(out, (u8*)sv.data, sv.count);
    }
    template <> 
    void format_arg_into_str<string_view*>(string* out, string_view* sv)
    {
        str_push_back_buf(out, (u8*)sv->data, sv->count);
    }
    template <> 
    void format_arg_into_str<const string_view*>(string* out, const string_view* sv)
    {
        str_push_back_buf(out, (u8*)sv->data, sv->count);
    }
    template <>
    void format_arg_into_str<void*>(string* out, void* arg)
    {
        format_arg_into_str(out, (u64)arg);
    }

    template <> 
    void format_arg_into_str<format_memory_to_str>(string* out, format_memory_to_str arg)
    {
        str_push_back_buf(out, arg.buffer, arg.size);
    }

#endif // CUTILE_IMPLEM
