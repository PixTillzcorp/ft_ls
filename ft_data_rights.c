/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_data_rights.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: heinfalt <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/12 13:12:31 by heinfalt          #+#    #+#             */
/*   Updated: 2017/10/12 13:12:54 by heinfalt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

static char	*ft_get_rights(mode_t rights)
{
	char	*ret;

	ret = ft_chrjoin_free("", (rights & S_IRUSR ? 'r' : '-'), 0);
	ret = ft_chrjoin_free(ret, (rights & S_IWUSR ? 'w' : '-'), 1);
	if (rights & S_ISUID)
		ret = ft_chrjoin_free(ret, (rights & S_IXUSR ? 's' : 'S'), 1);
	else
		ret = ft_chrjoin_free(ret, (rights & S_IXUSR ? 'x' : '-'), 1);
	ret = ft_chrjoin_free(ret, (rights & S_IRGRP ? 'r' : '-'), 1);
	ret = ft_chrjoin_free(ret, (rights & S_IWGRP ? 'w' : '-'), 1);
	if (rights & S_ISGID)
		ret = ft_chrjoin_free(ret, (rights & S_IXGRP ? 's' : 'S'), 1);
	else
		ret = ft_chrjoin_free(ret, (rights & S_IXGRP ? 'x' : '-'), 1);
	ret = ft_chrjoin_free(ret, (rights & S_IROTH ? 'r' : '-'), 1);
	ret = ft_chrjoin_free(ret, (rights & S_IWOTH ? 'w' : '-'), 1);
	if (rights & S_ISVTX)
		ret = ft_chrjoin_free(ret, (rights & S_IXOTH ? 't' : 'T'), 1);
	else
		ret = ft_chrjoin_free(ret, (rights & S_IXOTH ? 'x' : '-'), 1);
	return (ret);
}

char		*ft_data_wrx(const char *path)
{
	t_stat	stats;
	mode_t	rights;
	char	*buff;
	char	*tmp;

	buff = (char *)ft_memalloc(sizeof(char) * 100);
	buff[99] = '\0';
	if (lstat(path, &stats) < 0)
		ft_perror(ft_strdup("ft_ls "));
	rights = stats.st_mode;
	if (readlink(path, buff, 100) < 0)
		tmp = ft_chrjoin_free(ft_strdup(""), ft_data_type(rights & S_IFMT), 1);
	else
		tmp = ft_chrjoin_free(ft_strdup(""), 'l', 1);
	tmp = ft_strjoin_free(tmp, ft_get_rights(rights), 'b');
	free(buff);
	return (tmp);
}
