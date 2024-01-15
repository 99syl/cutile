#ifndef CUTILE_FILESYSTEM_H
#define CUTILE_FILESYSTEM_H

#include "num_types.h"
#include "array.h"

// Defined in str.h.
typedef struct string string;

typedef struct file
{
    void* handle; // Platform handle.
} file;

CUTILE_C_API b8 file_exists(string* path);
CUTILE_C_API b8 file_exists_cstr(const char* path);

CUTILE_C_API b8 directory_exists(string* path);
CUTILE_C_API b8 directory_exists_cstr(const char* path);

// This function copies a file to a new path.
// If the new path corresponds to an existing file, overwrite parameters tells if it should be overwritten. Therefore, if the new path already correponds to an existing file and overwritten is set to false, the function returns false.
CUTILE_C_API b8 copy_file(const char* path_of_file_to_copy, const char* path_of_new_file, b8 overwrite);

typedef enum file_access_mode
{
    file_access_mode_read          = 1 << 0,
    file_access_mode_write         = 1 << 1,
    file_access_mode_read_write    = file_access_mode_read | file_access_mode_write
} file_access_mode;

typedef enum file_create_mode
{
    file_create_if_not_exists = 0 << 1,
    file_always_create        = 1 << 0
} file_create_mode;

CUTILE_C_API b8   open_file(file_access_mode access_mode, const char* path, file* out);
CUTILE_C_API b8   create_file(file_create_mode create_mode, file_access_mode access_mode, const char* path, file* out);
CUTILE_C_API void close_file(file* file);

// Defined in memory.h.
typedef struct allocator allocator;

CUTILE_C_API b8 get_file_content_from_path(const char* path, allocator* allocator, u8** out, u64* size_in_bytes);
CUTILE_C_API b8 get_file_content(file* file, allocator* allocator, u8** out, u64* size_in_bytes);

CUTILE_C_API void read_from_file(file* file, u8* out, u64 nb_bytes_to_read);

CUTILE_C_API void write_in_file(file* file, const u8* buffer, u64 buffer_size_in_bytes);

CUTILE_C_API u64 get_file_size(file* file);
CUTILE_C_API b8  get_file_size_from_path(const char* path, u64* out);

CUTILE_C_API char* get_current_executable_path(allocator* allocator);
CUTILE_C_API char* get_current_executable_dir_path(allocator* allocator);

CUTILE_C_API char* concat_file_paths(const char* lhs, const char* rhs, allocator* allocator);
CUTILE_C_API void  concat_file_paths_into_cstr(const char* lhs, const char* rhs, const char* out);

// Returns the last element of a path.
// Elements are separated by path separators: '\' for Windows and '/' for Unix.
CUTILE_C_API const char* get_last_path_element(const char* path);

// Returns the extension of the filename without the '.' (e.g. "txt", "wav", ...etc).
// Returns null if filename does not have any.
// This function does not allocate any memory, it returns a pointer to the starting position of the extension.
CUTILE_C_API const char* get_filename_extension(const char* file_path);

#ifdef CUTILE_IMPLEM

    #ifdef _WIN32
        #include <windows.h>
    #elif defined(__unix__) || defined(__APPLE__)
        #include <unistd.h>
        #include <fcntl.h>
    #endif

    #include "./str.h"

    b8 file_exists(string* path)
    {
        char* cpath = create_cstr_from_str(path, path->allocator);
        bool8 res = file_exists_cstr(cpath);
        deallocate(path->allocator, cpath);
        return res;
    }

    b8 file_exists_cstr(const char* path)
    {
        #ifdef _WIN32
            DWORD dwAttrib = GetFileAttributesA(path);
            return (dwAttrib != INVALID_FILE_ATTRIBUTES);
        #endif
    }

    b8 directory_exists(string* path)
    {
        char* cpath = create_cstr_from_str(path, path->allocator);
        b8 res = directory_exists_cstr(cpath);
        deallocate(path->allocator, cpath);
        return res;
    }
    b8 directory_exists_cstr(const char* path)
    {
        #ifdef _WIN32
            DWORD dwAttrib = GetFileAttributesA(path);
            return (dwAttrib != INVALID_FILE_ATTRIBUTES && (dwAttrib & FILE_ATTRIBUTE_DIRECTORY));
        #endif
    }

    b8 copy_file(const char* path_of_file_to_copy, const char* path_of_new_file, b8 overwrite)
    {
        #ifdef _WIN32
        {
            return CopyFile(path_of_file_to_copy, path_of_new_file, !overwrite);
        }
        #endif

        // TODO: Implement for other platforms.
        return b8_false;
}

#ifdef _WIN32
    force_inline UINT file_access_mode_to_win32(file_access_mode mode)
    {
        DWORD flags = 0;
        if (mode & file_access_mode_read) flags |= GENERIC_READ;
        if (mode & file_access_mode_write) flags |= GENERIC_WRITE;
        return flags;
    }

    force_inline DWORD file_create_mode_to_win32(file_create_mode mode)
    {
        if (mode & file_create_if_not_exists) return CREATE_NEW;
        else return CREATE_ALWAYS;
    }
