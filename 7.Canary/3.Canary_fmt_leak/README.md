* In the disassembly, `gs:0x14` is the value of the canary:
	* This is at offset `35`
* The leak then occurs with the only call of printf shown
	* gcc optimizes the other `printf` calls into `puts` calls, as those are constant strings
	* printf is called at offset `98`
```
Dump of assembler code for function main:
   0x08049241 <+0>:	lea    ecx,[esp+0x4]
   0x08049245 <+4>:	and    esp,0xfffffff0
   0x08049248 <+7>:	push   DWORD PTR [ecx-0x4]
   0x0804924b <+10>:	push   ebp
   0x0804924c <+11>:	mov    ebp,esp
   0x0804924e <+13>:	push   ebx
   0x0804924f <+14>:	push   ecx
   0x08049250 <+15>:	sub    esp,0x30
   0x08049253 <+18>:	call   0x80490f0 <__x86.get_pc_thunk.bx>
   0x08049258 <+23>:	add    ebx,0x2da8
   0x0804925e <+29>:	mov    eax,gs:0x14
=> 0x08049264 <+35>:	mov    DWORD PTR [ebp-0xc],eax
   0x08049267 <+38>:	xor    eax,eax
   0x08049269 <+40>:	sub    esp,0xc
   0x0804926c <+43>:	lea    eax,[ebx-0x1ff0]
   0x08049272 <+49>:	push   eax
   0x08049273 <+50>:	call   0x8049070 <puts@plt>
   0x08049278 <+55>:	add    esp,0x10
   0x0804927b <+58>:	sub    esp,0xc
   0x0804927e <+61>:	lea    eax,[ebp-0x2c]
   0x08049281 <+64>:	push   eax
   0x08049282 <+65>:	call   0x8049050 <gets@plt>
   0x08049287 <+70>:	add    esp,0x10
   0x0804928a <+73>:	sub    esp,0xc
   0x0804928d <+76>:	lea    eax,[ebx-0x1fd0]
   0x08049293 <+82>:	push   eax
   0x08049294 <+83>:	call   0x8049070 <puts@plt>
   0x08049299 <+88>:	add    esp,0x10
   0x0804929c <+91>:	sub    esp,0xc
   0x0804929f <+94>:	lea    eax,[ebp-0x2c]
   0x080492a2 <+97>:	push   eax
=> 0x080492a3 <+98>:	call   0x8049040 <printf@plt>
   0x080492a8 <+103>:	add    esp,0x10
   0x080492ab <+106>:	sub    esp,0xc
   0x080492ae <+109>:	lea    eax,[ebx-0x1fb8]
   0x080492b4 <+115>:	push   eax
   0x080492b5 <+116>:	call   0x8049070 <puts@plt>
   0x080492ba <+121>:	add    esp,0x10
   0x080492bd <+124>:	sub    esp,0xc
   0x080492c0 <+127>:	lea    eax,[ebp-0x2c]
   0x080492c3 <+130>:	push   eax
   0x080492c4 <+131>:	call   0x8049050 <gets@plt>
   0x080492c9 <+136>:	add    esp,0x10
   0x080492cc <+139>:	mov    eax,0x0
   0x080492d1 <+144>:	mov    edx,DWORD PTR [ebp-0xc]
   0x080492d4 <+147>:	sub    edx,DWORD PTR gs:0x14
   0x080492db <+154>:	je     0x80492e2 <main+161>
   0x080492dd <+156>:	call   0x8049360 <__stack_chk_fail_local>
   0x080492e2 <+161>:	lea    esp,[ebp-0x8]
   0x080492e5 <+164>:	pop    ecx
   0x080492e6 <+165>:	pop    ebx
   0x080492e7 <+166>:	pop    ebp
   0x080492e8 <+167>:	lea    esp,[ecx-0x4]
   0x080492eb <+170>:	ret    
End of assembler dump.
```
* To get the offset to the canary, check what eax is at the first breakpoint
	* `i r eax`
	* The last byte of a canary is always a null byte, so it should end with 2 0s
* Then stop at the second breakpoint and check the difference between the canary and the input on the stack using 
	* `tele 30`
	* adjust this number depending on how much of the stack you need to see