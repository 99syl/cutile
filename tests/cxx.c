#define CUTILE_IMPLEM
#include "../cxx.h"
#include "../test.h"

int main()
{
    cutile_test_begin_m();

    u16 nb = 0x1234;

    u16 f = cutile_bswap_u16(nb);

    cutile_test_assert_m(f == 0x3412);

    cutile_test_end_m();
}
