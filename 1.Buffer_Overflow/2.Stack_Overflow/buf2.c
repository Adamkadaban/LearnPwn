#include <stdio.h>
#include <string.h>

int main(void)
{
  long code = 0;
  char name[16];
  
  setbuf(stdout, NULL);
  setbuf(stdin, NULL);
  setbuf(stderr, NULL);

  puts("Hi! What do you want to input?");

  gets(name);

  if(code == 0xcafebabe) {
    system("/bin/sh");
  }
}
