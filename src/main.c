#include <stdio.h>

#include "str.h"

int main(int argc, char* argv[]) {
    String astring;
    create_string_from_str(&astring, "And now ");

    String str;
    create_with_format(&str, "%d %d %d %u %x %X %p", 4, 532, 746, 57, 344, 346, 99643);

    append_string(&astring, &str);

    for(int i = 0; i < 105; i++)
        append_char(&astring, 'C');
    
    append_char(&astring, '\n');

    destroy_str(&str);

    print_string(&astring);

    printf("%lu %lu\n", astring.size, astring.allocated_size);

    destroy_str(&astring);

    return 0;
}
