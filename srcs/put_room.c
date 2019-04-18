/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   tmp.c                                            .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: loiberti <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/03/15 11:29:03 by loiberti     #+#   ##    ##    #+#       */
/*   Updated: 2019/04/18 10:54:40 by rgermain    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "lem_in.h"

static void	putnew_room(t_data *data, char **name, int x, int y)
{
	t_room	**tmp;

	tmp = &(data->room);
	while ((*tmp) && ft_strcmp((*tmp)->name, *name))
		tmp = &((*tmp)->next);
	if ((*tmp) && ft_strcmp((*tmp)->name, *name))
	{
		data->room_nb--;
		ft_dprintf(2, "/!\\double room\n\n");
		return ;
	}
	if (!((*tmp) = (t_room*)ft_memalloc(sizeof(t_room))))
	{
		ft_memdel((void**)name);
		display_error(data, 0);
	}
	(*tmp)->name = *name;
	(*tmp)->x = x;
	(*tmp)->y = y;
}

static void	put_infostartend(t_room *room, char **name, int x, int y)
{
	room->name = *name;
	room->x = x;
	room->y = y;
}

static void	put_room_startend(t_data *data, char *line, char index)
{
	char	*name;
	int		i;
	int		x;
	int		y;

	i = 0;
	while (line[i] && line[i] != ' ')
		i++;
	if (!(name = ft_strsub(line, 0, i)))
		display_error(data, 0);
	x = ft_atoi(line + ++i);
	while (line[i] && line[i] != ' ')
		i++;
	y = ft_atoi(line + i);
	if (index == 1)
		put_infostartend(&(data->start), &name, x, y);
	else if (index == 0)
		put_infostartend(&(data->end), &name, x, y);
}

void		put_room(t_data *data, char *line)
{
	int		i;
	char	*name;
	int		x;
	int		y;

	i = 0;
	if (!data->room_nb)
		lemin_info(data, "Put first room");
	data->b.room = TRUE;
	data->room_nb++;
	while (line[i] && line[i] != ' ')
		i++;
	if (!(name = ft_strsub(line, 0, i)))
		display_error(data, 0);
	x = ft_atoi(line + ++i);
	while (line[i] && line[i] != ' ')
		i++;
	y = ft_atoi(line + i);
	putnew_room(data, &name, x, y);
}

void		put_command(t_data *data, char **line)
{
	int	index;

	index = ft_strcmp(*line, "##start");
	put_line(data, line);
	if (get_next_line(data->info.fd, line) != 1 || !is_room(data, *line))
	{
		if (line)
			ft_memdel((void**)line);
		display_error(data, 1);
	}
	put_room_startend(data, *line, (index == 0 ? 1 : 0));
	if (index == 0)
		lemin_info(data, "Put Start");
	else
		lemin_info(data, "Put End");
	if (index == 0)
		data->b.start = TRUE;
	else
		data->b.end = TRUE;
}
