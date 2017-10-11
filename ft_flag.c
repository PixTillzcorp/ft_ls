#include "ft_ls.h"

static int	ft_is_flag(char c)
{
	int		ret;

	ret = 0;
	ret += (c == 'l' || c == 'a' ? 1 : 0);
	ret += (c == 'R' || c == '1' ? 1 : 0);
	ret += (c == 'r' || c == 't' || c == 'S' ? 1 : 0);
	return (ret);
}

int			ft_flag(const char **args, char **flag)
{
	int		i;
	int		j;

	i = 1;
	j = 1;
	while (args[i])
	{
		if (args[i][0] == '-')
		{
			while (ft_is_flag(args[i][j]))
				(*flag) = ft_chrjoin_free((*flag), args[i][j++], 1);
			if (args[i][j])
				ft_error(ft_chrjoin_free("ft_ls : illegal option -- ", args[i][j], 0), 1);
			i++;
			j = 1;
		}
		else
			return (i);
	}
	return (-1);
}
