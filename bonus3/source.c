#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

int	main(int argc, char **argv)
{
	int		uVar1;
	int		iVar2;
	char	*pcVar3;
	char	bVar4;
	char	local_98[65];
	char	local_57;
	char	local_56[66];
	FILE	*local_14;

	bVar4 = 0;
	local_14 = fopen("/home/user/end/.pass", "r");
	pcVar3 = local_98;
	for (iVar2 = 33; iVar2 != 0; iVar2--)
	{
		pcVar3[0] = '\0';
		pcVar3[1] = '\0';
		pcVar3[2] = '\0';
		pcVar3[3] = '\0';
		pcVar3 = pcVar3 + 4;
	}
	if ((local_14 == (FILE *)0) || (argc != 2))
		uVar1 = 0xffffffff;
	else
	{
		fread(local_98, 1, 66, local_14);
		local_57 = 0;
		iVar2 = atoi(argv[1]);
		local_98[iVar2] = '\0';
		fread(local_56, 1, 65, local_14);
		fclose(local_14);
		iVar2 = strcmp(local_98, argv[1]);
		if (iVar2 == 0)
			execl("/bin/sh", "sh", 0);
		else
			puts(local_56);
		uVar1 = 0;
	}
	return (uVar1);
}
