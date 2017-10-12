/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_data_size.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: heinfalt <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/12 13:12:55 by heinfalt          #+#    #+#             */
/*   Updated: 2017/10/12 13:12:59 by heinfalt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

long		ft_file_size(const char *path)
{
	t_stat	stats;

	if (lstat(path, &stats) < 0)
		ft_perror(ft_strdup("ft_ls "));
	return ((long)stats.st_size);
}

int			ft_len_min_max(const char *path)
{
	int		ret;

	ret = 0;
	ret += ft_nbrlen(ft_data_minor(path));
	ret += ft_nbrlen(ft_data_major(path));
	ret += 4;
	return (ret);
}

int			ft_data_minor(const char *path)
{
	t_stat	stats;

	if (lstat(path, &stats) < 0)
		ft_perror(ft_strdup("ft_ls "));
	return (minor(stats.st_rdev));
}

int			ft_data_major(const char *path)
{
	t_stat	stats;

	if (lstat(path, &stats) < 0)
		ft_perror(ft_strdup("ft_ls "));
	return (major(stats.st_rdev));
}

char		*ft_data_size(const char *path, int len)
{
	t_stat	stats;
	char	*ret;
	char	*tmp;
	int		i;

	if (lstat(path, &stats) < 0)
		ft_perror(ft_strdup("ft_ls "));
	i = 0;
	ret = (char *)ft_memalloc(sizeof(char) * len + 1);
	tmp = ft_litoa((long long)stats.st_size);
	while (tmp[i] && i < len)
	{
		ret[i] = tmp[i];
		i++;
	}
	while (i < len)
		ret[i++] = ' ';
	ret[i] = '\0';
	free(tmp);
	return (ret);
}
