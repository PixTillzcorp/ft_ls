#include "ft_ls.h"

static char		*ft_newpath(char *dest, const char *p, const char* d)
{
	int		i;
	int		j;

	i = 0;
	j = 0;
	dest = (char *)malloc(sizeof(char) * (ft_strlen(p) + ft_strlen(d) + 2));
	while (p[i])
		dest[j++] = p[i++];
	dest[j++] = '/';
	i = 0;
	while (d[i])
		dest[j++] = d[i++];
	dest[j] = '\0';
	return (dest);
}

static void	ft_rec_disp(const char *path, char *flags, int nbr_dir)
{
	DIR		*rep;
	s_dir	*file;
	char	*n_path;

	n_path = NULL;
	rep = ft_opendir(path);
	while ((file = readdir(rep)))
	{
		if (n_path)
			ft_memdel((void **)&n_path);
		if (file->d_name[0] == '.' && !ft_strchr(flags, 'a'))
			continue ;
		n_path = ft_newpath(n_path, path, file->d_name);
		if (ft_isdir(n_path) && ft_strcmp(file->d_name, ".") &&\
		ft_strcmp(file->d_name, "..") && !ft_is_l(n_path)) //mod
		{
			ft_putchar('\n');
			ft_disp_dir(n_path, flags, nbr_dir);
		}
	}
	ft_closedir(rep);
	if (n_path)
		ft_memdel((void **)&n_path);
}

char		**ft_put_in_tab(char **tab, const char *path, char *name)
{
	int		i;
	i = 0;
	while (tab[i])
		i++;
	tab[i] = ft_newpath(tab[i], path, name);
	return (tab);
}

int			ft_disp_dir(const char *path, char *flags, int nbr_dir)
{
	DIR		*rep;
	s_dir	*file;
	char	**tab;

	if (!(rep = ft_opendir(path)))
		return (0);
	tab = ft_init_tab(ft_nbrfile(path, (int)(ft_strchr(flags, 'a'))));
	if (ft_strcmp(path, ".") && nbr_dir > 1)
		ft_printf("%s:\n", path);
	if (ft_nbrfile(path, (int)(ft_strchr(flags, 'a'))) == 0)
		ft_putstr("(empty directory)\n\n");
	else
	{
		while ((file = readdir(rep)))
		{
			if (file->d_name[0] == '.' && !ft_strchr(flags, 'a'))
				continue;
			ft_put_in_tab(tab, path, file->d_name);
		}
		ft_print_sort(ft_sort_tab(tab, flags), flags, 0);
		if (strchr(flags, 'R'))
			ft_rec_disp(path, flags, nbr_dir);
	}
	ft_free_tab(tab);
	return(ft_closedir(rep));
}
