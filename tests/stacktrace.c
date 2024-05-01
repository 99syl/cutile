#define CUTILE_IMPLEM
#include "../stacktrace.h"
#include "../test.h"

test_begin();

void depth_two()
{
    stacktrace st = get_stacktrace(0, U16_MAX, &global_default_heap_allocator);
    destroy_stacktrace(&st);
}

void depth_one()
{
    stacktrace st = get_stacktrace(0, U16_MAX, &global_default_heap_allocator);
    {
        stacktrace_elem* st_elem;
        
        test_require(st.calls.count > 2);
        
        st_elem = &st.calls.data[0];
        test_assert(cstr_equals("depth_one", st_elem->symbol_name));
        
        st_elem = &st.calls.data[1];
        test_assert(cstr_equals("main", st_elem->symbol_name));
        
        destroy_stacktrace(&st);
    }
    depth_two();
}

int main(void)
{
    initialize_global_default_heap_allocator();
    depth_one();
    test_end();
}