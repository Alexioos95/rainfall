#include <stdio.h>
#include <string.h>
#include <unistd.h>

char	*DAT_080486a0 = " - ";

void	p(char *param_1, char *param_2)
{
	char	*pcVar1;
	char	local_100c[4104];
	
	puts(param_2);
	read(0, local_100c, 4096);
	pcVar1 = strchr(local_100c, '\n');
	*pcVar1 = '\0';
	strncpy(param_1, local_100c, 20);
	return;
}

void	pp(char *param_1)
{
	char			cVar1;
	unsigned int	uVar2;
	char			*pcVar3;
	char			bVar4;
	char			local_34[20];
	char			local_20[20];
	
	bVar4 = 0;
	p(local_34, DAT_080486a0);
	p(local_20, DAT_080486a0);
	strcpy(param_1, local_34);
	uVar2 = 0xffffffff;
	pcVar3 = param_1;
	do
	{
		if (uVar2 == 0)
			break;
		uVar2--;
		cVar1 = *pcVar3;
		pcVar3++;
	}
	while (cVar1 != '\0');
	param_1[0xfffffffe - uVar2] = ' ';
	param_1[0xfffffffe - uVar2 + 1] = '\0';
	strcat(param_1, local_20);
	return;
}

int	main(void)
{
	char	local_3a[54];

	pp(local_3a);
	puts(local_3a);
	return (0);
}
