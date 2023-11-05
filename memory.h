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

void copy_u8_memory(u8 *data, const u8* in, u32 count);
void copy_s8_memory(s8* data, const s8* in, u32 count);
void copy_u16_memory(u16* data, const u16* in, u32 count);
void copy_s16_memory(s16* data, const s16* in, u32 count);
void copy_u32_memory(u32* data, const u32* in, u32 count);
void copy_s32_memory(s32* data, const s32* in, u32 count);
void copy_u64_memory(u64* data, const u64* in, u32 count);
void copy_s64_memory(s64* data, const s64* in, u32 count);
#ifdef CUTILE_CPP
template <typename T>
void copy_memory(T* data, const T* in, u32 count);
#endif // CUTILE_CPP

void reverse_u8_memory(u8* data, u32 count);
void reverse_s8_memory(s8* data, u32 count);
void reverse_u16_memory(u16* data, u32 count);
void reverse_s16_memory(s16* data, u32 count);
void reverse_u32_memory(u32* data, u32 count);
void reverse_s32_memory(s32* data, u32 count);
void reverse_u64_memory(u64* data, u32 count);
void reverse_s64_memory(s64* data, u32 count);
#ifdef CUTILE_CPP
template <typename T>
void reverse_memory(T* data, u32 count);
#endif // CUTILE_CPP

bool8 u8_memory_equals (const u8*  lhs, const u8*  rhs, u32 count);
bool8 s8_memory_equals (const s8*  lhs, const s8*  rhs, u32 count);
bool8 u16_memory_equals(const u16* lhs, const u16* rhs, u32 count);
bool8 s16_memory_equals(const s16* lhs, const s16* rhs, u32 count);
bool8 u32_memory_equals(const u32* lhs, const u32* rhs, u32 count);
bool8 s32_memory_equals(const s32* lhs, const s32* rhs, u32 count);
bool8 u64_memory_equals(const u64* lhs, const u64* rhs, u32 count);
bool8 s64_memory_equals(const s64* lhs, const s64* rhs, u32 count);
#ifdef CUTILE_CPP
template <typename T>
bool8 memory_equals(const T* lhs, const T* rhs, u32 count);
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
#endif // CUTILE_CPP

#ifdef CUTILE_ALLOCATOR_ANALYZER
struct allocation_info
{
    bool8       available;
    void*       address;
    u64         size;
    u32         line;
    const char* filename;
};
#ifdef CUTILE_C
typedef struct allocation_info allocation_info;
#endif // CUTILE_C
struct allocation_table
{
    u64 count;
    u64 size;
    allocation_info* data;
};
#ifdef CUTILE_C
typedef struct allocation_table allocation_table;
#endif // CUTILE_C
extern allocation_table allocations_info;
#endif // CUTILE_ALLOCATOR_ANALYZER

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

void copy_u8_memory(u8 *data, const u8* in, u32 count)
{
    for (u32 i = 0; i < count; ++i) data[i] = in[i];
}
void copy_s8_memory(s8* data, const s8* in, u32 count)
{
    for (u32 i = 0; i < count; ++i) data[i] = in[i];
}
void copy_u16_memory(u16* data, const u16* in, u32 count)
{
    for (u32 i = 0; i < count; ++i) data[i] = in[i];
}
void copy_s16_memory(s16* data, const s16* in, u32 count)
{
    for (u32 i = 0; i < count; ++i) data[i] = in[i];
}
void copy_u32_memory(u32* data, const u32* in, u32 count)
{
    for (u32 i = 0; i < count; ++i) data[i] = in[i];
}
void copy_s32_memory(s32* data, const s32* in, u32 count)
{
    for (u32 i = 0; i < count; ++i) data[i] = in[i];
}
void copy_u64_memory(u64* data, const u64* in, u32 count)
{
    for (u32 i = 0; i < count; ++i) data[i] = in[i];
}
void copy_s64_memory(s64* data, const s64* in, u32 count)
{
    for (u32 i = 0; i < count; ++i) data[i] = in[i];
}
#ifdef CUTILE_CPP
template <typename T>
void copy_memory(T* data, const T* in, u32 count)
{
    for (u32 i = 0; i < count; ++i) data[i] = in[i];
}
#endif // CUTILE_CPP

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
void reverse_s8_memory(s8* data, u32 count)
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
void reverse_u16_memory(u16* data, u32 count)
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
void reverse_s16_memory(s16* data, u32 count)
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
void reverse_u32_memory(u32* data, u32 count)
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
void reverse_s32_memory(s32* data, u32 count)
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
void reverse_u64_memory(u64* data, u32 count)
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
void reverse_s64_memory(s64* data, u32 count)
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

