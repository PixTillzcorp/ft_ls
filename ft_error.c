/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_error.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: heinfalt <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/12 13:13:18 by heinfalt          #+#    #+#             */
/*   Updated: 2017/10/12 13:13:24 by heinfalt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void	ft_error(const char *msg, int usage)
{
	ft_putstr("ft_ls : ");
	ft_putstr(msg);
	ft_putchar('\n');
	if (msg)
		ft_memdel((void **)&msg);
	if (usage)
		printf("usage : ft_ls [-1GRSafglrt] [file ...]");
	exit(EXIT_FAILURE);
}

int		ft_check_input(const char *path, char *flags)
{
	DIR	*test;

	if ((test = opendir(path)))
		ft_closedir(test);
	else
	{
		if (ft_strchr(flags, 'd'))
			return (1);
		else if (errno == EACCES)
		{
			ft_putstr("ft_ls : ");
			perror(path);
			return (0);
		}
		else
		{
			ft_putstr("ft_ls : ");
			perror(path);
			return (0);
		}
	}
	return (1);
}

void	ft_perror(const char *msg)
{
	perror(msg);
	if (msg)
		ft_memdel((void **)&msg);
	exit(EXIT_FAILURE);
}
