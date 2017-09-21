#include "ft_ls.h"

char		*ft_data_name(const char *path)
{
	char	*ret;
	int		i;

	i = ft_strlen(path);
	while (path[i - 1] != '/')
		i--;
	ret = (char *)(path + i);
	return (ret);
}

int			ft_data_nlink(const char *path)
{
	s_stat	stats;
	int		ret;

	if (stat(path, &stats) < 0)
		ft_perror("");
	ret = (int)stats.st_nlink;
	return (ret);
}

char		*ft_data_uid(const char *path, int len)
{
	s_stat	stats;
	s_pwd	*usr;
	char	*ret;
	int		i;

	if (stat(path, &stats) < 0)
		ft_perror("");
	i = 0;
	ret = (char *)ft_memalloc(sizeof(char) * len + 1);
	usr = getpwuid(stats.st_uid);
	while (usr->pw_name[i])
	{
		ret[i] = usr->pw_name[i];
		i++;
	}
	while (i < len + 1)
		ret[i++] = ' ';
	ret[i] = '\0';
	return (ret);
}

char		*ft_data_gid(const char *path, int len)
{
	s_stat	stats;
	s_grp	*grp;
	char	*ret;
	int		i;

	if (stat(path, &stats) < 0)
		ft_perror("");
	i = 0;
	ret = (char *)ft_memalloc(sizeof(char) * len + 1);
	grp = getgrgid(stats.st_gid);
	while (grp->gr_name[i])
	{
		ret[i] = grp->gr_name[i];
		i++;
	}
	while (i < len + 1)
		ret[i++] = ' ';
	ret[i] = '\0';
	return (ret);
}

char		*ft_data_size(const char *path, int len)
{
	s_stat	stats;
	char	*ret;
	char	*tmp;
	int		i;

	if (stat(path, &stats) < 0)
		ft_perror("");
	i = 0;
	ret = (char *)ft_memalloc(sizeof(char) * len + 1);
	tmp = ft_litoa((long long)stats.st_size);
	while (tmp[i])
	{
		ret[i] = tmp[i];
		i++;
	}
	while (i < len + 1)
		ret[i++] = ' ';
	ret[i] = '\0';
	return (ret);
}
