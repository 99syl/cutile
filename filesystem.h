#ifndef CUTILE_FILESYSTEM_H
#define CUTILE_FILESYSTEM_H

#include "./num_types.h"
#include "./array.h"

// Defined in str.h
typedef struct string string;

bool8 file_exists(string* path);
bool8 file_exists_cstr(const char* path);

bool8 directory_exists(string* path);
bool8 directory_exists_cstr(const char* path);

typedef enum file_access_mode
{
    file_access_mode_read,
    file_access_mode_write,
    file_access_mode_read_write
} file_access_mode;

typedef struct file
{
    void* handle; // Platform/OS handle.
} file;

file open_file(file_access_mode access_mode, const char* path);
void close_file(file* file);

// Defined in memory.h
typedef struct allocator allocator;

typedef struct
{
    u8* content;
    u64 size_in_bytes;
} get_file_content_result;
get_file_content_result get_file_content_from_path(const char* path, allocator* allocator);
get_file_content_result get_file_content(file* file, allocator* allocator);

void read_from_file(file* file, u8* out, u64 nb_bytes_to_read);

void write_in_file(file* file, const u8* buffer, u64 buffer_size_in_bytes);

u64 get_file_size(file* file);

char* get_current_executable_path(allocator* allocator);
char* get_current_executable_dir_path(allocator* allocator);

#ifdef CUTILE_IMPLEM

    #ifdef _WIN32
        #include <windows.h>
    #endif

    #include "./str.h"

    bool8 file_exists(string* path)
    {
        char* cpath = create_cstr_from_str(path, path->allocator);
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
        char* cpath = create_cstr_from_str(path, path->allocator);
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

    file open_file(file_access_mode access_mode, const char* path)
    {
        file result;

        #ifdef _WIN32
            DWORD win32_access_mode = 0;
            switch (access_mode)
            {
                case file_access_mode_read: win32_access_mode = GENERIC_READ; break;
                case file_access_mode_write: win32_access_mode = GENERIC_WRITE; break;
                case file_access_mode_read_write: win32_access_mode = GENERIC_READ | GENERIC_WRITE; break;
            }
            result.handle = (void*)CreateFileA(
                path,
                win32_access_mode,
                0, // TODO: Make this value configurable maybe ?
                NULL,
                OPEN_EXISTING, //TODO: Make this value configurable maybe ?
                FILE_ATTRIBUTE_NORMAL, // TODO: Make this value configurable maybe ?
                NULL);
        #endif

        return result;
    }

    void close_file(file* file)
    {
        #ifdef _WIN32
            CloseHandle(file->handle);
        #endif
    }

    void write_in_file(file* file, const u8* buffer, u64 buffer_size_in_bytes)
    {
        #ifdef _WIN32
            DWORD written_bytes = 0;
            do
            {
                if (!WriteFile(file->handle, buffer + written_bytes, buffer_size_in_bytes - written_bytes, &written_bytes, nullptr)) break;
            } while (written_bytes < buffer_size_in_bytes);
        #endif
    }
    
    u64 get_file_size(file* file)
    {
        u64 result;

        #ifdef _WIN32
            GetFileSizeEx((HANDLE)file->handle, (PLARGE_INTEGER)&result);
        #endif

        return result;
    }

    void read_from_file(file* file, u8* out, u64 nb_bytes_to_read)
    {
        #ifdef _WIN32
            DWORD read_bytes = 0;
            do
            {
                if (!ReadFile(file->handle, out + read_bytes, nb_bytes_to_read - read_bytes, &read_bytes, nullptr)) break;
            } while (read_bytes < nb_bytes_to_read);
        #endif
    }

    get_file_content_result get_file_content_from_path(const char* path, allocator* allocator)
    {
        file file = open_file(file_access_mode_read, path);
        get_file_content_result result = get_file_content(&file, allocator);
        close_file(&file);
        return result;
    }

    get_file_content_result get_file_content(file* file, allocator* allocator)
    {
        u64 file_size = get_file_size(file);
        u8* data = (u8*)allocate(allocator, file_size);
        read_from_file(file, data, file_size);
        get_file_content_result result;
        result.content = data;
        result.size_in_bytes = file_size;
        return result;
    }

    char* get_current_executable_path(allocator* allocator)
    {
        #ifdef _WIN32
            char tmp[MAX_PATH];
            DWORD path_len = GetModuleFileNameA(NULL, tmp, MAX_PATH);
            DWORD err = GetLastError();
            if (err == ERROR_INSUFFICIENT_BUFFER || !path_len) return nullptr;
            char* result = (char*)allocate(allocator, sizeof(char) * path_len + 1);
            copy_s8_memory(result, tmp, path_len);
            result[path_len] = '\0';
            return result;
        #endif
    }
    char* get_current_executable_dir_path(allocator* allocator)
    {
        char* exe_path = get_current_executable_path(allocator);
        #ifdef _WIN32
            u32 last_sep_index = 0;
            for (u32 i = 0; exe_path[i]; ++i)
            {
                if (exe_path[i] == '\\') last_sep_index = i;
            }
            char* exe_dir = create_cstr_from_sub_cstr(exe_path, 0, last_sep_index, allocator);
            deallocate(allocator, exe_path);
            return exe_dir;
        #endif
    }

#endif // CUTILE_IMPLEM

#endif // !CUTILE_FILESYSTEM_H
