#ifndef CUTILE_STR_H
#define CUTILE_STR_H

#include "./cutile.h"
#include "./memory.h"

typedef struct string
{
    u8* data;
    u32 count;
    u32 size;

    allocator* allocator;
} string;

CUTILE_C_API string create_empty_str(allocator* allocator);
CUTILE_C_API string create_str_from_cstr(const char* cstr, allocator* allocator);
CUTILE_C_API string copy_str(const string* original, allocator* allocator);
CUTILE_C_API string create_str_from_buf(const u8* buf, u32 buf_len, allocator* allocator);

CUTILE_C_API void destroy_str(string* str);

CUTILE_C_API void resize_str(string* str, u32 size);

CUTILE_C_API void str_push_back(string* str, u32 c);
CUTILE_C_API void str_push_back_u8(string* str, u8 c);
CUTILE_C_API void str_insert(string* str, u32 index, u32 c);
CUTILE_C_API void str_push_back_str(string* str, const string* rhs);
CUTILE_C_API void str_push_back_cstr(string* str, const char* rhs);
CUTILE_C_API void str_push_back_buf(string* str, u8* buf, u64 buf_size);
CUTILE_C_API void str_pop_back(string* str);

CUTILE_C_API void reverse_str(string* str);
CUTILE_C_API void reverse_sub_str(string* str, u32 offset, u32 count);

CUTILE_C_API u8    str_at(const string* str, u32 index);
CUTILE_C_API bool8 str_equals_cstr(const string* str, const char* cstr);
CUTILE_C_API bool8 str_begins_with(const string* str, const char* val);
CUTILE_C_API bool8 str_ends_with(const string* str, const char* val);

CUTILE_C_API char* create_cstr_from_str(const string* str, allocator* allocator);
CUTILE_C_API char* create_cstr_from_cstr(const char* cstr, allocator* allocator);
CUTILE_C_API char* create_cstr_from_sub_cstr(const char* cstr, u32 pos, u32 count, allocator* allocator);

CUTILE_C_API u32 cstr_length(const char* cstr);

CUTILE_C_API bool8 cstr_equals(const char* lhs, const char* rhs);

CUTILE_C_API char* concat_cstrs(const char* lhs, const char* rhs, allocator* allocator);

typedef struct string_view
{
    const char* data;
    u64         count;
} string_view;

#define create_string_view_m(str_array)                                 \
    (string_view{.data = str_array, .count = sizeof(str_array)/sizeof(s8)})
#define create_string_view_from_str_m(str)      \
    (string_view{.data = str.data, .count = str.count})

CUTILE_C_API b8 str_view_equals_cstr(string_view* lhs, const char* rhs);

CUTILE_C_API u8 sub_str_to_u8(const string* s, u32 offset, u32 count);
CUTILE_C_API s8 sub_str_to_s8(const string* s, u32 offset, u32 count);
CUTILE_C_API u16 sub_str_to_u16(const string* s, u32 offset, u32 count);
CUTILE_C_API s16 sub_str_to_s16(const string* s, u32 offset, u32 count);
CUTILE_C_API u32 sub_str_to_u32(const string* s, u32 offset, u32 count);
CUTILE_C_API s32 sub_str_to_s32(const string* s, u32 offset, u32 count);
CUTILE_C_API u64 sub_str_to_u64(const string* s, u32 offset, u32 count);
CUTILE_C_API s64 sub_str_to_s64(const string* s, u32 offset, u32 count);
CUTILE_C_API u8 str_to_u8(const string* s);
CUTILE_C_API s8 str_to_s8(const string* s);
CUTILE_C_API u16 str_to_u16(const string* s);
CUTILE_C_API s16 str_to_s16(const string* s);
CUTILE_C_API u32 str_to_u32(const string* s);
CUTILE_C_API s32 str_to_s32(const string* s);
CUTILE_C_API u64 str_to_u64(const string* s);
CUTILE_C_API s64 str_to_s64(const string* s);
#ifdef CUTILE_CPP
    template <typename IntegerType>
    IntegerType sub_str_to_nb(const string* s, u32 offset, u32 count);
    template <typename IntegerType>
    IntegerType str_to_nb(const string* s);
#endif // CUTILE_CPP

