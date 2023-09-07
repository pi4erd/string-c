#include <stdio.h>

#include "str.h"

int main(int argc, char* argv[]) {
    String* str = from_c_str("Hello, ");
    String* other = from_c_str("World!");

    for(int i = 0; i < 10; i++)
        append_string(str, other);

    free_str(other);

    for(int i = 0; i < 1000000; i++)
        append_char(str, 'c');
    
    append_char(str, '\n');

    print_string(str);

    free_str(str);

    return 0;
}
