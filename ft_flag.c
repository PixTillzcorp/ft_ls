#include "ft_ls.h"

int			ft_a_or_f(char *flags)
{
	if (flags)
	{
		if (ft_strchr(flags, 'a'))
			return (1);
		else if (ft_strchr(flags, 'f'))
			return (1);
		else
			return (0);
	}
	return (0);
}

static int	ft_is_flag(char c)
{
	int		ret;

	ret = 0;
	ret += (c == 'l' || c == 'a' || c == 'g' ? 1 : 0);
	ret += (c == 'r' || c == 't' || c == 'S' ? 1 : 0);
	ret += (c == 'R' || c == '1' || c == 'f' ? 1 : 0);
	ret += (c == 'd' ? 1 : 0);
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
