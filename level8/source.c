//////////////////////////////////////////////
////// WITHOUT OBFUSCATION;  SIMPLIFIED //////
//////////////////////////////////////////////

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

char	*auth = NULL;
char	*service = NULL;
char	*DAT_08048819 = "auth ";

int	main(void)
{
	char			cVar1;
	char			*pcVar2;
	char			*pcVar3;
	char			*pcVar4;
	int				iVar5;
	unsigned int	uVar6;
	char			*pbVar7;
	char			*pbVar8;
	bool			bVar9;
	char			uVar10;
	char			uVar11;
	bool			bVar12;
	char			uVar13;
	char			bVar14;
	char			local_90[5];
	char			local_8b[2];
	char			acStack_89[125];

	bVar14 = 0;
	while (1)
	{
		// Print and input
		printf("%p, %p \n", auth, service);
		pcVar4 = fgets((char *)local_90, 128, stdin);
		bVar9 = false;
		// Check NULL
		bVar12 = pcVar4 == NULL;
		if (bVar12)
			return (0);
		// Input is 'auth '
		iVar5 = 5;
		pbVar7 = local_90;
		pbVar8 = DAT_08048819;
		do
		{
			if (iVar5 == 0)
				break;
			iVar5--;
			bVar9 = *pbVar7 < *pbVar8;
			bVar12 = *pbVar7 == *pbVar8;
			pbVar7++;
			pbVar8++;
		}
		while (bVar12);
		uVar10 = 0;
		uVar13 = (bVar9 == 0 && bVar12 == 1);
		if ((bool)uVar13)
		{
			auth = (char *)malloc(4);
			auth[0] = '\0';
			auth[1] = '\0';
			auth[2] = '\0';
			auth[3] = '\0';
			uVar6 = 0xffffffff;
			pcVar4 = local_8b;
			while (uVar6 > 0 && pcVar4[uVar6] != '\0')
				uVar6--;
			uVar10 = uVar6 < 30;
			uVar13 = uVar6 == 30;
			if (uVar6 < 31)
				strcpy(auth, local_8b);
		}
		// Input is 'reset'
		iVar5 = 5;
		pbVar7 = local_90;
		pbVar8 = (char *)"reset";
		do
		{
			if (iVar5 == 0)
				break;
			iVar5--;
			uVar10 = *pbVar7 < *pbVar8;
			uVar13 = *pbVar7 == *pbVar8;
			pbVar7++;
			pbVar8++;
		}
		while ((bool)uVar13);
		uVar11 = 0;
		uVar10 = (uVar10 == 0 && uVar13 == 1);
		if (uVar10)
			free(auth);
		// Input is 'service'
		iVar5 = 6;
		pbVar7 = local_90;
		pbVar8 = (char *)"service";
		do
		{
			if (iVar5 == 0)
				break;
			iVar5--;
			uVar11 = *pbVar7 < *pbVar8;
			uVar10 = *pbVar7 == *pbVar8;
			pbVar7++;
			pbVar8++;
		}
		while ((bool)uVar10);
		uVar13 = 0;
		uVar10 = (uVar10 == 0 && uVar11 == 1);
		if ((bool)uVar10)
		{
			uVar13 = (char *)0xfffffff8 < local_90;
			uVar10 = acStack_89 == (char *)0x0;
			service = strdup(acStack_89);
		}
		iVar5 = 5;
		pbVar7 = local_90;
		pbVar8 = (char *)"login";
		do
		{
			if (iVar5 == 0)
				break;
			iVar5--;
			uVar13 = *pbVar7 < *pbVar8;
			uVar10 = *pbVar7 == *pbVar8;
			pbVar7++;
			pbVar8++;
		}
		while ((bool)uVar10);
		if (uVar13 == 0 && uVar10 == 1)
		{
			if (*(int *)(auth + 32) == 0)
				fwrite("Password:\n", 1, 10, stdout);
			else
				system("/bin/sh");
		}
	}
}

/////////////////////////////////////////////////
//////// WITH OBFUSCATION, AS PER GHIDRA ////////
/////////////////////////////////////////////////

