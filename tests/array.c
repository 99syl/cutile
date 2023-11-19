#define CUTILE_IMPLEM
#include "../array.h"
#include "../test.h"

int main(int ac, char** av)
{
    s16_array array = create_s16_array(10, 5, &basic_heap_allocator);
    
    s16_array_push(&array, 5);
    {
        test_assert(array.data[0] == 5);
    }

    return test_result;
}