/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: heinfalt <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/12 13:13:54 by heinfalt          #+#    #+#             */
/*   Updated: 2017/10/12 13:13:58 by heinfalt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

static void		ft_colored_output(const char *path, char *flags, mode_t st_mode)
{
	char		type;

	if (ft_strchr(flags, 'G'))
	{
		type = ft_data_type(st_mode & S_IFMT);
		if (type == 'd')
			ft_putstr_clrd(ft_data_name(path), "\033[36m");
		else if (type == 'l')
			ft_putstr_clrd(ft_data_name(path), "\033[35m");
		else if (type == 'b')
			ft_putstr_clrd(ft_data_name(path), "\033[34m\033[46m");
		else if (type == 'c')
			ft_putstr_clrd(ft_data_name(path), "\033[34m\033[43m");
		else if (type == 'p')
			ft_putstr_clrd(ft_data_name(path), "\033[33m");
		else if (type == 's')
			ft_putstr_clrd(ft_data_name(path), "\033[32m");
		else if (type == '-' && (S_IEXEC & st_mode))
			ft_putstr_clrd(ft_data_name(path), "\033[31m");
		else
			ft_putstr(ft_data_name(path));
	}
	else
		ft_putstr(ft_data_name(path));
}

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
		if (pos % output == 0 && tab[pos])
			ft_putchar('\n');
		else
			ft_putxchar(' ', len - ft_strlen(ft_data_name(tab[pos - 1])));
		if (tab[pos] == NULL && output != 1)
			ft_putchar('\n');
	}
}

static int		ft_total_blocks(char **tab)
{
	t_stat		stats;
	int			i;
	int			ret;

	i = 0;
	ret = 0;
	while (tab[i])
	{
		if (lstat(tab[i++], &stats) < 0)
			ft_perror(ft_strdup("ft_ls "));
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
		ft_putxchar(' ', (padding.b_size / 2) - 1 - ft_printf("%d",\
		ft_data_major(path)));
		ft_putchar(',');
		ft_putxchar(' ', (padding.b_size / 2) + (padding.b_size % 2)\
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
	t_stat		stats;
	char		*buff;
	int			i;

	i = 0;
	if (ft_strchr(flags, 'l') && !single)
		ft_printf("total %d\n", ft_total_blocks(tab));
	padding = ft_padding(tab);
	while (tab[i])
	{
		if (!(buff = (char *)ft_memalloc(sizeof(char) * 100)))
			ft_perror(ft_strdup("ft_ls "));
		buff[99] = '\0';
		if (lstat(tab[i], &stats) < 0)
			ft_perror(ft_strdup("ft_ls "));
		if (ft_strchr(flags, 'l'))
			ft_print_large(tab[i], flags, padding);
		ft_colored_output(tab[i], flags, stats.st_mode);
		if (readlink(tab[i++], buff, 100) > 0 && ft_strchr(flags, 'l'))
			ft_printf(" -> %s", buff);
		ft_padding_out(tab, flags, i);
		free(buff);
	}
}
