#include "ft_ls.h"

static void		ft_padding_out(char **tab, char *flags, int pos)
{
	static char	**tab_add;
	static int	len;
	static int	output;

	if (ft_strchr(flags, 'l') || ft_strchr(flags, '1'))
		ft_putchar('\n');
	else
	{
		if (tab_add != tab)
		{
			tab_add = tab;
			len = ft_lenmax_name(tab) + 2;
			if (!(output = ft_get_winsize() / len))
				output = 1;
		}
		if (pos % output == 0)
			ft_putchar('\n');
		else
			ft_putxchar(' ', len - ft_strlen(ft_data_name(tab[pos - 1])));
		if (tab[pos] == NULL && output != 1)
			ft_putchar('\n');
	}
}

static int		ft_total_blocks(char **tab)
{
	s_stat		stats;
	int			i;
	int			ret;

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

void			ft_print_large(const char *path, char *flags, t_pad padding)
{
	ft_putstr_free(ft_data_wrx(path), 1);
	ft_printf("%4d ", ft_data_nlink(path));
	if (!ft_strchr(flags, 'g'))
	{
		ft_putstr_free(ft_data_uid(path, padding.n_uid), 1);
		ft_putchar(' ');
	}
	ft_putstr_free(ft_data_gid(path, padding.n_gid), 1);
	ft_putchar(' ');
	if (ft_is_bc(path))
	{
		ft_putxchar(' ', (padding.b_size / 2) - ft_printf("%d",\
		ft_data_major(path)));
		ft_putchar(',');
		ft_putxchar(' ', (padding.b_size / 2) + (padding.b_size % 2) - 1\
		- ft_printf(" %d", ft_data_major(path)));
		ft_putchar(' ');
	}
	else
	{
		ft_putstr_free(ft_data_size(path, padding.b_size), 1);
		ft_putchar(' ');
	}
	ft_putstr_free(ft_data_date(path), 1);
	ft_putchar(' ');
}

void			ft_print_sort(char **tab, char *flags, int single)
{
	t_pad		padding;
	s_stat		stats;
	char		*buff;
	int			i;

	i = 0;
	if (ft_strchr(flags, 'l') && !single)
		ft_printf("total %d\n", ft_total_blocks(tab));
	padding = ft_padding(tab);
	while (tab[i])
	{
		if (!(buff = (char *)ft_memalloc(sizeof(char) * 100)))
			ft_perror("");
		buff[99] = '\0';
		if (lstat(tab[i], &stats) < 0)
			ft_perror("");
		if (ft_strchr(flags, 'l'))
			ft_print_large(tab[i], flags, padding);
		ft_putstr(ft_data_name(tab[i]));
		if (readlink(tab[i++], buff, 100) > 0 && ft_strchr(flags, 'l'))
			ft_printf(" -> %s", buff);
		ft_padding_out(tab, flags, i);
		free(buff);
	}
}
