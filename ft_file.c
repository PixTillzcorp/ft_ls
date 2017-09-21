#include "ft_ls.h"

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