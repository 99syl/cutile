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

void* allocate(allocator* allocator, u64 size);
void deallocate(allocator* allocator, void* ptr);

u8* dump_u8_memory(const u8* in, u32 count, allocator* allocator);
s8* dump_s8_memory(const s8* in, u32 count, allocator* allocator);

#ifdef CUTILE_ALLOCATOR_ANALYZER
    #include "./stacktrace.h"

    typedef enum allocation_info_status
    {
        allocation_info_status_available,
        allocation_info_status_unavailable,
        allocation_info_status_invalid_address,
        allocation_info_status_double_free,
    } allocation_info_status;

    typedef struct allocation_info
    {
        bool8                   available;
        void*                   address;
        u64                     size;

        stacktrace              stacktrace;
        stacktrace_array        free_stacktraces;
        
        allocation_info_status  status;
    } allocation_info;
    declare_array_of(allocation_info);

    typedef struct allocation_table
    {
        allocation_info_array   infos;
        u64                     total_allocated;
        u64                     total_freed;
        allocator*              allocator; // This allocator will be used to allocate data inside `add_new_alloc_info` or `try_remove_alloc_info`.
    } allocation_table;

    allocation_table create_allocation_table(allocator* allocator);
    void destroy_allocation_table(allocation_table* tbl);

    void    add_new_alloc_info(allocation_table* alloc_table, void* allocation_address, u64 size);
    b8      try_remove_alloc_info(allocation_table* alloc_table, void* allocation_address);
    
    extern allocation_table global_allocation_table;
    void init_global_allocation_table();
#else // !CUTILE_ALLOCATOR_ANALYZER
    #define create_allocation_table(a)
    #define destroy_allocation_table(a)
    #define add_new_alloc_info(a, b, c)
    #define try_remove_alloc_info(a, b)
    #define init_global_allocation_table()
#endif

allocator create_heap_allocator(void* heap);
allocator create_default_heap_allocator();

extern allocator global_default_heap_allocator;
void initialize_global_default_heap_allocator();

#ifdef CUTILE_IMPLEM

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
        
        // Same as `heap_allocate` but does not push any information into an allocation table. 
        internal void* heap_allocate_no_analyzer(void* null, u64 size)
        {
            #ifdef _WIN32
                persist HANDLE process_heap = GetProcessHeap();
                return HeapAlloc(process_heap, 0, size);
            #endif
        }
        // Same as `heap_deallocate` but does not push any information into an allocation table. 
        internal void heap_deallocate_no_analyzer(void* null, void* ptr)
        {
            #ifdef _WIN32
                persist HANDLE process_heap = GetProcessHeap();
                HeapFree(process_heap, 0, ptr);
            #endif
        }

        allocation_table create_allocation_table(allocator* allocator)
        {
            allocation_table tbl;
            tbl.infos = create_allocation_info_array(20, 20, allocator);
            tbl.total_allocated = 0;
            tbl.total_freed = 0;
            tbl.allocator = allocator;
            return tbl;
        }
        internal void destroy_allocation_info(allocation_info* inf)
        {
            destroy_stacktrace(&inf->stacktrace);
            destroy_stacktrace_array_deeply(&inf->free_stacktraces, &destroy_stacktrace);
        }
        void destroy_allocation_table(allocation_table* tbl)
        {
            destroy_allocation_info_array_deeply(&tbl->infos, &destroy_allocation_info);
            tbl->total_allocated = 0;
            tbl->total_freed = 0;
        }

        void add_new_alloc_info(allocation_table* alloc_table, void* allocation_address, u64 size)
        {
            allocation_info* alloc_info = nullptr;

            // Search for an available node.
            for (u32 i = 0; i < alloc_table->infos.count; ++i)
            {
                if (alloc_table->infos.data[i].status == allocation_info_status_available)
                {
                    alloc_info = &alloc_table->infos.data[i];
                    clear_stacktrace(&alloc_info->stacktrace);
                    clear_stacktrace_array_deeply(&alloc_info->free_stacktraces, &clear_stacktrace);
                    break;
                }
            }

            // No available node found so add a new one.
            if (alloc_info == nullptr)
            {
                allocation_info new_elem;
                new_elem.stacktrace = get_stacktrace(1, U16_MAX, alloc_table->allocator);
                new_elem.free_stacktraces = create_stacktrace_array(2, 2, alloc_table->allocator);
                allocation_info_array_push(&alloc_table->infos, new_elem);
                alloc_info = &alloc_table->infos.data[alloc_table->infos.count - 1];
            }
            else fill_stacktrace(&alloc_info->stacktrace, 1, U16_MAX);

            alloc_info->status = allocation_info_status_unavailable;
            alloc_info->address = allocation_address;
            alloc_info->size = size;

            alloc_table->total_allocated += size;
        }

        b8 try_remove_alloc_info(allocation_table* alloc_table, void* allocation_address)
        {
            stacktrace st = get_stacktrace(1, U16_MAX, alloc_table->allocator);
            for (u32 i = 0; i < alloc_table->infos.count; ++i)
            {
                allocation_info* alloc_info = &alloc_table->infos.data[i];
                if (alloc_info->address == allocation_address)
                {
                    stacktrace_array_push(&alloc_info->free_stacktraces, st);
                    switch (alloc_info->status)
                    {
                        case allocation_info_status_unavailable:
                            alloc_table->total_freed += alloc_info->size;
                            alloc_info->status = allocation_info_status_available;
                            return b8_true;
                        case allocation_info_status_available:
                        case allocation_info_status_double_free:
                            alloc_info->status = allocation_info_status_double_free;
                            return b8_false;
                        case allocation_info_status_invalid_address:
                            return b8_false;
                    }
                }
            }

            // Address never allocated! Invalid deallocation!
            allocation_info new_elem;
            new_elem.free_stacktraces = create_stacktrace_array(2, 2, alloc_table->allocator);
            new_elem.status = allocation_info_status_invalid_address;
            new_elem.address = allocation_address;
            new_elem.size = 0;
            stacktrace_array_push(&new_elem.free_stacktraces, st);
            allocation_info_array_push(&alloc_table->infos, new_elem);
            return b8_false;
        }

        internal allocator  global_allocation_table_allocator = { nullptr, &heap_allocate_no_analyzer, &heap_deallocate_no_analyzer };
        allocation_table    global_allocation_table;
        void init_global_allocation_table() { global_allocation_table = create_allocation_table(&global_allocation_table_allocator); }
        
    #endif // CUTILE_ALLOCATOR_ANALYZER
    
    void* allocate(allocator* allocator, u64 size)
    {
        return allocator->allocate(allocator->user, size);
    }
    void deallocate(allocator* allocator, void* ptr)
    {
        allocator->deallocate(allocator->user, ptr);
    }

    void* heap_allocate(void* heap, u64 size)
    {
        void* ptr;
        #ifdef _WIN32
            ptr = HeapAlloc(heap, 0, size);
        #endif

        #ifdef CUTILE_ALLOCATOR_ANALYZER
            add_new_alloc_info(&global_allocation_table, ptr, size);
        #endif // !CUTILE_ALLOCATOR_ANALYZER

        return ptr;
    }

    void heap_deallocate(void* heap, void* ptr)
    {
        #ifdef CUTILE_ALLOCATOR_ANALYZER
            if (!try_remove_alloc_info(&global_allocation_table, ptr)) return; // Returns here so it prevents double free/freeing invalid address when using CUTILE_ALLOCATOR_ANALYZER.
        #endif // !CUTILE_ALLOCATOR_ANALYZER
        
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

#endif // !CUTILE_MEMORY_H
