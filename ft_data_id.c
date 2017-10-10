#include "ft_ls.h"

char		*ft_data_name(const char *path)
{
	char	*ret;
	int		i;

	i = ft_strlen(path);
	while (path[i - 1] != '/' && i != 0)
		i--;
	ret = (char *)(path + i);
	return (ret);
}

char		*ft_data_uid(const char *path, int len)
{
	s_stat	stats;
	s_pwd	*usr;
	char	*ret;
	int		i;

	if (lstat(path, &stats) < 0)
		ft_perror("");
	i = 0;
	if (!(usr = getpwuid(stats.st_uid)))
	{
		len -= (int)(ft_strlen(ret = ft_itoa((int)stats.st_uid)));
		ret = ft_strjoin_free(ret, ft_strchain(' ', len), 'b');
		return (ret);
	}
	ret = (char *)ft_memalloc(sizeof(char) * len + 1);
	while (usr->pw_name[i] && i < len)
	{
		ret[i] = usr->pw_name[i];
		i++;
	}
	while (i < len)
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

	if (lstat(path, &stats) < 0)
		ft_perror("");
	i = 0;
	if (!(grp = getgrgid(stats.st_gid)))
	{
		len -= (int)(ft_strlen(ret = ft_itoa((int)stats.st_gid)));
		ret = ft_strjoin_free(ret, ft_strchain(' ', len), 'b');
		return (ret);
	}
	ret = (char *)ft_memalloc(sizeof(char) * len + 1);
	while (grp->gr_name[i] && i < len)
	{
		ret[i] = grp->gr_name[i];
		i++;
	}
	while (i < len)
		ret[i++] = ' ';
	ret[i] = '\0';
	return (ret);
}
