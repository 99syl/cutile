#ifndef CUTILE_MEMORY_H

    #include "num_types.h"

    CUTILE_C_API void fill_u8_memory(u8* data, u32 count, u8 value);
    CUTILE_C_API void fill_s8_memory(s8* data, u32 count, s8 value);
    CUTILE_C_API void fill_u16_memory(u16* data, u32 count, u16 value);
    CUTILE_C_API void fill_s16_memory(s16* data, u32 count, s16 value);
    CUTILE_C_API void fill_u32_memory(u32* data, u32 count, u32 value);
    CUTILE_C_API void fill_s32_memory(s32* data, u32 count, s32 value);
    CUTILE_C_API void fill_u64_memory(u64* data, u32 count, u64 value);
    CUTILE_C_API void fill_s64_memory(s64* data, u32 count, s64 value);
    
    CUTILE_C_API void copy_u8_memory(u8 *data, const u8* in, u32 count);
    CUTILE_C_API void copy_s8_memory(s8* data, const s8* in, u32 count);
    CUTILE_C_API void copy_u16_memory(u16* data, const u16* in, u32 count);
    CUTILE_C_API void copy_s16_memory(s16* data, const s16* in, u32 count);
    CUTILE_C_API void copy_u32_memory(u32* data, const u32* in, u32 count);
    CUTILE_C_API void copy_s32_memory(s32* data, const s32* in, u32 count);
    CUTILE_C_API void copy_u64_memory(u64* data, const u64* in, u32 count);
    CUTILE_C_API void copy_s64_memory(s64* data, const s64* in, u32 count);
    CUTILE_C_API void copy_f32_memory(f32* data, const f32* in, u32 count);
    CUTILE_C_API void copy_f64_memory(f64* data, const f64* in, u32 count);
    
    CUTILE_C_API void reverse_u8_memory(u8* data, u32 count);
    CUTILE_C_API void reverse_s8_memory(s8* data, u32 count);
    CUTILE_C_API void reverse_u16_memory(u16* data, u32 count);
    CUTILE_C_API void reverse_s16_memory(s16* data, u32 count);
    CUTILE_C_API void reverse_u32_memory(u32* data, u32 count);
    CUTILE_C_API void reverse_s32_memory(s32* data, u32 count);
    CUTILE_C_API void reverse_u64_memory(u64* data, u32 count);
    CUTILE_C_API void reverse_s64_memory(s64* data, u32 count);
    
    CUTILE_C_API bool8 u8_memory_equals (const u8*  lhs, const u8*  rhs, u32 count);
    CUTILE_C_API bool8 s8_memory_equals (const s8*  lhs, const s8*  rhs, u32 count);
    CUTILE_C_API bool8 u16_memory_equals(const u16* lhs, const u16* rhs, u32 count);
    CUTILE_C_API bool8 s16_memory_equals(const s16* lhs, const s16* rhs, u32 count);
    CUTILE_C_API bool8 u32_memory_equals(const u32* lhs, const u32* rhs, u32 count);
    CUTILE_C_API bool8 s32_memory_equals(const s32* lhs, const s32* rhs, u32 count);
    CUTILE_C_API bool8 u64_memory_equals(const u64* lhs, const u64* rhs, u32 count);
    CUTILE_C_API bool8 s64_memory_equals(const s64* lhs, const s64* rhs, u32 count);
    
    CUTILE_C_API b8 memory_equals(u8* lhs, u64 lhs_size, u8* rhs, u64 rhs_size);
    
    // Size is in data_type size unit.
    #define declare_memory_view_of_m(data_type)      \
        typedef struct data_type##_memory_view       \
        {                                            \
            const data_type*    data;                \
            u64                 size;                \
        } data_type##_memory_view;                   \
    
    #define memory_view_m(data_type) data_type##_memory_view
    
    declare_memory_view_of_m(s8);
    declare_memory_view_of_m(u8);
    declare_memory_view_of_m(s16);
    declare_memory_view_of_m(u16);
    declare_memory_view_of_m(s32);
    declare_memory_view_of_m(u32);
    declare_memory_view_of_m(s64);
    declare_memory_view_of_m(u64);
    
    #define memory_view_from_fixed_size_array_m(arr)                \
        {                                                           \
            .data = arr,                                            \
            .size = fixed_array_length_m(arr)                       \
        };                                                          \
        
    // Performs allocations/deallocations with the current process' default heap. (e.g. GetProcessHeap() on Win32).
    CUTILE_C_API void* default_heap_allocate(u64 size);
    CUTILE_C_API void  default_heap_deallocate(void* ptr);
    
    CUTILE_C_API void* heap_allocate(void* heap, u64 size);
    CUTILE_C_API void  heap_deallocate(void* heap, void* ptr);
    
    typedef struct allocator allocator;
    typedef struct allocator
    {
        void* (*allocate)(allocator*, u64 size);
        void  (*deallocate)(allocator*, void* ptr);
    } allocator;
    
    maybe_inline void* allocate(allocator* allocator, u64 size);
    maybe_inline void  deallocate(allocator* allocator, void* ptr);
    
    // NOTE: "struct" keyword in cast in front of allocator_ptr because MSVC could not tell if allocator was a variable or a type !!!
    #define allocate_m(allocator_ptr, T) (T*)(allocate((struct allocator*)allocator_ptr, sizeof(T)))
    #define allocate_many_m(allocator_ptr, T, count) (T*)(allocate(((struct allocator*)allocator_ptr), sizeof(T) * count))
    
    #define declare_allocator_m allocator __allocator_base
    
    // TODO: Implement platform independant heap allocator.
    typedef struct
    {
        declare_allocator_m;
    
        void* heap;
    } heap_allocator;
    
    CUTILE_C_API heap_allocator create_heap_allocator(void* heap);
    CUTILE_C_API heap_allocator create_default_heap_allocator();
    
    typedef struct
    {
        declare_allocator_m;
    
        u8*           buffer;
        u64           buffer_size;
        u64           offset;
    } arena_allocator;
    
    CUTILE_C_API arena_allocator create_arena_allocator(u8* buffer, u64 buffer_size);
    CUTILE_C_API void        reset_arena_allocator(arena_allocator*);
    
    #ifdef CUTILE_DEFAULT_ALLOCATOR_NAME
        CUTILE_C_API allocator* CUTILE_DEFAULT_ALLOCATOR_NAME;
    #else
        CUTILE_C_API allocator* default_allocator;
    #endif
    
    #ifdef CUTILE_IMPLEM
        #ifdef _WIN32
            #include <windows.h>
        #else 
            #include <stdlib.h>  // malloc, free. TODO: Implement for other platforms instead of using lib c.
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
    
        void copy_f32_memory(f32* data, const f32* in, u32 count)
        {
            for (u32 i = 0; i < count; ++i) data[i] = in[i];
        }
    
        void copy_f64_memory(f64* data, const f64* in, u32 count)
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
    
        b8 memory_equals(u8* lhs, u64 lhs_size, u8* rhs, u64 rhs_size)
        {
            if (lhs_size != rhs_size) return b8_false;
            for (u32 i = 0; i < rhs_size; ++i)
            {
                if (lhs[i] != rhs[i]) return b8_false;
            }
            return b8_true;
        }
    
        void* default_heap_allocate(u64 size)
        {
            #ifdef _WIN32
                return heap_allocate(GetProcessHeap(), size);
            #else
                return heap_allocate(nullptr, size); // TODO: Implement for other platforms.
            #endif
        }
    
        void default_heap_deallocate(void* ptr)
        {
            #ifdef _WIN32
                heap_deallocate(GetProcessHeap(), ptr);
            #else
                heap_deallocate(nullptr, ptr); // TODO: Implement for other platforms.
            #endif
        }
    
        void* heap_allocate(void* heap, u64 size)
        {
            void* ptr;
            #ifdef _WIN32
                ptr = HeapAlloc(heap, 0, size);
            #else
                ptr = malloc(size); // TODO: Implement for other platforms.
            #endif
    
            return ptr;
        }
    
        void heap_deallocate(void* heap, void* ptr)
        {
            #ifdef _WIN32
                HeapFree(heap, 0, ptr);
            #else
                free(ptr); // TODO: Implement for other platforms.
            #endif
        }
    
        internal void* heap_allocator_allocate(allocator* opaque_allocator, u64 size)
        {
        heap_allocator* allocator = (heap_allocator*)opaque_allocator;
        return heap_allocate(allocator->heap, size);
        }
        internal void heap_allocator_deallocate(allocator* opaque_allocator, void* ptr)
        {
        heap_allocator* allocator = (heap_allocator*)opaque_allocator;
        heap_deallocate(allocator->heap, ptr);
        }
    
        maybe_inline heap_allocator create_heap_allocator(void* heap)
        {
            heap_allocator res =
            {
                .__allocator_base = {.allocate = &heap_allocator_allocate, .deallocate = &heap_allocator_deallocate },
                #ifdef _WIN32
                    .heap = heap
                #endif
            };
            return res;
        }
    
        heap_allocator create_default_heap_allocator()
        {
            #ifdef _WIN32
                return create_heap_allocator(GetProcessHeap());
        #else
                return create_heap_allocator(nullptr);
            #endif
        }
    
        internal void* __arena_allocate(allocator* opaque_arena, u64 size)
        {
        arena_allocator* arena = (arena_allocator*)opaque_arena;
            if (arena->offset + size >= arena->buffer_size) return nullptr;
            void* ptr = arena->buffer + arena->offset;
            arena->offset += size;
            return ptr;
        }
    
        internal void __arena_deallocate(allocator* opaque_arena, void* f)
        {
        }
    
        arena_allocator create_arena_allocator(u8* buffer, u64 buffer_size)
        {
            arena_allocator result =
            {
            { &__arena_allocate, &__arena_deallocate },
                buffer, buffer_size, 0
            };
            return result;
        }
    
        void reset_arena_allocator(arena_allocator* arena)
        {
            arena->offset = 0;
        }
    
    #endif // CUTILE_IMPLEM
    
    maybe_inline void* allocate(allocator* allocator, u64 size)
    {
        return allocator->allocate(allocator, size);
    }
    
    maybe_inline void deallocate(allocator* allocator, void* ptr)
    {
        allocator->deallocate(allocator, ptr);
    }
    
    #define CUTILE_MEMORY_H
#endif
