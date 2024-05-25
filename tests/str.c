#define CUTILE_IMPLEM
#include "../str.h"
#include "../test.h"
#include "../number.h"

int main(int ac, char** av)
{
    cutile_test_begin_m();

    cutile_allocator* default_allocator;
    cutile_heap_allocator heapallocator = cutile_create_default_heap_allocator();
    default_allocator = (allocator*)&heapallocator;

    // UTF-8
    {
        cutile_string s1 = create_str_from_cstr("こんにちは！", default_allocator);
        cutile_string s2 = create_str_from_cstr("プログラミングが好き。", default_allocator);
        cutile_string s3 = create_str_from_cstr("ASCIIとUTF-8.", default_allocator);

        cutile_test_assert_m(str_is_valid_utf8(&s1));
        cutile_test_assert_m(str_is_valid_utf8(&s2));
        cutile_test_assert_m(str_is_valid_utf8(&s3));

        cutile_test_assert_m(str_utf8_count(&s1) == 6);
        cutile_test_assert_m(str_utf8_count(&s2) == 11);
        cutile_test_assert_m(str_utf8_count(&s3) == 12);
    }

    // String to number conversions tests.
    {
        u32 i = 50;
        s32 j = -12893;
        s64 k = 2438750912;
    
        int dig; cutile_get_s32_digits_m(j, dig);
        cutile_string si = u32_to_str(i, default_allocator);
        cutile_string sj = s32_to_str(j, default_allocator);
        cutile_string sk = s64_to_str(k, default_allocator);
        u32_into_str(i, &sk);

        cutile_test_assert_m(str_equals_cstr(&si, "50"));
        cutile_test_assert_m(str_equals_cstr(&sj, "-12893"));
        cutile_test_assert_m(str_equals_cstr(&sk, "243875091250"));

        cutile_test_assert_m(str_equals_cstr2(u8_to_str(u8_max, default_allocator), "255"));
        cutile_test_assert_m(str_equals_cstr2(u8_to_str(u8_min, default_allocator), "0"));
        cutile_test_assert_m(str_equals_cstr2(s8_to_str(s8_max, default_allocator), "127"));
        cutile_test_assert_m(str_equals_cstr2(s8_to_str(s8_min, default_allocator), "-128"));
        cutile_test_assert_m(cstr_equals(u8_to_cstr(u8_max, default_allocator), "255"));
        cutile_test_assert_m(cstr_equals(u8_to_cstr(u8_min, default_allocator), "0"));
        cutile_test_assert_m(cstr_equals(s8_to_cstr(s8_max, default_allocator), "127"));
        cutile_test_assert_m(cstr_equals(s8_to_cstr(s8_min, default_allocator), "-128"));

        cutile_test_assert_m(str_equals_cstr2(u16_to_str(u16_max, default_allocator), "65535"));
        cutile_test_assert_m(str_equals_cstr2(u16_to_str(u16_min, default_allocator), "0"));
        cutile_test_assert_m(str_equals_cstr2(s16_to_str(s16_max, default_allocator), "32767"));
        cutile_test_assert_m(str_equals_cstr2(s16_to_str(s16_min, default_allocator), "-32768"));
        cutile_test_assert_m(cstr_equals(u16_to_cstr(u16_max, default_allocator), "65535"));
        cutile_test_assert_m(cstr_equals(u16_to_cstr(u16_min, default_allocator), "0"));
        cutile_test_assert_m(cstr_equals(s16_to_cstr(s16_max, default_allocator), "32767"));
        cutile_test_assert_m(cstr_equals(s16_to_cstr(s16_min, default_allocator), "-32768"));

        cutile_test_assert_m(str_equals_cstr2(u32_to_str(u32_max, default_allocator), "4294967295"));
        cutile_test_assert_m(str_equals_cstr2(u32_to_str(u32_min, default_allocator), "0"));
        cutile_test_assert_m(str_equals_cstr2(s32_to_str(s32_max, default_allocator), "2147483647"));
        cutile_test_assert_m(str_equals_cstr2(s32_to_str(s32_min, default_allocator), "-2147483648"));
        cutile_test_assert_m(cstr_equals(u32_to_cstr(u32_max, default_allocator), "4294967295"));
        cutile_test_assert_m(cstr_equals(u32_to_cstr(u32_min, default_allocator), "0"));
        cutile_test_assert_m(cstr_equals(s32_to_cstr(s32_max, default_allocator), "2147483647"));
        cutile_test_assert_m(cstr_equals(s32_to_cstr(s32_min, default_allocator), "-2147483648"));

        string adfjk = u64_to_str(u64_max, default_allocator);
        cutile_test_assert_m(str_equals_cstr2(u64_to_str(u64_max, default_allocator), "18446744073709551615"));
        cutile_test_assert_m(str_equals_cstr2(u64_to_str(u64_min, default_allocator), "0"));
        cutile_test_assert_m(str_equals_cstr2(s64_to_str(s64_max, default_allocator), "9223372036854775807"));
        cutile_test_assert_m(str_equals_cstr2(s64_to_str(s64_min, default_allocator), "-9223372036854775808"));
        cutile_test_assert_m(cstr_equals(u64_to_cstr(u64_max, default_allocator), "18446744073709551615"));
        cutile_test_assert_m(cstr_equals(u64_to_cstr(u64_min, default_allocator), "0"));
        cutile_test_assert_m(cstr_equals(s64_to_cstr(s64_max, default_allocator), "9223372036854775807"));
        cutile_test_assert_m(cstr_equals(s64_to_cstr(s64_min, default_allocator), "-9223372036854775808"));
    }

    // Number to string conversions tests.
    {
        cutile_string s;

        cutile_test_assert_m(str_to_u8(&s) == 255);
        s = create_str_from_cstr("0", default_allocator);
        cutile_test_assert_m(str_to_u8(&s) == 0);
        s = create_str_from_cstr("127", default_allocator);
        cutile_test_assert_m(str_to_s8(&s) == 127);
        s = create_str_from_cstr("-128", default_allocator);
        cutile_test_assert_m(str_to_s8(&s) == -128);

        s = create_str_from_cstr("65535", default_allocator);
        cutile_test_assert_m(str_to_u16(&s) == 65535);
        s = create_str_from_cstr("0", default_allocator);
        cutile_test_assert_m(str_to_u16(&s) == 0);
        s = create_str_from_cstr("32767", default_allocator);
        cutile_test_assert_m(str_to_s16(&s) == 32767);
        s = create_str_from_cstr("-32768", default_allocator);
        cutile_test_assert_m(str_to_s16(&s) == -32768);

        s = create_str_from_cstr("4294967295", default_allocator);
        cutile_test_assert_m(str_to_u32(&s) == 4294967295);
        s = create_str_from_cstr("0", default_allocator);
        cutile_test_assert_m(str_to_u32(&s) == 0);
        s = create_str_from_cstr("2147483647", default_allocator);
        cutile_test_assert_m(str_to_s32(&s) == 2147483647);
        s = create_str_from_cstr("-2147483648", default_allocator);
        cutile_test_assert_m(str_to_s32(&s) == -2147483648);

        s = create_str_from_cstr("18446744073709551615", default_allocator);
        cutile_test_assert_m(str_to_u64(&s) == 18446744073709551615ULL);
        s = create_str_from_cstr("0", default_allocator);
        cutile_test_assert_m(str_to_u64(&s) == 0);
        s = create_str_from_cstr("9223372036854775807", default_allocator);
        cutile_test_assert_m(str_to_s64(&s) == 9223372036854775807);
        s = create_str_from_cstr("-9223372036854775808", default_allocator);
        cutile_test_assert_m(str_to_s64(&s) == -9223372036854775808ULL);

        s = create_str_from_cstr("EXTRACT 2 SUB -4839 NB 777!-1", default_allocator);
        cutile_test_assert_m(sub_str_to_u8(&s, 8, 1) == 2);
        cutile_test_assert_m(sub_str_to_s16(&s, 14, 5) == -4839);
        cutile_test_assert_m(sub_str_to_s16(&s, 23, 3) == 777);
        cutile_test_assert_m(sub_str_to_s64(&s, s.count-2, 2) == -1);
    }

    cutile_test_end_m();
}
