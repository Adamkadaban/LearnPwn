#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void checkAdmin() {
    char answer[50] = {0};

    printf("Are you an admin? ");
    fgets(answer, 200, stdin);
    if(strcmp(answer, "yes, give me the codes") == 0 || strcmp(answer, "yes, give me the codes\n") == 0) {
        adminDebug();
    }
    
    // Give them a second try because I'm so nice :)
    printf("Are you an admin? ");
    fgets(answer, 200, stdin);
    if(strcmp(answer, "yes, give me the codes") == 0 || strcmp(answer, "yes, give me the codes\n") == 0) {
        adminDebug();
    }
}

int main() {
    checkAdmin();
}

void adminDebug() {
    printf("HERE ARE THE SECRET CODES, DON'T SHARE THEM WITH HACKERS\n");
    printf("%p %p %p\n", &main, &checkAdmin, &fgets);
}
