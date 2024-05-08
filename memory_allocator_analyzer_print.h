#ifndef CUTILE_MEMORY_ALLOCATOR_ANALYZER_PRINT_H

    #include "memory_allocator_analyzer.h"
    #include "print.h"
    
    maybe_inline void print_allocation_table(allocation_table* status, allocator* allocator)
    {
        string str = create_sized_empty_str(1024, allocator);
    
        for (u32 i = 0; i < status->allocations.count; ++i)
        {
            allocation_info* alloc_info = &status->allocations.data[i];
    
            if (alloc_info->status == allocation_info_status_unavailable)
            {
                str_push_back_cstr(&str, "Block of size ");
                u64_into_str(alloc_info->size, &str);
                str_push_back_cstr(&str, " not freed at address ");
                u64_into_str((u64)alloc_info->address, &str);
                str_push_back_cstr(&str, ":\n");
                for (u32 i = 0; i < alloc_info->stacktrace.calls.count; ++i)
                {
                    stacktrace_elem* stacktrace_elem = &alloc_info->stacktrace.calls.data[i];
                    str_push_back_cstr(&str, "\t ");
                    str_push_back_cstr(&str, stacktrace_elem->filename);
                    str_push_back(&str, '.');
                    u32_into_str(stacktrace_elem->line, &str);
                    str_push_back_cstr(&str, " (");
                    str_push_back_cstr(&str, stacktrace_elem->symbol_name);
                    str_push_back_cstr(&str, ")\n");
                }
            }
            else if (alloc_info->status == allocation_info_status_invalid_address)
            {
                str_push_back_cstr(&str, "Invalid free of ");
                u64_into_str((u64)alloc_info->address, &str);
                str_push_back_cstr(&str, ":\n");
                for (u32 i = 0; i < alloc_info->free_stacktraces.count; ++i)
                {
                    str_push_back_cstr(&str, "\tDeallocation ");
                    u64_into_str(i, &str);
                    str_push_back_cstr(&str, ":\n");
    
                    stacktrace* st = &alloc_info->free_stacktraces.data[i];
                    for (u32 i = 0; i < st->calls.count; ++i)
                    {
                        stacktrace_elem* stacktrace_elem = &st->calls.data[i];
                        str_push_back_cstr(&str, "\t\t ");
                        str_push_back_cstr(&str, stacktrace_elem->filename);
                        str_push_back(&str, '.');
                        u32_into_str(stacktrace_elem->line, &str);
                        str_push_back_cstr(&str, " (");
                        str_push_back_cstr(&str, stacktrace_elem->symbol_name);
                        str_push_back_cstr(&str, ")\n");
                    }
                }
            }
            else if (alloc_info->status == allocation_info_status_double_free)
            {
                str_push_back_cstr(&str, "Double free of ");
                u64_into_str((u64)alloc_info->address, &str);
                str_push_back_cstr(&str, ":\n");
                for (u32 i = 0; i < alloc_info->free_stacktraces.count; ++i)
                {
                    str_push_back_cstr(&str, "\tDeallocation ");
                    u64_into_str(i, &str);
                    str_push_back_cstr(&str, ":\n");
    
                    stacktrace* st = &alloc_info->free_stacktraces.data[i];
                    for (u32 i = 0; i < st->calls.count; ++i)
                    {
                        stacktrace_elem* stacktrace_elem = &st->calls.data[i];
                        str_push_back_cstr(&str, "\t\t ");
                        str_push_back_cstr(&str, stacktrace_elem->filename);
                        str_push_back(&str, '.');
                        u32_into_str(stacktrace_elem->line, &str);
                        str_push_back_cstr(&str, " (");
                        str_push_back_cstr(&str, stacktrace_elem->symbol_name);
                        str_push_back_cstr(&str, ")\n");
                    }
                }
            }
        }
    
        str_push_back_cstr(&str, "Total allocated: ");
        u64_into_str(status->total_allocated, &str);
        str_push_back_cstr(&str, " bytes.\n");
        str_push_back_cstr(&str, "Total freed: ");
        u64_into_str(status->total_freed, &str);
        str_push_back_cstr(&str, " bytes.\n");
    
        print(&str);
        destroy_str(&str);
    }

    #define CUTILE_MEMORY_ALLOCATOR_ANALYZER_PRINT_H
#endif
