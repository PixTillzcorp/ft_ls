#include "ft_ls.h"

int			main(int argc, const char **argv)
{
	char	*flags;
	int		multi;
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
	multi = argc - dir;
	if (dir < 0)
		ft_disp_dir(".", flags, 0);
	else
	{
		while (dir < argc)
		{
			ft_disp_dir(argv[dir++], flags, multi);
			printf((dir == argc ? "" : "\n"));
		}
	}
	return (ft_ret_free(flags, 0));
}
