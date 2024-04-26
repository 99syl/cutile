#pragma once

#include "num_types.h"

maybe_inline s32 get_u8_digits(u8 nb)
{
    if (nb < 10) return 1;
    if (nb < 100) return 2;
    return 3;
}
    
maybe_inline s32 get_s8_digits(s8 nb)
{
    if (nb < 0) nb = nb == s8_min ? s8_max : -nb;
    if (nb < 10) return 1;
    if (nb < 100) return 2;
    return 3;
}
    
maybe_inline s32 get_u16_digits(u16 nb)
{
    if (nb < 10) return 1;
    if (nb < 100) return 2;
    if (nb < 1000) return 3;
    if (nb < 10000) return 4;
    return 5;
}
    
maybe_inline s32 get_s16_digits(s16 nb)
{
    if (nb < 0) nb = nb == s16_min ? s16_max : -nb;
    if (nb < 10) return 1;
    if (nb < 100) return 2;
    if (nb < 1000) return 3;
    if (nb < 10000) return 4;
    return 5;
}
    
maybe_inline s32 get_u32_digits(u32 nb)
{
    if (nb < 10) return 1;
    else if (nb < 100) return 2;
    else if (nb < 1000) return 3;
    else if (nb < 10000) return 4;
    else if (nb < 100000) return 5;
    else if (nb < 1000000) return 6;
    else if (nb < 10000000) return 7;
    else if (nb < 100000000) return 8;
    else if (nb < 1000000000) return 9;
    return 10;
}
    
maybe_inline s32 get_s32_digits(s32 nb)
{
    if (nb < 0) nb = nb == s32_min ? s32_max : -nb;
    if (nb < 10) return 1;
    if (nb < 100) return 2;
    if (nb < 1000) return 3;
    if (nb < 10000) return 4;
    if (nb < 100000) return 5;
    if (nb < 1000000) return 6;
    if (nb < 10000000) return 7;
    if (nb < 100000000) return 8;
    if (nb < 1000000000) return 9;
    return 10;
}
    
maybe_inline s64 get_u64_digits(u64 nb)
{
    if (nb < 10) return 1;
    if (nb < 100) return 2;
    if (nb < 1000) return 3;
    if (nb < 10000) return 4;
    if (nb < 100000) return 5;
    if (nb < 1000000) return 6;
    if (nb < 10000000) return 7;
    if (nb < 100000000) return 8;
    if (nb < 1000000000) return 9;
    if (nb < 10000000000) return 11;
    if (nb < 100000000000) return 12;
    if (nb < 1000000000000) return 13;
    if (nb < 10000000000000) return 14;
    if (nb < 100000000000000) return 15;
    if (nb < 1000000000000000) return 16;
    if (nb < 10000000000000000) return 17;
    if (nb < 100000000000000000) return 18;
    if (nb < 1000000000000000000) return 19;
    return 20;
}
    
maybe_inline s64 get_s64_digits(s64 nb)
{
    if (nb < 0) nb = nb == s64_min ? s64_max : -nb;
    if (nb < 10) return 1;
    if (nb < 100) return 2;
    if (nb < 1000) return 3;
    if (nb < 10000) return 4;
    if (nb < 100000) return 5;
    if (nb < 1000000) return 6;
    if (nb < 10000000) return 7;
    if (nb < 100000000) return 8;
    if (nb < 1000000000) return 9;
    if (nb < 10000000000) return 11;
    if (nb < 100000000000) return 12;
    if (nb < 1000000000000) return 13;
    if (nb < 10000000000000) return 14;
    if (nb < 100000000000000) return 15;
    if (nb < 1000000000000000) return 16;
    if (nb < 10000000000000000) return 17;
    if (nb < 100000000000000000) return 18;
    if (nb < 1000000000000000000) return 19;
    return 20;
}
