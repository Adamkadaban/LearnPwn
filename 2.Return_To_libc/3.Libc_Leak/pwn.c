#include <stdio.h>
#include <string.h>
#include <unistd.h>

int main(){
	char buffer[128];
	setvbuf(stdout, NULL, _IONBF, 0);
	puts("I am hungry you have to feed me to win this challenge...\n");
	puts("Now give me some sweet desert: ");
	gets(buffer);
	return 0;
}