/*
#include <stdio.h>
#include <stdbool.h>

char	*auth = NULL;
char	*service = NULL;
char	*DAT_08048819 = "auth ";

int main(void)
{
	char cVar1;
	char *pcVar2;
	char *pcVar3;
	char *pcVar4;
	int iVar5;
	unsigned int uVar6;
	char *pbVar7;
	char *pbVar8;
	bool bVar9;
	char uVar10;
	char uVar11;
	bool bVar12;
	char uVar13;
	char bVar14;
	char local_90[5];
	char local_8b[2];
	char acStack_89[125];
	
	bVar14 = 0;
	do
	{
		printf("%p, %p \n", auth, service);
		pcVar4 = fgets((char *)local_90, 128, stdin);
		bVar9 = false;
		bVar12 = pcVar4 == NULL;
		if (bVar12)
			return (0);
		iVar5 = 5;
		pbVar7 = local_90;
		pbVar8 = &DAT_08048819;
		do
		{
			if (iVar5 == 0)
				break;
			iVar5 = iVar5 + -1;
			bVar9 = *pbVar7 < *pbVar8;
			bVar12 = *pbVar7 == *pbVar8;
			pbVar7 = pbVar7 + (unsigned int)bVar14 * -2 + 1;
			pbVar8 = pbVar8 + (unsigned int)bVar14 * -2 + 1;
		}
		while (bVar12);
		uVar10 = 0;
		uVar13 = (!bVar9 && !bVar12) == bVar9;
		if ((bool)uVar13)
		{
			auth = (char *)malloc(4);
			pcVar4 = auth + 1;
			pcVar2 = auth + 2;
			pcVar3 = auth + 3;
			auth[0] = '\0';
			*pcVar4 = '\0';
			*pcVar2 = '\0';
			*pcVar3 = '\0';
			uVar6 = 0xffffffff;
			pcVar4 = local_8b;
			do
			{
				if (uVar6 == 0)
					break;
				uVar6 = uVar6 - 1;
				cVar1 = *pcVar4;
				pcVar4 = pcVar4 + (unsigned int)bVar14 * -2 + 1;
			}
			while (cVar1 != '\0');
			uVar6 = ~uVar6 - 1;
			uVar10 = uVar6 < 30;
			uVar13 = uVar6 == 30;
			if (uVar6 < 31)
				strcpy(auth, local_8b);
		}
		iVar5 = 5;
		pbVar7 = local_90;
		pbVar8 = (char *)"reset";
		do
		{
			if (iVar5 == 0)
				break;
			iVar5 = iVar5 + -1;
			uVar10 = *pbVar7 < *pbVar8;
			uVar13 = *pbVar7 == *pbVar8;
			pbVar7 = pbVar7 + (unsigned int)bVar14 * -2 + 1;
			pbVar8 = pbVar8 + (unsigned int)bVar14 * -2 + 1;
		}
		while ((bool)uVar13);
		uVar11 = 0;
		uVar10 = (!(bool)uVar10 && !(bool)uVar13) == (bool)uVar10;
		if ((bool)uVar10)
			free(auth);
		iVar5 = 6;
		pbVar7 = local_90;
		pbVar8 = (char *)"service";
		do
		{
			if (iVar5 == 0)
				break;
			iVar5 = iVar5 + -1;
			uVar11 = *pbVar7 < *pbVar8;
			uVar10 = *pbVar7 == *pbVar8;
			pbVar7 = pbVar7 + (unsigned int)bVar14 * -2 + 1;
			pbVar8 = pbVar8 + (unsigned int)bVar14 * -2 + 1;
		}
		while ((bool)uVar10);
		uVar13 = 0;
		uVar10 = (!(bool)uVar11 && !(bool)uVar10) == (bool)uVar11;
		if ((bool)uVar10)
		{
			uVar13 = (char *)0xfffffff8 < local_90;
			uVar10 = acStack_89 == (char *)0x0;
			service = strdup(acStack_89);
		}
		iVar5 = 5;
		pbVar7 = local_90;
		pbVar8 = (char *)"login";
		do
		{
			if (iVar5 == 0)
				break;
			iVar5 = iVar5 + -1;
			uVar13 = *pbVar7 < *pbVar8;
			uVar10 = *pbVar7 == *pbVar8;
			pbVar7 = pbVar7 + (unsigned int)bVar14 * -2 + 1;
			pbVar8 = pbVar8 + (unsigned int)bVar14 * -2 + 1;
		}
		while ((bool)uVar10);
		if ((!(bool)uVar13 && !(bool)uVar10) == (bool)uVar13)
		{
			if (*(int *)(auth + 0x20) == 0)
				fwrite("Password:\n", 1, 10, stdout);
			else
				system("/bin/sh");
		}
	}
	while (true);
}
*/
