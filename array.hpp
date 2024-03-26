#ifndef CUTILE_ARRAY_HPP
#define CUTILE_ARRAY_HPP

#include "array.h"
#include "memory.h"

template <typename T>
struct array
{
    T*  data;

    u32 count;     // Number of elements currently contained in the array.
    u32 size;      // Number of elements that the array is able to contain.

    u32 increment; // How much more space we want to reserve each time a resize is needed.
                   // Value is expressed in number of elements.

    allocator* allocator;
};

template <typename T>
maybe_inline array<T> create_array(u32 size, u32 increment, allocator* allocator = &global_default_heap_allocator);

template <typename T>
maybe_inline void destroy_array(array<T>* array);

template <typename T>
maybe_inline void resize_array(array<T>* array, u32 new_size);

template <typename T>
maybe_inline void array_push(array<T>* array, T val);

template <typename T>
maybe_inline void array_push_repeated(array<T>* array, T val, u32 count);

template <typename T>
maybe_inline void array_push_buffer(array<T>* array, const T* buf, u32 n);

template <typename T>
maybe_inline void array_push_array(array<T>* out, const array<T>* in);

template <typename T>
maybe_inline void array_pop(array<T>* array);

template <typename T>
maybe_inline void reverse_array(array<T>* array);
template <typename T>
maybe_inline void reverse_array_slice(array<T>* array, u32 offset, u32 count);

template <typename T>
maybe_inline T  get_array_elem(array<T>* array, u32 index);
template <typename T>
maybe_inline T* get_array_ptr_elem(array<T>* array, u32 index);

template <typename T>
maybe_inline void copy_array_to_buffer(const array<T>* in, T* out);
template <typename T>
maybe_inline void copy_array_slice_to_buffer(const array<T>* in, T* out, u32 offset, u32 count);

/*
  =============================
         IMPLEMENTATION:
  =============================
*/

template <typename T>
maybe_inline array<T> create_array(u32 size, u32 incr, allocator* allocator)
{
    array<T> result;
    init_array_macro(result, T, size, incr, allocator);
    return result;
}

template <typename T>
maybe_inline void destroy_array(array<T>* array)
{
    destroy_array_macro(array);
}

template <typename T>
maybe_inline void destroy_array_deeply(array<T>* array, void(*destroy_elem_func)(T* data))
{
    destroy_array_deeply_macro(array, destroy_elem_func);
}

template <typename T>
maybe_inline void resize_array(array<T>* array, u32 new_size)
{
    T* new_data = allocate_many_m(array->allocator, T, new_size);
    if (new_size < array->count)
    {
        for (u32 i = 0; i < new_size; ++i)
        {
            new_data[i] = array->data[i];
        }
        array->count = new_size;
    }
    else
    {
        for (u32 i = 0; i < array->count; ++i)
        {
            new_data[i] = array->data[i];
        }
    }
    array->data = new_data;
    array->size = new_size;
}

template <typename T>
maybe_inline void array_push(array<T>* array, T val)
{
    array_push_macro(array, T, val);
}

template <typename T>
maybe_inline void array_push_repeated(array<T>* array, T val, u32 count)
{
    array_push_repeated_macro(array, T, val, count);
}

template <typename T>
maybe_inline void array_push_buffer(array<T>* out, const T* buf, u32 n)
{
    if (out->count + n > out->size)
    {
        resize_array(out, out->size + n);
    }
    for (u32 i = 0; i < n; ++i)
    {
        out->data[out->count] = buf[i];
        out->count++;
    }
}

template <typename T>
maybe_inline void array_push_array(array<T>* out, const array<T>* in)
{
    if (out->count + in->count > out->size)
    {
        resize_array(out, out->size + in->count);
    }
    for (u32 i = 0; i < in->count; ++i)
    {
        out->data[out->count] = in->data[i];
        out->count++;
    }
}

template <typename T>
maybe_inline void array_pop(array<T>* array)
{
    array_pop_macro(array);
}

template <typename T>
maybe_inline void clear_array(array<T>* array)
{
    clear_array_macro(array);
}

template <typename T>
maybe_inline void clear_array_deeply(array<T>* array, void (*destroy_elem_func)(T* elem))
{
    clear_array_macro_deeply(array, destroy_elem_func);
}

template <typename T>
maybe_inline void reverse_array(array<T>* array)
{
    reverse_array_macro(array, T);
}

template <typename T>
maybe_inline void reverse_array_slice(array<T>* array, u32 offset, u32 count)
{
    reverse_array_slice_macro(array, T, offset, count);
}

template <typename T>
maybe_inline T get_array_elem(array<T>* array, u32 index)
{
    return array->data[index];
}

template <typename T>
maybe_inline T* get_array_ptr_elem(array<T>* array, u32 index)
{
    return &array->data[index];
}

template <typename T>
maybe_inline void copy_array_to_buffer(const array<T>* in, T* out)
{
    for (u32 i = 0; i < in->count; ++i)
    {
        out[i] = in[i];
    }
}

template <typename T>
maybe_inline void copy_array_slice_to_buffer(const array<T>* in, T* out, u32 offset, u32 count)
{
    for (u32 i = 0; i < count; ++i)
    {
        out[i] = in[i + offset];
    }
}

#endif // !CUTILE_ARRAY_HPP
