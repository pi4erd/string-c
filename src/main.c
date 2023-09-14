#include <stdio.h>

#include "str.h"

int main(int argc, char* argv[]) {
    String* str1 = str_new();
    String* str2 = from_c_str("this is a string\n");

    copy_into(str1, str2); // str2 -> str1

    print_string(str1);
    print_string(str2);

    return 0;
}
