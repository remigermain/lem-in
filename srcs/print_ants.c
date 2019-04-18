/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   print_ants.c                                     .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: rgermain <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/04/17 16:27:39 by rgermain     #+#   ##    ##    #+#       */
/*   Updated: 2019/04/18 19:33:55 by rgermain    ###    #+. /#+    ###.fr     */
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
	if (data->soluce.nb_soluce == 0)
		data->soluce.nb_soluce++;
	if (!(tab = (int**)ft_memalloc(sizeof(int*) * data->soluce.nb_soluce)))
		display_error(data, 0);
	while (++i < data->soluce.nb_soluce)
	{
		j = 0;
		if (!(tab[i] = (int*)malloc(sizeof(int) * (
							data->soluce.path_cost[i] + 1))))
			display_error(data, 0);
		while (j < (data->soluce.path_cost[i] + 1))
			tab[i][j++] = -2;
		tab[i][j] = -1;
	}
	return (tab);
}

static int	print_ants2(t_data *data, int **tab)
{
	int	i;
	int	j;
	int	saved;

	i = -1;
	saved = 0;
	while (++i < data->soluce.nb_soluce)
	{
		j = -1;
		while (++j <= data->soluce.path_cost[i])
		{
			if (tab[i][j] >= 0)
			{
				if (j == 0)
					saved++;
				if (test_bit(&(data->info.flags), 2))
					ft_printf("L%d-%s", tab[i][j],
							find_name(data, data->soluce.tab[i][j]));
				if (test_bit(&(data->info.flags), 2) && i < data->ants_nb)
					ft_printf(" ");
			}
		}
	}
	return (saved);
}

void		print_ants(t_data *data)
{
	int	**tab;
	int	name;
	int	saved;

	name = 1;
	saved = 0;
	tab = alloc_ants(data);
	while (saved < data->ants_nb)
	{
		add_ants(data, tab, &name);
		saved += print_ants2(data, tab);
		if ((data->info.line++) && test_bit(&(data->info.flags), 2))
			ft_printf("\n");
		move_ants(data, tab);
	}
	if (!test_bit(&(data->info.flags), 2))
	{
		lemin_info(data, "Print line");
		ft_printf("%s[  %d   ]%s\n", T_BLUE, data->info.line, T_WHITE);
		if (data->info.line <= data->info.line_nb)
			ft_printf("\n%s GOOD%s\n", T_GREEN, T_WHITE);
		else
			ft_printf("\n%s FUCK%s\n", T_RED, T_WHITE);
	}
	lemin_info(data, "Print ants end");
}
