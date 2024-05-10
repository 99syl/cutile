#ifndef CUTILE_ARRAY_HPP

    #include "array.h"
    #include "memory.h"
    
    template <typename T>
    struct array
    {
        T*  data;
    
        u32 count;     // Number of elements currently contained in the array.
        u32 size;      // Number of elements that the array is able to contain.
    
        u32 increment; // How much more space we want to reserve each time a resize is needed when pushing data.
                       // Value is expressed in number of elements (sizeof(T)*increment).
    
        allocator* allocator;
    };
    
    template <typename T>
    maybe_inline array<T> create_array(u32 size, u32 increment, allocator* allocator = default_allocator);
    
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
    maybe_inline array<T> create_array(u32 size, u32 increment, allocator* allocator)
    {
        CUTILE_ASSERT(increment);
        array<T> array;
        array.data = allocate_many_m(allocator, T, size);
        array.count = 0;
        array.size = size;
        array.increment = increment;
        array.allocator = allocator;
        return array;
    }
    
    template <typename T>
    maybe_inline void destroy_array(array<T>* array)
    {
        destroy_array_m(array);
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
        CUTILE_ASSERT(array->increment);
        if (array->count >= array->size)
        {
            resize_array(array, array->count + array->increment);
        }
        array->data[array->count] = val;
        array->count++;
    }
    
    template <typename T>
    maybe_inline void array_push_repeated(array<T>* array, T val, u32 count)
    {
        if (array->count + count >= array->size)
        {
            resize_array(array, array->count + count);
        }
        for (u32 i = 0; i < count; ++i) array->data[array->count++] = val;
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
        array_pop_m(array);
    }
    
    template <typename T>
    maybe_inline void clear_array(array<T>* array)
    {
        clear_array_m(array);
    }
    
    template <typename T>
    maybe_inline void clear_array_deeply(array<T>* array, void (*destroy_elem_func)(T* elem))
    {
        clear_array_deeply_m(array, destroy_elem_func);
    }
    
    template <typename T>
    maybe_inline void reverse_array(array<T>* array)
    {
        reverse_array_slice(array, 0, array->count);
    }
    
    template <typename T>
    maybe_inline void reverse_array_slice(array<T>* array, u32 offset, u32 count)
    {
        u32 end = count * 0.5;
        for (u32 i = offset; i < end; ++i)
        {
            T dump = array->data[i];
            u32 rhs_i = count - 1 - i;
            array->data[i] = array->data[rhs_i];
            array->data[rhs_i] = dump;
        }
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

    #define CUTILE_ARRAY_HPP

#endif
