/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_padding.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: heinfalt <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/12 13:13:48 by heinfalt          #+#    #+#             */
/*   Updated: 2017/10/12 13:13:51 by heinfalt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

static int	ft_padd_uid(char **tab)
{
	t_stat	stats;
	t_pwd	*usr;
	int		ret;
	int		i;

	i = 0;
	ret = 0;
	while (tab[i])
	{
		if (lstat(tab[i++], &stats) < 0)
			ft_perror("");
		if (!(usr = getpwuid(stats.st_uid)))
		{
			if (ret < ft_nbrlen((int)stats.st_uid))
				ret = ft_nbrlen((int)stats.st_uid);
		}
		else if (ret < (int)ft_strlen(usr->pw_name))
			ret = (int)ft_strlen(usr->pw_name);
	}
	return (ret);
}

static int	ft_padd_gid(char **tab)
{
	t_stat	stats;
	t_grp	*grp;
	int		ret;
	int		i;

	i = 0;
	ret = 0;
	while (tab[i])
	{
		if (lstat(tab[i++], &stats) < 0)
			ft_perror("");
		if (!(grp = getgrgid(stats.st_gid)))
		{
			if (ret < ft_nbrlen((int)stats.st_gid))
				ret = ft_nbrlen((int)stats.st_gid);
		}
		else if (ret < (int)ft_strlen(grp->gr_name))
			ret = (int)ft_strlen(grp->gr_name);
	}
	return (ret);
}

static int	ft_padd_size(char **tab)
{
	t_stat	stats;
	int		ret;
	int		i;

	i = 0;
	ret = 0;
	while (tab[i])
	{
		if (lstat(tab[i], &stats) < 0)
			ft_perror("");
		if (ft_is_bc(tab[i]))
		{
			if (ret < ft_len_min_max(tab[i]))
				ret = ft_len_min_max(tab[i]);
		}
		else if (ret < ft_llnbrlen(stats.st_size))
			ret = ft_llnbrlen(stats.st_size);
		i++;
	}
	return (ret);
}

int			ft_get_winsize(void)
{
	t_ws	win;

	if (ioctl(0, TIOCGWINSZ, &win) < 0)
		ft_perror("ioctl");
	return ((win.ws_col == 0 ? 1 : win.ws_col));
}

t_pad		ft_padding(char **tab)
{
	t_pad	padding;

	padding.n_uid = ft_padd_uid(tab);
	padding.n_gid = ft_padd_gid(tab);
	padding.b_size = ft_padd_size(tab);
	return (padding);
}
