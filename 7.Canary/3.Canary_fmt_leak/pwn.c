#include <stdio.h>
#include <stdlib.h>

void win(){
	system("/bin/sh");
}

int main(){
	char buf[32];

	printf("Say hi to the cute little bird!\n");
	gets(buf);

	printf("\nThe bird says hi back:\n");
	printf(buf);

	printf("\n\nWant to say hi again?\n");
	gets(buf);

	return 0;
}