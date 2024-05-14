#ifndef CUTILE_ARRAY_H

    #include "memory.h"

    #define fixed_array_length_m(arr) (sizeof(arr)/sizeof(arr[0]))
    
    #define array_m(type) type##_array
    
    // Generates an struct representing an array.
    // The represented array is a contiguous collection of elements of the same type.
    // Calling declare_array_of_m(type) macro will generate the following API:
    /*
       (type)_array
       {
            data:      type*
            count:     u32
            size:      u32
            increment: u32        // How much the array must increase its buffer when needed (in type size unit).
            allocator: allocator*
       }

       create_(type)_array: (size: u32, increment: u32, allocator: allocator*) -> (type)_array
       TODO: Continue documentation...
    */
    #define declare_array_of_m(type)                                                                                \
        typedef struct type##_array                                                                                 \
        {                                                                                                           \
            type*       data;                                                                                       \
            u32         count;                                                                                      \
            u32         size;                                                                                       \
            u32         increment;                                                                                  \
            allocator*  allocator;                                                                                  \
        } type##_array;                                                                                             \
                                                                                                                    \
        maybe_inline type##_array create_##type##_array(u32 size, u32 increment, allocator* allocator)              \
        {                                                                                                           \
            CUTILE_ASSERT(increment);                                                                               \
            type##_array array;                                                                                     \
            array.data = allocate_many_m(allocator, type, size);                                                    \
            array.count = 0;                                                                                        \
            array.size = size;                                                                                      \
            array.increment = increment;                                                                            \
            array.allocator = allocator;                                                                            \
            return array;                                                                                           \
        }                                                                                                           \
                                                                                                                    \
        maybe_inline void         destroy_##type##_array(type##_array* array)                                       \
        {                                                                                                           \
            deallocate(array->allocator, array->data);                                                              \
        }                                                                                                           \
                                                                                                                    \
        maybe_inline void         destroy_##type##_array_deeply(type##_array* arr, void (*destroy_func)(type* elem))\
        {                                                                                                           \
            for (u32 i = 0; i < arr->count; ++i)                                                                    \
            {                                                                                                       \
                destroy_func(&(arr->data[i]));                                                                      \
            }                                                                                                       \
            destroy_##type##_array(arr);                                                                            \
        }                                                                                                           \
                                                                                                                    \
        maybe_inline void         resize_##type##_array(type##_array* array, u32 new_size)                          \
        {                                                                                                           \
            type* new_data = (type*)allocate(array->allocator, sizeof(type) * new_size);                            \
            if (new_size < array->count)                                                                            \
            {                                                                                                       \
                for (u32 i = 0; i < new_size; ++i)                                                                  \
                {                                                                                                   \
                    new_data[i] = array->data[i];                                                                   \
                }                                                                                                   \
                array->count = new_size;                                                                            \
            }                                                                                                       \
            else                                                                                                    \
            {                                                                                                       \
                for (u32 i = 0; i < array->count; ++i)                                                              \
                {                                                                                                   \
                    new_data[i] = array->data[i];                                                                   \
                }                                                                                                   \
            }                                                                                                       \
            deallocate(array->allocator, array->data);                                                              \
            array->data = new_data;                                                                                 \
            array->size = new_size;                                                                                 \
        }                                                                                                           \
                                                                                                                    \
        maybe_inline void         type##_array_push(type##_array* array, type val)                                  \
        {                                                                                                           \
            CUTILE_ASSERT(array->increment);                                                                        \
            if (array->count >= array->size)                                                                        \
            {                                                                                                       \
                resize_##type##_array(array, array->count + array->increment);                                      \
            }                                                                                                       \
            array->data[array->count] = val;                                                                        \
            array->count++;                                                                                         \
        }                                                                                                           \
                                                                                                                    \
        maybe_inline type*        type##_array_push_empty(type##_array* array)                                      \
        {                                                                                                           \
            CUTILE_ASSERT(array->increment);                                                                        \
            if (array->count >= array->size)                                                                        \
                resize_##type##_array(array, array->count + array->increment);                                      \
            u32 index = array->count;                                                                               \
            array->count++;                                                                                         \
            return &array->data[index];                                                                             \
        }                                                                                                           \
                                                                                                                    \
        maybe_inline void         type##_array_push_repeated(type##_array* array, type val, u32 count)              \
        {                                                                                                           \
            if (array->count + count >= array->size)                                                                \
            {                                                                                                       \
                resize_##type##_array(array, array->count + count);                                                 \
            }                                                                                                       \
            for (u32 i = 0; i < count; ++i) array->data[array->count++] = val;                                      \
        }                                                                                                           \
                                                                                                                    \
        maybe_inline void         type##_array_push_buffer(type##_array* array, type* buf, u32 n)                   \
        {                                                                                                           \
            if (array->count + n >= array->size)                                                                    \
            {                                                                                                       \
                resize_##type##_array(array, array->count + n);                                                     \
            }                                                                                                       \
            for (u32 i = 0; i < n; ++i) array->data[array->count++] = buf[i];                                       \
        }                                                                                                           \
                                                                                                                    \
        maybe_inline void         type##_array_push_array(type##_array* out, type##_array* in)                      \
        {                                                                                                           \
            type##_array_push_buffer(out, in->data, in->count);                                                     \
        }                                                                                                           \
                                                                                                                    \
        maybe_inline void         type##_array_pop(type##_array* array)                                             \
        {                                                                                                           \
            array_pop_m(array);                                                                                     \
        }                                                                                                           \
                                                                                                                    \
        maybe_inline void         type##_array_remove(type##_array* array, u32 index)                               \
        {                                                                                                           \
            array_remove_m(array, index);                                                                           \
        }                                                                                                           \
                                                                                                                    \
        maybe_inline void         clear_##type##_array(type##_array* array)                                         \
        {                                                                                                           \
            clear_array_m(array);                                                                                   \
        }                                                                                                           \
                                                                                                                    \
        maybe_inline void         clear_##type##_array_deeply(type##_array* arr, void (*destroy_func)(type* elem))  \
        {                                                                                                           \
            clear_array_deeply_m(arr, destroy_func);                                                                \
        }                                                                                                           \
                                                                                                                    \
        maybe_inline void         reverse_##type##_array_slice(type##_array* array, u32 offset, u32 count)          \
        {                                                                                                           \
            u32 end = count * 0.5;                                                                                  \
            for (u32 i = offset; i < end; ++i)                                                                      \
            {                                                                                                       \
                type dump = array->data[i];                                                                         \
                u32 rhs_i = count - 1 - i;                                                                          \
                array->data[i] = array->data[rhs_i];                                                                \
                array->data[rhs_i] = dump;                                                                          \
            }                                                                                                       \
        }                                                                                                           \
                                                                                                                    \
        maybe_inline void         reverse_##type##_array(type##_array* array)                                       \
        {                                                                                                           \
            reverse_##type##_array_slice(array, 0, array->count);                                                   \
        }                                                                                                           \

    maybe_inline void* allocate(allocator*, u64);

    // Some shortcut macros for generated array functions with declare_array_of_m macro:

    #define destroy_array_m(array_ptr) deallocate((array_ptr)->allocator, (array_ptr)->data);
    
    #define destroy_array_deeply_m(array_ptr, destroy_array_elem_func)      \
    {                                                                       \
        for (u32 i = 0; i < array_ptr->count; ++i)                          \
        {                                                                   \
            destroy_array_elem_func(&(array_ptr)->data[i]);                 \
        }                                                                   \
        destroy_array_m(array_ptr);                                         \
    }
    
    #define array_pop_m(array_ptr) array_ptr->count -= 1
    
    #define array_remove_m(array_ptr, index)                    \
    {                                                           \
        for (u32 i = index; i < array_ptr->count - 1; ++i)      \
        {                                                       \
            array_ptr->data[i] = array_ptr->data[i + 1];        \
        }                                                       \
        array_ptr->count -= 1;                                  \
    }
    
    #define clear_array_m(array_ptr) array_ptr->count = 0;
    
    #define clear_array_deeply_m(array_ptr, destroy_array_elem_func)    \
    {                                                                   \
        for (u32 i = 0; i < array_ptr->count; ++i)                      \
        {                                                               \
            destroy_array_elem_func(&array_ptr->data[i]);               \
        }                                                               \
        clear_array_m(array_ptr);                                       \
    }                                                                   \
    
    #if defined(__clang__) || defined(__GNUC__)
        #pragma GCC diagnostic ignored "-Wchanges-meaning"
    #endif

    // Generate some array types.
    declare_array_of_m(s8);
    declare_array_of_m(u8);
    declare_array_of_m(s16);
    declare_array_of_m(u16);
    declare_array_of_m(s32);
    declare_array_of_m(u32);
    declare_array_of_m(s64);
    declare_array_of_m(u64);
    
    #if defined(__clang__) || defined(__GNUC__)
        #pragma GCC diagnostic pop
    #endif

    typedef struct array_view
    {
        const u8* data;
        u32       count;
    } array_view;
    
    #define declare_array_view_m(type) typedef struct type##_array_view { const type* data; u32 count; } type##_array_view

    #define array_view_m(type) type##_array_view

    #define view_from_fixed_size_array_m(arr) { (u8*)arr, sizeof(arr)/sizeof(arr[0]) }
    #define view_from_array_m(arr) { (u8*)arr.data, arr.count }
    
    #define CUTILE_ARRAY_H
#endif
