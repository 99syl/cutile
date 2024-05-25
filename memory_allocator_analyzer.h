// TODO: This API is a first draft, let's think later (or not) of a clever design...

#ifndef CUTILE_MEMORY_ALLOCATOR_ANALYZER_H

    #ifndef _WIN32
        #error "Only WIN32 platforms are supported at the moment."
    #endif

    #include "stacktrace.h"

    typedef enum
    {
        cutile_allocation_info_status_available,
        cutile_allocation_info_status_unavailable,
        cutile_allocation_info_status_invalid_address,
        cutile_allocation_info_status_double_free,
    } cutile_allocation_info_status;
    
    typedef struct
    {
        void*                  address;
        u64                    size;
    
        cutile_stacktrace             stacktrace;
        cutile_stacktrace_array       free_stacktraces;
    
        cutile_allocation_info_status status;
    } cutile_allocation_info;
    
    declare_array_of_m(allocation_info);
    
    typedef struct allocation_table
    {
        allocation_info_array allocations;
        u64                   total_allocated;
        u64                   total_freed;
    } allocation_table;

    // The allocator will be used to allocate data required to store allocations information. For obvious reason, it should be a different allocator than the ones being analyzed :).
    // Please note that to make the analysis working, you must use the returned value for your allocations and not the one given as parameters.
    CUTILE_C_API allocation_table start_allocators_analysis(allocator*);
    #define                       start_allocators_analysis_m(allocator_ptr)
    CUTILE_C_API void             finish_allocators_analysis(allocation_table*);

    // Call those functions in your own allocator in order to update allocation information in the table.
    void add_new_alloc_info(allocation_table* table, u64 size, void* address);
    b8   try_remove_alloc_info(allocation_table* table, void* address);

    typedef struct
    {
        declare_allocator_m;

        heap_allocator    heap_allocator;
        allocation_table* table;

        void (*bad_deallocate_handler)(struct allocation_table*, void*);
    } analyzable_heap_allocator;
    analyzable_heap_allocator create_analyzable_heap_allocator(allocation_table*);

    #ifdef CUTILE_IMPLEM

        void add_new_alloc_info(allocation_table* table, u64 size, void* address)
        {
            allocation_info* alloc_info = nullptr;

            // Search for an available node.
            for (u32 i = 0; i < table->allocations.count; ++i)
            {
                if (table->allocations.data[i].status == allocation_info_status_available)
                {
                    alloc_info = &table->allocations.data[i];
                    clear_stacktrace(&alloc_info->stacktrace);
                    clear_stacktrace_array_deeply(&alloc_info->free_stacktraces, &clear_stacktrace);
                    break;
                }
            }

            // No available node found so add a new one.
            if (alloc_info == nullptr)
            {
                allocation_info new_elem;
                new_elem.stacktrace = get_stacktrace(1, U16_MAX, table->allocations.allocator);
                new_elem.free_stacktraces = create_stacktrace_array(2, 2, table->allocations.allocator);
                allocation_info_array_push(&table->allocations, new_elem);
                alloc_info = &table->allocations.data[table->allocations.count - 1];
            }
            else fill_stacktrace(&alloc_info->stacktrace, 1, U16_MAX);

            alloc_info->status = allocation_info_status_unavailable;
            alloc_info->address = address;
            alloc_info->size = size;

            table->total_allocated += size;
        }

        b8 try_remove_alloc_info(allocation_table* table, void* address)
        {
            stacktrace st = get_stacktrace(1, U16_MAX, table->allocations.allocator);
            for (u32 i = 0; i < table->allocations.count; ++i)
            {
                allocation_info* alloc_info = &table->allocations.data[i];
                if (alloc_info->address == address)
                {
                    stacktrace_array_push(&alloc_info->free_stacktraces, st);
                    switch (alloc_info->status)
                    {
                    case allocation_info_status_unavailable:
                        table->total_freed += alloc_info->size;
                        alloc_info->status = allocation_info_status_available;
                        return b8_true;
                    case allocation_info_status_available:
                    case allocation_info_status_double_free:
                        alloc_info->status = allocation_info_status_double_free;
                        return b8_false;
                    case allocation_info_status_invalid_address:
                        return b8_false;
                    }
                }
            }

            // Address never allocated!!!
            allocation_info new_elem;
            new_elem.free_stacktraces = create_stacktrace_array(2, 2, table->allocations.allocator);
            new_elem.status = allocation_info_status_invalid_address;
            new_elem.address = address;
            new_elem.size = 0;
            stacktrace_array_push(&new_elem.free_stacktraces, st);
            allocation_info_array_push(&table->allocations, new_elem);
            return b8_false;
        }

        allocation_table start_allocator_analysis(allocator* allocatorrr)
        {
            allocation_table result;

            result.allocations = create_allocation_info_array(20, 20, allocatorrr);
            result.total_allocated = 0;
            result.total_freed = 0;

            return result;
        }

        internal void destroy_allocation_info(allocation_info* inf)
        {
            destroy_stacktrace(&inf->stacktrace);
            destroy_stacktrace_array_deeply(&inf->free_stacktraces, &destroy_stacktrace);
        }

        void finish_allocators_analysis(allocation_table* table)
        {
            destroy_allocation_info_array_deeply(&table->allocations, &destroy_allocation_info);
        }

        internal void* analyzable_heap_allocator_allocate(allocator* opaque_wrapper_allocator, u64 size)
        {
            analyzable_heap_allocator* wrapper = (analyzable_heap_allocator*)opaque_wrapper_allocator;

            void* result = allocate((allocator*)&wrapper->heap_allocator, size);
            add_new_alloc_info(wrapper->table, size, result);

            return result;
        }

        internal void analyzable_heap_allocator_deallocate(allocator* opaque_wrapper_allocator, void* ptr)
        {
            analyzable_heap_allocator* wrapper = (analyzable_heap_allocator*)opaque_wrapper_allocator;

            if (try_remove_alloc_info(wrapper->table, ptr))
            {
                deallocate((allocator*)&wrapper->heap_allocator, ptr);
            }
            else
            {
                if (wrapper->bad_deallocate_handler) wrapper->bad_deallocate_handler(wrapper->table, ptr);
            }
        }

        analyzable_heap_allocator create_analyzable_heap_allocator(allocation_table* tbl)
        {
            analyzable_heap_allocator result;
            result.__allocator_base.allocate = &analyzable_heap_allocator_allocate;
            result.__allocator_base.deallocate = &analyzable_heap_allocator_deallocate;
            result.heap_allocator = create_default_heap_allocator();
            result.table = tbl;
            result.bad_deallocate_handler = nullptr;
            return result;
        }

    #endif // CUTILE_IMPLEM

    #undef  start_allocators_analysis_m
    #define start_allocators_analysis_m(allocator_ptr) start_allocator_analysis((allocator*)allocator_ptr)

    #define CUTILE_MEMORY_ALLOCATOR_ANALYZER_H
#endif
