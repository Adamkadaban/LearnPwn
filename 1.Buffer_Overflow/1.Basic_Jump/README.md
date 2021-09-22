* Code:
```c
#include <stdio.h>
#include <stdlib.h>

void getName(){
	char name[15] = {0}; // !! Our buffer is only 15 characters... but: !!


	printf("What's your name? ");
	fgets(name, 100, stdin); // !! We are reading 100 characters despite only being able to store 15 characters !!
	printf("Cool name %s!", name);

}


void main(){
	getName();
}

void openShell(){
	system("/bin/sh");
}

```
* Decompiling in Ghidra, we get the following code for all the user defined functions:
```c
void getName(void){
  undefined8 local_17;
  undefined4 local_f;
  undefined2 local_b;
  undefined local_9;
  
  local_17 = 0;
  local_f = 0;
  local_b = 0;
  local_9 = 0;
  printf("What\'s your name? ");
  fgets((char *)&local_17,100,stdin);
  printf("Cool name %s!",&local_17);
  return;
}

void main(void){
  getName();
  return;
}


void openShell(void){
  system("/bin/sh");
  return;
}
```

* Stack:
```
---------------------------
|   main Return Address   | ↓️  
---------------------------
|     main Saved RBP      | ↓
---------------------------
| getName Return Address  | ↓
---------------------------
|   getName Saved RBP     | ↓
---------------------------
| getName 'name' Variable | ↓
---------------------------
| openShell Return Address| ↓
---------------------------
|   openShell Saved RBP   | ↓
---------------------------
```
* Notice the stack grow downwards
	* Every stack frame always starts with the return address, then the frame pointer
	* The return address is where the computer goes at the end of the function


* First, we want to be able to make the program crash. If we can do that, we can make it crash how we want to make the program do something malicious.

