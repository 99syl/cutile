#pragma once

#include "str.h"

template <typename NumberType>
maybe_inline NumberType str_to_nb(const string* s);

template <typename NumberType>
maybe_inline NumberType sub_str_to_nb(const string* s, u32 offset, u32 count);

template <typename NumberType>
maybe_inline string nb_to_str(NumberType val, allocator* = default_allocator);

template <typename NumberType>
maybe_inline void nb_into_str(NumberType val, string* out);

template <typename NumberType>
maybe_inline void nb_into_sub_str(NumberType val, string* out, u32 offset);

// IMPLEMENTATION:

template <typename NumberType>
maybe_inline NumberType str_to_nb(const string* s)
{
    return sub_str_to_nb<NumberType>(s, 0, s->count);
}

template <>
maybe_inline u8 sub_str_to_nb<u8>(const string* s, u32 offset, u32 count) { return sub_str_to_u8(s, offset, count); }
template <>
maybe_inline s8 sub_str_to_nb<s8>(const string* s, u32 offset, u32 count) { return sub_str_to_s8(s, offset, count); }
template <>
maybe_inline u16 sub_str_to_nb<u16>(const string* s, u32 offset, u32 count) { return sub_str_to_u16(s, offset, count); }
template <>
maybe_inline s16 sub_str_to_nb<s16>(const string* s, u32 offset, u32 count) { return sub_str_to_s16(s, offset, count); }
template <>
maybe_inline u32 sub_str_to_nb<u32>(const string* s, u32 offset, u32 count) { return sub_str_to_u32(s, offset, count); }
template <>
maybe_inline s32 sub_str_to_nb<s32>(const string* s, u32 offset, u32 count) { return sub_str_to_s32(s, offset, count); }
template <>
maybe_inline u64 sub_str_to_nb<u64>(const string* s, u32 offset, u32 count) { return sub_str_to_u64(s, offset, count); }
template <>
maybe_inline s64 sub_str_to_nb<s64>(const string* s, u32 offset, u32 count) { return sub_str_to_s64(s, offset, count); }

template <typename NumberType>
maybe_inline string nb_to_str(NumberType val, allocator*)
{
    string result = create_empty_str(allocator);
    nb_into_str(val, &result);
    return result;
}

template <typename NumberType>
maybe_inline void nb_into_str(NumberType val, string* out)
{
    return nb_into_sub_str(val, out, out->count);
}

template <>
maybe_inline void nb_into_sub_str<u8>(u8 val, string* out, u32 offset) { u8_into_sub_str(val, out, offset); }

template <>
maybe_inline void nb_into_sub_str<s8>(s8 val, string* out, u32 offset) { s8_into_sub_str(val, out, offset); }

template <>
maybe_inline void nb_into_sub_str<u16>(u16 val, string* out, u32 offset) { u16_into_sub_str(val, out, offset); }

template <>
maybe_inline void nb_into_sub_str<s16>(s16 val, string* out, u32 offset) { s16_into_sub_str(val, out, offset); }

template <>
maybe_inline void nb_into_sub_str<u32>(u32 val, string* out, u32 offset) { u32_into_sub_str(val, out, offset); }

template <>
maybe_inline void nb_into_sub_str<s32>(s32 val, string* out, u32 offset) { s32_into_sub_str(val, out, offset); }

template <>
maybe_inline void nb_into_sub_str<u64>(u64 val, string* out, u32 offset) { u64_into_sub_str(val, out, offset); }

template <>
maybe_inline void nb_into_sub_str<s64>(s64 val, string* out, u32 offset) { s64_into_sub_str(val, out, offset); }
