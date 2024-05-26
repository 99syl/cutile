#define CUTILE_IMPLEM
#include "../shared_library.h"
#include "../test.h"

int main()
{
    cutile_test_begin_m();

    cutile_shared_library sl = {0};
    #if LINUX
        sl = cutile_load_shared_library("shared_library_sample.so");
    #elif WINDOWS
        sl = cutile_load_shared_library("shared_library_sample.dll");
    #endif
    cutile_test_require_m(sl.handle);

    void (*proc)();
    #if defined(CUTILE_C)
        proc = cutile_get_shared_library_proc(&sl, "dummy_func");
    #elif defined(CUTILE_CPP)
        proc = cutile::get_shared_library_proc(&sl, "dummy_func");
    #endif
    cutile_test_require_m(proc);

    cutile_test_end_m();
}
