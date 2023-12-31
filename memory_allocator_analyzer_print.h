#ifndef CUTILE_MEMORY_ALLOCATOR_ANALYZER_PRINT_H
#define CUTILE_MEMORY_ALLOCATOR_ANALYZER_PRINT_H

#ifndef CUTILE_ALLOCATOR_ANALYZER
    #error "Cannot use \"memory_allocator_analyzer_print.h\" because CUTILE_ALLOCATOR_ANALYZER is not defined."
#endif

#include "./memory.h"
#include "./print.hpp"

force_inline void print_allocation_table_state(allocation_table* table)
{
    u32 total_allocated = table->total_allocated;
    u32 total_freed = table->total_freed;
    for (u32 i = 0; i < table->infos.count; ++i)
    {
        allocation_info alloc_info = table->infos.data[i];
        if (alloc_info.status == allocation_info_status_unavailable)
        {
            println("Block of size % not freed at address %:", alloc_info.size, alloc_info.address);
            for (u32 i = 0; i < alloc_info.stacktrace.calls.count; ++i)
            {
                stacktrace_elem stacktrace_elem = alloc_info.stacktrace.calls.data[i];
                println("\t %.% (%)", stacktrace_elem.filename, stacktrace_elem.line, stacktrace_elem.symbol_name);
            }
        }
        else if (alloc_info.status == allocation_info_status_invalid_address)
        {
            println("Invalid free of %:", alloc_info.address);
            for (u32 i = 0; i < alloc_info.free_stacktraces.count; ++i)
            {
                println("\tDeallocation %:", i);
                stacktrace* st = &alloc_info.free_stacktraces.data[i];
                for (u32 i = 0; i < st->calls.count; ++i)
                {
                    stacktrace_elem stacktrace_elem = st->calls.data[i];
                    println("\t\t %.% (%)", stacktrace_elem.filename, stacktrace_elem.line, stacktrace_elem.symbol_name);
                }
            }
        }
        else if (alloc_info.status == allocation_info_status_double_free)
        {
            println("Double free of %:", alloc_info.address);
            for (u32 i = 0; i < alloc_info.free_stacktraces.count; ++i)
            {
                println("\tDeallocation %:", i);
                stacktrace* st = &alloc_info.free_stacktraces.data[i];
                for (u32 i = 0; i < st->calls.count; ++i)
                {
                    stacktrace_elem stacktrace_elem = st->calls.data[i];
                    println("\t\t %.% (%)", stacktrace_elem.filename, stacktrace_elem.line, stacktrace_elem.symbol_name);
                }
            }
        }
    }
    println("Total allocated bytes: %.", total_allocated);
    println("Total freed bytes: %.", total_freed);
}

#endif
