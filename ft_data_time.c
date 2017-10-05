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
