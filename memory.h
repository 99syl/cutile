#ifndef CUTILE_MEMORY_H
#define CUTILE_MEMORY_H

#include "./num_types.h"

void fill_u8_memory(u8* data, u32 count, u8 value);
void fill_s8_memory(s8* data, u32 count, s8 value);
void fill_u16_memory(u16* data, u32 count, u16 value);
void fill_s16_memory(s16* data, u32 count, s16 value);
void fill_u32_memory(u32* data, u32 count, u32 value);
void fill_s32_memory(s32* data, u32 count, s32 value);
void fill_u64_memory(u64* data, u32 count, u64 value);
void fill_s64_memory(s64* data, u32 count, s64 value);

void copy_u8_memory(u8 *data, const u8* in, u32 count);
void copy_s8_memory(s8* data, const s8* in, u32 count);
void copy_u16_memory(u16* data, const u16* in, u32 count);
void copy_s16_memory(s16* data, const s16* in, u32 count);
void copy_u32_memory(u32* data, const u32* in, u32 count);
void copy_s32_memory(s32* data, const s32* in, u32 count);
void copy_u64_memory(u64* data, const u64* in, u32 count);
void copy_s64_memory(s64* data, const s64* in, u32 count);

void reverse_u8_memory(u8* data, u32 count);
void reverse_s8_memory(s8* data, u32 count);
void reverse_u16_memory(u16* data, u32 count);
void reverse_s16_memory(s16* data, u32 count);
void reverse_u32_memory(u32* data, u32 count);
void reverse_s32_memory(s32* data, u32 count);
void reverse_u64_memory(u64* data, u32 count);
void reverse_s64_memory(s64* data, u32 count);

bool8 u8_memory_equals (const u8*  lhs, const u8*  rhs, u32 count);
bool8 s8_memory_equals (const s8*  lhs, const s8*  rhs, u32 count);
bool8 u16_memory_equals(const u16* lhs, const u16* rhs, u32 count);
bool8 s16_memory_equals(const s16* lhs, const s16* rhs, u32 count);
bool8 u32_memory_equals(const u32* lhs, const u32* rhs, u32 count);
bool8 s32_memory_equals(const s32* lhs, const s32* rhs, u32 count);
bool8 u64_memory_equals(const u64* lhs, const u64* rhs, u32 count);
bool8 s64_memory_equals(const s64* lhs, const s64* rhs, u32 count);

#define declare_memory_view_of(data_type)       \
    typedef struct data_type##_memory_view      \
    {                                           \
        const data_type*    data;               \
        u32                 size;               \
    } data_type##_memory_view;

declare_memory_view_of(s8);
declare_memory_view_of(u8);
declare_memory_view_of(s16);
declare_memory_view_of(u16);
declare_memory_view_of(s32);
declare_memory_view_of(u32);
declare_memory_view_of(s64);
declare_memory_view_of(u64);

// Performs allocations/deallocations with the current process' default heap. (e.g. GetProcessHeap() on Win32).
void* default_heap_allocate(u64 size);
void  default_heap_deallocate(void* ptr);

void* heap_allocate(void* heap, u64 size);
void  heap_deallocate(void* heap, void* ptr);

typedef struct allocator
{
    void*   user;
    void*   (*allocate)(void* user, u64 size);
    void    (*deallocate)(void* user, void* ptr);
} allocator;

void*   allocate(allocator* allocator, u64 size);
void    deallocate(allocator* allocator, void* ptr);

u8* dump_u8_memory(const u8* in, u32 count, allocator* allocator);
s8* dump_s8_memory(const s8* in, u32 count, allocator* allocator);

#ifdef CUTILE_ALLOCATOR_ANALYZER
    typedef struct allocation_info
    {
        bool8       available;
        void*       address;
        u64         size;
        u32         line;
        const char* filename;
    } allocation_info;

    typedef struct allocation_table
    {
        u64 count;
        u64 size;
        allocation_info* data;
    } allocation_table;

    extern allocation_table allocations_info;
#endif // CUTILE_ALLOCATOR_ANALYZER

allocator create_heap_allocator(void* heap);
allocator create_default_heap_allocator();

extern allocator global_default_heap_allocator;
void initialize_global_default_heap_allocator();

#ifdef CUTILE_IMPLEM

    #ifdef _WIN32
        #include <Windows.h>
    #endif

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

    void* default_heap_allocate(u64 size)
    {
        #ifdef _WIN32
            return heap_allocate(GetProcessHeap(), size);
        #endif
    }
    void default_heap_deallocate(void* ptr)
    {
        #ifdef _WIN32
            heap_deallocate(GetProcessHeap(), ptr);
        #endif
    }

    u8* dump_u8_memory(const u8* in, u32 count, allocator* allocator)
    {
        u8* result = (u8*)allocate(allocator, count);
        copy_u8_memory(result, in, count);
        return result;
    }
    s8* dump_s8_memory(const s8* in, u32 count, allocator* allocator)
    {
        s8* result = (s8*)allocate(allocator, count);
        copy_s8_memory(result, in, count);
        return result;
    }

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
    #endif // CUTILE_ALLOCATOR_ANALYZER

    void* heap_allocate(void* heap, u64 size)
    {
        #ifdef _WIN32
            return HeapAlloc(heap, 0, size);
        #endif
    }

    void heap_deallocate(void* heap, void* ptr)
    {
        #ifdef _WIN32
            HeapFree(heap, 0, ptr);
        #endif
    }

    allocator create_heap_allocator(void* heap)
    {
        allocator res =
        {
            #ifdef _WIN32
                .user = heap,
            #endif
            .allocate = &heap_allocate,
            .deallocate = &heap_deallocate
        };
        return res;
    }

    allocator create_default_heap_allocator()
    {
        allocator res =
        {
            #ifdef _WIN32
                .user = GetProcessHeap(),
            #endif
            .allocate = &heap_allocate,
            .deallocate = &heap_deallocate
        };
        return res;
    }

    allocator global_default_heap_allocator;
    void initialize_global_default_heap_allocator() { global_default_heap_allocator = create_default_heap_allocator(); }

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
                allocation_info* new_data = (allocation_info*) default_heap_allocate(sizeof(allocation_info) * allocations_info.size);
                copy_u8_memory((u8*)new_data, (u8*)allocations_info.data, sizeof(allocation_info) * allocations_info.count);
                default_heap_deallocate(allocations_info.data);
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
#endif // CUTILE_ALLOCATOR_ANALYZER

#endif // !CUTILE_MEMORY_H
