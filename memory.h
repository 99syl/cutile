#ifndef CUTILE_MEMORY_H
#define CUTILE_MEMORY_H

#include "./num_types.h"
#include "./cutile.h"

void fill_u8_memory(u8* data, u32 count, u8 value);
void fill_s8_memory(s8* data, u32 count, s8 value);
void fill_u16_memory(u16* data, u32 count, u16 value);
void fill_s16_memory(s16* data, u32 count, s16 value);
void fill_u32_memory(u32* data, u32 count, u32 value);
void fill_s32_memory(s32* data, u32 count, s32 value);
void fill_u64_memory(u64* data, u32 count, u64 value);
void fill_s64_memory(s64* data, u32 count, s64 value);
#ifdef CUTILE_CPP
template <typename T>
void fill_memory(T* data, u32 count, T value);
#endif // CUTILE_CPP

void reverse_u8_memory(u8* data, u32 count);
void reverse_s8_memory(u8* data, u32 count);
void reverse_u16_memory(u8* data, u32 count);
void reverse_s16_memory(u8* data, u32 count);
void reverse_u32_memory(u8* data, u32 count);
void reverse_s32_memory(u8* data, u32 count);
void reverse_u64_memory(u8* data, u32 count);
void reverse_s64_memory(u8* data, u32 count);
#ifdef CUTILE_CPP
template <typename T>
void reverse_memory(T* data, u32 count);
#endif // CUTILE_CPP

struct allocator
{
    void*   user;
    void*   (*allocate)(void* user, u64 size);
    void    (*deallocate)(void* user, void* ptr);
};
#ifdef CUTILE_C
typedef struct allocator allocator;
#endif

void*   allocate(allocator* allocator, u64 size);
void    deallocate(allocator* allocator, void* ptr);
#ifdef CUTILE_CPP
template <typename T>
T*      allocate(allocator* allocator, u64 count);
template <typename T>
void    deallocate(allocator* allocator, T* ptr);
#endif

allocator create_basic_heap_allocator();

extern allocator basic_heap_allocator;

#ifdef CUTILE_IMPLEM

#include <stdlib.h> //> malloc, free

void fill_u8_memory(u8* data, u32 count, u8 value)
{
    for (u32 i = 0; i < count; ++i) data[i] = value;
}
void fill_s8_memory(s8* data, u32 count, s8 value)
{
    for (u32 i = 0; i < count; ++i) data[i] = value;
}
void fill_u16_memory(u16* data, u32 count, u16 value)
{
    for (u32 i = 0; i < count; ++i) data[i] = value;
}
void fill_s16_memory(s16* data, u32 count, s16 value)
{
    for (u32 i = 0; i < count; ++i) data[i] = value;
}
void fill_u32_memory(u32* data, u32 count, u32 value)
{
    for (u32 i = 0; i < count; ++i) data[i] = value;
}
void fill_s32_memory(s32* data, u32 count, s32 value)
{
    for (u32 i = 0; i < count; ++i) data[i] = value;
}
void fill_u64_memory(u64* data, u32 count, u64 value)
{
    for (u32 i = 0; i < count; ++i) data[i] = value;
}
void fill_s64_memory(s64* data, u32 count, s64 value)
{
    for (u32 i = 0; i < count; ++i) data[i] = value;
}
#ifdef CUTILE_CPP
template <typename T>
void fill_memory(T* data, u32 count, T value)
{
    for (u32 i = 0; i < count; ++i) data[i] = value;
}
#endif

void reverse_u8_memory(u8* data, u32 count)
{
    u32 end = count * 0.5;
    for (u32 i = 0; i < end; ++i) 
    {
        u8 dump = data[i];
        u32 rhs_i = count - 1 - i;
        data[i] = data[rhs_i];
        data[rhs_i] = dump;
    }
}
void reverse_s8_memory(u8* data, u32 count)
{
    u32 end = count * 0.5;
    for (u32 i = 0; i < end; ++i) 
    {
        u8 dump = data[i];
        u32 rhs_i = count - 1 - i;
        data[i] = data[rhs_i];
        data[rhs_i] = dump;
    }
}
void reverse_u16_memory(u8* data, u32 count)
{
    u32 end = count * 0.5;
    for (u32 i = 0; i < end; ++i) 
    {
        u8 dump = data[i];
        u32 rhs_i = count - 1 - i;
        data[i] = data[rhs_i];
        data[rhs_i] = dump;
    }
}
void reverse_s16_memory(u8* data, u32 count)
{
    u32 end = count * 0.5;
    for (u32 i = 0; i < end; ++i) 
    {
        u8 dump = data[i];
        u32 rhs_i = count - 1 - i;
        data[i] = data[rhs_i];
        data[rhs_i] = dump;
    }
}
void reverse_u32_memory(u8* data, u32 count)
{
    u32 end = count * 0.5;
    for (u32 i = 0; i < end; ++i) 
    {
        u8 dump = data[i];
        u32 rhs_i = count - 1 - i;
        data[i] = data[rhs_i];
        data[rhs_i] = dump;
    }
}
void reverse_s32_memory(u8* data, u32 count)
{
    u32 end = count * 0.5;
    for (u32 i = 0; i < end; ++i) 
    {
        u8 dump = data[i];
        u32 rhs_i = count - 1 - i;
        data[i] = data[rhs_i];
        data[rhs_i] = dump;
    }
}
void reverse_u64_memory(u8* data, u32 count)
{
    u32 end = count * 0.5;
    for (u32 i = 0; i < end; ++i) 
    {
        u8 dump = data[i];
        u32 rhs_i = count - 1 - i;
        data[i] = data[rhs_i];
        data[rhs_i] = dump;
    }
}
void reverse_s64_memory(u8* data, u32 count)
{
    u32 end = count * 0.5;
    for (u32 i = 0; i < end; ++i) 
    {
        u8 dump = data[i];
        u32 rhs_i = count - 1 - i;
        data[i] = data[rhs_i];
        data[rhs_i] = dump;
    }
}
#ifdef CUTILE_CPP
template <typename T>
void reverse_memory(T* data, u32 count)
{
    u32 end = count * 0.5;
    for (u32 i = 0; i < end; ++i) 
    {
        u8 dump = data[i];
        u32 rhs_i = count - 1 - i;
        data[i] = data[rhs_i];
        data[rhs_i] = dump;
    }
}
#endif // CUTILE_CPP

void*   allocate(allocator* allocator, u64 size)
{
    return allocator->allocate(allocator->user, size);
}
void    deallocate(allocator* allocator, void* ptr)
{
    return allocator->deallocate(allocator->user, ptr);
}
#ifdef CUTILE_CPP
template <typename T>
T*      allocate(allocator* allocator, u64 count)
{
    return (T*)(allocate(allocator, sizeof(T) * count));
}
template <typename T>
void    deallocate(allocator* allocator, T* ptr)
{
    return deallocate(allocator, (void*)ptr);
}
#endif // CUTILE_CPP

void* basic_heap_allocate(void* user, u64 size)
{
    return malloc(size);
}

void basic_heap_deallocate(void* user, void* ptr)
{
    free(ptr);
}

allocator create_basic_heap_allocator()
{
    return 
    {
        0,
        &basic_heap_allocate,
        &basic_heap_deallocate
    };
}

#endif // CUTILE_IMPLEM

#endif // !CUTILE_MEMORY_H
