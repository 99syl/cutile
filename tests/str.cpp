#define CUTILE_IMPLEM
#include "../str.h"

int main(int ac, char **av)
{
    int ret = 0;

    // String<->Numeric conversions tests.
    {
        u32 i = 50;
        s32 j = -12893;
        s64 k = 2438750912;
    
        string si = u32_to_str(i, &basic_heap_allocator);
        string sj = s32_to_str(j, &basic_heap_allocator);
        string sk = s64_to_str(k, &basic_heap_allocator);

        // ret = !(si.data[0] == '5');
        // ret = !(si.data[1] == '0');
        ret = !(si.count == 2);

        // ret = !(sj.data[0] == '-');
        // ret = !(sj.data[1] == '1');
        // ret = !(sj.data[2] == '2');
        // ret = !(sj.data[3] == '8');
        // ret = !(sj.data[4] == '9');
        // ret = !(sj.data[5] == '3');
        // ret = !(sj.count == 6);
    }

    return ret;
}
