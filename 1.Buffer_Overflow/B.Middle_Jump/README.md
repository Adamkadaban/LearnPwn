* Because we can't add function parameters on the stack for 64-bit binaries, we can just skip into the middle of the function

```bash
Dump of assembler code for function win:
   0x0000000000401195 <+0>:	push   rbp
   0x0000000000401196 <+1>:	mov    rbp,rsp
   0x0000000000401199 <+4>:	sub    rsp,0x10
   0x000000000040119d <+8>:	mov    DWORD PTR [rbp-0x4],edi
   0x00000000004011a0 <+11>:	cmp    DWORD PTR [rbp-0x4],0x539
   0x00000000004011a7 <+18>:	je     0x4011ba <win+37>
   0x00000000004011a9 <+20>:	lea    rax,[rip+0xe72]        # 0x402022
   0x00000000004011b0 <+27>:	mov    rdi,rax
   0x00000000004011b3 <+30>:	call   0x401030 <puts@plt>
   0x00000000004011b8 <+35>:	jmp    0x4011ce <win+57>
   0x00000000004011ba <+37>:	lea    rax,[rip+0xe66]        # 0x402027
   0x00000000004011c1 <+44>:	mov    rdi,rax
   0x00000000004011c4 <+47>:	mov    eax,0x0
   0x00000000004011c9 <+52>:	call   0x401040 <system@plt>
   0x00000000004011ce <+57>:	leave  
   0x00000000004011cf <+58>:	ret    
End of assembler dump.
```
* Above, we can see that the `return` in the source code is at win+35. After the return is at win+37, which is where we jump to get to the call of `system`
