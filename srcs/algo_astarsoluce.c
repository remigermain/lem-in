/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   algo_putsoluceastar.c                            .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: rgermain <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/04/01 17:51:03 by rgermain     #+#   ##    ##    #+#       */
/*   Updated: 2019/04/23 15:15:42 by rgermain    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "lem_in.h"

static void	remove_node2(t_data *data, int room)
{
	int i;

	i = -1;
	if (room < 2)
		return ;
	while (++i < (data->room_nb + 2))
	{
		if (!test_bit(&(data->matrix.tab[room][i / 8]), i % 8))
			clear_bit(&(data->matrix.tab[room][i / 8]), i % 8);
		if (!test_bit(&(data->matrix.tab[i][room / 8]), room % 8))
			clear_bit(&(data->matrix.tab[i][room / 8]), room % 8);
	}
}

static void	remove_node(t_data *data)
{
	int i;
	int j;

	i = 0;
	while (data->soluce.tab && i < data->soluce.nb_soluce)
	{
		j = 1;
		while (data->soluce.tab[i][j] != -1)
			remove_node2(data, data->soluce.tab[i][j++]);
		i++;
	}
	data->matrix.end_len = 0;
}

static int	len_path(t_algo *al)
{
	t_soluce st;

	ft_bzero(&st, sizeof(t_soluce));
	while (st.pos < al->l && al->nb_file[st.pos] != -1)
		st.pos++;
	st.l++;
	while (st.pos > 0)
	{
		st.i = 0;
		st.j = 0;
		while ((st.j + al->nb_file[st.i]) < st.pos)
			st.j += al->nb_file[st.i++];
		st.pos = st.i;
		st.l++;
	}
	return (st.l);
}

static void	alloc_path(t_data *data, t_soluce *st, t_algo *al)
{
	ft_bzero(st, sizeof(t_soluce));
	if (!(st->path = (int*)ft_memalloc(sizeof(int) *
					(len_path(al) + 1))))
	{
		ft_memdel((void**)&(al->file));
		ft_memdel((void**)&(al->nb_file));
		display_error(data, 0);
	}
}

void		put_soluceastar(t_data *data, t_algo *al)
{
	t_soluce st;

	lemin_info(data, "start put_soluce A *");
	alloc_path(data, &st, al);
	while (st.pos < al->l && al->nb_file[st.pos] != -1)
		st.pos++;
	st.path[st.l++] = ROOM_END;
	al->file[st.pos] = 0;
	al->nb_file[st.pos] = 0;
	while (st.pos > 0)
	{
		st.i = 0;
		st.j = 0;
		while ((st.j + al->nb_file[st.i]) < st.pos)
			st.j += al->nb_file[st.i++];
		st.pos = st.i;
		st.path[st.l++] = al->file[st.pos];
	}
	st.path[st.l] = -1;
	data->soluce.path_cost[data->soluce.nb_soluce] = st.l - 2;
	data->soluce.tab[data->soluce.nb_soluce++] = st.path;
	remove_node(data);
	lemin_info(data, "End put_soluce A *");
}
