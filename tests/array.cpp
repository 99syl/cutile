#define CUTILE_IMPLEM
#include "../array.hpp"
#include "../test.h"

allocator* default_allocator;

int main()
{
    test_begin();

    heap_allocator heapall = create_default_heap_allocator();
    default_allocator = (allocator*)&heapall;

    auto arr = create_array<int>(5, 5);
    
    array_push(&arr, 5);
    {
        test_assert(arr.count == 1);
        test_assert(arr.data[0] == 5);
    }
    
    array_pop(&arr);
    {
        test_assert(arr.count == 0);
    }

    array_push_repeated(&arr, 20, 10);
    {
        test_assert(arr.count == 10);
        test_assert(arr.size == 10);
        for (u32 i = 0; i < arr.count; ++i)
        {
            test_assert(arr.data[i] == 20);
        }
    }
    
    test_end();
}