bool8 u8_memory_equals (const u8*  lhs, const u8*  rhs, u32 count)
{
    for (u32 i = 0; i < count; ++i) if (lhs[i] != rhs[i]) return bool8_false;
    return bool8_true;
}
bool8 s8_memory_equals (const s8*  lhs, const s8*  rhs, u32 count)
{
    for (u32 i = 0; i < count; ++i) if (lhs[i] != rhs[i]) return bool8_false;
    return bool8_true;
}
bool8 u16_memory_equals(const u16* lhs, const u16* rhs, u32 count)
{
    for (u32 i = 0; i < count; ++i) if (lhs[i] != rhs[i]) return bool8_false;
    return bool8_true;
}
bool8 s16_memory_equals(const s16* lhs, const s16* rhs, u32 count)
{
    for (u32 i = 0; i < count; ++i) if (lhs[i] != rhs[i]) return bool8_false;
    return bool8_true;
}
bool8 u32_memory_equals(const u32* lhs, const u32* rhs, u32 count)
{
    for (u32 i = 0; i < count; ++i) if (lhs[i] != rhs[i]) return bool8_false;
    return bool8_true;
}
bool8 s32_memory_equals(const s32* lhs, const s32* rhs, u32 count)
{
    for (u32 i = 0; i < count; ++i) if (lhs[i] != rhs[i]) return bool8_false;
    return bool8_true;
}
bool8 u64_memory_equals(const u64* lhs, const u64* rhs, u32 count)
{
    for (u32 i = 0; i < count; ++i) if (lhs[i] != rhs[i]) return bool8_false;
    return bool8_true;
}
bool8 s64_memory_equals(const s64* lhs, const s64* rhs, u32 count)
{
    for (u32 i = 0; i < count; ++i) if (lhs[i] != rhs[i]) return bool8_false;
    return bool8_true;
}
#ifdef CUTILE_CPP
template <typename T>
bool8 memory_equals(const T* lhs, const T* rhs, u32 count)
{
    for (u32 i = 0; i < count; ++i) if (lhs[i] != rhs[i]) return bool8_false;
    return bool8_true;
}
#endif // CUTILE_CPP

#ifdef CUTILE_ALLOCATOR_ANALYZER
allocation_table allocations_info = { 0, 0, nullptr };
#else // !CUTILE_ALLOCATOR_ANALYZER
void* allocate(allocator* allocator, u64 size)
{
    return allocator->allocate(allocator->user, size);
}
void deallocate(allocator* allocator, void* ptr)
{
    allocator->deallocate(allocator->user, ptr);
}
#ifdef CUTILE_CPP
template <typename T>
T* allocate(allocator* allocator, u64 count)
{
    return (T*)(allocate(allocator, sizeof(T) * count));
}
template <typename T>
void deallocate(allocator* allocator, T* ptr)
{
    deallocate(allocator, (void*)ptr);
}
#endif // CUTILE_CPP
#endif // !CUTILE_ALLOCATOR_ANALYZER

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
    allocator res =
    {
        .user = 0,
        .allocate = &basic_heap_allocate,
        .deallocate = &basic_heap_deallocate
    };
    return res;
}

allocator basic_heap_allocator =
{
    .user = 0,
    .allocate = &basic_heap_allocate,
    .deallocate = &basic_heap_deallocate
};

#endif // CUTILE_IMPLEM

#ifdef CUTILE_ALLOCATOR_ANALYZER
force_inline void* allocate(allocator* allocator, u64 size)
{
    void* data = allocator->allocate(allocator->user, size);
    allocation_info* elem = allocations_info.data;

    // Search for an available node.
    for (u32 i = 0; i < allocations_info.count; ++i)
    {
        if (allocations_info.data[i].available)
        {
            elem = &allocations_info.data[i];
            break;
        }
    }

    // No available node found so add a new one.
    if (elem == allocations_info.data)
    {
        // Increase buffer size if it's full
        if (allocations_info.count == allocations_info.size)
        {
            allocations_info.size += 100;
            allocation_info* new_data = (allocation_info*) basic_heap_allocate(nullptr, sizeof(allocation_info) * allocations_info.size);
            copy_u8_memory((u8*)new_data, (u8*)allocations_info.data, sizeof(allocation_info) * allocations_info.count);
            basic_heap_deallocate(nullptr, allocations_info.data);
            allocations_info.data = new_data;
        }
        elem = &allocations_info.data[allocations_info.count++];
    }
    elem->available = bool8_false;
    elem->address = data;
    elem->size = size;
    elem->line = __LINE__;
    elem->filename = __FILE__;

    return data;
}
force_inline void deallocate(allocator* allocator, void* ptr)
{
    for (u32 i = 0; i < allocations_info.count; ++i)
    {
        if (allocations_info.data[i].address == ptr)
        {
            allocations_info.data[i].available = bool8_true;
            --allocations_info.count;
            break;
        }
    }
    allocator->deallocate(allocator->user, ptr);
}
#ifdef CUTILE_CPP
template <typename T>
force_inline T* allocate(allocator* allocator, u64 count)
{
    return (T*)(allocate(allocator, sizeof(T) * count));
}
template <typename T>
force_inline void deallocate(allocator* allocator, T* ptr)
{
    return deallocate(allocator, (void*)ptr);
}
#endif // CUTILE_CPP
#endif // CUTILE_ALLOCATOR_ANALYZER

#endif // !CUTILE_MEMORY_H
