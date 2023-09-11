#include <str.h>

#include <stdio.h>
#include <string.h>
#include <stdarg.h>

#define TODO() (fprintf(stderr, "Not yet implemented"), exit(1))

String *str_new()
{
    String* result = (String*)malloc(sizeof(String));
    result->size = 0;
    result->internal_pointer = (char*)malloc(FIRST_ALLOCATION_SIZE);
    result->allocated_size = FIRST_ALLOCATION_SIZE;
    result->internal_pointer[0] = 0; // first character zero
    return result;
}

String *from_c_str(const char *string)
{
    size_t str_size = strlen(string);

    String* result = (String*)malloc(sizeof(String));
    result->allocated_size = FIRST_ALLOCATION_SIZE;
    if(str_size + 1 > FIRST_ALLOCATION_SIZE) {
        size_t a = (str_size + 1) / NEW_ALLOCATION_SIZE + 1;
        result->allocated_size += a * NEW_ALLOCATION_SIZE;
    }
    result->internal_pointer = (char*)malloc(result->allocated_size);
    memcpy(result->internal_pointer, string, str_size + 1);
    result->size = str_size;

    return result;
}

void free_str(String *str)
{
    free(str->internal_pointer);
    free(str);
}

String *copy_str(String *from)
{
    String* result = str_new();

    append_string(result, from); // that can be considered copy, right?

    return result;
}

void copy_into(String *to, String *from)
{
    TODO();
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
    size_t other_size = strlen(other) + 1;
    String tmp;

    tmp.allocated_size = other_size;
    tmp.internal_pointer = (char*)malloc(other_size);
    memcpy(tmp.internal_pointer, other, other_size);
    tmp.size = other_size - 1;

    append_string(str, &tmp);
}

void s_append_until(String *str, const char *other, size_t size)
{
    size_t ln = strlen(other);

    if(size > ln) return;
    else if(size == ln) {
        s_append_string(str, other);
        return;
    }

    char* str_to_append = (char*)malloc(ln + 1); // +1 because null terminator
    strcpy(str_to_append, other);
    
    str_to_append[size] = 0; // put the ending here

    s_append_string(str, str_to_append);

    free(str_to_append);
}

void append_until(String *str, String* other, size_t size) {
    if(size > other->size) return;
    else if(size == other->size) {
        append_string(str, other);
        return;
    }

    char* str_to_append = (char*)malloc(other->size + 1); // +1 because null terminator
    strcpy(str_to_append, other->internal_pointer);
    
    str_to_append[size] = 0; // put the ending here

    s_append_string(str, str_to_append);

    free(str_to_append);
}

void append_string(String *str, String *other)
{
    if(str->size + other->size >= str->allocated_size) {
        size_t a = other->size / NEW_ALLOCATION_SIZE + 1;
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
    
    char* new = (char*)malloc(new_size);

    memcpy(new, str->internal_pointer, str->size);

    free(str->internal_pointer);

    str->internal_pointer = new;
    str->allocated_size = new_size;
}

void print_string(String* str) {
    printf("%s", str->internal_pointer);
}

void insert_char(String **str, size_t position, char c)
{
    String* new = str_new();
    append_until(new, *str, position);
    append_char(new, c);
    s_append_string(new, (*str)->internal_pointer + position);

    free_str(*str);
    *str = new; // Interchange the string so noone notices )
}

void s_insert_string(String **str, size_t position, const char *other)
{
    String* new = str_new();
    append_until(new, *str, position);
    s_append_string(new, other);
    s_append_string(new, (*str)->internal_pointer + position);

    free_str(*str);
    *str = new; // Interchange the string so noone notices )
}

void insert_string(String **str, size_t position, String *other)
{
    s_insert_string(str, position, other->internal_pointer);
}
