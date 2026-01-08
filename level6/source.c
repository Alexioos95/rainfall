#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void	n(void)
{
	system("/bin/cat /home/user/level7/.pass");
	return;
}

void	m(void *param_1, int param_2, char *param_3, int param_4, int param_5)
{
	puts("Nope");
	return;
}

void	main(int argc, char **argv)
{
	char			*__dest;
	unsigned int	*puVar1;

	__dest = (char *)malloc(64);
	puVar1 = (unsigned int *)malloc(4);
	*puVar1 = m;
	strcpy(__dest, argv[1]);
	((void (*)(void)) *puVar1)();
	return;
}
