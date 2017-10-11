#include "ft_ls.h"

void		ft_insert(char **tab, char *str)
{
	int		i;

	i = 0;
	while (tab[i])
		i++;
	tab[i] = ft_strdup(str);
}

char		**ft_init_tab(int size)
{
	char	**ret;
	int		i;

	i = 0;
	if (!(ret = (char **)ft_memalloc(sizeof(char *) * (size + 1))))
	{
		perror("");
		exit(-1);
	}
	while (i < size)
		ret[i++] = NULL;
	ret[i] = NULL;
	return (ret);
}

void		ft_free_tab(char **tab)
{
	int		i;

	i = 0;
	if (tab[i])
	{
		while(tab[i])
			ft_memdel((void **)&tab[i++]);
		ft_memdel((void **)&tab[i]);
		free(tab);
		tab = NULL;
	}
}
