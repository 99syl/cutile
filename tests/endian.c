#define CUTILE_IMPLEM
#include "../endian.h"
#include "../test.h"
#include "../platform.h"
#include <stdio.h>
int main()
{
    cutile_test_begin_m();

    u16 nb = 0x1234;

    u16 f = cutile_bswap16_m(nb);
    printf("%#04x\n", f);

    cutile_test_assert_m(f == 0x3412);

    cutile_test_end_m();
}
