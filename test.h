#pragma once

#include "print.h"
#include "process.h"

#define test_begin() int __cutile_test_result = 0;

#define test_assert(predicate)                              \
    {                                                       \
        if (!(predicate))                                   \
        {                                                   \
            println_cstr("Assertion failed, " __FILE__ "." current_line_cstr_m ": " #predicate);   \
            __cutile_test_result = 1;					\
        }                                                   \
    }

#define test_require(predicate)                     \
    {                                               \
        test_assert(predicate);                     \
        if (__cutile_test_result) exit_process(__cutile_test_result); \
    }

#define test_end() println_cstr(__cutile_test_result ? "Test failed !" : "Test success !"); return __cutile_test_result;
