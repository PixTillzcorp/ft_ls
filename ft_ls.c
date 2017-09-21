#include "ft_ls.h"

int			main(int argc, const char **argv)
{
	char	*flags;
	int		dir;

	flags = ft_strdup("");
	dir = 0;
	if (argc < 2)
	{
		ft_disp_dir(".", flags);
		free(flags);
		return (0);
	}
	else
		dir = ft_flag(argv, &flags);
	if (dir < 0)
		ft_disp_dir(".", flags);
	else
	{
		while (dir < argc)
			ft_disp_dir(argv[dir++], flags);
	}
	free(flags);
	return (0);
}
