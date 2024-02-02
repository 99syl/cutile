#ifndef CUTILE_ENDIAN_H

#include "cxx.h"
#include "num_types.h"

maybe_inline b8 is_platform_big_endian();
maybe_inline b8 is_platform_little_endian();

maybe_inline u16 read_be_u16(const u8*);
maybe_inline u16 read_be_u16(u16);
maybe_inline u32 read_be_u32(const u8*);
maybe_inline u32 read_be_u32(u32);
maybe_inline u64 read_be_u64(const u8*);
maybe_inline u64 read_be_u64(u64);

maybe_inline u16 read_le_u16(const u8*);
maybe_inline u16 read_le_u16(u16);
maybe_inline u32 read_le_u32(const u8*);
maybe_inline u32 read_le_u32(u32);
maybe_inline u64 read_le_u64(const u8*);
maybe_inline u64 read_le_u64(u64);

maybe_inline void write_be_u16(u16, u8* out);
maybe_inline void write_be_u32(u32, u8* out);
maybe_inline void write_be_u64(u64, u8* out);

maybe_inline void write_le_u16(u16, u8* out);
maybe_inline void write_le_u32(u32, u8* out);
maybe_inline void write_le_u64(u64, u8* out);

////////////////////////////////////////
//      IMPLEMENTATION:

maybe_inline b8 is_platform_big_endian()
{
    s32 i = 1;
    return *((s8*)&i)==0;
}

maybe_inline b8 is_platform_little_endian()
{
    s32 i = 1;
    return *((s8*)&i)==1;
}

maybe_inline u16 read_be_u16(const u8* bytes)
{
    return bytes[1] | (bytes[0] << 8);
}

maybe_inline u16 read_be_u16(u16 n)
{
    return read_be_u16((u8*)&n);
}

maybe_inline u32 read_be_u32(const u8* bytes)
{
    return ((u32)read_be_u16(bytes) << 16) | (u32)read_be_u16(bytes + 2);
}

maybe_inline u32 read_be_u32(u32 n)
{
    return read_be_u32((u8*)&n);
}

maybe_inline u64 read_be_u64(const u8* bytes)
{
    return ((u64)read_be_u32(bytes) << 32) | (u64)read_be_u32(bytes + 4);
}

maybe_inline u64 read_be_u64(u64 n)
{
    return read_be_u64((u8*)&n);
}

maybe_inline u16 read_le_u16(const u8* bytes)
{
    return bytes[0] | (bytes[1] << 8);
}

maybe_inline u16 read_le_u16(u16 n)
{
    return read_le_u16((u8*)&n);
}

maybe_inline u32 read_le_u32(const u8* bytes)
{
    return read_le_u16(bytes) | (read_le_u16(bytes + 2) << 16);
}

maybe_inline u32 read_le_u32(u32 n)
{
    return read_le_u32((u8*)&n);
}

maybe_inline u64 read_le_u64(const u8* bytes)
{
    return (u64)read_le_u32(bytes) | ((u64)read_le_u32(bytes + 4) << 32);
}

maybe_inline u64 read_le_u64(u64 n)
{
    return read_le_u64((u8*)&n);
}

maybe_inline void write_be_u16(u16 v, u8* bytes)
{
    bytes[0] = (v >> 8) & 0xFF;
    bytes[1] = v & 0xFF;
}

maybe_inline void write_be_u32(u32 v, u8* bytes)
{
    write_be_u16(v >> 16, bytes);
    write_be_u16(v, bytes + 2);
}

maybe_inline void write_be_u64(u64 v, u8* bytes)
{
    write_be_u32(v >> 32, bytes);
    write_be_u32(v, bytes + 4);
}

maybe_inline void write_le_u16(u16 v, u8* bytes)
{
    bytes[0] = v & 0xFF;
    bytes[1] = (v >> 8) & 0xFF;
}

maybe_inline void write_le_u32(u32 v, u8* bytes)
{
    write_le_u16(v, bytes);
    write_le_u16(v >> 16, bytes + 2);
}

maybe_inline void write_le_u64(u64 v, u8* bytes)
{
    write_le_u32(v, bytes);
    write_le_u32(v >> 32, bytes + 4);
}

#define CUTILE_ENDIAN_H
#endif
