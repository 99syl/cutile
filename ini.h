#ifndef CUTILE_INI_H
#define CUTILE_INI_H

#include "./array.h"

typedef struct ini_field
{
    const u8* name_start;       // Where the name starts.
    const u8* name_end;         // Where the name ends.
    const u8* val_start;        // Where the value starts.
    const u8* val_end;          // Where the value ends.
} ini_field;
declare_array_of(ini_field);

typedef struct ini_section
{
    const u8* decl_start;       // [
    const u8* decl_end;         // ]
    const u8* name;             // Name of the section.
    u64       name_size;        // Size in bytes of the section name.
    const u8* content_start;    // After section declaration.
    const u8* content_end;      // One byte before next section declaration or end of file.
    
    ini_field_array fields;
} ini_section;
declare_array_of(ini_section);

typedef struct ini_error
{
    const char* msg;            // Null if there is no error.
    const char* filename;       // Null if parse directly from memory and not from filesystem.
    u32         line;           // Line where the error occurred if it comes from the ini data.
} ini_error;

typedef struct
{
    ini_error         error;
    ini_section       global_section;
    ini_section_array sections;
} parse_ini_result;
parse_ini_result parse_ini(const u8* data, u64 data_size, allocator* allocator);

typedef struct
{
    bool8 found;
    const u8* value_start;
    u64 value_size;
} ini_entry_value_result;
ini_entry_value_result get_ini_global_entry_value(const char* entry_name, const parse_ini_result* parsed_data);
ini_entry_value_result get_ini_entry_value(const char* section_name, const char* entry_name, const parse_ini_result* parsed_data);

void destroy_ini_parsed_data(parse_ini_result* parsed_data);

