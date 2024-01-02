#ifndef CUTILE_ENDIAN_H
#define CUTILE_ENDIAN_H

#include "./cxx.h"

force_inline u16 read_be_u16(u8* bytes)
{
    return bytes[1] | (bytes[0] << 8);
}

force_inline u16 read_be_u16(u16 n)
{
    return read_be_u16((u8*)&n);
}

force_inline u32 read_be_u32(u8* bytes)
{
    return (read_be_u16(bytes) << 16) | (bytes[2] << 8) | bytes[3];
}

force_inline u32 read_be_u32(u32 n)
{
    return read_be_u32((u8*)&n);
}

force_inline u64 read_be_u64(u8* bytes)
{
    return ((u64)read_be_u32(bytes) << 32) | ((u64)bytes[4] << 24) | ((u64)bytes[5] << 16) | ((u64)bytes[6] << 8) | (u64)bytes[7];
}

force_inline u64 read_be_u64(u64 n)
{
    return read_be_u64((u8*)&n);
}

force_inline b8 is_platform_big_endian()
{
    s32 i = 1;
    return *((s8*)&i)==0;
}

force_inline b8 is_platform_little_endian()
{
    s32 i = 1;
    return *((s8*)&i)==1;
}

#endif // !CUTILE_ENDIAN_H
