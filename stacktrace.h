#ifndef CUTILE_STACKTRACE_H

    #ifndef _WIN32
        #error "stacktrace.h is not supported yet on other platforms than WIN32"
    #endif

    #include "array.h"

    typedef struct cutile_stacktrace_elem
    {
        u32               line;
        char*             filename;
        char*             symbol_name;
        cutile_allocator* allocator;
    } cutile_stacktrace_elem;
    
    declare_array_of_m(stacktrace_elem);
    
    typedef struct cutile_stacktrace
    {
        cutile_stacktrace_elem_array calls;
    } cutile_stacktrace;
    
    declare_array_of_m(stacktrace);
    
    stacktrace  get_stacktrace(u16 skip, u16 depth, allocator* allocator);
    b8          fill_stacktrace(stacktrace* stacktrace, u16 skip, u16 depth);
    void        clear_stacktrace(stacktrace* stacktrace);
    void        destroy_stacktrace(stacktrace* stacktrace);
    
    #ifdef CUTILE_IMPLEM
    
        #ifdef _WIN32
            #include <windows.h>
            #ifdef _MSC_VER
                #pragma comment(lib, "DbgHelp.lib")
            #endif
            #include <dbghelp.h>
            #include "print.h"
            // str.h:
            CUTILE_C_API char* create_cstr_from_cstr(const char*, allocator*);
            CUTILE_C_API char* create_cstr_from_sub_cstr(const char*, u32, u32, allocator*);
        #endif
    
        stacktrace get_stacktrace(u16 skip, u16 depth, allocator* allocator)
        {
            stacktrace result;
            result.calls = create_stacktrace_elem_array(500, 5, allocator);
            fill_stacktrace(&result, skip + 1, depth);
            return result;
        }
    
        b8 fill_stacktrace(stacktrace* stacktrace, u16 skip, u16 depth)
        {
            u16 current_skip = 0;
            u16 current_depth = 0;
            #ifdef _WIN32
                persist HANDLE current_process = nullptr;
                HANDLE current_thread = GetCurrentThread();
                CONTEXT context;
                STACKFRAME64 stackframe;
                
                if (!current_process)
                {
                    current_process = GetCurrentProcess();
                    if (!SymInitialize(current_process, nullptr, TRUE))
                    {
                        return b8_false;
                    }
                }
                RtlCaptureContext(&context);
                fill_s8_memory((s8*)&stackframe, sizeof(STACKFRAME64), 0);
                stackframe.AddrPC.Offset = context.Rip;
                stackframe.AddrPC.Mode = AddrModeFlat;
                stackframe.AddrFrame.Offset = context.Rbp;
                stackframe.AddrFrame.Mode = AddrModeFlat;
                stackframe.AddrStack.Offset = context.Rsp;
                stackframe.AddrStack.Mode = AddrModeFlat;
    
                do
                {
                    if (StackWalk(IMAGE_FILE_MACHINE_AMD64, current_process, current_thread, &stackframe, &context, nullptr, &SymFunctionTableAccess64, &SymGetModuleBase64, nullptr))
                    {
                        if (current_skip < skip + 1)
                        {
                            ++current_skip;
                            continue;
                        }
                        
                        if (current_depth < depth) ++current_depth;
                        else break;
    
                        DWORD64         displacement;
                        DWORD           line_displacement;
                        s8              symbol_info[sizeof(SYMBOL_INFO) + 255];
                        IMAGEHLP_LINE64 line_info;
                        PSYMBOL_INFO    psymbol_info = (PSYMBOL_INFO)symbol_info;
                        
                        psymbol_info->SizeOfStruct = sizeof(SYMBOL_INFO);
                        psymbol_info->MaxNameLen = 255;
                        line_info.SizeOfStruct = sizeof(IMAGEHLP_LINE64);
                        if (SymFromAddr(current_process, stackframe.AddrPC.Offset, &displacement, (PSYMBOL_INFO)symbol_info) &&
                            SymGetLineFromAddr(current_process, stackframe.AddrPC.Offset, &line_displacement, &line_info))
                        {
                            stacktrace_elem stacktrace_elem;
                            stacktrace_elem.line = line_info.LineNumber;
                            stacktrace_elem.allocator = stacktrace->calls.allocator;
                            stacktrace_elem.filename = create_cstr_from_cstr(line_info.FileName, stacktrace_elem.allocator);
                            stacktrace_elem.symbol_name = create_cstr_from_sub_cstr(psymbol_info->Name, 0, psymbol_info->NameLen, stacktrace_elem.allocator);
                            stacktrace_elem_array_push(&stacktrace->calls, stacktrace_elem);
                        }
                        else break;
                    }
                    else break;
                } while (b8_true);
    
            return b8_true;
    
            #endif
        }
    
        internal void destroy_stacktrace_elem(stacktrace_elem* e)
        {
            deallocate(e->allocator, e->filename);
            e->filename = nullptr;
            deallocate(e->allocator, e->symbol_name);
            e->symbol_name = nullptr;
            e->allocator = nullptr;
        }
    
        void clear_stacktrace(stacktrace* stacktrace)
        {
            clear_stacktrace_elem_array_deeply(&stacktrace->calls, &destroy_stacktrace_elem);
        }
    
        void destroy_stacktrace(stacktrace* stacktrace)
        {
            destroy_stacktrace_elem_array_deeply(&stacktrace->calls, &destroy_stacktrace_elem);
        }
    
    #endif // CUTILE_IMPLEM

    #define CUTILE_STACKTRACE_H
#endif
