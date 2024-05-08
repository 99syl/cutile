#define CUTILE_IMPLEM
#include "../str.h"
#include "../test.h"

int main(int ac, char** av)
{
    test_begin();

    allocator* default_allocator;
    heap_allocator heapallocator = create_default_heap_allocator();
    default_allocator = (allocator*)&heapallocator;

    // UTF-8
    {
        string s1 = create_str_from_cstr("こんにちは！", default_allocator);
        string s2 = create_str_from_cstr("プログラミングが好き。", default_allocator);
        string s3 = create_str_from_cstr("ASCIIとUTF-8.", default_allocator);

        test_assert(str_is_valid_utf8(&s1));
        test_assert(str_is_valid_utf8(&s2));
        test_assert(str_is_valid_utf8(&s3));

        test_assert(str_utf8_count(&s1) == 6);
        test_assert(str_utf8_count(&s2) == 11);
        test_assert(str_utf8_count(&s3) == 12);
    }

    // String to number conversions tests.
    {
        u32 i = 50;
        s32 j = -12893;
        s64 k = 2438750912;
    
        string si = u32_to_str(i, default_allocator);
        string sj = s32_to_str(j, default_allocator);
        string sk = s64_to_str(k, default_allocator);
        u32_into_str(i, &sk);

        test_assert(str_equals_cstr(&si, "50"));
        test_assert(str_equals_cstr(&sj, "-12893"));
        test_assert(str_equals_cstr(&sk, "243875091250"));

        test_assert(str_equals_cstr2(u8_to_str(u8_max, default_allocator), "255"));
        test_assert(str_equals_cstr2(u8_to_str(u8_min, default_allocator), "0"));
        test_assert(str_equals_cstr2(s8_to_str(s8_max, default_allocator), "127"));
        test_assert(str_equals_cstr2(s8_to_str(s8_min, default_allocator), "-128"));
        test_assert(cstr_equals(u8_to_cstr(u8_max, default_allocator), "255"));
        test_assert(cstr_equals(u8_to_cstr(u8_min, default_allocator), "0"));
        test_assert(cstr_equals(s8_to_cstr(s8_max, default_allocator), "127"));
        test_assert(cstr_equals(s8_to_cstr(s8_min, default_allocator), "-128"));

        test_assert(str_equals_cstr2(u16_to_str(u16_max, default_allocator), "65535"));
        test_assert(str_equals_cstr2(u16_to_str(u16_min, default_allocator), "0"));
        test_assert(str_equals_cstr2(s16_to_str(s16_max, default_allocator), "32767"));
        test_assert(str_equals_cstr2(s16_to_str(s16_min, default_allocator), "-32768"));
        test_assert(cstr_equals(u16_to_cstr(u16_max, default_allocator), "65535"));
        test_assert(cstr_equals(u16_to_cstr(u16_min, default_allocator), "0"));
        test_assert(cstr_equals(s16_to_cstr(s16_max, default_allocator), "32767"));
        test_assert(cstr_equals(s16_to_cstr(s16_min, default_allocator), "-32768"));

        test_assert(str_equals_cstr2(u32_to_str(u32_max, default_allocator), "4294967295"));
        test_assert(str_equals_cstr2(u32_to_str(u32_min, default_allocator), "0"));
        test_assert(str_equals_cstr2(s32_to_str(s32_max, default_allocator), "2147483647"));
        test_assert(str_equals_cstr2(s32_to_str(s32_min, default_allocator), "-2147483648"));
        test_assert(cstr_equals(u32_to_cstr(u32_max, default_allocator), "4294967295"));
        test_assert(cstr_equals(u32_to_cstr(u32_min, default_allocator), "0"));
        test_assert(cstr_equals(s32_to_cstr(s32_max, default_allocator), "2147483647"));
        test_assert(cstr_equals(s32_to_cstr(s32_min, default_allocator), "-2147483648"));

        string adfjk = u64_to_str(u64_max, default_allocator);
        test_assert(str_equals_cstr2(u64_to_str(u64_max, default_allocator), "18446744073709551615"));
        test_assert(str_equals_cstr2(u64_to_str(u64_min, default_allocator), "0"));
        test_assert(str_equals_cstr2(s64_to_str(s64_max, default_allocator), "9223372036854775807"));
        test_assert(str_equals_cstr2(s64_to_str(s64_min, default_allocator), "-9223372036854775808"));
        test_assert(cstr_equals(u64_to_cstr(u64_max, default_allocator), "18446744073709551615"));
        test_assert(cstr_equals(u64_to_cstr(u64_min, default_allocator), "0"));
        test_assert(cstr_equals(s64_to_cstr(s64_max, default_allocator), "9223372036854775807"));
        test_assert(cstr_equals(s64_to_cstr(s64_min, default_allocator), "-9223372036854775808"));
    }

    // Number to string conversions tests.
    {
	string s;

        test_assert(str_to_u8(&s) == 255);
        s = create_str_from_cstr("0", default_allocator);
        test_assert(str_to_u8(&s) == 0);
        s = create_str_from_cstr("127", default_allocator);
        test_assert(str_to_s8(&s) == 127);
        s = create_str_from_cstr("-128", default_allocator);
        test_assert(str_to_s8(&s) == -128);

        s = create_str_from_cstr("65535", default_allocator);
        test_assert(str_to_u16(&s) == 65535);
        s = create_str_from_cstr("0", default_allocator);
        test_assert(str_to_u16(&s) == 0);
        s = create_str_from_cstr("32767", default_allocator);
        test_assert(str_to_s16(&s) == 32767);
        s = create_str_from_cstr("-32768", default_allocator);
        test_assert(str_to_s16(&s) == -32768);

        s = create_str_from_cstr("4294967295", default_allocator);
        test_assert(str_to_u32(&s) == 4294967295);
        s = create_str_from_cstr("0", default_allocator);
        test_assert(str_to_u32(&s) == 0);
        s = create_str_from_cstr("2147483647", default_allocator);
        test_assert(str_to_s32(&s) == 2147483647);
        s = create_str_from_cstr("-2147483648", default_allocator);
        test_assert(str_to_s32(&s) == -2147483648);

        s = create_str_from_cstr("18446744073709551615", default_allocator);
        test_assert(str_to_u64(&s) == 18446744073709551615);
        s = create_str_from_cstr("0", default_allocator);
        test_assert(str_to_u64(&s) == 0);
        s = create_str_from_cstr("9223372036854775807", default_allocator);
        test_assert(str_to_s64(&s) == 9223372036854775807);
        s = create_str_from_cstr("-9223372036854775808", default_allocator);
        test_assert(str_to_s64(&s) == -9223372036854775808);

        s = create_str_from_cstr("EXTRACT 2 SUB -4839 NB 777!-1", default_allocator);
        test_assert(sub_str_to_u8(&s, 8, 1) == 2);
        test_assert(sub_str_to_s16(&s, 14, 5) == -4839);
        test_assert(sub_str_to_s16(&s, 23, 3) == 777);
        test_assert(sub_str_to_s64(&s, s.count-2, 2) == -1);
    }

    test_end();
}
