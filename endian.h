#ifndef CUTILE_ENDIAN_H

    #include "cxx.h"

    #define cutile_is_cpu_big_endian_m(out)
    #define cutile_is_cpu_little_endian_m(out)

    maybe_inline b8 cutile_is_cpu_big_endian()
    {
        b8 res;
        cutile_is_cpu_big_endian_m(res);
        return res;
    }

    maybe_inline b8 cutile_is_cpu_little_endian()
    {
        b8 res;
        cutile_is_cpu_little_endian_m(res);
        return res;
    }

    ////////////////////////////////////////
    //      IMPLEMENTATION:

    #undef  cutile_is_cpu_big_endian_m
    #define cutile_is_cpu_big_endian_m(out) \
    {                                       \
        s32 __cu_is_be_i = 1;               \
        out = *((s8*)&__cu_is_be_i) == 0;   \
    }                                       \

    #undef  cutile_is_cpu_little_endian_m
    #define cutile_is_cpu_little_endian_m(out)  \
    {                                           \
        s32 __cu_is_le_i = 1;                   \
        out = *((s8*)&__cu_is_le_i) == 1;       \
    }                                           \

    #define CUTILE_ENDIAN_H
#endif
