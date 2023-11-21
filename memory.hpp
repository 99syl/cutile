#ifndef CUTILE_MEMORY_HPP
#define CUTILE_MEMORY_HPP

#include "./num_types.h"

template <typename T>
struct memory_view
{
    const T* data;
    u32      count;
};

#endif // !CUTILE_MEMORY_HPP