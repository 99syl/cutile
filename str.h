#pragma once

#include "cutile.h"
#include "memory.h"

// Represents an UTF-8 string.
typedef struct string
{
    u8* data;
    u32 count;
    u32 size;

    allocator* allocator;
} string;

// String Creation:
CUTILE_C_API string create_empty_str(allocator* allocator);
CUTILE_C_API string create_sized_empty_str(u32 size, allocator*);
CUTILE_C_API string create_str_from_cstr(const char* cstr, allocator* allocator);
CUTILE_C_API string copy_str(const string* original, allocator* allocator);
CUTILE_C_API string create_str_from_buf(const u8* buf, u32 buf_len, allocator* allocator);

// String Destruction:
CUTILE_C_API void destroy_str(string* str);

// String Modification:
CUTILE_C_API void str_push_back(string* str, u32 c); // Equivalent to str_push_back_u32.
CUTILE_C_API void str_push_back_u32(string* str, u32 c);
CUTILE_C_API void str_push_back_s8(string* str, s8 c);
CUTILE_C_API void str_insert_u32(string* str, u32 index, u32 c);
CUTILE_C_API void str_insert_s8(string* str, u32 index, s8 c);
CUTILE_C_API void str_push_back_str(string* str, const string* rhs);
CUTILE_C_API void str_push_back_cstr(string* str, const char* rhs);
CUTILE_C_API void str_push_back_buf(string* str, u8* buf, u64 buf_size);
CUTILE_C_API void str_pop_back(string* str);
CUTILE_C_API void resize_str(string* str, u32 size);

// String Transformation:
CUTILE_C_API void reverse_str(string* str);
CUTILE_C_API void reverse_sub_str(string* str, u32 offset, u32 count);

// String Lookup:
CUTILE_C_API u8    str_at(const string* str, u32 index);
CUTILE_C_API bool8 str_equals_cstr(const string* str, const char* cstr);
CUTILE_C_API bool8 str_begins_with(const string* str, const char* val);
CUTILE_C_API bool8 str_ends_with(const string* str, const char* val);

// CString Creation:
CUTILE_C_API char* create_cstr_from_str(const string* str, allocator* allocator);
CUTILE_C_API char* create_cstr_from_cstr(const char* cstr, allocator* allocator);
CUTILE_C_API char* create_cstr_from_sub_cstr(const char* cstr, u32 pos, u32 count, allocator* allocator);

// CString Lookup:
CUTILE_C_API u32   cstr_length(const char* cstr);
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

// String-View Lookup:
CUTILE_C_API b8 str_view_equals_cstr(string_view* lhs, const char* rhs);

// Conversion functions between strings and numbers:

CUTILE_C_API u8  sub_str_to_u8(const string* s, u32 offset, u32 count);
CUTILE_C_API s8  sub_str_to_s8(const string* s, u32 offset, u32 count);
CUTILE_C_API u16 sub_str_to_u16(const string* s, u32 offset, u32 count);
CUTILE_C_API s16 sub_str_to_s16(const string* s, u32 offset, u32 count);
CUTILE_C_API u32 sub_str_to_u32(const string* s, u32 offset, u32 count);
CUTILE_C_API s32 sub_str_to_s32(const string* s, u32 offset, u32 count);
CUTILE_C_API u64 sub_str_to_u64(const string* s, u32 offset, u32 count);
CUTILE_C_API s64 sub_str_to_s64(const string* s, u32 offset, u32 count);