#ifdef CUTILE_IMPLEM

    #include "memory.h"

    typedef struct ini_parser_state
    {
        const u8* data;
        u64 data_size;
        u64 index;
        u64 line;
    } ini_parser_state;

    typedef enum ini_parser_token_kind
    {
        ini_parser_token_kind_separator,
        ini_parser_token_kind_op, // operator
        ini_parser_token_kind_name_or_value,
        ini_parser_token_kind_end,
        ini_parser_token_kind_unknown
    } ini_parser_token_kind;

    typedef struct ini_parser_token
    {
        ini_parser_token_kind kind;
        const u8* start;
        const u8* end;
        u64 line;
    } ini_parser_token;

    internal ini_parser_token get_next_ini_parser_token(ini_parser_state* state)
    {
        ini_parser_token tok;
        u8 ch;

        // Extracts characters until one is relevant.
        do
        {
            if (state->index >= state->data_size) goto end_of_data;

            ch = state->data[state->index];
            
            if (ch == ' ' || ch == '\t')
            {
                ++state->index;
                continue;
            }
            else if (ch == '\n')
            {
                ++state->index;
                ++state->line;
            }
            else break;
        } while (1);
        
        // Comment
        if (ch == ';')
        {
            do
            {
                if (state->index >= state->data_size) goto end_of_data;

                ch = state->data[state->index++];

                if (ch == '\n') // End of comment.
                {
                    ++state->line;
                    return get_next_ini_parser_token(state);
                }
            } while (1);
        }

        tok.line = state->line;

        // Section separators.
        if (ch == '[' || ch == ']')
        {
            tok.kind = ini_parser_token_kind_separator;
            tok.start = state->data + state->index;
            tok.end = tok.start;
            ++state->index;
        }

        // Assignment operator.
        else if (ch == '=')
        {
            tok.kind = ini_parser_token_kind_op;
            tok.start = state->data + state->index;
            tok.end = tok.start;
            ++state->index;
        }

        // Section name or entry name or entry value.
        else if ((ch >= 'a' && ch <= 'z') || (ch >= 'A' && ch <= 'Z'))
        {
            tok.kind = ini_parser_token_kind_name_or_value;
            tok.start = state->data + state->index;
            tok.end = tok.start;
            ++state->index;
            while (state->index < state->data_size)
            {
                ch = state->data[state->index];
                if ((ch >= 'a' && ch <= 'z') || (ch >= 'A' && ch <= 'Z'))
                {
                    ++tok.end;
                    ++state->index;
                }
                else break;
            }
        }

        // Number value.
        else if (ch >= '0' && ch <= '9')
        {
            tok.kind = ini_parser_token_kind_name_or_value;
            tok.start = state->data + state->index;
            tok.end = tok.start;
            ++state->index;
            while (state->index < state->data_size)
            {
                ch = state->data[state->index];
                if (ch >= '0' && ch <= '9')
                {
                    ++tok.end;
                    ++state->index;
                }
                else break;
            };
        }

        // Null terminator (C-strings)
        else if (ch == 0) goto end_of_data;
        
        // Unknown token... Something is wrong!
        else tok.kind = ini_parser_token_kind_unknown;
        
        return tok;

    end_of_data:
        tok.kind = ini_parser_token_kind_end;
        tok.line = state->line;
        return tok;
    }

    internal void parse_ini_entry(ini_parser_token* name, ini_parser_state* state, ini_section* section, parse_ini_result* result)
    {
        ini_parser_token assignment_op_tok = get_next_ini_parser_token(state);
        if (assignment_op_tok.kind != ini_parser_token_kind_op)
        {
            result->error.msg = "Assignment operator expected after entry declaration.";
            result->error.line = state->line;
            return;
        }

        ini_parser_token value_tok = get_next_ini_parser_token(state);
        if (value_tok.kind != ini_parser_token_kind_name_or_value)
        {
            result->error.msg = "Value expected after assignment operation.";
            result->error.line = state->line;
            return;
        }

        ini_field field;
        field.name_start = name->start;
        field.name_end = name->end;
        field.val_start = value_tok.start;
        field.val_end = value_tok.end;
        
        ini_field_array_push(&section->fields, field);
    }

    internal void parse_ini_section(ini_parser_token* tok, ini_parser_state* state, parse_ini_result* result)
    {
        if (*tok->start == ']')
        {
            result->error.msg = "Section declaration should start with '[' but it was ']'.";
            result->error.line = state->line;
            return;
        }

        ini_parser_token section_name_tok = get_next_ini_parser_token(state);
        if (section_name_tok.kind != ini_parser_token_kind_name_or_value)
        {
            result->error.msg = "A name for the section was expected.";
            result->error.line = state->line;
            return;
        }

        ini_parser_token section_end_sep_tok = get_next_ini_parser_token(state);
        if (section_end_sep_tok.kind != ini_parser_token_kind_separator)
        {
            result->error.msg = "Separator expected at the end of section declaration.";
            result->error.line = state->line;
            return;
        }
        if (*section_end_sep_tok.start == '[')
        {
            result->error.msg = "Section declaration should end with ']' but it was '['.";
            result->error.line = state->line;
            return;
        }

        ini_section section;
        section.decl_start = tok->start;
        section.decl_end = section_end_sep_tok.start;
        section.name = section_name_tok.start;
        section.name_size = section_name_tok.end - section.name + 1;
        section.fields = create_ini_field_array(5, 5, result->sections.allocator);

        int loop = 1;
        while (loop)
        {
            // An error occurred, just leave the loop to stop processing the ini file.
            // TODO: Handle multi errors maybe instead of exiting at the first error in the data ?
            if (result->error.msg != nullptr) break;

            ini_parser_token next_tok = get_next_ini_parser_token(state);

            switch (next_tok.kind)
            {

            case ini_parser_token_kind_name_or_value:
                if (section.fields.count == 0) section.content_start = next_tok.start; // Represents begin of content if this is the first field.
                parse_ini_entry(&next_tok, state, &section, result);
                break;

            case ini_parser_token_kind_separator:
                if (section.fields.count == 0) section.content_start = next_tok.start - 1; // Begin of content equals end of content if there is no field.
                section.content_end = next_tok.start - 1;
                parse_ini_section(&next_tok, state, result);
                break;

            case ini_parser_token_kind_end:
                section.content_end = state->data + state->data_size - 1;
                if (section.fields.count == 0) section.content_start = section.content_end; // Begin of content equals end of content if there is no field.
                loop = 0;
                break;
                
            default:
                result->error.msg = "Encounter an unknown token!";
                result->error.line = state->line;
                break;

            }
        }

        ini_section_array_push(&result->sections, section);
    }

    internal void parse_ini_global_section(ini_parser_state* state, parse_ini_result* result)
    {
        result->global_section.decl_start = nullptr;
        result->global_section.decl_end = nullptr;
        result->global_section.content_start = state->data;
        result->global_section.content_end = state->data;
        result->global_section.name = nullptr;
        result->global_section.name_size = 0;
        result->global_section.fields = create_ini_field_array(5, 5, result->sections.allocator);
        
        int loop = 1;
        while (loop)
        {
            // An error occurred, just leave the loop to stop processing the ini file.
            // TODO: Handle multi errors maybe instead of exiting at the first error in the data ?
            if (result->error.msg != nullptr) break;
            
            ini_parser_token tok = get_next_ini_parser_token(state);

            switch (tok.kind)
            {

                // New section. No more in global section.
            case ini_parser_token_kind_separator:
                if (result->sections.count == 0) result->global_section.content_end = tok.start - 1;
                parse_ini_section(&tok, state, result);
                break;

            case ini_parser_token_kind_name_or_value:
                parse_ini_entry(&tok, state, &result->global_section, result);
                break;

            case ini_parser_token_kind_end:
                result->global_section.content_end = state->data + state->data_size - 1;
                loop = 0;
                break;

            default:
                result->error.msg = "Encounter an unknown token!";
                result->error.line = state->line;
                break;
            }
        }
    }

    parse_ini_result parse_ini(const u8* data, u64 data_size, allocator* allocator)
    {
        parse_ini_result result;
        result.error.msg = nullptr;
        result.sections = create_ini_section_array(5, 5, allocator);

        ini_parser_state state;
        state.data = data;
        state.data_size = data_size;
        state.index = 0;
        state.line = 1;
        
        parse_ini_global_section(&state, &result);
        return result;
    }

    #include "./str.h"

    internal ini_entry_value_result get_ini_section_entry_value(const ini_section* section, const char* entry_name)
    {
        ini_entry_value_result result;
        result.found = bool8_false;
        u32 entry_name_len = cstr_length(entry_name);
        for (u32 i = 0; i < section->fields.count; ++i)
        {
            const ini_field* field = &section->fields.data[i];

            if (field->name_end - field->name_start + 1 != entry_name_len) continue;
            if (!u8_memory_equals((const u8*)entry_name, field->name_start, entry_name_len)) continue;

            // FOUND!
            result.found = bool8_true;
            result.value_start = field->val_start;
            result.value_size = field->val_end - field->val_start + 1;
            break;
        }
        return result;
    }

    ini_entry_value_result get_ini_global_entry_value(const char* entry_name, const parse_ini_result* parsed_data)
    {
        return get_ini_section_entry_value(&parsed_data->global_section, entry_name);
    }

    ini_entry_value_result get_ini_entry_value(const char* section_name, const char* entry_name, const parse_ini_result* parsed_data)
    {
        u32 section_name_len = cstr_length(section_name);
        for (u32 i = 0; i < parsed_data->sections.count; ++i)
        {
            const ini_section* section = &parsed_data->sections.data[i];

            if (section->name_size != section_name_len) continue;
            if (!u8_memory_equals((const u8*)section_name, section->name, section_name_len)) continue;

            // SECTION FOUND!
            return get_ini_section_entry_value(section, entry_name);
        }
        ini_entry_value_result result;
        result.found = bool8_false;
        return result;
    }

    void destroy_ini_parsed_data(parse_ini_result* parsed_data)
    {
        destroy_ini_field_array(&parsed_data->global_section.fields);
        for (u32 i = 0; i < parsed_data->sections.count; ++i)
        {
            destroy_ini_field_array(&parsed_data->sections.data[i].fields);
        }
        destroy_ini_section_array(&parsed_data->sections);
    }

#endif // CUTILE_IMPLEM

#endif // !CUTILE_INI_H
