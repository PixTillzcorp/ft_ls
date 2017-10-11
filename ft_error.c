#include "ft_ls.h"

void		ft_error(const char *msg, int usage)
{
	ft_putstr(msg);
	ft_putchar('\n');
	if (msg)
		ft_memdel((void **)&msg);
	if (usage)
		printf("usage : ft_ls [-1GRSafglrt] [file ...]");
	exit(-1);
}

void		ft_check_input(const char **input, int nbr_arg, int pos)
{
	DIR		*test;

	while (pos < nbr_arg)
	{
		if ((test = ft_opendir(input[pos++])))
			ft_closedir(test);
	}
}

void		ft_perror(const char *msg)
{
	perror(msg);
	if (msg)
		ft_memdel((void **)&msg);
	exit(-1);
}
