#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BUF_SIZE 128


int main (int argc, char **argv){
    puts("I will repeat you:\n");
    unsigned int len;
    char* input = NULL;
    getline(&input, &len, stdin);

    char * buf = malloc(sizeof(char)*BUF_SIZE);
    FILE *f = fopen("flag.txt","r");
    fgets(buf,BUF_SIZE,f);
    
    printf(input);

 
}

