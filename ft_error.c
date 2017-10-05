#include "ft_ls.h"

void		ft_error(const char *msg, int usage)
{
	ft_putstr(msg);
	ft_putchar('\n');
	if (msg)
		ft_memdel((void **)&msg);
	if (usage)
		printf("usage : ft_ls [-Ralrt] [file ...]");
	exit(-1);
}

void		ft_perror(const char *msg)
{
	perror(msg);
	if (msg)
		ft_memdel((void **)&msg);
	exit(-1);
}
