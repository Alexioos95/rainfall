#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>

static const char *UNK_080c5348 = "/bin/sh";
static const char *UNK_080c5350 = "No !\n";

void	main(int argc, char **argv)
{
	int		iVar1;
	char	*uStack_20;
	char	*uStack_1c;
	int		uStack_14;
	int		uStack_18;
	
	iVar1 = atoi(argv[1]);
	if (iVar1 == 423)
	{
		uStack_20 = strdup(UNK_080c5348);
		uStack_1c = 0;
		uStack_14 = getegid();
		uStack_18 = geteuid();
		setresgid(uStack_14, uStack_14, uStack_14);
		setresuid(uStack_18, uStack_18, uStack_18);
		execv(UNK_080c5348, &uStack_20);
	}
	else
		fwrite(UNK_080c5350, 1, 5, stderr);
	return ;
}
