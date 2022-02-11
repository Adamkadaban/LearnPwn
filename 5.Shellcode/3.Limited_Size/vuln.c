#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LENGTH 1000

void execute(char *shellcode, size_t length) {
    if (!shellcode || !length) {
        exit(1);
    }
    size_t new_length = length * 2;
    char result[new_length + 1];

    int spot = 0;
    for (int i = 0; i < new_length; i++) {
        if ((i % 4) < 2) {
            result[i] = shellcode[spot++];
        } else {
            result[i] = '\x90';
        }
    }
    // result[new_length] = '\xcc';
    result[new_length] = '\xc3';

    // Execute code
    int (*code)() = (int(*)())result;
    code();
}

int main(int argc, char *argv[]) {
    setbuf(stdout, NULL);
    char buf[MAX_LENGTH];
    size_t length = 0;
    char c = '\0';

    printf("Give me code to run:\n");
    c = fgetc(stdin);
    while ((c != '\n') && (length < MAX_LENGTH)) {
        buf[length] = c;
        c = fgetc(stdin);
        length++;
    }
    if (length % 2) {
        buf[length] = '\x90';
        length++;
    }
    execute(buf, length);
    return 0;
}
