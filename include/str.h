#pragma once

#include <stdlib.h>

#define FIRST_ALLOCATION_SIZE 32 // bytes
#define NEW_ALLOCATION_SIZE 8

typedef struct _str_struct {
    char* internal_pointer;
    size_t size;
    size_t allocated_size;
} String;

String* str_new();
void free_str(String* str);

void append_char(String* str, char c);
void s_append_string(String* str, char* other);
void append_string(String* str, String* other);
void recalculate_size(String* str);
void reallocate_string(String* str, size_t new_size);
void print_string(String* str);
