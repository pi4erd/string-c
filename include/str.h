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
String* from_c_str(const char* string);
void free_str(String* str);

String* copy_str(String* from);
void copy_into(String* to, String* from);

void append_char(String* str, char c);
void s_append_string(String* str, const char* other);
void s_append_until(String* str, const char* other, size_t size);
void append_until(String* str, String* other, size_t size);
void append_string(String* str, String* other);
void recalculate_size(String* str);
void reallocate_string(String* str, size_t new_size);
void print_string(String* str);

void insert_char(String** str, size_t position, char c);
void s_insert_string(String** str, size_t position, const char* other);
void insert_string(String** str, size_t position, String* other);
