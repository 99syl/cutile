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
        u32_into_str(i, &sk);

        ret = !(si.data[0] == '5');
        ret = !(si.data[1] == '0');
        ret = !(si.count == 2);

        ret = !(sj.data[0] == '-');
        ret = !(sj.data[1] == '1');
        ret = !(sj.data[2] == '2');
        ret = !(sj.data[3] == '8');
        ret = !(sj.data[4] == '9');
        ret = !(sj.data[5] == '3');
        ret = !(sj.count == 6);

        ret = !(sk.data[0] == '2');
        ret = !(sk.data[1] == '4');
        ret = !(sk.data[2] == '3');
        ret = !(sk.data[3] == '8');
        ret = !(sk.data[4] == '7');
        ret = !(sk.data[5] == '5');
        ret = !(sk.data[6] == '0');
        ret = !(sk.data[7] == '9');
        ret = !(sk.data[8] == '1');
        ret = !(sk.data[9] == '2');
        ret = !(sk.data[10] == '5');
        ret = !(sk.data[11] == '0');
        ret = !(sk.count == 12);
    }

    return ret;
}
