#ifndef CUTILE_TEST_H
#define CUTILE_TEST_H

#include "print.h"

CUTILE_C_API int test_result;

#define test_assert(predicate)                              \
    {                                                       \
        if (!(predicate))                                   \
        {                                                   \
            println_cstr("Assertion failed, " __FILE__ "." current_line_cstr_m ": " #predicate);   \
            test_result = 1;                                \
        }                                                   \
    }

#define test_require(predicate)                     \
    {                                               \
        test_assert(predicate);                     \
        if (test_result) process_exit(test_result); \
    }

#ifdef CUTILE_IMPLEM
    int test_result = 0;
#endif // CUTILE_IMPLEM

#endif //! CUTILE_TEST_H
