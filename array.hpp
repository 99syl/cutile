#ifndef CUTILE_ARRAY_HPP
#define CUTILE_ARRAY_HPP

#include "./array.h"

template <typename T>
struct array
{
    T*  data;

    u32 count; // In T unit.
    u32 size;  // In T unit.

    u32 increment; // In T unit.

    allocator* allocator;
};

template <typename T>
force_inline array<T> create_array(u32 size, u32 increment, allocator* allocator = &global_default_heap_allocator);

template <typename T>
force_inline void destroy_array(array<T>* array);

template <typename T>
force_inline void resize_array(array<T>* array, u32 new_size);

template <typename T>
force_inline void array_push(array<T>* array, T val);

template <typename T>
force_inline void array_push_repeated(array<T>* array, T val, u32 count);

template <typename T>
force_inline void array_push_buffer(array<T>* array, const T* buf, u32 n);

template <typename T>
force_inline void array_push_array(array<T>* out, const array<T>* in);

template <typename T>
force_inline void array_pop(array<T>* array);

template <typename T>
force_inline void reverse_array(array<T>* array);
template <typename T>
force_inline void reverse_array_slice(array<T>* array, u32 offset, u32 count);

template <typename T>
force_inline T  get_array_elem(array<T>* array, u32 index);
template <typename T>
force_inline T* get_array_ptr_elem(array<T>* array, u32 index);

template <typename T>
force_inline void copy_array_to_buffer(const array<T>* in, T* out);
template <typename T>
force_inline void copy_array_slice_to_buffer(const array<T>* in, T* out, u32 offset, u32 count);


/*
  =============================
         IMPLEMENTATION:
  =============================
*/

template <typename T>
force_inline array<T> create_array(u32 size, u32 incr, allocator* allocator)
{
    array<T> result;
    init_array_macro(result, T, size, incr, allocator);
    return result;
}

template <typename T>
force_inline void destroy_array(array<T>* array)
{
    destroy_array_macro(array);
}

template <typename T>
force_inline void resize_array(array<T>* array, u32 new_size)
{
    resize_array_macro(array, T, new_size);
}

template <typename T>
force_inline void array_push(array<T>* array, T val)
{
    array_push_macro(array, T, val);
}

template <typename T>
force_inline void array_push_repeated(array<T>* array, T val, u32 count)
{
    array_push_repeated_macro(array, T, val, count);
}

template <typename T>
force_inline void array_push_buffer(array<T>* array, const T* buf, u32 n)
{
    array_push_buffer_macro(array, T, buf, n);
}

template <typename T>
force_inline void array_push_array(array<T>* out, const array<T>* in)
{
    array_push_array_macro(out, T, in);
}

template <typename T>
force_inline void array_pop(array<T>* array)
{
    array_pop_macro(array);
}

template <typename T>
force_inline void reverse_array(array<T>* array)
{
    reverse_array_macro(array, T);
}

template <typename T>
force_inline void reverse_array_slice(array<T>* array, u32 offset, u32 count)
{
    reverse_array_slice_macro(array, T, offset, count);
}

template <typename T>
force_inline T get_array_elem(array<T>* array, u32 index)
{
    return array->data[index];
}

template <typename T>
force_inline T* get_array_ptr_elem(array<T>* array, u32 index)
{
    return &array->data[index];
}

template <typename T>
force_inline void copy_array_to_buffer(const array<T>* in, T* out)
{
    for (u32 i = 0; i < in->count; ++i)
    {
        out[i] = in[i];
    }
}

template <typename T>
force_inline void copy_array_slice_to_buffer(const array<T>* in, T* out, u32 offset, u32 count)
{
    for (u32 i = 0; i < count; ++i)
    {
        out[i] = in[i + offset];
    }
}

#endif // !CUTILE_ARRAY_HPP
