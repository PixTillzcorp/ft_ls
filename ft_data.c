#include "ft_ls.h"

long		ft_data_mtime(const char *path)
{
	s_stat	stats;

	if (stat(path, &stats) < 0)
		ft_perror("");
	return ((long)stats.st_mtimespec.tv_sec);
}

char		*ft_data_date(const char *path)
{
	s_stat	stats;
	time_t	*nowaday;
	char	*date;
	char	*ret;
	int		i;

	nowaday = NULL;
	i = 7;
	ret = (char *)ft_memalloc(sizeof(char) * 13);
	ret[12] = '\0';
	if (stat(path, &stats) < 0)
		ft_perror("");
	date = ctime(&stats.st_mtimespec.tv_sec);
	if ((long)time(nowaday) - (long)stats.st_mtimespec.tv_sec > 15778800)
	{
		ret = ft_strncpy(ret, date + 4, ft_strlen(date) - 8);
		while (ret[i] && i < 11)
			ret[i++] = *((date++) + 20);
		ret[i++] = ' ';
		ret[i] = '\0';
		return (ret);
	}
	return (ft_strncpy(ret, date + 4, ft_strlen(date) - 13));
}

static char	ft_data_type(mode_t type)
{
	if (type == S_IFDIR)
		return ('d');
	else if (type == S_IFCHR)
		return ('c');
	else if (type == S_IFLNK)
		return ('l');
	else if (type == S_IFBLK)
		return ('b');
	else if (type == S_IFSOCK)
		return ('s');
	else if (type == S_IFIFO)
		return ('p');
	else if (type == S_IFREG)
		return ('-');
	return (0);
}

static char	*ft_get_rights(mode_t rights)
{
	char	*ret;

	ret = ft_chrjoin_free("", (rights & S_IRUSR ? 'r' : '-'), 0);
	ret = ft_chrjoin_free(ret, (rights & S_IWUSR ? 'w' : '-'), 1);
	if (rights & S_ISUID)
		ret = ft_chrjoin_free(ret, (rights & S_IXUSR ? 's' : 'S'), 1);
	else
		ret = ft_chrjoin_free(ret, (rights & S_IXUSR ? 'x' : '-'), 1);
	ret = ft_chrjoin_free(ret, (rights & S_IRGRP ? 'r' : '-'), 1);
	ret = ft_chrjoin_free(ret, (rights & S_IWGRP ? 'w' : '-'), 1);
	if (rights & S_ISGID)
		ret = ft_chrjoin_free(ret, (rights & S_IXGRP ? 's' : 'S'), 1);
	else
		ret = ft_chrjoin_free(ret, (rights & S_IXGRP ? 'x' : '-'), 1);
	ret = ft_chrjoin_free(ret, (rights & S_IROTH ? 'r' : '-'), 1);
	ret = ft_chrjoin_free(ret, (rights & S_IWOTH ? 'w' : '-'), 1);
	if (rights & S_ISVTX)
		ret = ft_chrjoin_free(ret, (rights & S_IXOTH ? 't' : 'T'), 1);
	else
		ret = ft_chrjoin_free(ret, (rights & S_IXOTH ? 'x' : '-'), 1);
	return (ret);
}

char		*ft_data_wrx(const char *path)
{
	s_stat	stats;
	mode_t	rights;
	char	*buff;
	char	*tmp;

	buff = (char *)ft_memalloc(sizeof(char) * 100);
	buff[99] = '\0';
	if (stat(path, &stats) < 0)
		ft_perror("");
	rights = stats.st_mode;
	if (readlink(path, buff, 100) < 0)
		tmp = ft_chrjoin_free(ft_strdup(""), ft_data_type(rights & S_IFMT), 1);
	else
		tmp = ft_chrjoin_free(ft_strdup(""), 'l', 1);
	tmp = ft_strjoin_free(tmp, ft_get_rights(rights), 'b');
	free(buff);
	return (tmp);
}
