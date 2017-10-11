#include "ft_ls.h"

static void	ft_sort_size(char **tab)
{
	long	size_f;
	long	comp;
	int		i;
	int		j;

	i = 0;
	while (tab[i])
	{
		j = i;
		comp = ft_file_size(tab[i]);
		while (tab[j])
		{
			if (comp < (size_f = ft_file_size(tab[j])))
			{
				comp = size_f;
				ft_swap_chr(&tab[i], &tab[j]);
			}
			j++;
		}
		i++;
	}
}

static void	ft_rev_sort(char **tab)
{
	int		i;
	int		j;

	i = 0;
	j = 0;
	while (tab[j + 1])
		j++;
	while (i < j)
		ft_swap_chr(&tab[i++], &tab[j--]);
}

static void	ft_sort_abc(char **tab)
{
	char	*name_1;
	char	*name_2;
	int		i;
	int		j;

	i = 0;
	while (tab[i])
	{
		j = i;
		name_1 = ft_data_name(tab[i]);
		while (tab[j])
		{
			name_2 = ft_data_name(tab[j]);
			if (0 < ft_strcmp(name_1, name_2))
			{
				name_1 = name_2;
				ft_swap_chr(&tab[i], &tab[j]);
			}
			j++;
		}
		i++;
	}
}

static void	ft_sort_time(char **tab)
{
	long	time_f;
	long	comp;
	int		i;
	int		j;

	i = 0;
	while (tab[i])
	{
		j = i;
		comp = ft_data_mtime(tab[i]);
		while (tab[j])
		{
			if (comp < (time_f = ft_data_mtime(tab[j])))
			{
				comp = time_f;
				ft_swap_chr(&tab[i], &tab[j]);
			}
			j++;
		}
		i++;
	}
}

char		**ft_sort_tab(char **tab, char *flags)
{
	ft_sort_abc(tab);
	if (ft_strchr(flags, 'S'))
		ft_sort_size(tab);
	if (ft_strchr(flags, 't'))
		ft_sort_time(tab);
	if (ft_strchr(flags, 'r'))
		ft_rev_sort(tab);
	return (tab);
}
