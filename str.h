#ifndef CUTILE_STR_H
#define CUTILE_STR_H

#include "./cutile.h"
#include "./memory.h"

struct string
{
    u8* data;
    u32 count;
    u32 size;

    allocator* allocator;
};
#ifdef CUTILE_C
typedef struct string string;
#endif

string create_empty_str(allocator* allocator);
string create_str_from_cstr(const char* cstr, allocator* allocator);

void destroy_str(string* str);

void resize_str(string* str, u32 size);

void str_push_back(string* str, u32 c);
void str_pop_back(string* str);

void reverse_str(string* str);
void reverse_sub_str(string* str, u32 offset, u32 count);

bool str_begins_with(const string* str, const char* val);
bool str_ends_with(const string* str, const char* val);

char* create_cstr_from_str(const string* str, allocator* allocator);

u32 cstr_length(const char* cstr);

bool8 cstr_equals(const char* lhs, const char* rhs);

#ifdef CUTILE_IMPLEM

#define CUTILE_STR_INCREMENT_COUNT 5

string create_empty_str(allocator* allocator)
{
    string s;
    s.data = (u8*)allocate(allocator, sizeof(u8) * CUTILE_STR_INCREMENT_COUNT);
    s.count = CUTILE_STR_INCREMENT_COUNT;
    s.size = s.count;
    s.allocator = allocator;
    return s;
}
string create_str_from_cstr(const char* cstr, allocator* allocator)
{
    u32 count = cstr_length(cstr);
    string s;
    s.data = (u8*)allocate(allocator, sizeof(u8) * count);
    s.count = count;
    s.size = count;
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
    if (size < str->count) {
        for (u32 i = 0; i < size; ++i) new_data[i] = str->data[i];
        str->count = size;
    }
    else {
        for (u32 i = 0; i < str->count; ++i) new_data[i] = str->data[i];
    }
    deallocate(str->allocator, str->data);
    str->data = new_data;
    str->size = size;
}

void str_push_back(string* str, u32 c)
{
    if (str->count == str->size) resize_str(str, str->size + CUTILE_STR_INCREMENT_COUNT);
    str->data[str->count++] = c;
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

bool str_begins_with(const string* str, const char* val)
{
    u32 count = cstr_length(val);
    if (count > str->count) return false;
    for (u32 i = 0; i < count; ++i) if (str->data[i] != val[i]) return false;
    return true;
}
bool str_ends_with(const string* str, const char* val)
{
    u32 count = cstr_length(val);
    if (count > str->count) return false;
    for (u32 i = count - 1; i <= count /* loop until overflow */; --i) if (str->data[i] != val[i]) return false;
    return true;
}

char* create_cstr_from_str(const string* str, allocator* allocator)
{
    char* res = (char*)allocate(allocator, str->count + 1);
    copy_s8_memory(res, (char*)str->data, str->count);
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

#endif

#endif // CUTILE_STR_H
