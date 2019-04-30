/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   lem_infree.c                                     .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: rgermain <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/03/15 18:19:53 by rgermain     #+#   ##    ##    #+#       */
/*   Updated: 2019/04/23 10:34:06 by rgermain    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "lem_in.h"

static void	free_line(t_line **line)
{
	if ((*line))
	{
		free_line(&((*line)->next));
		ft_memdel((void**)&((*line)->line));
		ft_memdel((void**)line);
	}
}

static void	free_room(t_room **room)
{
	if (*room)
	{
		free_room(&((*room)->next));
		ft_memdel((void**)&((*room)->name));
		ft_memdel((void**)room);
	}
}

static void	free_room2(t_room **room)
{
	size_t	i;

	i = -1;
	while (room && room[++i])
		ft_memdel((void**)&(room[i]));
	ft_memdel((void**)&room);
}

void		lemin_free(t_data *data)
{
	int	i;

	i = -1;
	lemin_info(data, "free all alocation");
	free_line(&(data->file));
	free_room(&(data->room));
	free_room2(data->room2);
	ft_memdeltab_char(&(data->matrix.tab));
	ft_memdel((void**)&(data->matrix.tab));
	ft_memdel((void**)&(data->start.name));
	ft_memdel((void**)&(data->end.name));
	ft_memdeltab_int(&(data->soluce.tab), tabintlen(data->soluce.path_cost));
	ft_memdel((void**)&(data->soluce.path_cost));
	ft_memdel((void**)&(data->soluce.good_path));
}
