#define CUTILE_IMPLEM
#include "../hash_table.h"
#include "../test.h"

u64 dummy_hash(u8* data, u64 data_size)
{
    return data[0];
};

b8 dummy_compare(u8* lhs, u64 lhs_size, u8* rhs, u64 rhs_size)
{
    if (rhs_size != lhs_size) return b8_false;
    for (u32 i = 0; i < rhs_size; ++i)
    {
        if (lhs[i] != rhs[i]) return b8_false;
    }
    return b8_true;
}

int main(int ac, char** av)
{
    test_begin();

    initialize_global_default_heap_allocator();

    hash_table tbl = create_hash_table(24,
                                       &dummy_hash,
                                       &dummy_compare,
                                       sizeof(u8),
                                       &global_default_heap_allocator);

    u8* val = hash_table_emplace(&tbl, "1", 1);
    *val = 55;
    test_assert(*hash_table_get(&tbl, "1", 1) == 55);

    u8* val2 = hash_table_emplace(&tbl, "2", 1);
    *val2 = 128;
    test_assert(*hash_table_get(&tbl, "2", 1) == 128);

    u8* val5 = hash_table_emplace(&tbl, "5", 1);
    *val5 = 3;
    test_assert(*hash_table_get(&tbl, "5", 1) == 3);
    
    u8* val11 = hash_table_emplace(&tbl, "11", 2);
    *val11 = 12;
    test_assert(*hash_table_get(&tbl, "11", 2) == 12);

    test_assert(tbl.count == 4);

    hash_table_remove(&tbl, "1", 1);
    test_assert(hash_table_get(&tbl, "1", 1) == nullptr);

    test_assert(tbl.count == 3);

    test_assert(*hash_table_get(&tbl, "11", 2) == 12);

    test_end();
}
