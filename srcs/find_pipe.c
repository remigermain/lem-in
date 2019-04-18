/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   find_pipe.c                                      .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: rgermain <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/03/18 11:20:30 by rgermain     #+#   ##    ##    #+#       */
/*   Updated: 2019/03/29 00:59:41 by rgermain    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "lem_in.h"

static t_bool	create_staticroom(t_data *data)
{
	t_room	**lst;
	size_t	i;

	lst = &(data->room);
	i = 0;
	if (!(data->room2 = (t_room**)ft_memalloc(sizeof(t_room*) *
					(data->room_nb + 1))))
		return (FALSE);
	while ((*lst))
	{
		if (!(data->room2[i] = (t_room*)ft_memalloc(sizeof(t_room))))
			return (FALSE);
		(data->room2[i]->name) = (*lst)->name;
		data->room2[i]->x = (*lst)->x;
		data->room2[i]->y = (*lst)->y;
		lst = &((*lst)->next);
		i++;
	}
	data->room2[i] = NULL;
	lemin_info(data, "Create static room");
	return (TRUE);
}

static void		find_nopipe_endstart(t_data *data, char **line, int j)
{
	if (data->start.name && !ft_strncmp((*line), data->start.name, j))
		data->matrix.pipe1 = 0;
	else if (data->end.name && !ft_strncmp((*line), data->end.name, j))
		data->matrix.pipe1 = 1;
	if (data->start.name && !ft_strcmp((*line) + j + 1, data->start.name))
		data->matrix.pipe2 = 0;
	else if (data->end.name && !ft_strcmp((*line) + j + 1, data->end.name))
		data->matrix.pipe2 = 1;
}

t_bool			find_nopipe(t_data *data, char **line, int j)
{
	size_t	i;

	i = 0;
	data->matrix.pipe1 = -1;
	data->matrix.pipe2 = -1;
	if (!data->room2 && !create_staticroom(data))
	{
		ft_memdel((void**)line);
		display_error(data, 0);
	}
	find_nopipe_endstart(data, line, j);
	while (data->room2[i] && (data->matrix.pipe1 == -1 ||
				data->matrix.pipe2 == -1))
	{
		if (data->matrix.pipe1 == -1 &&
				!ft_strncmp((*line), data->room2[i]->name, j))
			data->matrix.pipe1 = i + 2;
		if (data->matrix.pipe2 == -1 &&
				!ft_strcmp((*line) + j + 1, data->room2[i]->name))
			data->matrix.pipe2 = i + 2;
		i++;
	}
	if (data->matrix.pipe1 != -1 && data->matrix.pipe2 != -1)
		return (TRUE);
	return (FALSE);
}
