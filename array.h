#ifndef CUTILE_ARRAY_H
#define CUTILE_ARRAY_H

#include "./memory.h"

#ifdef CUTILE_CPP

template <typename T>
struct array
{
    T*  data;

    u32 count; // In T unit.
    u32 size;  // In bytes.

    u32 increment; // In T unit.

    allocator* allocator;
};

template <typename T>
array<T> create_array(u32 size, u32 increment, allocator* allocator = &basic_heap_allocator);

template <typename T>
void destroy_array(array<T>* array);

template <typename T>
void resize_array(array<T>* array, u32 new_size);

template <typename T>
void array_push(array<T>* array, T val);

template <typename T>
void array_push_repeated(array<T>* array, T val, u32 count);

template <typename T>
void array_push_buffer(array<T>* array, const T* buf, u32 n);

template <typename T>
void array_push_array(array<T>* out, const array<T>* in);

template <typename T>
void array_pop(array<T>* array);

template <typename T>
void reverse_array(array<T>* array);
template <typename T>
void reverse_array_slice(array<T>* array, u32 offset, u32 count);

template <typename T>
T  get_array_elem(array<T>* array, u32 index);
template <typename T>
T* get_array_ptr_elem(array<T>* array, u32 index);

template <typename T>
void copy_array_to_buffer(const array<T>* in, T* out);
template <typename T>
void copy_array_slice_to_buffer(const array<T>* in, T* out, u32 offset, u32 count);

#ifdef CUTILE_IMPLEM

template <typename T>
inline array<T> create_array(u32 size, u32 incr, allocator* allocator)
{
    return array<T>
    {
        .data = allocate<T>(allocator, size),
        .size = size,
        .increment = incr,
        .allocator = allocator
    };
}

template <typename T>
inline void destroy_array(array<T>* arr, void (*destroy_data_func)(T* data))
{
    if (destroy_data_func) {
        for (u32 i = 0; i < arr->count; ++i) {
            destroy_data_func(&arr->data[i]);
        }
    }
    deallocate<T>(arr->allocator, arr->data);
}

template <typename T>
inline void resize_array(array<T>* array, u32 new_size)
{
    T* new_data = allocate<T>(array->allocator, new_size);

    u32 i = 0;
    for (; i < array->count && i < new_size; ++i) // TODO: There is a double check here, it might be improved ?
    {
        new_data[i] = array->data[i];
    }
    array->count = i;

    deallocate(array->allocator, array->data);
    array->data = new_data;
    array->size = new_size; 
}

template <typename T>
inline void array_push(array<T>* array, T val)
{
    if (array->size == array->count) {
        resize_array(array, array->size + array->increment);
    }
    array->data[array->count++] = val;
}

template <typename T>
inline void array_push_repeated(array<T>* array, T val, u32 count)
{
    if (array->size <= array->count + count) {
        resize_array(array, array->size + count + array->increment);
    }
    for (u32 i = 0; i < count; ++i) {
        array->data[array->count++] = val;
    }
}

template <typename T>
inline void array_push_buffer(array<T>* array, const T* buf, u32 n)
{
    if (array->count + n >= array->size) {
        resize_array(array, array->count + n + array->increment);
    }

    for (u32 i = 0; i < n; ++i)
    {
        array->data[array->count++] = buf[i];
    }
}

template <typename T>
inline void array_push_array(array<T>* out, const array<T>* in)
{
    array_push_buffer(out, in->data, in->count);
}

template <typename T>
inline void array_pop(array<T>* array)
{
    array->count -= 1;
}


template <typename T>
inline void reverse_array(array<T>* array)
{
    reverse_array_slice(array, 0, array->count);
}

template <typename T>
inline void reverse_array_slice(array<T>* array, u32 offset, u32 count)
{
    u32 end = count * 0.5;
    for (u32 i = offset; i < end; ++i) {
        T dump = get_array_elem(array, i);
        u32 rhs_i = count - 1 - i;
        array->data[i] = array->data[rhs_i];
        array->data[rhs_i] = dump;
    }
}

template <typename T>
inline T get_array_elem(array<T>* array, u32 index)
{
    return array->data[index];
}

template <typename T>
inline T* get_array_ptr_elem(array<T>* array, u32 index)
{
    return &array->data[index];
}

template <typename T>
void copy_array_to_buffer(const array<T>* in, T* out)
{
    for (u32 i = 0; i < in->count; ++i)
    {
        out[i] = in[i];
    }
}

template <typename T>
void copy_array_slice_to_buffer(const array<T>* in, T* out, u32 offset, u32 count)
{
    for (u32 i = 0; i < count; ++i)
    {
        out[i] = in[i + offset];
    }
}

#endif // CUTILE_IMPLEM

#endif // CUTILE_CPP

#endif // !CUTILE_ARRAY_H