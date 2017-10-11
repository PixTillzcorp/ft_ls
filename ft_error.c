#include "ft_ls.h"

void		ft_error(const char *msg, int usage)
{
	ft_putstr(msg);
	ft_putchar('\n');
	if (msg)
		ft_memdel((void **)&msg);
	if (usage)
		printf("usage : ft_ls [-1RalrtS] [file ...]");
	exit(-1);
}

void		ft_check_input(const char **input, int nbr_arg, int pos)
{
	DIR		*test;

	while (pos < nbr_arg)
		test = ft_opendir(input[pos++]);
}

void		ft_perror(const char *msg)
{
	perror(msg);
	if (msg)
		ft_memdel((void **)&msg);
	exit(-1);
}
