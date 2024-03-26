#ifndef CUTILE_ARRAY_H
#define CUTILE_ARRAY_H

#include "num_types.h"
#include "memory.h"

// Deprecated, use fixed_array_length_m instead.
#define fixed_array_length(arr) (sizeof(arr)/sizeof(arr[0]))

#define fixed_array_length_m(arr) (sizeof(arr)/sizeof(arr[0]))

#define array_m(type) type##_array

// Generates an array struct of the given type.
// Calling declare_array_of_m(type) macro will generate the following API:
/*
   (type)_array
   {
        data:      type*
        count:     u32
        size:      u32
        increment: u32
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
        type##_array array;                                                                                     \
        init_array_macro(array, type, size, increment, allocator);                                              \
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
        type* new_data = (type*)allocate(array->allocator,  sizeof(type) * new_size);                           \
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
        array_push_empty_m(array, type);                                                                        \
    }                                                                                                           \
                                                                                                                \
    maybe_inline void         type##_array_push_repeated(type##_array* array, type val, u32 count)              \
    {                                                                                                           \
        array_push_repeated_macro(array, type, val, count);                                                     \
    }                                                                                                           \
                                                                                                                \
    maybe_inline void         type##_array_push_buffer(type##_array* array, type* buf, u32 n)                   \
    {                                                                                                           \
        array_push_buffer_macro(array, type, buf, n);                                                           \
    }                                                                                                           \
                                                                                                                \
    maybe_inline void         type##_array_push_array(type##_array* out, type##_array* in)                      \
    {                                                                                                           \
        array_push_array_macro(out, type, in);                                                                  \
    }                                                                                                           \
                                                                                                                \
    maybe_inline void         type##_array_pop(type##_array* array)                                             \
    {                                                                                                           \
        array_pop_macro(array);                                                                                 \
    }                                                                                                           \
                                                                                                                \
    maybe_inline void         type##_array_remove(type##_array* array, u32 index)                               \
    {                                                                                                           \
        array_remove_macro(array, index);                                                                       \
    }                                                                                                           \
                                                                                                                \
    maybe_inline void         clear_##type##_array(type##_array* array)                                         \
    {                                                                                                           \
        clear_array_macro(array);                                                                               \
    }                                                                                                           \
                                                                                                                \
    maybe_inline void         clear_##type##_array_deeply(type##_array* arr, void (*destroy_func)(type* elem))  \
    {                                                                                                           \
        clear_array_deeply_macro(arr, destroy_func);                                                            \
    }                                                                                                           \
                                                                                                                \
    maybe_inline void         reverse_##type##_array(type##_array* array)                                       \
    {                                                                                                           \
        reverse_array_macro(array, type);                                                                       \
    }                                                                                                           \
                                                                                                                \
    maybe_inline void         reverse_##type##_array_slice(type##_array* array, u32 offset, u32 count)          \
    {                                                                                                           \
        reverse_array_slice_macro(array, type, offset, count);                                                  \
    }                                                                                                           \

CUTILE_C_API void* allocate(allocator*, u64);

#define init_array_macro(array, data_type, _size, _increment, _allocator)       \
{                                                                               \
    CUTILE_ASSERT(_increment);                                                  \
        array.data = (data_type*)allocate(allocator, sizeof(data_type) * size); \
    array.size = _size;                                                         \
    array.count = 0;                                                            \
    array.increment = _increment;                                               \
    array.allocator = _allocator;                                               \
}

CUTILE_C_API void deallocate(allocator*, void*);

#define destroy_array_m(array_ptr) destroy_array_macro(array_ptr)
#define destroy_array_macro(array_ptr)                      \
{                                                           \
    deallocate((array_ptr)->allocator, (array_ptr)->data);  \
}

#define destroy_array_deeply_macro(array_ptr, destroy_array_elem_func)  \
    {                                                                   \
        for (u32 i = 0; i < array_ptr->count; ++i)                      \
        {                                                               \
            destroy_array_elem_func(&(array_ptr)->data[i]);             \
        }                                                               \
        destroy_array_macro(array_ptr);                                 \
    }

#define resize_array_macro(array_ptr, data_type, new_size)                                              \
    {                                                                                                   \
        data_type* new_data =                                                                           \
            (data_type*)allocate(array_ptr->allocator, sizeof(data_type) * new_size);                   \
        if (new_size < array_ptr->count)                                                                \
        {                                                                                               \
            for (u32 i = 0; i < new_size; ++i)                                                          \
            {                                                                                           \
                new_data[i] = array_ptr->data[i];                                                       \
            }                                                                                           \
            array_ptr->count = new_size;                                                                \
        }                                                                                               \
        else                                                                                            \
        {                                                                                               \
            for (u32 i = 0; i < array_ptr->count; ++i)                                                  \
            {                                                                                           \
                new_data[i] = array_ptr->data[i];                                                       \
            }                                                                                           \
        }                                                                                               \
        deallocate(array_ptr->allocator, array_ptr->data);                                              \
        array_ptr->data = new_data;                                                                     \
        array_ptr->size = new_size;                                                                     \
    }

#define array_push_macro(array_ptr, type, val)                                              \
    {                                                                                       \
        CUTILE_ASSERT(array_ptr->increment);                                                \
        if (array_ptr->count >= array_ptr->size)                                            \
        {                                                                                   \
            resize_array_macro(array_ptr, type, array_ptr->count + array_ptr->increment);   \
        }                                                                                   \
        array_ptr->data[array_ptr->count] = val;                                            \
        array_ptr->count++;                                                                 \
    }

#define array_push_empty_m(array_ptr, type)                                                 \
    {                                                                                       \
        CUTILE_ASSERT(array_ptr->increment);                                                \
        if (array_ptr->count >= array_ptr->size)                                            \
        {                                                                                   \
            resize_array_macro(array_ptr, type, array_ptr->count + array_ptr->increment);   \
        }                                                                                   \
        u32 index = array_ptr->count;                                                       \
        array_ptr->count++;                                                                 \
        return &array_ptr->data[index];                                                     \
    }

#define array_push_repeated_macro(array_ptr, type, val, _count)                                     \
    {                                                                                               \
        if (array_ptr->count + _count >= array_ptr->size)                                           \
        {                                                                                           \
            resize_array_macro(array_ptr, type, array_ptr->count + _count);                         \
        }                                                                                           \
        for (u32 i = 0; i < _count; ++i) array_ptr->data[array_ptr->count++] = val;                 \
    }

#define array_push_buffer_macro(array_ptr, type, buf, n)                                        \
    {                                                                                           \
        if (array_ptr->count + n >= array_ptr->size)                                            \
        {                                                                                       \
            resize_array_macro(array_ptr, type, array_ptr->count + n);                          \
        }                                                                                       \
        for (u32 i = 0; i < n; ++i) array_ptr->data[array_ptr->count++] = buf[i];               \
    }

#define array_push_array_macro(out, type, in) array_push_buffer_macro(out, type, in->data, in->count)

#define array_pop_macro(array_ptr) array_ptr->count -= 1

#define array_remove_macro(array_ptr, index)                \
    {                                                       \
        for (u32 i = index; i < array_ptr->count - 1; ++i)  \
        {                                                   \
            array_ptr->data[i] = array_ptr->data[i + 1];    \
        }                                                   \
        array_ptr->count -= 1;                              \
    }

#define clear_array_macro(array_ptr) array_ptr->count = 0;

#define clear_array_deeply_macro(array_ptr, destroy_array_elem_func)    \
    {                                                                   \
        for (u32 i = 0; i < array_ptr->count; ++i)                      \
        {                                                               \
            destroy_array_elem_func(&array_ptr->data[i]);               \
        }                                                               \
        clear_array_macro(array_ptr);                                   \
    }

#define reverse_array_macro(array_ptr, type) reverse_array_slice_macro(array_ptr, type, 0, array->count)

#define reverse_array_slice_macro(array_ptr, type, offset, count)       \
    {                                                                   \
        u32 end = count * 0.5;                                          \
        for (u32 i = offset; i < end; ++i)                              \
        {                                                               \
            type dump = array_ptr->data[i];                             \
            u32 rhs_i = count - 1 - i;                                  \
            array_ptr->data[i] = array_ptr->data[rhs_i];                \
            array_ptr->data[rhs_i] = dump;                              \
        }                                                               \
    }

// Generate some array types.
declare_array_of_m(s8);
declare_array_of_m(u8);
declare_array_of_m(s16);
declare_array_of_m(u16);
declare_array_of_m(s32);
declare_array_of_m(u32);
declare_array_of_m(s64);
declare_array_of_m(u64);

typedef struct array_view
{
    const u8* data;
    u32       count;
} array_view;

#define declare_array_view_m(type) typedef struct type##_array_view { const type* data; u32 count; } type##_array_view

#define array_view_m(type) type##_array_view

#define view_from_fixed_size_array_m(arr) { (u8*)arr, sizeof(arr)/sizeof(arr[0]) }
#define view_from_array_m(arr) { (u8*)arr.data, arr.count }

#endif // !CUTILE_ARRAY_H
