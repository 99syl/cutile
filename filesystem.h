#ifndef CUTILE_FILESYSTEM_H
#define CUTILE_FILESYSTEM_H

#include "./num_types.h"

struct string;
#ifdef CUTILE_C
typedef struct string string;
#endif // CUTILE_C

bool8 file_exists(string* path);
bool8 file_exists_cstr(const char* path);

bool8 directory_exists(string* path);
bool8 directory_exists_cstr(const char* path);

#ifdef CUTILE_IMPLEM

#ifdef _WIN32
#include <windows.h>
#endif

#include "./str.h"

bool8 file_exists(string* path)
{
    const char* cpath = create_cstr_from_str(path, path->allocator);
    bool8 res = file_exists_cstr(cpath);
    deallocate(path->allocator, cpath);
    return res;
}
bool8 file_exists_cstr(const char* path)
{
#ifdef _WIN32
    DWORD dwAttrib = GetFileAttributesA(path);
    return (dwAttrib != INVALID_FILE_ATTRIBUTES);
#endif
}

bool8 directory_exists(string* path)
{
    const char* cpath = create_cstr_from_str(path, path->allocator);
    bool8 res = directory_exists_cstr(cpath);
    deallocate(path->allocator, cpath);
    return res;
}
bool8 directory_exists_cstr(const char* path)
{
#ifdef _WIN32
    DWORD dwAttrib = GetFileAttributesA(path);
    return (dwAttrib != INVALID_FILE_ATTRIBUTES && (dwAttrib & FILE_ATTRIBUTE_DIRECTORY));
#endif
}

#endif // CUTILE_IMPLEM

#endif