#endif

    b8 open_file(file_access_mode access_mode, const char* path, file* out)
    {
        #if defined(_WIN32)
            out->handle = (void*)CreateFileA(path, file_access_mode_to_win32(access_mode), 0, nullptr, OPEN_EXISTING, 0, nullptr);
    
            if (out->handle == INVALID_HANDLE_VALUE) return b8_false;
            return b8_true;
    
        #elif defined(__unix__) || defined(__APPLE__)
            int flags = 0;
            switch (access_mode)
            {
                case file_access_mode_read: flags = O_RDONLY; break;
                case file_access_mode_write: flags = O_WRONLY; break;
                case file_access_mode_read_write: flags = O_RDWR; break;
            }
            s64 fd = open(path, flags);
            out->handle = (void*)fd;
            return fd != -1 ? b8_true : b8_false;
    
         #endif
    }

    b8 create_file(file_create_mode create_mode, file_access_mode access_mode, const char* path, file* out)
    {
        #if defined(_WIN32)
        {
            out->handle = (void*)CreateFileA(path, file_access_mode_to_win32(access_mode), 0, nullptr, file_create_mode_to_win32(create_mode), 0, nullptr);
        
            if (out->handle == INVALID_HANDLE_VALUE) return b8_false;
            return b8_true;
        }
        #endif
    }

    void close_file(file* file)
    {
        #ifdef _WIN32
            CloseHandle(file->handle);
        #elif defined(__unix__) || defined(__APPLE__)
            close((u64)file->handle);
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
        #elif defined(__unix__) || defined(__APPLE__)
            write((u64)file->handle, buffer, buffer_size_in_bytes);
        #endif
    }
    
    u64 get_file_size(file* file)
    {
        u64 result;

        #ifdef _WIN32
            GetFileSizeEx((HANDLE)file->handle, (PLARGE_INTEGER)&result);
            return result;
        #elif defined(__unix__) || defined(__APPLE__)
            off_t curr_pos = lseek((u64)file->handle, 0, SEEK_CUR);
            off_t end_pos = lseek((u64)file->handle, 0, SEEK_END);
            lseek((u64)file->handle, curr_pos, SEEK_SET);
            result = (u64)end_pos;
            return result;
        #endif
    }

    b8 get_file_size_from_path(const char* path, u64* out)
    {
        file f;
        b8 file_opened = open_file(file_access_mode_read, path, &f);
        if (!file_opened) return b8_false;
        *out = get_file_size(&f);
        close_file(&f);
        return b8_true;
    }

    void read_from_file(file* file, u8* out, u64 nb_bytes_to_read)
    {
        #ifdef _WIN32
            DWORD read_bytes = 0;
            do
            {
                if (!ReadFile(file->handle, out + read_bytes, nb_bytes_to_read - read_bytes, &read_bytes, nullptr)) break;
            } while (read_bytes < nb_bytes_to_read);
        #elif defined(__unix__) || defined(__APPLE__)
            u64 read_bytes = 0;
            do
            {
                ssize_t rd = read((u64)file->handle, out, nb_bytes_to_read);
                if (rd == -1) break;
                read_bytes += rd;
            } while (read_bytes < nb_bytes_to_read);
        #else
            #error "read_from_file: Unsupported platform"
        #endif
    }

    b8 get_file_content_from_path(const char* path, allocator* allocator, u8** out, u64* size_in_bytes)
    {
        file file;
        b8 file_opened = open_file(file_access_mode_read, path, &file);
        if (!file_opened) return b8_false;
        get_file_content(&file, allocator, out, size_in_bytes);
        close_file(&file);
        return b8_true;
    }

    b8 get_file_content(file* file, allocator* allocator, u8** out, u64* size_in_bytes)
    {
        *size_in_bytes = get_file_size(file);
        *out = (u8*)allocate(allocator, *size_in_bytes);
        read_from_file(file, *out, *size_in_bytes);
        return b8_true;
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
    
    void concat_file_paths_into_cstr(const char* lhs, const char* rhs, char* out)
    {
        u32 lsize = cstr_length(lhs);
        u32 rsize = cstr_length(rhs);
        copy_s8_memory(out, lhs, lsize);
        #ifdef _WIN32
            out[lsize] = '\\';
        #elif defined(__unix__) || defined(__APPLE__)
            out[lsize] = '/';
        #else
            #error "concat_file_paths_into_cstr: Unsupported platforn."
        #endif
        copy_s8_memory(out, rhs, rsize);
        out[lsize + rsize + 1] = '\0';
    }

    char* concat_file_paths(const char* lhs, const char* rhs, allocator* allocator)
    {
        u32 lsize = cstr_length(lhs);
        u32 rsize = cstr_length(rhs);
        char* result = (char*)allocate(allocator, sizeof(char) * (lsize + rsize + 2));
        concat_file_paths_into_cstr(lhs, rhs, result);
        return result;
    }

    const char* get_last_path_element(const char* path)
    {
        persist char path_separator;
        #if defined(_WIN32)
        {
            path_separator = '\\';
        }
        #elif defined(__unix__)
        {
            path_separator = '/';
        }
        #endif
        const char* saved = path;
        while (*path)
        {
            if (*path == path_separator) saved = path;
            ++path;
        }
        return saved;
    }

    const char* get_filename_extension(const char* file_path)
    {
        const char* last_path_element = get_last_path_element(file_path);
        const char* saved = nullptr;
        while (*last_path_element)
        {
            if (*last_path_element == '.' && *(last_path_element + 1)) saved = last_path_element + 1;
            ++last_path_element;
        }
        return saved;
    }

#endif // CUTILE_IMPLEM

#endif // !CUTILE_FILESYSTEM_H
