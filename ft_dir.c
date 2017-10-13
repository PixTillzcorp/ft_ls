/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dir.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: heinfalt <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/12 13:13:12 by heinfalt          #+#    #+#             */
/*   Updated: 2017/10/12 13:13:17 by heinfalt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

static char		*ft_newpath(char *dest, const char *p, const char *d)
{
	int			i;
	int			j;

	i = 0;
	j = 0;
	if (!(dest = (char *)malloc(sizeof(char) * (ft_strlen(p) +\
	ft_strlen(d) + 2))))
		ft_perror(ft_strdup("ft_ls "));
	while (p[i])
		dest[j++] = p[i++];
	dest[j++] = '/';
	i = 0;
	while (d[i])
		dest[j++] = d[i++];
	dest[j] = '\0';
	return (dest);
}

static void		ft_rec_disp(char **tab, char *flags, int nbr_dir)
{
	int			i;

	i = 0;
	while (tab[i])
	{
		if (!ft_is_l(tab[i]) && ft_isdir(tab[i]) && ft_strcmp(ft_data_name(\
		tab[i]), ".") && ft_strcmp(ft_data_name(tab[i]), ".."))
		{
			ft_putchar('\n');
			ft_putstr(tab[i]);
			ft_putstr(":\n");
			ft_disp_dir(tab[i], flags, nbr_dir);
		}
		i++;
	}
}

char			**ft_put_in_tab(char **tab, const char *path, char *name)
{
	int			i;

	i = 0;
	while (tab[i])
		i++;
	tab[i] = ft_newpath(tab[i], path, name);
	return (tab);
}

int				ft_disp_dir(const char *path, char *flags, int nbr_dir)
{
	DIR			*rep;
	t_dir		*file;
	char		**tab;

	if (!(rep = ft_opendir(path)))
		return (0);
	tab = ft_init_tab(ft_nbrfile(path, ft_a_or_f(flags)));
	if (nbr_dir > 1)
		ft_printf("%s:\n", path);
	if (ft_nbrfile(path, ft_a_or_f(flags)) == 0)
		ft_putstr("(empty directory)\n");
	else
	{
		while ((file = readdir(rep)))
		{
			if (file->d_name[0] == '.' && !ft_a_or_f(flags))
				continue;
			ft_put_in_tab(tab, path, file->d_name);
		}
		ft_print_sort(ft_sort_tab(tab, flags), flags, 0);
		if (strchr(flags, 'R'))
			ft_rec_disp(tab, flags, nbr_dir);
	}
	ft_free_tab(tab);
	return (ft_closedir(rep));
}
