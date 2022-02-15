int main(){
	puts("Welcome to challenge 0!");
	vuln();
	puts("Sorry");
}

void vuln(){
	char buf[16];
	gets(buf);
}

void win(int x){
	if(x != 1337){
		puts("Nope");
		return;
	}
	system("/bin/sh");
}
