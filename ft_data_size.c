#include "ft_ls.h"

int			ft_len_min_max(const char *path)
{
	int		ret;

	ret = 0;
	ret += ft_nbrlen(ft_data_minor(path));
	ret += ft_nbrlen(ft_data_major(path));
	ret += 2;
	return (ret);
}

int			ft_data_nlink(const char *path)
{
	s_stat	stats;
	int		ret;

	if (lstat(path, &stats) < 0)
		ft_perror("");
	ret = (int)stats.st_nlink;
	return (ret);
}

int			ft_data_minor(const char *path)
{
	s_stat	stats;

	if (lstat(path, &stats) < 0)
		ft_perror("");
	return (minor(stats.st_rdev));
}

int			ft_data_major(const char *path)
{
	s_stat	stats;

	if (lstat(path, &stats) < 0)
		ft_perror("");
	return (major(stats.st_rdev));
}

char		*ft_data_size(const char *path, int len)
{
	s_stat	stats;
	char	*ret;
	char	*tmp;
	int		i;

	if (lstat(path, &stats) < 0)
		ft_perror("");
	i = 0;
	ret = (char *)ft_memalloc(sizeof(char) * len + 1);
	tmp = ft_litoa((long long)stats.st_size);
	while (tmp[i] && i < len)
	{
		ret[i] = tmp[i];
		i++;
	}
	while (i < len)
		ret[i++] = ' ';
	ret[i] = '\0';
	free(tmp);
	return (ret);
}
