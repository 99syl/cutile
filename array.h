#ifndef CUTILE_ARRAY_H
#define CUTILE_ARRAY_H

#include "./num_types.h"

#define fixed_array_length(arr) sizeof(arr)/sizeof(arr[0])

typedef struct allocator allocator;

// Generates an array implementation of the given type.
// Calling `declare_array_of(type)` macro will generate the following API:
/*

   (type)_array
   {
        data: type*
        count: u32
        size: u32
        increment: u32
        allocator: allocator*
   }

   create_(type)_array: (size: u32, increment: u32, allocator: allocator*) -> (type)_array
   TODO: Continue documentation...
*/
#define declare_array_of(type)          \
    typedef struct type##_array         \
    {                                   \
        type*       data;               \
        u32         count;              \
        u32         size;               \
        u32         increment;          \
        allocator*  allocator;          \
    } type##_array;                     \
    force_inline type##_array create_##type##_array(u32 size, u32 increment, allocator* allocator) \
    {                                                                   \
        type##_array array;                                             \
        init_array_macro(array, type, size, increment, allocator);      \
        return array;                                                   \
    }                                                                   \
    force_inline void destroy_##type##_array(type##_array* array) { destroy_array_macro(array); } \
    force_inline void destroy_##type##_array_deeply(type##_array* array, void (*destroy_elem_func)(type* elem)) { destroy_array_deeply_macro(array, destroy_elem_func); } \
    force_inline void resize_##type##_array(type##_array* array, u32 new_size) { resize_array_macro(array, type, new_size); } \
    force_inline void type##_array_push(type##_array* array, type val) { array_push_macro(array, type, val); } \
    force_inline void type##_array_push_repeated(type##_array* array, type val, u32 count) { array_push_repeated_macro(array, type, val, count); } \
    force_inline void type##_array_push_buffer(type##_array* array, type* buf, u32 n) { array_push_buffer_macro(array, type, buf, n); } \
    force_inline void type##_array_push_array(type##_array* out, const type##_array* in) { array_push_array_macro(out, type, in); } \
    force_inline void type##_array_pop(type##_array* array) { array_pop_macro(array); } \
    force_inline void clear_##type##_array(type##_array* array) { clear_array_macro(array); }  \
    force_inline void clear_##type##_array_deeply(type##_array* array, void (*destroy_elem_func)(type* elem)) { clear_array_deeply_macro(array, destroy_elem_func); }  \
    force_inline void reverse_##type##_array(type##_array* array) { reverse_array_macro(array, type); } \
    force_inline void reverse_##type##_array_slice(type##_array* array, u32 offset, u32 count) { reverse_array_slice_macro(array, type, offset, count); }

void* allocate(allocator*, u64);

#define init_array_macro(array, data_type, _size, _increment, _allocator)       \
    {                                                                           \
        array.data = (data_type*)allocate(allocator, sizeof(data_type) * size); \
        array.size = _size;                                                     \
        array.count = 0;                                                        \
        array.increment = _increment;                                           \
        array.allocator = _allocator;                                           \
    }

void deallocate(allocator*, void*);

#define destroy_array_macro(array_ptr) \
    {                                                   \
        deallocate(array_ptr->allocator, array->data);  \
        array_ptr->count = 0;                           \
        array_ptr->size = 0;                            \
        array_ptr->allocator = nullptr;                 \
        array_ptr->data = nullptr;                      \
    }


#define destroy_array_deeply_macro(array_ptr, destroy_array_elem_func)  \
    {                                                       \
        for (u32 i = 0; i < array_ptr->count; ++i)          \
        {                                                   \
            destroy_array_elem_func(&array_ptr->data[i]);   \
        }                                                   \
        destroy_array_macro(array_ptr);                     \
    }

#define resize_array_macro(array_ptr, data_type, new_size)                                              \
    {                                                                                                   \
        u32 count = new_size < array_ptr->count ? new_size : array_ptr->count;                          \
        data_type* new_data = (data_type*)allocate(array_ptr->allocator, sizeof(data_type) * new_size); \
        for (u32 i = 0; i < count; ++i) new_data[i] = array_ptr->data[i];                               \
        deallocate(array_ptr->allocator, array_ptr->data);                                              \
        array_ptr->data = new_data;                                                                     \
        array_ptr->count = count;                                                                       \
        array_ptr->size = new_size;                                                                     \
    }

#define array_push_macro(array_ptr, type, val)                                              \
    {                                                                                       \
        if (array_ptr->count >= array_ptr->size)                                            \
        {                                                                                   \
            resize_array_macro(array_ptr, type, array_ptr->count + array_ptr->increment);   \
        }                                                                                   \
        array_ptr->data[array_ptr->count++] = val;                                          \
    }

#define array_push_repeated_macro(array_ptr, type, val, _count)                                     \
    {                                                                                               \
        if (array_ptr->count + _count >= array_ptr->size)                                           \
        {                                                                                           \
            resize_array_macro(array_ptr, type, array_ptr->count + _count + array_ptr->increment);  \
        }                                                                                           \
        for (u32 i = 0; i < _count; ++i) array_ptr->data[array_ptr->count++] = val;                 \
    }

#define array_push_buffer_macro(array_ptr, type, buf, n)                                        \
    {                                                                                           \
        if (array_ptr->count + n >= array_ptr->size)                                            \
        {                                                                                       \
            resize_array_macro(array_ptr, type, array_ptr->count + n + array_ptr->increment);   \
        }                                                                                       \
        for (u32 i = 0; i < n; ++i) array_ptr->data[array_ptr->count++] = buf[i];               \
    }

#define array_push_array_macro(out, type, in) array_push_buffer_macro(out, type, in->data, in->count)

#define array_pop_macro(array_ptr) array_ptr->count -= 1

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
declare_array_of(s8);
declare_array_of(u8);
declare_array_of(s16);
declare_array_of(u16);
declare_array_of(s32);
declare_array_of(u32);
declare_array_of(s64);
declare_array_of(u64);

#endif // !CUTILE_ARRAY_H
