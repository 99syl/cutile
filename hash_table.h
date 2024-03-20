#ifndef CUTILE_HASH_TABLE_H

#include "memory.h"

typedef struct hash_table_entry hash_table_entry;
typedef struct hash_table_entry
{
    u64               key_length;
    u8*               key;
    u8*               value;
    hash_table_entry* next;
} hash_table_entry;

typedef u64 (*hash_function_ptr)(u8* data, u64 data_size);

typedef b8  (*compare_keys_function_ptr)(u8* lhs, u64 lhs_size, u8* rhs, u64 rhs_size);

CUTILE_C_API b8 default_compare_keys(u8* lhs, u64 lhs_size, u8* rhs, u64 rhs_size);

typedef struct hash_table
{
    hash_table_entry** entries;
    
    u32 count;
    u32 size;

    hash_function_ptr          hash_function;
    compare_keys_function_ptr  compare_keys_function;
    u64                        value_size_in_bytes;

    allocator* allocator;
} hash_table;

// This call might fail in case allocation fails.
// To check for allocation failure just check that hash_table.entries pointer is null.
CUTILE_C_API hash_table create_hash_table(u32                       base_size,
                                          hash_function_ptr         hash_function,
                                          compare_keys_function_ptr compare_keys_function,
                                          u64                       value_size_in_bytes,
                                          allocator*                allocator);

CUTILE_C_API void       destroy_hash_table(hash_table* hash_table);

// Call might fail if allocation fails, return nullptr in that case.
// Returns a pointer to the value stored in the inserted hash_table_entry otherwise.
// If the key is already emplaced, this call will not change the state of the given hash_table.
// The key content is copied so you can do whatever you want with it after this call.
CUTILE_C_API u8*        hash_table_emplace(hash_table* hash_table, u8* key, u64 key_length);

// Returns false if the entry could not be removed because the key has not been found.
// Returns true if the entry has been successfully removed.
CUTILE_C_API b8         hash_table_remove(hash_table* hash_table, u8* key, u64 key_length);

// Returns a pointer to the value associated to the given key.
// Returns nullptr if the key has not been found.
CUTILE_C_API u8*        hash_table_get(hash_table* hash_table, u8* key, u64 key_length);

CUTILE_C_API void       hash_table_for_each_entry(hash_table* hash_table,
                                                  void (*)(hash_table_entry* entry));

#ifdef CUTILE_IMPLEM

    hash_table create_hash_table(u32                       base_size,
                                 hash_function_ptr         hash_function,
                                 compare_keys_function_ptr compare_keys_function,
                                 u64                       value_size_in_bytes,
                                 allocator*                allocator)
    {
        hash_table res;

        res.entries = allocate_many_m(allocator, hash_table_entry*, base_size);
        if (res.entries == nullptr) return res;

        for (u32 i = 0; i < base_size; ++i)
        {
            res.entries[i] = nullptr;
        }

        res.count = 0;
        res.size = base_size;
        res.hash_function = hash_function;
        res.compare_keys_function = compare_keys_function;
        res.value_size_in_bytes = value_size_in_bytes;
        res.allocator = allocator;
        return res;
    }

    void destroy_hash_table(hash_table* hash_table)
    {
        for (u32 i = 0; i < hash_table->size; ++i)
        {
            hash_table_entry* head = hash_table->entries[i];
            while (head != nullptr)
            {
                hash_table_entry* tmp = head;
                head = head->next;
                deallocate(hash_table->allocator, tmp);
            }
        }

        deallocate(hash_table->allocator, hash_table->entries);
    }

    u8* hash_table_emplace(hash_table* hash_table, u8* key, u64 key_length)
    {
        u64 hash = hash_table->hash_function(key, key_length);
        u64 index = (hash % hash_table->size) - 1;

        hash_table_entry** head = &hash_table->entries[index];
        while (*head != nullptr)
        {
            hash_table_entry* entry = *head;
            if (hash_table->compare_keys_function(key, key_length, entry->key, entry->key_length))
            {
                return entry->value;
            }
            head = &entry->next;
        }

        hash_table_entry* new_entry = (hash_table_entry*)allocate(hash_table->allocator, sizeof(hash_table_entry) + hash_table->value_size_in_bytes + key_length);
        if (new_entry == nullptr) return nullptr;
        new_entry->key_length = key_length;
        new_entry->key = ((u8*)new_entry) + sizeof(hash_table_entry) + hash_table->value_size_in_bytes;
        copy_u8_memory(new_entry->key, key, key_length);
        new_entry->value = (u8*)new_entry + sizeof(hash_table_entry);
        new_entry->next = nullptr;
        *head = new_entry;
        hash_table->count++;

        return new_entry->value;
    }

    b8 hash_table_remove(hash_table* hash_table, u8* key, u64 key_length)
    {
        u64 hash = hash_table->hash_function(key, key_length);
        u64 index = (hash % hash_table->size) - 1;

        hash_table_entry** head = &hash_table->entries[index];

        while (*head != nullptr)
        {
            hash_table_entry* entry = *head;
            if (hash_table->compare_keys_function(key, key_length, entry->key, entry->key_length))
            {
                hash_table_entry* next = entry->next;
                deallocate(hash_table->allocator, entry);
                *head = next;
                hash_table->count--;
                return b8_true;
            }
            head = &entry->next;
        }
        return b8_false;
    }

    u8* hash_table_get(hash_table* hash_table, u8* key, u64 key_length)
    {
        u64 hash = hash_table->hash_function(key, key_length);
        u64 index = (hash % hash_table->size) - 1;

        hash_table_entry** head = &hash_table->entries[index];

        while (*head != nullptr)
        {
            hash_table_entry* entry = *head;
            if (hash_table->compare_keys_function(key, key_length, entry->key, entry->key_length))
            {
                return entry->value;
            }
            head = &entry->next;
        }
        return nullptr;
    }

    void hash_table_for_each_entry(hash_table* hash_table,
                                   void (*call)(hash_table_entry* entry))
    {
        for (u32 i = 0; i < hash_table->size; ++i)
        {
            hash_table_entry* head = hash_table->entries[i];
            while (head != nullptr)
            {
                call(head);
                head = head->next;
            }
        }
    }

#endif // CUTILE_IMPLEM

#define CUTILE_HASH_TABLE_H
#endif
