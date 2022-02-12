#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define FLAGFILE "flag.txt"

void getFlag(void){	
	char flag[40];
	FILE *fp = fopen(FLAGFILE, "r");

	if (!fp)	{
		perror(FLAGFILE);
		return;
	}

	fgets(flag, sizeof(flag), fp);
	fclose(fp);

	printf("%s\n", flag);
}

void greeter(void){
	char key[10];
	puts("Type in the admin password to enter:");
	printf("Address of greeter: %p\n", greeter);
	scanf("%s", key); // Unbounded SCANF(3)
}

int main(void){
	greeter();
	puts("Sorry, that's the wrong password");
	return 0;
}
