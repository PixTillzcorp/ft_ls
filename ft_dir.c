#include "ft_ls.h"

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

char		*ft_newpath(char *dest, const char *p, const char* d)
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

static void	ft_rec_disp(const char *path, char *flags)
{
	DIR		*rep;
	s_dir	*file;
	char	*n_path;

	n_path = NULL;
	rep = ft_opendir(path);
	printf("\n");
	while ((file = readdir(rep)))
	{
		if (n_path)
			ft_memdel((void **)&n_path);
		if (file->d_name[0] == '.' && !ft_strchr(flags, 'a'))
			continue;
		n_path = ft_newpath(n_path, path, file->d_name);
		if (ft_isdir(n_path) && ft_strcmp(file->d_name, ".")\
		&& ft_strcmp(file->d_name, ".."))
			ft_disp_dir(n_path, flags);
	}
	ft_closedir(rep);
	if (n_path)
		ft_memdel((void **)&n_path);
}

void		ft_disp_dir(const char *path, char *flags)
{
	DIR		*rep;
	s_dir	*file;
	char	**tab;

	rep = ft_opendir(path);
	tab = ft_init_tab(ft_nbrfile(path, (int)(ft_strchr(flags, 'a'))));
	if (ft_strcmp(path, "."))
		printf("%s:\n", path);
	if (ft_nbrfile(path, (int)(ft_strchr(flags, 'a'))) == 0)
		printf("(empty directory)\n\n");
	else
	{
		while ((file = readdir(rep)))
		{
			if (file->d_name[0] == '.' && !ft_strchr(flags, 'a'))
				continue;
			ft_put_in_tab(tab, path, file->d_name);
		}
		ft_print_sort(ft_sort_tab(tab, flags), flags);
		if (strchr(flags, 'R'))
			ft_rec_disp(path, flags);
	}
	ft_free_tab(tab);
	ft_closedir(rep);
}
