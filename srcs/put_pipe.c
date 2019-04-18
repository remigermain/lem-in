/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   put_pipe.c                                       .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: rgermain <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/03/18 12:05:08 by rgermain     #+#   ##    ##    #+#       */
/*   Updated: 2019/03/29 01:00:33 by rgermain    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "lem_in.h"

int				to_malloc(int nb)
{
	if (!(nb % 8))
		return (nb / 8);
	else
		return ((nb / 8) + 1);
}

static t_bool	create_matrix(t_data *data)
{
	int	i;
	int	len;

	i = 0;
	len = to_malloc(data->room_nb + 2);
	if (!(data->matrix.tab = (char**)ft_memalloc(sizeof(char*) *
					(data->room_nb + 2))))
		return (FALSE);
	while (i < (data->room_nb + 2))
	{
		if (!(data->matrix.tab[i] = (char*)ft_memalloc(len)))
			return (FALSE);
		i++;
	}
	lemin_info(data, "Create matrix");
	return (TRUE);
}

void			put_pipe(t_data *data, char **line)
{
	data->b.pipe = TRUE;
	data->pipe_nb++;
	if (!data->matrix.tab && !create_matrix(data))
	{
		ft_memdel((void**)line);
		display_error(data, 0);
	}
	data->matrix.tab[data->matrix.pipe1][data->matrix.pipe2 / 8] |=
		(1 << (data->matrix.pipe2 % 8));
	if (test_bit(&(data->info.flags), 3) ||
			test_bit(&(data->matrix.oriented), 1))
		data->matrix.tab[data->matrix.pipe2][data->matrix.pipe1 / 8] |=
		(1 << (data->matrix.pipe1 % 8));
	if (!test_bit(&(data->matrix.oriented), 1))
		clear_bit(&(data->matrix.oriented), 1);
}
