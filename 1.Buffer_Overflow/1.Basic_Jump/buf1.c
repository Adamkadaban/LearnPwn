#include <stdio.h>
#include <stdlib.h>


void getName(){
	char name[15] = {0};


	printf("What's your name? ");
	fgets(name, 100, stdin);
	printf("Cool name %s!", name);

}


int main(){
	getName();
}

void openShell(){
        system("/bin/sh");
}