CUTILE_C_API string u8_to_str(u8, allocator* allocator);
CUTILE_C_API string s8_to_str(s8, allocator* allocator);
CUTILE_C_API string u16_to_str(u16, allocator* allocator);
CUTILE_C_API string s16_to_str(s16, allocator* allocator);
CUTILE_C_API string u32_to_str(u32, allocator* allocator);
CUTILE_C_API string s32_to_str(s32, allocator* allocator);
CUTILE_C_API string u64_to_str(u64, allocator* allocator);
CUTILE_C_API string s64_to_str(s64, allocator* allocator);
CUTILE_C_API char* u8_to_cstr(u8, allocator* allocator);
CUTILE_C_API char* s8_to_cstr(s8, allocator* allocator);
CUTILE_C_API char* u16_to_cstr(u16, allocator* allocator);
CUTILE_C_API char* s16_to_cstr(s16, allocator* allocator);
CUTILE_C_API char* u32_to_cstr(u32, allocator* allocator);
CUTILE_C_API char* s32_to_cstr(s32, allocator* allocator);
CUTILE_C_API char* u64_to_cstr(u64, allocator* allocator);
CUTILE_C_API char* s64_to_cstr(s64, allocator* allocator);

// nb_into_str: Pushes the number at the end of the string.
CUTILE_C_API void u8_into_str(u8, string* out);
CUTILE_C_API void s8_into_str(s8, string* out);
CUTILE_C_API void u16_into_str(u16, string* out);
CUTILE_C_API void s16_into_str(s16, string* out);
CUTILE_C_API void u32_into_str(u32, string* out);
CUTILE_C_API void s32_into_str(s32, string* out);
CUTILE_C_API void u64_into_str(u64, string* out);
CUTILE_C_API void s64_into_str(s64, string* out);

CUTILE_C_API void u8_into_sub_str(u8, string* out, u32 index);
CUTILE_C_API void s8_into_sub_str(s8, string* out, u32 index);
CUTILE_C_API void u16_into_sub_str(u16, string* out, u32 index);
CUTILE_C_API void s16_into_sub_str(s16, string* out, u32 index);
CUTILE_C_API void u32_into_sub_str(u32, string* out, u32 index);
CUTILE_C_API void s32_into_sub_str(s32, string* out, u32 index);
CUTILE_C_API void u64_into_sub_str(u64, string* out, u32 index);
CUTILE_C_API void s64_into_sub_str(s64, string* out, u32 index);

#ifdef CUTILE_CPP
    template <typename IntegerType>
    CUTILE_CPP_API string nb_to_str(IntegerType val, allocator* = &global_default_heap_allocator);
    template <typename IntegerType>
    CUTILE_CPP_API void nb_into_str(IntegerType val, string* out);
    template <typename IntegerType>
    CUTILE_CPP_API void nb_into_sub_str(IntegerType val, string* out, u32 offset);
#endif // CUTILE_CPP

#ifdef CUTILE_CPP
    template <typename ...Args>
    force_inline string format_str(allocator* allocator, const char* fmt, Args ...args);
    template <typename ...Args>
    force_inline string format_str(const char* fmt, Args ...args);
    template <typename ...Args>
    force_inline void   format_str(string* out, const char* fmt, Args ...args);
    template <typename ...Args>
    force_inline string format_str(allocator* allocator, const string* fmt, Args ...args);
    template <typename ...Args>
    force_inline string format_str(const string* fmt, Args ...args);
    template <typename ...Args>
    force_inline void   format_str(string* out, const string* fmt, Args ...args);
    template <typename Arg>
    CUTILE_CPP_API void format_arg_into_str(string* out, Arg arg);
    template <> CUTILE_CPP_API void format_arg_into_str<u8>(string*, u8);
    template <> CUTILE_CPP_API void format_arg_into_str<s8>(string*, s8);
    template <> CUTILE_CPP_API void format_arg_into_str<u16>(string*, u16);
    template <> CUTILE_CPP_API void format_arg_into_str<s16>(string*, s16);
    template <> CUTILE_CPP_API void format_arg_into_str<u32>(string*, u32);
    template <> CUTILE_CPP_API void format_arg_into_str<s32>(string*, s32);
    template <> CUTILE_CPP_API void format_arg_into_str<u64>(string*, u64);
    template <> CUTILE_CPP_API void format_arg_into_str<s64>(string*, s64);
    template <> CUTILE_CPP_API void format_arg_into_str<const char*>(string*, const char*);
    template <> CUTILE_CPP_API void format_arg_into_str<char*>(string*, char*);
    template <> CUTILE_CPP_API void format_arg_into_str<string>(string*, string);
    template <> CUTILE_CPP_API void format_arg_into_str<string*>(string*, string*);
    template <> CUTILE_CPP_API void format_arg_into_str<string_view>(string*, string_view);
    template <> CUTILE_CPP_API void format_arg_into_str<string_view*>(string*, string_view*);
