/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_data_type.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: heinfalt <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/12 13:13:06 by heinfalt          #+#    #+#             */
/*   Updated: 2017/10/12 13:13:10 by heinfalt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

char		ft_data_type(mode_t type)
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

int			ft_is_bc(const char *path)
{
	t_stat	stats;

	if (lstat(path, &stats) < 0)
		ft_perror("");
	if (ft_data_type(stats.st_mode & S_IFMT) == 'b')
		return (1);
	if (ft_data_type(stats.st_mode & S_IFMT) == 'c')
		return (1);
	return (0);
}

int			ft_is_l(const char *path)
{
	t_stat	stats;

	if (lstat(path, &stats) < 0)
		ft_perror("");
	if (ft_data_type(stats.st_mode & S_IFMT) == 'l')
		return (1);
	return (0);
}

int			ft_isdir(const char *path)
{
	DIR		*is_dir;

	if ((is_dir = opendir(path)))
	{
		closedir(is_dir);
		return (1);
	}
	return (0);
}
