#include <stdio.h>
#include <string.h>
#include <unistd.h>

void	p(void)
{
	char			local_50[76];
	unsigned int	unaff_retaddr = (unsigned int)__builtin_return_address(0);
	
	fflush(stdout);
	gets(local_50);
	if ((unaff_retaddr & 0xb0000000) == 0xb0000000)
	{
		printf("(%p)\n", unaff_retaddr);
		exit(1);
	}
	puts(local_50);
	strdup(local_50);
	return;
}

void	main(void)
{
	p();
	return;
}
