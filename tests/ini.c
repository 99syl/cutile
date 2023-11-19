#define CUTILE_IMPLEM
#include "../ini.h"
#include "../test.h"

int main(int ac, char** av)
{
    basic_heap_allocator = create_basic_heap_allocator();
    const char ini_data[] =
        "foo=123\n"
        "bar=Value\n"
        "[SectionA]\n"
        "rab=321\n"
        ";; comment\n"
        "oof=uelaV";

    parse_ini_result result = parse_ini((const u8*)ini_data, sizeof(ini_data)/sizeof(char) - 1 /*  */, &basic_heap_allocator);
    ini_entry_value_result entry_value;
    entry_value = get_ini_global_entry_value("foo", &result);
    {
        test_assert(entry_value.found == bool8_true);
        test_assert(entry_value.value_start[0] == '1');
        test_assert(entry_value.value_size == 3);
    }
    entry_value = get_ini_global_entry_value("bar", &result);
    {
        test_assert(entry_value.found == bool8_true);
        test_assert(entry_value.value_start[0] == 'V');
        test_assert(entry_value.value_size == 5);
    }
    entry_value = get_ini_entry_value("SectionA", "rab", &result);
    {
        test_assert(entry_value.found == bool8_true);
        test_assert(entry_value.value_start[0] == '3');
        test_assert(entry_value.value_size == 3);
    }
    entry_value = get_ini_entry_value("SectionA", "oof", &result);
    {
        test_assert(entry_value.found == bool8_true);
        test_assert(entry_value.value_start[0] == 'u');
        test_assert(entry_value.value_size == 5);
    }
    
    return test_result;
}
