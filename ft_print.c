#include "ft_ls.h"

static int	ft_total_blocks(char **tab)
{
	s_stat	stats;
	int		i;
	int		ret;

	i = 0;
	ret = 0;
	while (tab[i])
	{
		if (stat(tab[i++], &stats) < 0)
			ft_perror("");
		ret += (int)stats.st_blocks;
	}
	return (ret);
}

static void	ft_print_large(const char *path, int *mlen)
{
	char	*put;

	printf("%s  ", (put = ft_data_wrx(path)));
	free(put);
	printf("%2d ", ft_data_nlink(path));
	printf("%s ", (put = ft_data_uid(path, mlen[0])));
	free(put);
	printf("%s ", (put = ft_data_gid(path, mlen[1])));
	free(put);
	printf("%s ", (put = ft_data_size(path, mlen[2])));
	free(put);
	printf("%12s ", (put = ft_data_date(path)));
	free(put);
}

static int	ft_llnbrlen(long long nbr)
{
	int count;

	count = 1;
	while (nbr != 0)
	{
		nbr /= 10;
		if (nbr != 0)
			count++;
		else
			break;
	}
	return (count);
}

static int	*ft_maxlen(char **tab)
{
	s_stat	stats;
	s_pwd	*usr;
	s_grp	*grp;
	int		*ret;
	int		i;

	i = 0;
	ret = (int *)ft_memalloc(sizeof(int) * 3);
	while (i < 3)
		ret[i++] = 0;
	i = 0;
	while (tab[i])
	{
		if (stat(tab[i++], &stats) < 0)
			ft_perror("");
		usr = getpwuid(stats.st_uid);
		grp = getgrgid(stats.st_gid);
		if (ret[0] < (int)ft_strlen(usr->pw_name))
			ret[0] = (int)ft_strlen(usr->pw_name);
		if (ret[1] < (int)ft_strlen(grp->gr_name))
			ret[1] = (int)ft_strlen(grp->gr_name);
		if (ret[2] < ft_llnbrlen(stats.st_size))
			ret[2] = ft_llnbrlen(stats.st_size);
	}
	return (ret);
}

void		ft_print_sort(char **tab, char *flags)
{
	s_stat	stats;
	char	*buff;
	int		*mlen;
	int		i;

	i = 0;
	mlen = ft_maxlen(tab);
	if (ft_strchr(flags, 'l'))
		printf("total %d\n", ft_total_blocks(tab));
	while (tab[i])
	{
		buff = (char *)ft_memalloc(sizeof(char) * 100);
		buff[99] = '\0';
		if (stat(tab[i], &stats) < 0)
			ft_perror("");
		if (ft_strchr(flags, 'l'))
			ft_print_large(tab[i], mlen);
		printf("%s", ft_data_name(tab[i]));
		if (readlink(tab[i++], buff, 100) > 0)
			printf(" -> %s", buff);
		printf("\n");
		free(buff);
	}
	free(mlen);
}
