#include "ft_ls.h"

static void	ft_swap_chr(char **a, char **b)
{
	char	*swap;

	swap = *a;
	*a = *b;
	*b = swap;
}

static char	**ft_rev_sort(char **tab)
{
	int		i;
	int		j;

	i = 0;
	j = 0;
	while (tab[j + 1])
		j++;
	while (i < j)
		ft_swap_chr(&tab[i++], &tab[j--]);
	return (tab);
}

static char	**ft_sort_time(char **tab)
{
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
			if (comp > ft_data_mtime(tab[j]))
			{
				comp = ft_data_mtime(tab[j]);
				ft_swap_chr(&tab[i], &tab[j]);
			}
			j++;
		}
		i++;
	}
	return (tab);
}

char		**ft_sort_tab(char **tab, char *flags)
{
	if (ft_strchr(flags, 't'))
		tab = ft_sort_time(tab);
	if (ft_strchr(flags, 'r'))
		tab = ft_rev_sort(tab);
	return (tab);
}
