#include "ft_ls.h"

static void	ft_find(const char **input, char *flags, int nbr_arg, int pos)
{
	int		multi;
	int		tmp;

	tmp = pos;
	multi = nbr_arg - pos;
	while (pos < nbr_arg)
	{
		if (ft_isdir(input[pos]))
			pos++;
		else
			ft_print_single(input[pos++], (ft_strchr(flags, 'l') ? 1 : 0));
	}
	pos = tmp;
	while (pos < nbr_arg)
	{
		if (ft_isdir(input[pos]))
		{
			ft_disp_dir(input[pos++], flags, multi);
			if (pos != nbr_arg)
				ft_putchar('\n');
		}
		else
			pos++;
	}
}

int			main(int argc, const char **argv)
{
	char	*flags;
	int		dir;

	flags = ft_strdup("");
	dir = 0;
	if (argc < 2)
	{
		ft_disp_dir(".", flags, 0);
		return (ft_ret_free(flags, 0));
	}
	else
		dir = ft_flag(argv, &flags);
	if (dir < 0)
		ft_disp_dir(".", flags, 0);
	else
		ft_find(argv, flags, argc, dir);
	return (ft_ret_free(flags, 0));
}
