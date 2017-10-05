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
		if (lstat(tab[i++], &stats) < 0)
			ft_perror("");
		ret += (int)stats.st_blocks;
	}
	return (ret);
}

void		ft_print_large(const char *path, t_pad padding)
{
	char	*put;

	printf("%s  ", (put = ft_data_wrx(path)));
	free(put);
	printf("%2d ", ft_data_nlink(path));
	printf("%s ", (put = ft_data_uid(path, padding.n_uid)));
	free(put);
	printf("%s ", (put = ft_data_gid(path, padding.n_gid)));
	free(put);
	if (ft_is_bc(path))
	{
		ft_putxchar(' ', padding.b_size - printf("%d, %d",\
		ft_data_major(path), ft_data_minor(path)));
	}
	else
	{
		printf("%s ", (put = ft_data_size(path, padding.b_size)));
		free(put);
	}
	printf("%s ", (put = ft_data_date(path)));
	free(put);
}

int			ft_print_single(const char *path, int large)
{
	t_pad	padding;
	s_stat	stats;
	s_pwd	*usr;
	s_grp	*grp;

	if (lstat(path, &stats) < 0)
		ft_perror("");
	if (large)
	{
		usr = getpwuid(stats.st_uid);
		grp = getgrgid(stats.st_gid);
		padding.n_uid = (int)ft_strlen(usr->pw_name);
		padding.n_gid = (int)ft_strlen(grp->gr_name);
		if (ft_is_bc(path))
			padding.b_size = ft_len_min_max(path);
		else
			padding.b_size = ft_llnbrlen(stats.st_size);
		ft_print_large(path, padding);
	}
	printf("%s\n", path);
	return (1);
}

void		ft_print_sort(char **tab, char *flags)
{
	t_pad	padding;
	s_stat	stats;
	char	*buff;
	int		i;

	i = 0;
	if (ft_strchr(flags, 'l'))
		printf("total %d\n", ft_total_blocks(tab));
	padding = ft_padding(tab);
	while (tab[i])
	{
		if (!(buff = (char *)ft_memalloc(sizeof(char) * 100)))
			ft_perror("");
		buff[99] = '\0';
		if (stat(tab[i], &stats) < 0)
			ft_perror("");
		if (ft_strchr(flags, 'l'))
			ft_print_large(tab[i], padding);
		printf("%s", ft_data_name(tab[i]));
		if (readlink(tab[i++], buff, 100) > 0)
			printf(" -> %s", buff);
		printf("\n");
		free(buff);
	}
}
