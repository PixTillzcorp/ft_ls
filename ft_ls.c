/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: heinfalt <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/12 13:13:42 by heinfalt          #+#    #+#             */
/*   Updated: 2017/10/12 13:13:45 by heinfalt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

static void	ft_print_single(const char *path, char *flags)
{
	char	**tab;
	t_pad	padding;

	if (ft_strchr(flags, 'l'))
	{
		tab = ft_init_tab(1);
		tab[0] = ft_strdup(path);
		padding = ft_padding(tab);
		ft_print_large(path, flags, padding);
		ft_free_tab(tab);
	}
	if (ft_strchr(flags, 'G'))
		ft_putstr("\033[36m.\033[0m\n");
	else
		ft_putstr(".\n");
}

static int	ft_get_file(const char **input, char *flags, int nbr, int pos)
{
	int		ret;
	int		i;

	i = 0;
	ret = 0;
	while (pos + i < nbr)
	{
		if ((!ft_isdir(input[pos + i]) || ft_strchr(flags, 'd') ||\
		(ft_is_l(input[pos + i]) && ft_strchr(flags, 'l'))) && input[pos + i])
			ret++;	
		i++;
	}
	return (ret);
}

static void	ft_single_file(const char **input, char *flags, int nbr, int pos)
{
	char	**tab;
	int		size;
	int		i;

	i = 0;
	size = ft_get_file(input, flags, nbr, pos);
	if (size)
	{
		tab = ft_init_tab(size);
		while (pos + i < nbr)
		{
			if ((!ft_isdir(input[pos + i]) || ft_strchr(flags, 'd') || (ft_is_l\
			(input[pos + i]) && ft_strchr(flags, 'l'))) && input[pos + i])
				ft_insert(tab, (char *)(input[pos + i]));
			i++;
		}
		ft_print_sort(ft_sort_tab(tab, flags), flags, 1);
		if (nbr - pos > size && tab[0])
			ft_putchar('\n');
		ft_free_tab(tab);
	}
}

static void	ft_find(const char **input, char *flags, int nbr_arg, int pos)
{
	int		i;

	i = 0;
	while (input[pos + i])
	{
		if (!ft_check_input(input[pos + (i++)], flags))
			input[pos + (i - 1)] = NULL;
	}
	ft_single_file(input, flags, nbr_arg, pos);
	if (!ft_strchr(flags, 'd'))
	{
		while (pos < nbr_arg)
		{
			if (ft_isdir(input[pos]) && !(ft_is_l(input[pos]) &&\
			ft_strchr(flags, 'l')))
			{
				ft_printf("%s:\n", input[pos]);
				ft_disp_dir(input[pos], flags, ft_nbrdir(input, nbr_arg));
				if (pos++ < ft_pos_last_dir(input, nbr_arg))
					ft_putchar('\n');
			}
			else
				pos++;
		}
	}
}

int			main(int argc, const char **argv)
{
	char	*flags;
	int		dir;

	flags = ft_strdup("");
	dir = 0;
	if (argc < 2)
	{
		ft_disp_dir(".", flags, 0);
		return (ft_ret_free(flags, 0));
	}
	else
		dir = ft_flag(argv, &flags);
	if (dir < 0)
	{
		if (ft_strchr(flags, 'd'))
			ft_print_single(".", flags);
		else
			ft_disp_dir(".", flags, 0);
	}
	else
		ft_find(argv, flags, argc, dir);
	return (ft_ret_free(flags, 0));
}
