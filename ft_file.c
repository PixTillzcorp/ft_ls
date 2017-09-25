#include "ft_ls.h"

static int	ft_llnbrlen(long long nbr)
{
	int count;

	count = 1;
	while (nbr != 0)
	{
		nbr /= 10;
		if (nbr != 0)
			count++;
		else
			break;
	}
	return (count);
}

int			ft_print_single(const char *path, int large)
{
	s_stat	stats;
	s_pwd	*usr;
	s_grp	*grp;
	int		*tab;

	if (stat(path, &stats) < 0)
		ft_perror("");
	tab = (int *)ft_memalloc(sizeof(int) * 3);
	if (large)
	{
		usr = getpwuid(stats.st_uid);
		grp = getgrgid(stats.st_gid);
		tab[0] = (int)ft_strlen(usr->pw_name);
		tab[1] = (int)ft_strlen(grp->gr_name);
		tab[2] = ft_llnbrlen(stats.st_size);
		ft_print_large(path, tab);
	}
	printf("%s\n", path);
	free(tab);
	return (1);
}

int			ft_nbrfile(const char *path, int a)
{
	int		count;
	DIR		*rep;
	s_dir	*file;

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
		perror("");
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