#endif // CUTILE_CPP

#ifdef CUTILE_IMPLEM

    #define CUTILE_STR_INCREMENT_COUNT 5

    string create_empty_str(allocator* allocator)
    {
        string s;
        s.data = (u8*)allocate(allocator, sizeof(u8) * CUTILE_STR_INCREMENT_COUNT);
        s.count = 0;
        s.size = CUTILE_STR_INCREMENT_COUNT;
        s.allocator = allocator;
        return s;
    }
    string create_str_from_cstr(const char* cstr, allocator* allocator)
    {
        u32 count = cstr_length(cstr);
        string s;
        s.data = (u8*)allocate(allocator, sizeof(u8) * count);
        copy_s8_memory((s8*)s.data, cstr, count);
        s.count = count;
        s.size = count;
        s.allocator = allocator;
        return s;
    }

    string copy_str(const string* original, allocator* allocator)
    {
        string s;
        s.data = (u8*)allocate(allocator, sizeof(u8) * original->count);
        copy_u8_memory(s.data, original->data, original->count);
        s.count = original->count;
        s.size = original->size;
        s.allocator = allocator;
        return s;
    }

    string create_str_from_buf(const u8* buf, u32 buf_len, allocator* allocator)
    {
        string s;
        s.data = dump_u8_memory(buf, buf_len, allocator);
        s.count = buf_len;
        s.size = s.count;
        s.allocator = allocator;
        return s;
    }

    void destroy_str(string* str)
    {
        deallocate(str->allocator, str->data);
    }

    void resize_str(string* str, u32 size)
    {
        u8* new_data = (u8*)allocate(str->allocator, size);
        if (size < str->count)
        {
            for (u32 i = 0; i < size; ++i) new_data[i] = str->data[i];
            str->count = size;
        }
        else
        {
            for (u32 i = 0; i < str->count; ++i) new_data[i] = str->data[i];
        }
        deallocate(str->allocator, str->data);
        str->data = new_data;
        str->size = size;
    }

    void str_push_back(string* str, u32 c)
    {
        u32 csize;
        if (c <= 0x007F) csize = 1;
        else if (c <= 0x07FF) csize = 2;
        else if (c <= 0xFFFF) csize = 3;
        else csize = 4;
        if (str->count + csize >= str->size) resize_str(str, str->size + csize + CUTILE_STR_INCREMENT_COUNT);
        for (u32 i = 0; i < csize; ++i)
        {
            str->data[str->count++] = (c >> (i * 8)) & 0xFF;
        }
    }

    void str_push_back_u8(string* str, u8 c)
    {
        if (str->count + 1 >= str->size) resize_str(str, str->size + 1 + CUTILE_STR_INCREMENT_COUNT);
        str->data[str->count++] = c;
    }
    void str_insert(string* str, u32 index, u32 c)
    {
        // Insertion range is [0, str->count].
        
        u32 csize;
        if (c <= 0x007F) csize = 1;
        else if (c <= 0x07FF) csize = 2;
        else if (c <= 0xFFFF) csize = 3;
        else csize = 4;
        if (str->count + csize > str->size) resize_str(str, str->size + csize + CUTILE_STR_INCREMENT_COUNT);
        if (str->count)
        {
            // Right to left copy.
            for (u32 i = index; i < str->count; ++i)
            {
                u32 j = str->count - (i - index) - 1;
                str->data[j + csize] = str->data[j];
            }
        }
        for (u32 i = 0; i < csize; ++i)
        {
            str->data[i + index] = (c >> (i * 8)) & 0xFF;
        }
        str->count += csize;
    }
    void str_push_back_str(string* str, const string* rhs)
    {
        if (str->count + rhs->count >= str->size) resize_str(str, str->size + rhs->count);
        copy_u8_memory(str->data + str->count, rhs->data, rhs->count);
        str->count += rhs->count;
    }
    void str_push_back_cstr(string* str, const char* rhs)
    {
        u32 rlen = cstr_length(rhs);
        if (str->count + rlen >= str->size) resize_str(str, str->size + rlen);
        copy_u8_memory(str->data + str->count, (u8*)rhs, rlen);
        str->count += rlen;
    }

    void str_push_back_buf(string* str, u8* buf, u64 buf_size)
    {
        if (str->count + buf_size >= str->size) resize_str(str, str->size + buf_size);
        copy_u8_memory(str->data + str->count, buf, buf_size);
        str->count += buf_size;
    }

    void str_pop_back(string* str)
    {
        str->count--;
    }

    void reverse_str(string* str)
    {
        reverse_u8_memory(str->data, str->count);
    }
    void reverse_sub_str(string* str, u32 offset, u32 count)
    {
        reverse_u8_memory(str->data + offset, count);
    }

    u8 str_at(const string* str, u32 index)
    {
        return str->data[index];
    }
    bool8 str_equals_cstr(const string* str, const char* cstr)
    {
        u32 clen = cstr_length(cstr);
        if (clen != str->count) return bool8_false;
        return u8_memory_equals(str->data, (u8*)cstr, clen);
    }
    bool8 str_begins_with(const string* str, const char* val)
    {
        u32 count = cstr_length(val);
        if (count > str->count) return bool8_false;
        return u8_memory_equals(str->data, (u8*)val, count);
    }
    bool8 str_ends_with(const string* str, const char* val)
    {
        u32 count = cstr_length(val);
        if (count > str->count) return bool8_false;
        return u8_memory_equals(str->data + str->count - count, (u8*)val, count);
    }

    u8  sub_str_to_u8(const string* s, u32 offset, u32 count)  { return sub_str_to_u64(s, offset, count); }
    s8  sub_str_to_s8(const string* s, u32 offset, u32 count)  { return sub_str_to_s64(s, offset, count); }
    u16 sub_str_to_u16(const string* s, u32 offset, u32 count) { return sub_str_to_u64(s, offset, count); }
    s16 sub_str_to_s16(const string* s, u32 offset, u32 count) { return sub_str_to_s64(s, offset, count); }
    u32 sub_str_to_u32(const string* s, u32 offset, u32 count) { return sub_str_to_u64(s, offset, count); }
    s32 sub_str_to_s32(const string* s, u32 offset, u32 count) { return sub_str_to_s64(s, offset, count); }
    u64 sub_str_to_u64(const string* s, u32 offset, u32 count)
    {
        u64 res = 0;
        u32 i = offset;
        for (; i < count + offset; ++i)
        {
            res *= 10;
            res += s->data[i] - '0';
        }
        return res;
    }
    s64 sub_str_to_s64(const string* s, u32 offset, u32 count)
    {
        s64 res = 0;
        u32 i = offset;
        bool8 neg = bool8_false;
        if (str_at(s, i) == '-') {
            neg = bool8_true;
            ++i;
        }
        for (; i < count + offset; ++i) {
            res *= 10;
            res += s->data[i] - '0';
        }
        return neg ? -res : res;
    }
    u8  str_to_u8(const string* s)
    {
        return sub_str_to_u8(s, 0, s->count);
    }
    s8  str_to_s8(const string* s)
    {
        return sub_str_to_s8(s, 0, s->count);
    }
    u16 str_to_u16(const string* s)
    {
        return sub_str_to_u16(s, 0, s->count);
    }
    s16 str_to_s16(const string* s)
    {
        return sub_str_to_s16(s, 0, s->count);
    }
    u32 str_to_u32(const string* s)
    {
        return sub_str_to_u32(s, 0, s->count);
    }
    s32 str_to_s32(const string* s)
    {
        return sub_str_to_s32(s, 0, s->count);
    }
    u64 str_to_u64(const string* s)
    {
        return sub_str_to_u64(s, 0, s->count);
    }
    s64 str_to_s64(const string* s)
    {
        return sub_str_to_s64(s, 0, s->count);
    }
    #ifdef CUTILE_CPP
        template <typename IntegerType>
        IntegerType sub_str_to_nb(const string* s, u32 offset, u32 count)
        {
            s64 res = 0;
            u32 i = offset;
            bool neg = false;
            if (str_at(s, i) == '-')
            {
                neg = true;
                ++i;
            }
            for (; i < count; ++i)
            {
                res *= 10;
                res += s->data[i] - '0';
            }
            return neg ? -res : res;
        }
        template <typename IntegerType>
        IntegerType str_to_nb(const string* s)
        {
            return sub_str_to_nb<IntegerType>(s, 0, s->count);
        }
    #endif // CUTILE_CPP
    
    string u8_to_str(u8 nb, allocator* allocator) { return u64_to_str(nb, allocator); }
    string s8_to_str(s8 nb, allocator* allocator) { return s64_to_str(nb, allocator); }
    string u16_to_str(u16 nb, allocator* allocator) { return u64_to_str(nb, allocator); }
    string s16_to_str(s16 nb, allocator* allocator) { return s64_to_str(nb, allocator); }
    string u32_to_str(u32 nb, allocator* allocator) { return u64_to_str(nb, allocator); }
    string s32_to_str(s32 nb, allocator* allocator) { return s64_to_str(nb, allocator); }
    string u64_to_str(u64 nb, allocator* allocator)
    {
        string s = create_empty_str(allocator);
        u64_into_sub_str(nb, &s, 0);
        return s;
    }
    string s64_to_str(s64 nb, allocator* allocator)
    {
        string s = create_empty_str(allocator);
        s64_into_sub_str(nb, &s, 0);
        return s;
    }

