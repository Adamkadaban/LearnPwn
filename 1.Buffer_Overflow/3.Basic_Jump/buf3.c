#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void getName() {
    char answer[50] = {0};

    printf("Are you an admin? ");
    fgets(answer, 200, stdin);
    if(strcmp(answer, "yes") == 0 || strcmp(answer, "yes\n") == 0) {
        newAdminDebug();
    }
}

int main() {
    getName();
}

void oldAdminDebug() {
    system("/bin/sh");
}

void newAdminDebug() {
    printf("Sorry, debugging is diabled due to hackers!!!\n");
    printf("Please contact Harry in IT for more information.");
}
