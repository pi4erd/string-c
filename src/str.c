#include "str.h"

#include <stdio.h>
#include <string.h>

String *str_new()
{
    String* result = (String*)malloc(sizeof(String));
    result->size = 0;
    result->internal_pointer = (char*)malloc(FIRST_ALLOCATION_SIZE);
    result->allocated_size = FIRST_ALLOCATION_SIZE;
    result->internal_pointer[0] = 0; // first character zero
    return result;
}

void free_str(String *str)
{
    free(str->internal_pointer);
    free(str);
}

void append_char(String *str, char c)
{
    if(str->size + 1 >= str->allocated_size) {
        reallocate_string(str, str->allocated_size + NEW_ALLOCATION_SIZE);
    }
    // [0][1][2]
    str->internal_pointer[str->size++] = c;
    str->internal_pointer[str->size] = 0;
}

void s_append_string(String *str, const char *other)
{
    size_t other_len = strlen(other);
    if(str->size + other_len > str->allocated_size) {
        size_t a = other_len / NEW_ALLOCATION_SIZE + 1; // why +1? cuz why not
        reallocate_string(str, str->allocated_size + a * NEW_ALLOCATION_SIZE);
    }
    char* from = str->internal_pointer + str->size;
    memcpy(from, other, other_len);

    str->size += other_len;
    str->internal_pointer[str->size] = 0;
}

void append_string(String *str, String *other)
{
    if(str->size + other->size > str->allocated_size) {
        size_t a = other->size / NEW_ALLOCATION_SIZE + 1; // why +1? cuz why not
        reallocate_string(str, str->allocated_size + a * NEW_ALLOCATION_SIZE);
    }
    char* from = str->internal_pointer + str->size;
    memcpy(from, other->internal_pointer, other->size);

    str->size += other->size;
    str->internal_pointer[str->size] = 0;
}

void recalculate_size(String *str)
{
    str->size = strlen(str->internal_pointer);
}

void reallocate_string(String *str, size_t new_size)
{
    if(new_size < str->allocated_size)
        new_size = str->allocated_size;
    
    char* new = malloc(new_size);

    memcpy(new, str->internal_pointer, str->size);

    free(str->internal_pointer);

    str->internal_pointer = new;
    str->allocated_size = new_size;
}

void print_string(String* str) {
    printf("%s", str->internal_pointer);
}
