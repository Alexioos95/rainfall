#include <stddef.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

int		language = 0;
char	*DAT_0804873d = "fi";
char	*DAT_08048740 = "nl";

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
		pcVar3 = local_60;
		puVar4 = (int *)((char *)local_60 - 76);
		for (iVar2 = 19; iVar2 != 0; iVar2--)
		{
			*puVar4 = *(int *)pcVar3;
			pcVar3 = pcVar3 + 4;
			puVar4++;
		}
		uVar1 = greetuser();
	}
	else
		uVar1 = 1;
	return (uVar1);
}
