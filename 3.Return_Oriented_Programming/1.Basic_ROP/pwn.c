#include <stdio.h>
#include <string.h>
#include <unistd.h>

char whatsThis[] = "/bin/sh";

int main(){
	setvbuf(stdout, NULL, _IONBF, 0);

	puts("Welcome to beginner ROP!");
	vuln();
	puts("Exiting");

	return 0;
}

void vuln(){
	char buf[32];
	puts("Enter the password: ");

	gets(buf);

	puts("Wrong password\n");
}

void soClose(){
	system("/bin/ls");
}
