/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_file.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: heinfalt <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/12 13:13:25 by heinfalt          #+#    #+#             */
/*   Updated: 2017/10/12 13:13:29 by heinfalt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

int			ft_llnbrlen(long long nbr)
{
	int		count;

	count = 1;
	while (nbr != 0)
	{
		nbr /= 10;
		if (nbr != 0)
			count++;
		else
			break ;
	}
	return (count);
}

int			ft_nbrdir(const char **input, int argc)
{
	int		count;
	int		i;

	i = 0;
	count = 0;
	while (i < argc)
	{
		if (ft_isdir(input[i++]))
			count++;
	}
	return (count);
}

int			ft_nbrfile(const char *path, int a)
{
	int		count;
	DIR		*rep;
	t_dir	*file;

	count = 0;
	if (!(rep = opendir(path)))
		exit(-1);
	while ((file = readdir(rep)))
	{
		if (file->d_name[0] == '.' && !a)
			continue;
		count++;
	}
	if (closedir(rep) < 0)
		exit(-1);
	return (count);
}

DIR			*ft_opendir(const char *path)
{
	DIR		*ret;

	if (!(ret = opendir(path)))
	{
		if (errno == ENOTDIR)
			return (NULL);
		perror(path);
		exit(-1);
	}
	return (ret);
}

int			ft_closedir(DIR *op_dir)
{
	if (closedir(op_dir) < 0)
	{
		perror("");
		exit(-1);
	}
	return (0);
}
