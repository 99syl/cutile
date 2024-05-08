#define CUTILE_IMPLEM
#include "../memory_allocator_analyzer.h"
#include "../memory_allocator_analyzer_print.h"
#include "../test.h"

test_begin();

allocator* default_allocator;

int main(int ac, char** av)
{
    // The allocator used by the allocation table to store allocation data.
    u8              allocation_table_data[U16_MAX];
    arena_allocator allocation_table_arena = create_arena_allocator(allocation_table_data, U16_MAX);

    // Where our allocation informations goes.
    allocation_table allocations_data = start_allocators_analysis_m(&allocation_table_arena);

    // The allocator we want to analyze.
    analyzable_heap_allocator heap_allocator_to_analyze = create_analyzable_heap_allocator(&allocations_data);
    default_allocator = (allocator*)&heap_allocator_to_analyze;

    string s = create_sized_empty_str(2048, default_allocator);
    string s2 = create_sized_empty_str(4096, default_allocator);

    print_allocation_table(&allocations_data, (allocator*)&allocation_table_arena);

    finish_allocators_analysis(&allocations_data);

    test_end();
}
