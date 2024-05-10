#define CUTILE_IMPLEM
#include "../array.h"
#include "../test.h"

allocator* default_allocator;

int main(int ac, char** av)
{
    test_begin();

    heap_allocator heap_allocator = create_default_heap_allocator();
    set_default_allocator_m(&heap_allocator);

    s16_array array = create_s16_array(10, 5, default_allocator);
    
    s16_array_push(&array, 5);
    {
        test_assert(array.count == 1);
        test_assert(array.size == 10);
        test_assert(array.data[0] == 5);
    }

    s16_array_push_repeated(&array, 10, 20);
    {
        test_assert(array.count == 21);
        test_assert(array.size == 21);
        test_assert(array.data[0] = 5);
        for (u32 i = 1; i < array.count; ++i)
        {
            test_assert(array.data[i] == 10);
        }
    }

    s16 buf[] = { 7, 8, 9 };
    s16_array_push_buffer(&array, buf, fixed_array_length_m(buf));
    {
        test_assert(array.count == 24);
        test_assert(array.size == 24);
        test_assert(array.data[0] = 5);
        for (u32 i = 1; i < 21; ++i)
        {
            test_assert(array.data[i] == 10);
        }
        test_assert(array.data[21] = 7);
        test_assert(array.data[22] = 8);
        test_assert(array.data[23] = 9);
    }

    test_end();
}
