/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   main.c                                           .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: loiberti <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/03/26 19:20:05 by loiberti     #+#   ##    ##    #+#       */
/*   Updated: 2019/04/18 19:25:53 by loiberti    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "lem_in.h"

void		zero_astar(t_data *data, t_algostar *st, t_algo *al)
{
	st->o_startlen = 0;
	st->o_endlen = 0;
	st->c_startlen = 0;
	st->c_endlen = 0;
	al->i = 0;
	al->l = 0;
	data->matrix.end_len = 0;
	ft_bzero(st->hs, sizeof(int) * (data->room_nb + 2));
	ft_bzero(st->olst, sizeof(int) * (data->pipe_nb));
	ft_bzero(st->clst, sizeof(int) * (data->room_nb));
	ft_bzero(st->cost, sizeof(int) * (data->room_nb + 2));
	ft_bzero(al->file, sizeof(int) * (data->pipe_nb));
	ft_bzero(al->nb_file, sizeof(int) * (data->pipe_nb));
}

int			count_connetion(t_data *data)
{
	int i;
	int start;
	int	end;

	i = 0;
	start = 0;
	end = 0;
	while (i < (data->room_nb + 2))
	{
		if (!test_bit(&(data->matrix.tab[i][0]), 0))
			start++;
		if (!test_bit(&(data->matrix.tab[i][0]), 1))
			end++;
		i++;
	}
	return (MIN(end, start));
}

static void	alloc_star(t_data *data, t_algostar *st, t_algo *al)
{
	ft_bzero(st, sizeof(t_algostar));
	ft_bzero(al, sizeof(t_algo));
	lemin_info(data, "alloc algo A *");
	if (!(st->hs = (int*)ft_memalloc(sizeof(int) * (data->room_nb + 2))) ||
		!(st->olst = (int*)ft_memalloc(sizeof(int) * (data->pipe_nb))) ||
		!(st->clst = (int*)ft_memalloc(sizeof(int) * (data->room_nb))) ||
		!(st->cost = (int*)ft_memalloc(sizeof(int) * (data->room_nb + 2))) ||
		!(al->file = (int*)ft_memalloc(sizeof(int) * (data->pipe_nb))) ||
		!(al->nb_file = (int*)ft_memalloc(sizeof(int) * (data->pipe_nb))))
	{
		if (st->hs)
			ft_memdel((void**)&(st->hs));
		if (st->olst)
			ft_memdel((void**)&(st->olst));
		if (st->clst)
			ft_memdel((void**)&(st->clst));
		if (st->cost)
			ft_memdel((void**)&(st->cost));
		if (al->file)
			ft_memdel((void**)&(al->file));
		display_error(data, 0);
	}
}

void		algo(t_data *data)
{
	int			max;
	int			i;
	t_algostar	st;
	t_algo		al;

	if (!(max = count_connetion(data)))
		display_error(data, 1);
	i = 0;
	alloc_star(data, &st, &al);
	if (!(data->soluce.tab = (int**)malloc(sizeof(int*) * (max + 1))) ||
			!(data->soluce.path_cost = (int*)malloc(sizeof(int) * (max + 1))))
		display_error(data, 0);
	while (i++ < max && algo_astar(data, &st, &al))
		zero_astar(data, &st, &al);
	data->soluce.path_cost[data->soluce.nb_soluce] = -1;
}
