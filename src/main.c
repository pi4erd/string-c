#include <stdio.h>

#include "str.h"

int main(int argc, char* argv[]) {
    String stack_str;
    create_string_from_str(&stack_str, "Hello, world!");

    s_append_string(&stack_str, " You are my friend!\n");

    print_string(&stack_str);

    destroy_str(&stack_str);

    return 0;
}
