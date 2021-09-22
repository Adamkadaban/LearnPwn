#include <stdio.h>

void getName(){
	char name[15] = {0};

	//look at this weird trick I found :)
	printf("%p\n", &printf);
	printf("What's your name? ");
	fgets(name, 100, stdin);
	printf("Cool name %s!", name);

	// ensures exploit works on all computers
	asm("xor %r12, %r12");
	asm("xor %r13, %r13");
	asm("xor %rcx, %rcx");
	asm("xor %rdx, %rdx");
	asm("xor %rsi, %rsi");

}

int main(){
	getName();
}


// Removed because of hackers :(
// void openShell(){
// 	system("/bin/sh");
// }
