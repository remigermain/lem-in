/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   algo_astart.c                                    .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: rgermain <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/04/01 15:43:07 by rgermain     #+#   ##    ##    #+#       */
/*   Updated: 2019/04/23 14:26:37 by rgermain    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "lem_in.h"

static t_bool	find_path(t_data *data, t_algo *al)
{
	al->nb_file[al->l++] = -1;
	lemin_info(data, "fin algo A *");
	put_soluceastar(data, al);
	return (TRUE);
}

static t_bool	find_occur(int *node, int start, int end, int occur)
{
	int i;

	i = start - 1;
	while (++i <= end)
		if (node[i] == occur)
			return (TRUE);
	return (FALSE);
}

static t_bool	exist_neighbor(t_algostar *st, int room, int voisin)
{
	if ((find_occur(st->olst, st->o_startlen, st->o_endlen, voisin) &&
			st->hs[room] > st->hs[voisin]) ||
			(find_occur(st->clst, st->c_startlen, st->c_endlen, voisin) &&
			st->hs[room] > st->hs[voisin]))
	{
		return (TRUE);
	}
	return (FALSE);
}

static int		neighbor_pop(t_data *data, int room, int *i, t_algostar *st)
{
	int	voisin;

	voisin = -1;
	while ((*i) < (data->room_nb + 2))
	{
		if (!test_bit(&(data->matrix.tab[room][(*i) / 8]), (*i) % 8))
		{
			voisin = ((*i));
			break ;
		}
		(*i)++;
	}
	if (voisin == -1)
		return (-1);
	if (!exist_neighbor(st, room, voisin) || voisin == ROOM_END)
	{
		st->cost[voisin] = st->cost[room] + 1;
		st->hs[voisin] += st->cost[voisin] + st->cost[ROOM_END];
		st->olst[st->o_endlen++] = voisin;
		if (st->o_endlen >= st->alloc)
			realloc_olst(data, st);
		return (1);
	}
	return (-1);
}

int				algo_astar(t_data *data, t_algostar *st, t_algo *al)
{
	int	room;
	int	i;

	lemin_info(data, "debut algo A *");
	st->olst[st->o_endlen++] = ROOM_START;
	while (st->o_endlen > st->c_endlen && (i = -1) != 0)
	{
		room = st->olst[st->o_startlen];
		al->file[data->matrix.end_len++] = room;
		if (room == ROOM_END)
			return (find_path(data, al));
		while (++i < (data->room_nb + 2))
			if (neighbor_pop(data, room, &i, st) == 1)
				al->nb_file[al->l]++;
		al->l++;
		st->clst[st->c_endlen++] = room;
		st->o_startlen++;
	}
	lemin_info(data, "fin algo A * [no_soluce]");
	return (FALSE);
}
