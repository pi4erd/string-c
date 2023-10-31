#pragma once

#include <stdlib.h>

#define FIRST_ALLOCATION_SIZE 32 // bytes
#define NEW_ALLOCATION_SIZE 8

typedef struct _str_struct {
    char* internal_pointer;
    size_t size;
    size_t allocated_size;
} String;

/**
 * @brief Creates a new empty heap-allocated string
 * 
 * @return String* A pointer to a string struct
 */
String* str_new();
/**
 * @brief Creates a new heap-allocated string with specific value in it
 * 
 * @param string String value
 * @return String* A pointer to a string struct
 */
String* from_c_str(const char* string);

/**
 * @brief Creates a string into an allocated pointer. Assigns internal pointer,
 * size, allocated size, does not change the string pointer itself
 * 
 * @param str String pointer to create a string into
 */
void create_string(String* str);
/**
 * @brief Creates a string into an allocated pointer. Assigns internal pointer,
 * size, allocated size, does not change the string pointer itself. Copies
 * a given string into a newly-allocated string
 * 
 * @param str String to create
 * @param string C-type string to copy
 */
void create_string_from_str(String* str, const char* string);

/**
 * @brief Frees memory of a heap allocated string. For stack-allocated strings
 * use `destroy_str`
 * 
 * @param str Pointer to a string pointer
 */
void free_str(String** str);
/**
 * @brief Frees memory of a stack allocated string. For heap-allocated strings
 * use `free_str`
 * 
 * @param str Pointer to a string struct
 */
void destroy_str(String* str);

/**
 * @brief Creates a copy of a string struct
 * 
 * @param from String to copy from
 * @return String* A copy of a given string
 */
String* copy_str(String* from);

/**
 * @brief Copies a string into an allocated string struct
 * 
 * @param to String pointer to copy to
 * @param from String pointer to copy from
 */
void copy_into(String* to, String* from);

/**
 * @brief Appends a character at the end of a string
 * 
 * @param str String to append char to
 * @param c Character to append
 */
void append_char(String* str, char c);
/**
 * @brief Appends a C-type string to the end of a string struct
 * 
 * @param str String to append C-type string to
 * @param other C-type string
 */
void s_append_string(String* str, const char* other);
/**
 * @brief Appends a C-type string to the end of a string struct with a specified
 * size
 * 
 * @param str A string to append to
 * @param other C-type string to append
 * @param size Size of a C-type string to append until
 */
void s_append_until(String* str, const char* other, size_t size);
/**
 * @brief Appends a string to the end of another string until a specified size
 * 
 * @param str A string to append to
 * @param other A string to append
 * @param size Size to append until
 */
void append_until(String* str, String* other, size_t size);
/**
 * @brief Appends a string to the end of another string
 * 
 * @param str String to append to
 * @param other String to append
 */
void append_string(String* str, String* other);
/**
 * @brief Prints a string's internal pointer to stdout
 * 
 * @param str A string to print
 */
void print_string(String* str);

/**
 * @brief Creates a string with a format as a value. If string is already 
 * allocated, reallocates it.
 * 
 * @param str A string to create
 * @param format A format of a string
 * @param ... Arguments
 */
void create_with_format(String* str, const char* format, ...);

/**
 * @brief Recalculates a size of a string based on the internal pointer
 * 
 * @param str String to recaltulate size of
 */
void recalculate_size(String* str);
/**
 * @brief Reallocates a string using the size of string
 * 
 * @param str A string to reallocate
 */
void reallocate_string_by_size(String* str);
/**
 * @brief Reallocates a string with a new size
 * 
 * @param str A string to reallocate
 * @param new_size A new string allocated size
 */
void reallocate_string(String* str, size_t new_size);

/**
 * @brief Removes character at index and collapses string
 * 
 * @param str The string to change
 * @param position Index of char to delete
 */
void remove_char_at(String* str, size_t position);
/**
 * @brief Removes span of characters from string
 * 
 * @param str String to change
 * @param from Index to remove from, inclusive
 * @param until Index to remove until, exclusive
 */
void remove_span(String* str, size_t from, size_t until);

/**
 * @brief Inserts a character in position
 * 
 * @param str A string to insert into
 * @param position Position to insert to
 * @param c A character to insert
 */
void insert_char(String* str, size_t position, char c);
/**
 * @brief Inserts a C-type string in position
 * 
 * @param str A string to insert into
 * @param position Position to insert to
 * @param other A C-type string to insert
 */
void s_insert_string(String* str, size_t position, const char* other);
/**
 * @brief Inserts a string into another string in position
 * 
 * @param str A string to insert into
 * @param position A position to insert to
 * @param other A string to insert
 */
void insert_string(String* str, size_t position, String* other);

/**
 * @brief Reverses all characters in string
 * 
 * @param str String to reverse
 */
void reverse_str(String* str);

/**
 * @brief Finds char in string
 * 
 * @param location Location of char, pointer to return to
 * @param str String to find char in
 * @param c Char to find
 * @return int 0 if not found, 1 if found
 */
int find_char(size_t* location, const String* str, char c);
void replace_char(String* str, char c, char new);
void replace_char_at(String* str, size_t position, char new);
void replace_first_found_str(String* str, const char* str_to_replace, const char* new);
void replace_all_found_str(String* str, const char* str_to_replace, const char* new);
void s_replace_char_with_string(String* str, char c, char* new);

/**
 * @brief Trims an end of a string from whitespace characters. They are:
 * Space (0x20), Newline (0x0A), Tab (0x09) and CR (0x0D)
 * 
 * @param str String to trim
 */
void trim_end_string(String* str);

#ifdef STR_H_IMPL
    // TODO: Add implementation for header-only mode
#endif
