/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   display_path.c                                   .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: loiberti <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/04/17 12:34:54 by loiberti     #+#   ##    ##    #+#       */
/*   Updated: 2019/04/24 19:04:12 by loiberti    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "lem_in.h"

static void	add_div_res(t_data *data, int *good_p, int count)
{
	int	i;
	int	div;
	int	res;

	i = -1;
	div = 0;
	res = 0;
	data->soluce.nb_soluce++;
	if ((data->soluce.nb_soluce + 1) > 0)
		div = (data->ants_nb - count) / (data->soluce.nb_soluce);
	if ((data->soluce.nb_soluce + 1) > 0)
		res = (data->ants_nb - count) % (data->soluce.nb_soluce);
	while (++i < data->soluce.nb_soluce)
	{
		good_p[i] += div;
		if (i < res)
			good_p[i] += 1;
		if (!good_p[i])
		{
			good_p[i] = -1;
			break ;
		}
	}
	data->soluce.nb_soluce = i;
	lemin_info(data, "Display path end");
}

void		nb_ants_by_path(t_data *data, int **good_p, int *cost_p)
{
	int		i;
	long	count;

	lemin_info(data, "Display path");
	if (!(*good_p = (int*)ft_memalloc(sizeof(int) *
					(data->soluce.nb_soluce + 1))))
		display_error(data, 0);
	count = data->ants_nb;
	count++;
	while (count > data->ants_nb && (i = -1))
	{
		count = 0;
		while (++i < data->soluce.nb_soluce && count <= data->ants_nb)
		{
			count += (cost_p[data->soluce.nb_soluce - 1] - cost_p[i]);
			(*good_p)[i] = (cost_p[data->soluce.nb_soluce - 1] - cost_p[i]);
		}
		data->soluce.nb_soluce--;
	}
	(*good_p)[i] = -1;
	add_div_res(data, *good_p, count);
}
