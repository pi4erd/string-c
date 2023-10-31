#include <str.h>

#include <stdio.h>
#include <string.h>
#include <stdarg.h>
#include <stdbool.h>

#define TODO() (fprintf(stderr, "Not yet implemented\n"), exit(1))

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

void create_string(String *str)
{
    str->size = 0;
    str->internal_pointer = (char*)malloc(FIRST_ALLOCATION_SIZE);
    str->allocated_size = FIRST_ALLOCATION_SIZE;
    str->internal_pointer[0] = 0;
}

void create_string_from_str(String *str, const char *string)
{
    size_t str_size = strlen(string);

    str->allocated_size = FIRST_ALLOCATION_SIZE;
    if(str_size + 1 > FIRST_ALLOCATION_SIZE) {
        size_t a = (str_size + 1) / NEW_ALLOCATION_SIZE + 1;
        str->allocated_size += a * NEW_ALLOCATION_SIZE;
    }
    str->internal_pointer = (char*)malloc(str->allocated_size);
    memcpy(str->internal_pointer, string, str_size + 1);
    str->size = str_size;
}

void free_str(String **str)
{
    free((*str)->internal_pointer);
    free(*str);
    *str = NULL;
}

void destroy_str(String *str)
{
    free(str->internal_pointer);
}

String *copy_str(String *from)
{
    String* result = str_new();

    append_string(result, from); // that can be considered copy, right?

    return result;
}