CUTILE_C_API u8  str_to_u8(const string* s);
CUTILE_C_API s8  str_to_s8(const string* s);
CUTILE_C_API u16 str_to_u16(const string* s);
CUTILE_C_API s16 str_to_s16(const string* s);
CUTILE_C_API u32 str_to_u32(const string* s);
CUTILE_C_API s32 str_to_s32(const string* s);
CUTILE_C_API u64 str_to_u64(const string* s);
CUTILE_C_API s64 str_to_s64(const string* s);

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

    string create_sized_empty_str(u32 size, allocator* allocator)
    {
	string s;
	s.data = (u8*)allocate(allocator, sizeof(u8) * size);
	s.count = 0;
	s.size = sizeof(u8)*size;
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

    void str_push_back_u32(string* str, u32 c)
    {
	// TODO: THere is room for improvement !

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

    void str_push_back_s8(string* str, s8 c)
    {
        if (str->count + 1 >= str->size) resize_str(str, str->size + 1 + CUTILE_STR_INCREMENT_COUNT);
        str->data[str->count++] = c;
    }

    void str_insert_u32(string* str, u32 index, u32 c)
    {
	// TODO: There is room for improvement !
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

    void str_insert_s8(string* str, u32 index, s8 c)
    {
        // Insertion range is [0, str->count].
        
        if (str->count + 1 > str->size) resize_str(str, str->size + CUTILE_STR_INCREMENT_COUNT);
        if (str->count)
        {
            // Right to left copy.
            for (u32 i = index; i < str->count; ++i)
            {
                u32 j = str->count - (i - index) - 1;
                str->data[j + 1] = str->data[j];
            }
        }
	str->data[index] = c;
        str->count += 1;
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

    #define sub_str_to_unsigned_nb_m(res, str, offset, count) \
    {							      \
        res = 0;					      \
	u32 i = offset;					      \
	for (; i < count + offset; ++i)			      \
	{						      \
            res *= 10;					      \
	    res += str->data[i] - '0';			      \
	}						      \
    }						              \
    
    #define sub_str_to_signed_nb_m(res, str, offset, count) \
    {							    \
        res = 0;					    \
        u32 i = offset;					    \
        bool8 neg = bool8_false;			    \
        if (str_at(s, i) == '-') {			    \
            neg = bool8_true;				    \
            ++i;					    \
        }						    \
        for (; i < count + offset; ++i) {		    \
            res *= 10;					    \
            res += s->data[i] - '0';			    \
        }						    \
        res = neg ? -res : res;			            \
    }						            \

    maybe_inline u8  sub_str_to_u8(const string* s, u32 offset, u32 count) { u8 res; sub_str_to_unsigned_nb_m(res, s, offset, count); return res; }

    maybe_inline s8  sub_str_to_s8(const string* s, u32 offset, u32 count)  { s8 res; sub_str_to_signed_nb_m(res, s, offset, count); return res; }

    maybe_inline u16 sub_str_to_u16(const string* s, u32 offset, u32 count) { u16 res; sub_str_to_unsigned_nb_m(res, s, offset, count); return res; }

    maybe_inline s16 sub_str_to_s16(const string* s, u32 offset, u32 count) { s16 res; sub_str_to_signed_nb_m(res, s, offset, count); return res; }

    maybe_inline u32 sub_str_to_u32(const string* s, u32 offset, u32 count) { u32 res; sub_str_to_unsigned_nb_m(res, s, offset, count); return res; }

    maybe_inline s32 sub_str_to_s32(const string* s, u32 offset, u32 count) { s32 res; sub_str_to_signed_nb_m(res, s, offset, count); return res; }

    maybe_inline u64 sub_str_to_u64(const string* s, u32 offset, u32 count) { u64 res; sub_str_to_unsigned_nb_m(res, s, offset, count); return res; }

    maybe_inline s64 sub_str_to_s64(const string* s, u32 offset, u32 count) { s64 res; sub_str_to_signed_nb_m(res, s, offset, count); return res; }

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

    #include "number.h"

    #define unsigned_nb_to_str_m(nb, digits, allocator) 		\
    {									\
        string out = create_sized_empty_str(digits, allocator);		\
	out.count = digits;						\
        for (u32 i = digits; i > 0; --i)				\
        {								\
            out.data[i - 1] = nb % 10 + '0';				\
            nb /= 10;							\
        }								\
	return out;							\
    }									\

    #define signed_nb_to_str_m(nb, digits, allocator)    	        \
    {									\
        u32 shift;							\
        string out;							\
        if (nb < 0)                                                     \
        {                                                               \
            out = create_sized_empty_str(digits+1, allocator);		\
            out.data[0] = '-';						\
            shift = 1;                                                  \
        }                                                               \
        else                                                            \
        {                                                               \
            out = create_sized_empty_str(digits, allocator);		\
            shift = 0;                                                  \
        }                                                               \
        for (u32 i = digits; i > 0; --i)                                \
        {                                                               \
            out.data[i - 1 + shift] = nb % 10 + '0';			\
            nb /= 10;                                                   \
        }                                                               \
        out.count = digits + shift;					\
	return out;							\
    }								        \

    string u8_to_str(u8 nb, allocator* allocator) { unsigned_nb_to_str_m(nb, get_u8_digits(nb), allocator); }

    string s8_to_str(s8 nb, allocator* allocator) { signed_nb_to_str_m(nb, get_s8_digits(nb), allocator); }

    string u16_to_str(u16 nb, allocator* allocator) { unsigned_nb_to_str_m(nb, get_u16_digits(nb), allocator); }

    string s16_to_str(s16 nb, allocator* allocator) { signed_nb_to_str_m(nb, get_s16_digits(nb), allocator); }

    string u32_to_str(u32 nb, allocator* allocator) { unsigned_nb_to_str_m(nb, get_u32_digits(nb), allocator); }

    string s32_to_str(s32 nb, allocator* allocator) { signed_nb_to_str_m(nb, get_s32_digits(nb), allocator); }

    string u64_to_str(u64 nb, allocator* allocator) { unsigned_nb_to_str_m(nb, get_u64_digits(nb), allocator); }

    string s64_to_str(s64 nb, allocator* allocator) { signed_nb_to_str_m(nb, get_s64_digits(nb), allocator); }

    #define unsigned_nb_to_cstr_m(nb, digits, allocator) 		\
    {									\
        char* out = allocate_many_m(allocator, char, digits+1);		\
	out[digits] = '\0';						\
        for (u32 i = digits; i > 0; --i)				\
        {								\
            out[i - 1] = nb % 10 + '0';				        \
            nb /= 10;							\
        }								\
	return out;							\
    }									\

    #define signed_nb_to_cstr_m(nb, digits, allocator)			\
    {                                                                   \
        u32 shift;                                                      \
        char* out;							\
        if (nb < 0)							\
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

    char* u8_to_cstr(u8 nb, allocator* allocator) { u32 digits = get_u8_digits(nb); unsigned_nb_to_cstr_m(nb, digits, allocator); }

    char* s8_to_cstr(s8 nb, allocator* allocator) { u32 digits = get_s8_digits(nb); signed_nb_to_cstr_m(nb, digits, allocator); }

    char* u16_to_cstr(u16 nb, allocator* allocator) { u32 digits = get_u16_digits(nb); unsigned_nb_to_cstr_m(nb, digits, allocator); }

    char* s16_to_cstr(s16 nb, allocator* allocator) { u32 digits = get_s16_digits(nb); signed_nb_to_cstr_m(nb, digits, allocator); }

    char* u32_to_cstr(u32 nb, allocator* allocator) { u32 digits = get_u32_digits(nb); unsigned_nb_to_cstr_m(nb, digits, allocator); }

    char* s32_to_cstr(s32 nb, allocator* allocator) { u32 digits = get_s32_digits(nb); signed_nb_to_cstr_m(nb, digits, allocator); }

    char* u64_to_cstr(u64 nb, allocator* allocator) { u32 digits = get_u64_digits(nb); unsigned_nb_to_cstr_m(nb, digits, allocator); }

    char* s64_to_cstr(s64 nb, allocator* allocator) { u32 digits = get_s64_digits(nb); signed_nb_to_cstr_m(nb, digits, allocator); }

    void u8_into_str(u8 nb, string* out) { u8_into_sub_str(nb, out, out->count); }

    void s8_into_str(s8 nb, string* out) { s8_into_sub_str(nb, out, out->count); }

    void u16_into_str(u16 nb, string* out) { u16_into_sub_str(nb, out, out->count); }

    void s16_into_str(s16 nb, string* out) { s16_into_sub_str(nb, out, out->count); }

    void u32_into_str(u32 nb, string* out) { u32_into_sub_str(nb, out, out->count); }

    void s32_into_str(s32 nb, string* out) { s32_into_sub_str(nb, out, out->count); }

    void u64_into_str(u64 nb, string* out) { u64_into_sub_str(nb, out, out->count); }

    void s64_into_str(s64 nb, string* out) { s64_into_sub_str(nb, out, out->count); }

    #define unsigned_nb_into_sub_str(nb, str, index)		   \
        do							   \
	{							   \
	    s8 remainder = nb % 10;				   \
            nb /= 10;						   \
            str_insert_s8(str, index, remainder + '0');		   \
	} while (nb);					           \

    #define signed_nb_into_sub_str(nb, str, index)	           \
    {   							   \
        if (nb < 0)						   \
	{						           \
	    str_insert_s8(out, index++, '-');			   \
            nb = -nb;						   \
	}							   \
        do							   \
	{							   \
	    s8 remainder = nb % 10;				   \
            nb /= 10;						   \
            str_insert_s8(str, index, remainder + '0');		   \
	} while (nb);					           \
    }							           \

    maybe_inline void u8_into_sub_str(u8 nb, string* out, u32 index) { unsigned_nb_into_sub_str(nb, out, index); }

    maybe_inline void s8_into_sub_str(s8 nb, string* out, u32 index) { signed_nb_into_sub_str(nb, out, index); }

    maybe_inline void u16_into_sub_str(u16 nb, string* out, u32 index) { unsigned_nb_into_sub_str(nb, out, index); }

    maybe_inline void s16_into_sub_str(s16 nb, string* out, u32 index) { signed_nb_into_sub_str(nb, out, index); }

    maybe_inline void u32_into_sub_str(u32 nb, string* out, u32 index) { unsigned_nb_into_sub_str(nb, out, index); }

    maybe_inline void s32_into_sub_str(s32 nb, string* out, u32 index) { signed_nb_into_sub_str(nb, out, index); }

    maybe_inline void u64_into_sub_str(u64 nb, string* out, u32 index) { unsigned_nb_into_sub_str(nb, out, index); }

    maybe_inline void s64_into_sub_str(s64 nb, string* out, u32 index) { signed_nb_into_sub_str(nb, out, index); }

#endif // CUTILE_IMPLEM
