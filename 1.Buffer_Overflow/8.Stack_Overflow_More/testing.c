#include <stdio.h>
#include <string.h>

int main(void)
{
  long code = 0x4141414141414141;
  long cool = 0x4242424242424242;
  char name[16];

  setbuf(stdout, NULL);
  setbuf(stdin, NULL);
  setbuf(stderr, NULL);

  puts("Hi! What do you want to input?");

  gets(&name);
  if(strcmp(name,"hello") == 0){
    if(code == 0xcafebabe) {
      if(cool == 0xdeadbeef) {
        system("/bin/sh");
      }
    }
  }
}