void copy_into(String *to, String *from)
{
    if(to == NULL || from == NULL)
        return;

    // TODO: Add null check to every realloc!
    to->internal_pointer = (char*)realloc(to->internal_pointer, from->allocated_size);
    to->allocated_size = from->allocated_size;
    to->size = from->size;

    memcpy(to->internal_pointer, from->internal_pointer, from->allocated_size);
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

void reallocate_string_by_size(String *str)
{
    size_t alloc_size = str->size / NEW_ALLOCATION_SIZE + 1;
    if(alloc_size * NEW_ALLOCATION_SIZE < FIRST_ALLOCATION_SIZE)
        alloc_size = FIRST_ALLOCATION_SIZE / NEW_ALLOCATION_SIZE;
    
    // TODO: Add null check to every realloc!
    str->internal_pointer = (char*)realloc(str->internal_pointer, alloc_size * NEW_ALLOCATION_SIZE);
    str->allocated_size = alloc_size * NEW_ALLOCATION_SIZE;
}

void reallocate_string(String *str, size_t new_size)
{
    if(new_size < str->allocated_size)
        new_size = str->allocated_size;
    
    // TODO: Add null check to every realloc!
    str->internal_pointer = (char*)realloc(str->internal_pointer, new_size);
    
    str->allocated_size = new_size;
}

void remove_char_at(String *str, size_t position)
{
    if(position >= str->size) return;

    char* copy = (char*)malloc(str->size);

    strcpy(copy, str->internal_pointer);

    str->internal_pointer[position] = 0;
    recalculate_size(str);

    s_append_string(str, copy + position + 1);

    free(copy);
}

void remove_span(String *str, size_t from, size_t until)
{
    if(from >= str->size) return;

    char* copy = (char*)malloc(str->size);

    strcpy(copy, str->internal_pointer);

    str->internal_pointer[from] = 0;
    if(until >= str->size) {
        recalculate_size(str);
        reallocate_string_by_size(str);
        return;
    }
    recalculate_size(str);

    s_append_string(str, copy + until);

    free(copy);
}

void print_string(String* str) {
    fwrite(str->internal_pointer, str->size, 1, stdout);
}

String int_to_string(int num, int radix, bool lowercase) {
    const char chars_upper[] = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    const char chars_lower[] = "0123456789abcdefghijklmnopqrstuvwxyz";

    bool neg = num < 0;

    String new;
    create_string(&new);

    if(neg) {
        num *= -1;
    }

    while(num > 0) {
        int digit = num % radix;
        num /= radix;

        if(!lowercase)
            append_char(&new, chars_upper[digit]);
        else
            append_char(&new, chars_lower[digit]);
    }

    if(neg) append_char(&new, '-');
    
    reverse_str(&new); // FIXME: There should be a better way to do this

    return new;
}

String uint_to_string(uint32_t num, uint32_t radix, bool lowercase) {
    const char chars_upper[] = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    const char chars_lower[] = "0123456789abcdefghijklmnopqrstuvwxyz";

    String new;
    create_string(&new);

    while(num > 0) {
        uint32_t digit = num % radix;
        num /= radix;

        if(!lowercase)
            append_char(&new, chars_upper[digit]);
        else
            append_char(&new, chars_lower[digit]);
    }

    reverse_str(&new); // FIXME: There should be a better way to do this

    return new;
}

void create_with_format(String *str, const char *format, ...)
{
    create_string(str);

    va_list vl;
    va_start(vl, format);

    size_t fmt_len = strlen(format);

    enum {
        STATE_CHAR, STATE_FMT, STATE_PRN
    };

    int state = STATE_CHAR;

    size_t i = 0;

    uint64_t u64;
    uint32_t nm;
    int number;

    while(i < fmt_len) {
        char c = format[i];
        switch (state)
        {
        case STATE_CHAR:
            if(c == '%') {
                state = STATE_FMT;
                i++;
                break;
            }
            append_char(str, c);
            i++;
            break;
        case STATE_FMT:
            switch(c) {
                case '%':
                    append_char(str, '%');
                    break;
                case 's':
                    const char* strptr = va_arg(vl, char*);
                    s_append_string(str, strptr);
                    break;
                case 'c':
                    char c = va_arg(vl, int);
                    append_char(str, c);
                    break;
                case 'd':
                case 'i':
                    number = va_arg(vl, int);
                    String numstr = int_to_string(number, 10, true);
                    append_string(str, &numstr);
                    destroy_str(&numstr);
                    break;
                case 'u':
                    nm = va_arg(vl, uint32_t);
                    numstr = uint_to_string(nm, 10, true);
                    append_string(str, &numstr);
                    destroy_str(&numstr);
                    break;
                case 'x':
                    u64 = va_arg(vl, uint64_t);
                    numstr = uint_to_string(u64, 16, true);
                    append_string(str, &numstr);
                    destroy_str(&numstr);
                    break;
                case 'p':
                case 'X':
                    u64 = va_arg(vl, uint64_t);
                    numstr = uint_to_string(u64, 16, false);
                    append_string(str, &numstr);
                    destroy_str(&numstr);
                    break;
                case 'o':
                    u64 = va_arg(vl, uint64_t);
                    numstr = uint_to_string(u64, 8, false);
                    append_string(str, &numstr);
                    destroy_str(&numstr);
                    break;
                case 'f':
                case 'F': // decimalfloating point
                    TODO();
                    break;
                case 'e':
                    TODO();
                    break;
                case 'E':
                    TODO();
                    break;
                case 'g':
                case 'G':
                    TODO();
                    break;
                case 'n':
                    number = va_arg(vl, int);
                    break;
                default:
                    break;
            }
            i++;
            state = STATE_CHAR;
            break;
        default:
            break;
        }
        
    }

    va_end(vl);
}

void insert_char(String *str, size_t position, char c)
{
    char* copy = (char*)malloc(str->size + 1);
    strcpy(copy, str->internal_pointer);

    str->internal_pointer[position] = 0;
    recalculate_size(str);

    append_char(str, c);
    s_append_string(str, copy + position);

    free(copy);
}

void s_insert_string(String *str, size_t position, const char *other)
{
    char* copy = (char*)malloc(str->size + 1);
    strcpy(copy, str->internal_pointer);

    str->internal_pointer[position] = 0;
    recalculate_size(str);

    s_append_string(str, other);
    s_append_string(str, copy + position);

    free(copy);
}

void insert_string(String *str, size_t position, String *other)
{
    char* copy = (char*)malloc(str->size + 1);
    strcpy(copy, str->internal_pointer); // FIXME: change to memcpy

    str->internal_pointer[position] = 0;
    recalculate_size(str);

    append_string(str, other);
    s_append_string(str, copy + position);

    free(copy);
}

void reverse_str(String *str)
{
    char* copy = (char*)malloc(str->size + 1);
    strcpy(copy, str->internal_pointer); // FIXME: change to memcpy

    for(size_t i = 0; i < str->size; i++) {
        str->internal_pointer[i] = copy[str->size - i - 1];
    }

    free(copy);
}

int find_char(size_t *location, const String *str, char c)
{
    for(size_t i = 0; i < str->size; i++) {
        if(str->internal_pointer[i] == c) {
            *location = i;
            return 1;
        }
    }
    return 0;
}

void replace_char(String *str, char c, char new)
{
    size_t pos;

    // TODO: Add error handling better than just to ignore it or exit
    if(!find_char(&pos, str, c)) return;

    remove_char_at(str, pos);

    insert_char(str, pos, new);
}

void replace_char_at(String *str, size_t position, char new)
{
    remove_char_at(str, position);

    insert_char(str, position, new);
}

void replace_first_found_str(String *str, const char *str_to_replace, const char *new)
{
    size_t str_size = strlen(str_to_replace);

    if(str_size == 0) return;

    size_t pos = 0;
    size_t offset = 0;
    size_t i = 0;

    while(i < str->size) {
        if(offset >= str_size) {
            break; // Exit because we found the string
        }
        if(str_to_replace[offset] == str->internal_pointer[i]) {
            offset++;
        } else {
            pos++;
            offset = 0;
        }
        i++;
    }

    if(offset == 0)
        return;

    remove_span(str, pos, pos + offset);
    s_insert_string(str, pos, new);
}

void replace_all_found_str(String *str, const char *str_to_replace, const char *new)
{
    size_t str_size = strlen(str_to_replace);
    size_t new_str_size = strlen(new);

    if(str_size == 0) return;

    size_t offset = 0;
    size_t prev_iter_pos = 0;
    do {
        size_t pos = 0;
        size_t i = prev_iter_pos;
        offset = 0;

        while(i < str->size) {
            if(offset >= str_size) {
                break; // Exit because we found the string
            }
            if(str_to_replace[offset] == str->internal_pointer[i]) {
                offset++;
            } else {
                pos = i + 1;
                offset = 0;
            }
            i++;
        }

        prev_iter_pos = pos + new_str_size - 1;

        if(offset != 0) {
            remove_span(str, pos, pos + offset);
            s_insert_string(str, pos, new);
            continue;
        } else break;
    } while(offset != 0); // just in case
}

void s_replace_char_with_string(String *str, char c, char *new)
{
    size_t pos;

    // TODO: Add error handling better than just to ignore it or exit
    if(!find_char(&pos, str, c)) return;

    remove_char_at(str, pos);

    s_insert_string(str, pos, new);
}

void trim_end_string(String *str)
{
    char c;
    size_t offset = str->size;

    while((c = str->internal_pointer[--offset]) || offset >= 0) {
        if(c == ' ' || c == '\n' || c == '\t' || c == '\r')
            str->internal_pointer[offset] = 0;
        else break;
    }
    str->size = offset + 1;

    reallocate_string_by_size(str);
}