#define unsigned_nb_to_cstr_m(digits, nb, allocator, out)      \
    {                                                          \
        out = allocate_many_m(allocator, char, digits+1);      \
        out[digits] = '\0';                                    \
        for (u32 i = digits; i > 0; --i)                       \
        {                                                      \
            out[i - 1] = nb % 10 + '0';                        \
            nb /= 10;                                          \
        }                                                      \
        return out;                                            \
    }

#define signed_nb_to_cstr_m(digits, neg, nb, allocator, out)            \
    {                                                                   \
        u32 shift;                                                      \
        if (neg)                                                        \
        {                                                               \
            out = allocate_many_m(allocator, char, digits+2);           \
            out[0] = '-';                                               \
            shift = 1;                                                  \
            out[digits+1] = '\0';                                       \
        }                                                               \
        else                                                            \
        {                                                               \
            out = allocate_many_m(allocator, char, digits+1);           \
            shift = 0;                                                  \
        }                                                               \
        for (u32 i = digits; i > 0; --i)                                \
        {                                                               \
            out[i - 1 + shift] = nb % 10 + '0';                         \
            nb /= 10;                                                   \
        }                                                               \
        return out;                                                     \
    }

    force_inline s32 _u8_to_str_get_u8_digits(u8 nb)
    {
        if (nb < 10) return 1;
        if (nb < 100) return 2;
        return 3;
    }
    
    force_inline s32 _s8_to_str_get_s8_digits(s8 nb)
    {
        if (nb < 0) nb = nb == s8_min ? s8_max : -nb;
        if (nb < 10) return 1;
        if (nb < 100) return 2;
        return 3;
    }
    
    force_inline s32 _u16_to_str_get_u16_digits(u16 nb)
    {
        if (nb < 10) return 1;
        if (nb < 100) return 2;
        if (nb < 1000) return 3;
        if (nb < 10000) return 4;
        return 5;
    }
    
    force_inline s32 _s16_to_str_get_s16_digits(s16 nb)
    {
        if (nb < 0) nb = nb == s16_min ? s16_max : -nb;
        if (nb < 10) return 1;
        if (nb < 100) return 2;
        if (nb < 1000) return 3;
        if (nb < 10000) return 4;
        return 5;
    }
    
    force_inline s32 _u32_to_str_get_u32_digits(u32 nb)
    {
        if (nb < 10) return 1;
        else if (nb < 100) return 2;
        else if (nb < 1000) return 3;
        else if (nb < 10000) return 4;
        else if (nb < 100000) return 5;
        else if (nb < 1000000) return 6;
        else if (nb < 10000000) return 7;
        else if (nb < 100000000) return 8;
        else if (nb < 1000000000) return 9;
        return 10;
    }
    
    force_inline s32 _s32_to_str_get_s32_digits(s32 nb)
    {
        if (nb < 0) nb = nb == s32_min ? s32_max : -nb;
        if (nb < 10) return 1;
        if (nb < 100) return 2;
        if (nb < 1000) return 3;
        if (nb < 10000) return 4;
        if (nb < 100000) return 5;
        if (nb < 1000000) return 6;
        if (nb < 10000000) return 7;
        if (nb < 100000000) return 8;
        if (nb < 1000000000) return 9;
        return 10;
    }
    
    force_inline s64 _u64_to_str_get_u64_digits(u64 nb)
    {
        if (nb < 10) return 1;
        if (nb < 100) return 2;
        if (nb < 1000) return 3;
        if (nb < 10000) return 4;
        if (nb < 100000) return 5;
        if (nb < 1000000) return 6;
        if (nb < 10000000) return 7;
        if (nb < 100000000) return 8;
        if (nb < 1000000000) return 9;
        if (nb < 10000000000) return 11;
        if (nb < 100000000000) return 12;
        if (nb < 1000000000000) return 13;
        if (nb < 10000000000000) return 14;
        if (nb < 100000000000000) return 15;
        if (nb < 1000000000000000) return 16;
        if (nb < 10000000000000000) return 17;
        if (nb < 100000000000000000) return 18;
        if (nb < 1000000000000000000) return 19;
        return 20;
    }
    
    force_inline s64 _s64_to_str_get_s64_digits(s64 nb)
    {
        if (nb < 0) nb = nb == s64_min ? s64_max : -nb;
        if (nb < 10) return 1;
        if (nb < 100) return 2;
        if (nb < 1000) return 3;
        if (nb < 10000) return 4;
        if (nb < 100000) return 5;
        if (nb < 1000000) return 6;
        if (nb < 10000000) return 7;
        if (nb < 100000000) return 8;
        if (nb < 1000000000) return 9;
        if (nb < 10000000000) return 11;
        if (nb < 100000000000) return 12;
        if (nb < 1000000000000) return 13;
        if (nb < 10000000000000) return 14;
        if (nb < 100000000000000) return 15;
        if (nb < 1000000000000000) return 16;
        if (nb < 10000000000000000) return 17;
        if (nb < 100000000000000000) return 18;
        if (nb < 1000000000000000000) return 19;
        return 20;
    }

    char* u8_to_cstr(u8 nb, allocator* allocator)
    {
        s32 digits = _u8_to_str_get_u8_digits(nb);
        char* result;
        unsigned_nb_to_cstr_m(digits, nb, allocator, result);
        return result;
    }

    char* s8_to_cstr(s8 nb, allocator* allocator)
    {
        s32 digits = _s8_to_str_get_s8_digits(nb);
        b8 neg = nb < 0;
        char* result;
        signed_nb_to_cstr_m(digits, neg, nb, allocator, result);
        return result;
    }

    char* u16_to_cstr(u16 nb, allocator* allocator)
    {
        s32 digits = _u16_to_str_get_u16_digits(nb);
        char* result;
        unsigned_nb_to_cstr_m(digits, nb, allocator, result);
        return result;
    }

    char* s16_to_cstr(s16 nb, allocator* allocator)
    {
        s32 digits = _s16_to_str_get_s16_digits(nb);
        b8 neg = nb < 0;
        char* result;
        signed_nb_to_cstr_m(digits, neg, nb, allocator, result);
        return result;
    }

    char* u32_to_cstr(u32 nb, allocator* allocator)
    {
        s32 digits = _u32_to_str_get_u32_digits(nb);
        char* result;
        unsigned_nb_to_cstr_m(digits, nb, allocator, result);
        return result;
    }

    char* s32_to_cstr(s32 nb, allocator* allocator)
    {
        s32 digits = _s32_to_str_get_s32_digits(nb);
        b8 neg = nb < 0;
        char* result;
        signed_nb_to_cstr_m(digits, neg, nb, allocator, result);
        return result;
    }

    char* u64_to_cstr(u64 nb, allocator* allocator)
    {
        s32 digits = _u64_to_str_get_u64_digits(nb);
        char* result;
        unsigned_nb_to_cstr_m(digits, nb, allocator, result);
        return result;
    }

    char* s64_to_cstr(s64 nb, allocator* allocator)
    {
        s32 digits = _s64_to_str_get_s64_digits(nb);
        b8 neg = nb < 0;
        char* result;
        signed_nb_to_cstr_m(digits, neg, nb, allocator, result);
        return result;
    }
    
    void u8_into_str(u8 nb, string* out) { u64_into_sub_str(nb, out, out->count); }
    void s8_into_str(s8 nb, string* out) { s64_into_sub_str(nb, out, out->count); }
    void u16_into_str(u16 nb, string* out) { u64_into_sub_str(nb, out, out->count); }
    void s16_into_str(s16 nb, string* out) { s64_into_sub_str(nb, out, out->count); }
    void u32_into_str(u32 nb, string* out) { u64_into_sub_str(nb, out, out->count); }
    void s32_into_str(s32 nb, string* out) { s64_into_sub_str(nb, out, out->count); }
    void u64_into_str(u64 nb, string* out) { u64_into_sub_str(nb, out, out->count); }
    void s64_into_str(s64 nb, string* out) { s64_into_sub_str(nb, out, out->count); }
    void u8_into_sub_str(u8 nb, string* out, u32 index) { u64_into_sub_str(nb, out, index); }
    void s8_into_sub_str(s8 nb, string* out, u32 index) { s64_into_sub_str(nb, out, index); }
    void u16_into_sub_str(u16 nb, string* out, u32 index) { u64_into_sub_str(nb, out, index); }
    void s16_into_sub_str(s16 nb, string* out, u32 index) { s64_into_sub_str(nb, out, index); }
    void u32_into_sub_str(u32 nb, string* out, u32 index) { u64_into_sub_str(nb, out, index); }
    void s32_into_sub_str(s32 nb, string* out, u32 index) { s64_into_sub_str(nb, out, index); }
    void u64_into_sub_str(u64 nb, string* out, u32 index)
    {
        do
        {
            auto remainder = nb % 10;
            nb /= 10;
            str_insert(out, index, remainder + '0');
        } while (nb);
    }
    void s64_into_sub_str(s64 nb, string* out, u32 index)
    {
        if (nb < 0)
        {
            str_insert(out, index++, '-');
            nb = -nb;
        }
        do
        {
            auto remainder = nb % 10;
            nb /= 10;
            str_insert(out, index, remainder + '0');
        } while (nb);
    }

    #ifdef CUTILE_CPP

        template <> string nb_to_str<u8>(u8 nb, allocator* allocator) { return u64_to_str(nb, allocator); }
        template <> string nb_to_str<s8>(s8 nb, allocator* allocator) { return s64_to_str(nb, allocator); }
        template <> string nb_to_str<u16>(u16 nb, allocator* allocator) { return u64_to_str(nb, allocator); }
        template <> string nb_to_str<s16>(s16 nb, allocator* allocator) { return s64_to_str(nb, allocator); }
        template <> string nb_to_str<u32>(u32 nb, allocator* allocator) { return u64_to_str(nb, allocator); }
        template <> string nb_to_str<s32>(s32 nb, allocator* allocator) { return s64_to_str(nb, allocator); }
        template <> string nb_to_str<u64>(u64 nb, allocator* allocator) { return u64_to_str(nb, allocator); }
        template <> string nb_to_str<s64>(s64 nb, allocator* allocator) { return s64_to_str(nb, allocator); }

        template <> void nb_into_str<u8>(u8 nb, string* out) { u64_into_str(nb, out); }
        template <> void nb_into_str<s8>(s8 nb, string* out) { s64_into_str(nb, out); }
        template <> void nb_into_str<u16>(u16 nb, string* out) { u64_into_str(nb, out); }
        template <> void nb_into_str<s16>(s16 nb, string* out) { s64_into_str(nb, out); }
        template <> void nb_into_str<u32>(u32 nb, string* out) { u64_into_str(nb, out); }
        template <> void nb_into_str<s32>(s32 nb, string* out) { s64_into_str(nb, out); }
        template <> void nb_into_str<u64>(u64 nb, string* out) { u64_into_str(nb, out); }
        template <> void nb_into_str<s64>(s64 nb, string* out) { s64_into_str(nb, out); }

        template <> void nb_into_sub_str<u8>(u8 nb, string* out, u32 index) { u64_into_sub_str(nb, out, index); }
        template <> void nb_into_sub_str<s8>(s8 nb, string* out, u32 index) { s64_into_sub_str(nb, out, index); }
        template <> void nb_into_sub_str<u16>(u16 nb, string* out, u32 index) { u64_into_sub_str(nb, out, index); }
        template <> void nb_into_sub_str<s16>(s16 nb, string* out, u32 index) { s64_into_sub_str(nb, out, index); }
        template <> void nb_into_sub_str<u32>(u32 nb, string* out, u32 index) { u64_into_sub_str(nb, out, index); }
        template <> void nb_into_sub_str<s32>(s32 nb, string* out, u32 index) { s64_into_sub_str(nb, out, index); }
        template <> void nb_into_sub_str<u64>(u64 nb, string* out, u32 index) { u64_into_sub_str(nb, out, index); }
        template <> void nb_into_sub_str<s64>(s64 nb, string* out, u32 index) { s64_into_sub_str(nb, out, index); }

    #endif // CUTILE_CPP
    
    char* create_cstr_from_str(const string* str, allocator* allocator)
    {
        char* res = (char*)allocate(allocator, str->count + 1);
        copy_s8_memory(res, (char*)str->data, str->count);
        res[str->count] = '\0';
        return res;
    }

    char* create_cstr_from_cstr(const char* cstr, allocator* allocator)
    {
        u32 cstr_len = cstr_length(cstr);
        return create_cstr_from_sub_cstr(cstr, 0, cstr_len, allocator);
    }

    char* create_cstr_from_sub_cstr(const char* cstr, u32 pos, u32 count, allocator* allocator)
    {
        char* res = (char*)allocate(allocator, count + 1);
        copy_s8_memory(res, cstr + pos, count);
        res[count] = '\0';
        return res;
    }

    u32 cstr_length(const char* cstr)
    {
        u32 i = 0;
        while (*(cstr + i)) ++i;
        return i; 
    }

    bool8 cstr_equals(const char* lhs, const char* rhs)
    {
        for (;;)
        {
            if (!(*lhs) && !(*rhs)) break;
            if (*lhs++ != *rhs++) return bool8_false;
        }
        return bool8_true;
    }

    char* concat_cstrs(const char* lhs, const char* rhs, allocator* allocator)
    {
        u32 l_length = cstr_length(lhs);
        u32 r_length = cstr_length(rhs);
        char* result = (char*)allocate(allocator, sizeof(char) * (l_length + r_length + 1));
        copy_s8_memory(result, lhs, l_length);
        copy_s8_memory(result + l_length, rhs, r_length);
        result[l_length + r_length] = '\0';
        return result;
    }

    b8 str_view_equals_cstr(string_view* lhs, const char* rhs)
    {
        u32 rhs_length = cstr_length(rhs);

        if (lhs->count != rhs_length) return b8_false;

        for (u32 i = 0; i < rhs_length; ++i)
        {
            if (rhs[i] != lhs->data[i]) return b8_false;
        }
        return b8_true;
    }

    #ifdef CUTILE_CPP
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
            format_arg_into_str(out, (u64)arg);
        }
        template <>
        void format_arg_into_str<s32>(string* out, s32 arg)
        {
            format_arg_into_str(out, (s64)arg);
        }
        template <>
        void format_arg_into_str<u16>(string* out, u16 arg)
        {
            format_arg_into_str(out, (u64)arg);
        }
        template <>
        void format_arg_into_str<s16>(string* out, s16 arg)
        {
            format_arg_into_str(out, (s64)arg);
        }
        template <>
        void format_arg_into_str<u8>(string* out, u8 arg)
        {
            format_arg_into_str(out, (u64)arg);
        }
        template <>
        void format_arg_into_str<s8>(string* out, s8 arg)
        {
            format_arg_into_str(out, (s64)arg);
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
        void format_arg_into_str<const string*>(string* out, const string* arg)
        {
            str_push_back_str(out, arg);
        }
        template <>
        void format_arg_into_str<string*>(string* out, string* arg)
        {
            str_push_back_str(out, arg);
        }
        template <>
        void format_arg_into_str<string>(string* out, string arg)
        {
            format_arg_into_str(out, &arg);
        }

        template <>
        void format_arg_into_str<void*>(string* out, void* arg)
        {
            format_arg_into_str(out, (u64)arg);
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

    #endif // CUTILE_CPP

#endif // CUTILE_IMPLEM

// Inline implementations:
#ifdef CUTILE_CPP

    template <typename ...Args>
    force_inline string format_str(allocator* allocator, const char* fmt, Args ...args)
    {
        auto str = create_empty_str(allocator);
        format_str(&str, fmt, args...);
        return str;
    }
    template <typename ...Args>
    force_inline string format_str(const char* fmt, Args ...args)
    {
        return format_str(&global_default_heap_allocator, fmt, args...);
    }
    template <typename ...Args>
    force_inline void format_str(string* out, const char* fmt, Args ...args)
    {
        u32 len = cstr_length(fmt);
        u32 i = 0;
        (format_next_arg_into_str(fmt, out, args, &i, len), ...);
        if (i < len) str_push_back_cstr(out, fmt + i);
    }
    template <typename Arg>
    force_inline void format_next_arg_into_str(const char* fmt, string* out, Arg arg, u32* i, u32 len)
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
                str_push_back_u8(out, c);
                ++(*i);
            }
        }
    }
    template <typename ...Args>
    force_inline string format_str(allocator* allocator, const string* fmt, Args ...args)
    {
        auto str = create_empty_str(allocator);
        format_str(&str, fmt, args...);
        return str;
    }
    template <typename ...Args>
    force_inline string format_str(const string* fmt, Args ...args)
    {
        return format_str(&global_default_heap_allocator, fmt, args...);
    }
    template <typename ...Args>
    force_inline void format_str(string* out, const string* fmt, Args ...args)
    {
        u32 i = 0;
        (format_next_arg_into_string(fmt, out, args, &i), ...);
    }
    template <typename Arg>
    force_inline void format_next_arg_into_string(const string* fmt, string* out, Arg arg, u32* i)
    {
        while (*i < fmt->count) 
        {
            u8 c = fmt->data[*i];
            if (c == '%') 
            {
                format_arg_into_string(out, arg);
                ++(*i);
                return;
            }
            else 
            {
                str_push_back_u8(out, c);
                ++(*i);
            }
        }
    }

#endif // CUTILE_CPP // ^- Inline implementations

#endif // !CUTILE_STR_H
