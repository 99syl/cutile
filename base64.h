#pragma once

#include "num_types.h"
#include "memory.h"

extern const s8 base64_table[64];
extern const u8 base64_dtable[255];

u8* base64_encode(const u8* in, u64 len, u64* out_len, allocator* allocator);
u8* base64_encode_cstr(const char* cstr, u64* out_len, allocator* allocator);

u8* base64_decode(const u8* in, u64 len, u64* out_len, allocator* allocator);
u8* base64_decode_cstr(const char* cstr, u64* out_len, allocator* allocator);

#ifdef CUTILE_IMPLEM

    #include "str.h"

    const s8 base64_table[] =
    {
        'A','B','C','D','E','F','G','H','I','J','K','L','M','N','O',
        'P','Q','R','S','T','U','V','W','X','Y','Z','a','b','c','d',
        'e','f','g','h','i','j','k','l','m','n','o','p','q','r','s',
        't','u','v','w','x','y','z','0','1','2','3','4','5','6','7','8','9','+','/'
    };

    u8* base64_encode(const u8* in, u64 len, u64* out_len, allocator* allocator)
    {
        // Calculates the length of the output.
        u64 remainder = len % 4;
        if (remainder)      *out_len = len + remainder;
        else                *out_len = len;
    
        // Generates output.
        u8* out = (u8*)allocate(allocator, *out_len);
        u8* pos = out;
        u8* end = out + *out_len;
        while (len >= 3)
        {
            *pos++ = (u8)base64_table[in[0] >> 2];
            *pos++ = (u8)base64_table[((in[0] & 0x03) << 4) | (in[1] >> 4)];    // x03 = b00000011
            *pos++ = (u8)base64_table[((in[1] & 0x0F) << 2) | (in[2] >> 6)];    // x0F = b00001111
            *pos++ = (u8)base64_table[in[2] & 0x3F];                            // x3F = b00111111
            len -= 3;
            in += 3;
        }
        if (end - pos)
        {
            if (len == 2)
            {
                *pos++ = (u8)base64_table[in[0] >> 2];
                *pos++ = (u8)base64_table[((in[0] & 0x03) << 4) | (in[1] >> 4)];    // x03 = b00000011
                *pos++ = (u8)base64_table[((in[1] & 0x0F) << 2)];                   // x0F = b00001111
            }
            else if (len == 1)
            {
                *pos++ = (u8)base64_table[in[0] >> 2];
                *pos++ = (u8)base64_table[((in[0] & 0x03) << 4)];   // x03 = b00000011
                *pos++ = '=';
            }
            *pos = '=';
        }
    
        return out;
    }

    u8* base64_encode_cstr(const char* cstr, u64* out_len, allocator* allocator)
    {
        u32 len = cstr_length(cstr);
        return base64_encode((u8*)cstr, len, out_len, allocator);
    }

    const u8 base64_dtable[] =
    {
        80, 80, 80, 80, 80, 80, 80, 80, 80, 80, 80, 80, 80, 80, 80, 80, /* 0 - 15 */
        80, 80, 80, 80, 80, 80, 80, 80, 80, 80, 80, 80, 80, 80, 80, 80, /* 16 - 31 */
        80, 80, 80, 80, 80, 80, 80, 80, 80, 80, 80, 62, 80, 80, 80, 63, /* 32 - 47 */
        52, 53, 54, 55, 56, 57, 58, 59, 60, 61, 80, 80, 80, 64, 80, 80, /* 48 - 63 */
        80,  0,  1,  2,  3,  4,  5,  6,  7,  8,  9, 10, 11, 12, 13, 14, /* 64 - 79 */
        15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 80, 80, 80, 80, 80, /* 80 - 96 */
        80, 26, 27, 28, 29, 30, 31, 32, 33, 34, 35, 36, 37, 38, 39, 40, /* 87 - 111 */
        41, 42, 43, 44, 45, 46, 47, 48, 49, 50, 51, 80, 80, 80, 80, 80 /* 112 - 127 */
    }; 

    u8* base64_decode(const u8* in, u64 len, u64* out_len, allocator* allocator)
    {
        // Calculates the length of the output.
        *out_len = 0;
        for (u32 i = 0; i < len; ++i) if (in[i] != '=' && base64_dtable[in[i]] != 0x80) ++(*out_len);
        *out_len = (*out_len * 0.25) * 3;
        
        // Generates output.
        u8* out = (u8*)allocate(allocator, *out_len);
        u8* pos = out;
        while (len >= 8)
        {
            u8 c1 = base64_dtable[*in];
            u8 c2 = base64_dtable[*(in + 1)];
            u8 c3 = base64_dtable[*(in + 2)];
            u8 c4 = base64_dtable[*(in + 3)];
            *pos++ = (c1 << 2) | (c2 >> 4);
            *pos++ = (c2 << 4) | (c3 >> 2);
            *pos++ = (c3 << 6) | c4;
            len -= 4;
            in += 4;
        }
        u8 c1 = base64_dtable[*in];
        if (in[1] == '=')
        {
            *pos = c1 << 2;
            return out;
        }
        else
        {
            u8 c2 = base64_dtable[in[1]];
            *pos++ = (c1 << 2) | (c2 >> 4);
            if (in[2] == '=')
            {
                *pos++ = c2 << 4;
                return out;
            }
            else
            {
                u8 c3 = base64_dtable[in[2]];
                *pos++ = (c2 << 4) | (c3 >> 2);
                if (in[3] == '=')
                {
                    *pos++ = c3 << 6;
                    return out;
                }
                else
                {
                    u8 c4 = base64_dtable[in[3]];
                    *pos++ = (c3 << 6) | c4;
                    return out;
                }
            }
        }
    }

    u8* base64_decode_cstr(const char* cstr, u64* out_len, allocator* allocator)
    {
        u32 clen = cstr_length(cstr);
        return base64_decode((u8*)cstr, clen, out_len, allocator);
    }

#endif // CUTILE_IMPLEM
