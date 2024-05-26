#ifndef CUTILE_ARRAY_H

    #include "memory.h"

    #define cutile_fixed_array_length_m(arr)  (sizeof(arr)/sizeof(arr[0]))

    // Generates a struct representing a contiguous collection of elements of the same type.
    #define cutile_generate_array_struct_m(type)    \
        typedef struct type##_array                 \
        {                                           \
            type*              data;                \
            u32                count;               \
            u32                size;                \
            u32                increment;           \
            cutile_allocator*  allocator;           \
        } type##_array;                             \

    #define cutile_generate_array_content_m(type)   \
            type*              data;                \
            u32                count;               \
            u32                size;                \
            u32                increment;           \
            cutile_allocator*  allocator;           \

    // Generate some basic array types.
    cutile_generate_array_struct_m(s8);
    cutile_generate_array_struct_m(u8);
    cutile_generate_array_struct_m(s16);
    cutile_generate_array_struct_m(u16);
    cutile_generate_array_struct_m(s32);
    cutile_generate_array_struct_m(u32);
    cutile_generate_array_struct_m(s64);
    cutile_generate_array_struct_m(u64);

    #define cutile_array_m(type) type##_array

    #define cutile_create_array_m(type, _size, _increment, allocator_ptr, out)  \
    {                                                                           \
        out.data = cutile_allocate_many_T_m(allocator_ptr, type, _size);        \
        out.count = 0;                                                          \
        out.size = _size;                                                       \
        out.increment = _increment;                                             \
        out.allocator = allocator_ptr;                                          \
    }                                                                           \

    #define cutile_create_array__m(type, size, increment, out) cutile_create_array_m(type, size, increment, cutile_default_allocator, out)

    #define cutile_destroy_array_m(array) deallocate_m((array).allocator, (array).data)

    #define cutile_destroy_array_deeply_m(array, destroy_array_elem_func)   \
    {                                                                       \
        for (u32 i = 0; i < (array).count; ++i)                             \
        {                                                                   \
            destroy_array_elem_func(&((array).data[i]));                    \
        }                                                                   \
        cutile_destroy_array_m(array);                                      \
    }

    #define cutile_resize_array_m(type, array, new_size)                            \
    {                                                                               \
        type* new_data =                                                            \
            (type*)cutile_allocate_m((array).allocator, sizeof(type) * (new_size)); \
        if (new_size < (array).count)                                               \
        {                                                                           \
            for (u32 i = 0; i < new_size; ++i)                                      \
            {                                                                       \
                new_data[i] = (array).data[i];                                      \
            }                                                                       \
            (array).count = new_size;                                               \
        }                                                                           \
        else                                                                        \
        {                                                                           \
            for (u32 i = 0; i < array.count; ++i)                                   \
            {                                                                       \
                new_data[i] = (array).data[i];                                      \
            }                                                                       \
        }                                                                           \
        cutile_deallocate_m((array).allocator, (array).data);                       \
        (array).data = new_data;                                                    \
        (array).size = new_size;                                                    \
    }                                                                               \
 
    #define cutile_array_push_m(type, array, val)                                   \
    {                                                                               \
        if (array.count >= (array).size)                                            \
        {                                                                           \
            cutile_resize_array_m(type, array, (array).count + array.increment);    \
        }                                                                           \
        (array).data[(array).count] = val;                                          \
        (array).count++;                                                            \
    }                                                                               \

    #define cutile_array_push_empty_m(type, array)                          \
    {                                                                       \
        if ((array).count >= (array).size)                                  \
        {                                                                   \
            cutile_resize_array(array, (array).count + array.increment);    \
        }                                                                   \
        (array).count++;                                                    \
    }                                                                       \

    #define cutile_array_push_repeated_m(type, array, val, _count)              \
    {                                                                           \
        if (array.count + _count >= array.size)                                 \
        {                                                                       \
            cutile_resize_array_m(type, array, (array).count + (_count));       \
        }                                                                       \
        for (u32 i = 0; i < _count; ++i) (array).data[(array).count++] = val;   \
    }                                                                           \

    #define cutile_array_push_buffer_m(type, array, buf, n)                 \
    {                                                                       \
        if (array.count + n >= (array).size)                                \
        {                                                                   \
            cutile_resize_array_m(type, (array), (array).count + (n));      \
        }                                                                   \
        for (u32 i = 0; i < n; ++i) (array).data[(array).count++] = buf[i]; \
    }                                                                       \

    #define cutile_array_push_array_m(type, out_array, in_array) cutile_array_push_buffer_m(type, out_array, in_array.data, in_array.count)

    #define cutile_array_pop_m(array) array.count--

    #define cutile_array_remove_m(array, index)         \
    {                                                   \
        for (u32 i = index; i < array.count - 1; ++i)   \
        {                                               \
            (array).data[i] = (array).data[i + 1];      \
        }                                               \
        array.count -= 1;                               \
    }                                                   \

    #define cutile_clear_array_m(array) array.count = 0

    #define cutile_clear_array_deeply_m(array, destroy_array_elem_func) \
    {                                                                   \
        for (u32 i = 0; i < array.count; ++i)                           \
        {                                                               \
            destroy_array_elem_func(&(array).data[i]);                  \
        }                                                               \
        cutile_clear_array_m(array);                                    \
    }

    #define cutile_reverse_array_slice_m(type, array, offset, count)    \
    {                                                                   \
        u32 end = (count) * 0.5;                                        \
        for (u32 i = offset; i < end; ++i)                              \
        {                                                               \
            type dump = array.data[i];                                  \
            u32 rhs_i = (count) - 1 - i;                                \
            (array).data[i] = (array).data[rhs_i];                      \
            (array).data[rhs_i] = dump;                                 \
        }                                                               \
    }                                                                   \

    #define cutile_reverse_array_m(type, array) cutile_reverse_array_slice_m(type, array, 0, array.count);

    #ifndef NO_CUTILE_SHORT_INTERFACE_NAMES
        #define fixed_array_length_m(arr) cutile_fixed_array_length_m(arr)

        #define array_m(type)                                             cutile_array_m(type)
        #define create_array_m(type, size, increment, allocator_ptr, out) cutile_create_array_m(type, size, increment, allocator_ptr, out)
        #define destroy_array_m(array)                                    cutile_destroy_array_m(array)
        #define destroy_array_deeply_m(array, destroy_array_elem_func)    cutile_destroy_array_deeply_m(array, destroy_array_elem_func)
        #define resize_array_m(type, array, new_size)                     cutile_resize_array_m(type, array, new_size)
        #define array_push_m(type, array, val)                            cutile_array_push_m(type, array, val)
        #define array_push_empty_m(type, array)                           cutile_array_push_empty_m(type, array)
        #define array_push_repeated_m(type, array, val, count)            cutile_array_push_repeated_m(type, array, val, count)
        #define array_push_buffer_m(type, array, buf, n)                  cutile_array_push_buffer_m(type, array, buf, n)
        #define array_push_array_m(type, out_array, in_array)             cutile_array_push_array_m(type, out_array, in_array)
        #define array_pop_m(array)                                        cutile_array_pop_m(array)
        #define array_remove_m(array, index)                              cutile_array_remove_m(array, index)
        #define clear_array_m(array)                                      cutile_clear_array_m(array)
        #define clear_array_deeply_m(array, destroy_array_elem_func)      cutile_clear_array_deeply_m(array, destroy_array_elem_func)
        #define reverse_array_slice_m(type, array, offset, count)         cutile_reverse_array_slice_m(type, array, offset, count)
        #define reverse_array_m(type, array)                              cutile_reverse_array_m(type, array)
    #endif

    #define CUTILE_ARRAY_H
#endif
