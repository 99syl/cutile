#define CUTILE_IMPLEM
#include "../array.h"
#include "../test.h"

int main(int ac, char** av)
{
    test_begin();

    allocator default_allocator = create_default_heap_allocator();

    s16_array array = create_s16_array(10, 5, &default_allocator);
    
    s16_array_push(&array, 5);
    {
        test_assert(array.data[0] == 5);
    }

    test_end();
}
