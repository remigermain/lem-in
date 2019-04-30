/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   print_ants.c                                     .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: rgermain <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/04/17 16:27:39 by rgermain     #+#   ##    ##    #+#       */
/*   Updated: 2019/04/25 11:34:00 by loiberti    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "lem_in.h"

static void	add_ants(t_data *data, int **tab, int *name)
{
	int i;

	i = -1;
	while (++i < data->soluce.nb_soluce)
	{
		if (data->soluce.good_path[i] > 0)
		{
			tab[i][data->soluce.path_cost[i]] = (*name)++;
			data->soluce.good_path[i]--;
		}
		else
			tab[i][data->soluce.path_cost[i]] = -2;
	}
}

static void	move_ants(t_data *data, int **tab)
{
	int i;
	int	j;

	i = -1;
	while (++i < data->soluce.nb_soluce)
	{
		j = 0;
		while (++j <= data->soluce.path_cost[i])
			tab[i][j - 1] = tab[i][j];
	}
}

static int	**alloc_ants(t_data *data)
{
	int	**tab;
	int i;
	int	j;

	i = -1;
	lemin_info(data, "Print ants start");
	if (!(tab = (int**)ft_memalloc(sizeof(int*) * data->soluce.nb_soluce)))
		display_error(data, 0);
	while (++i < data->soluce.nb_soluce)
	{
		j = 0;
		if (!(tab[i] = (int*)ft_memalloc(sizeof(int) * (
							data->soluce.path_cost[i] + 2))))
		{
			ft_memdeltab_int(&tab, i);
			display_error(data, 0);
		}
		while (j < (data->soluce.path_cost[i] + 1))
			tab[i][j++] = -2;
		tab[i][j] = -1;
	}
	return (tab);
}

static int	print_ants2(t_data *data, int **tab, int *name, int *saved)
{
	int	i;
	int	j;

	i = -1;
	add_ants(data, tab, name);
	while (++i < data->soluce.nb_soluce)
	{
		j = -1;
		while (++j <= data->soluce.path_cost[i])
		{
			if (tab[i][j] >= 0)
			{
				if (j == 0)
					(*saved)++;
				if (test_bit(&(data->info.flags), 2))
					ft_printf("L%d-%s", tab[i][j],
							find_name(data, data->soluce.tab[i][j]));
				if (test_bit(&(data->info.flags), 2) && i < data->ants_nb)
					ft_printf(" ");
			}
		}
	}
	move_ants(data, tab);
	return (1);
}

void		print_ants(t_data *data)
{
	int	**tab;
	int	name;
	int	saved;

	name = 1;
	saved = 0;
	tab = alloc_ants(data);
	while (saved < data->ants_nb && print_ants2(data, tab, &name, &saved))
		if ((++data->info.line_print) && test_bit(&(data->info.flags), 2))
			ft_printf("\n");
	if (!test_bit(&(data->info.flags), 2))
	{
		lemin_info(data, "Print line");
		ft_printf("%s[  %4d   ]%s\n", T_BLUE, data->info.line_print, T_WHITE);
		ft_printf("%s[  %4d   ]%s\n", T_PURPLE, data->info.line_print -
											data->info.line_indice, T_WHITE);
		if (data->info.line_print <= data->info.line_indice)
			ft_printf("\n%s GOOD%s\n", T_GREEN, T_WHITE);
		else
			ft_printf("\n%s NOT GOOD%s\n", T_RED, T_WHITE);
	}
	ft_memdeltab_int(&tab, data->soluce.nb_soluce);
	lemin_info(data, "Print ants end");
}
