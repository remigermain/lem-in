/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   tools.c                                          .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: loiberti <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/03/14 14:36:08 by loiberti     #+#   ##    ##    #+#       */
/*   Updated: 2019/04/18 19:52:54 by rgermain    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "lem_in.h"

t_bool	create_visited(t_data *data)
{
	if (!(data->matrix.visited = (char*)ft_memalloc(
					to_malloc(data->room_nb + 2))))
		return (FALSE);
	lemin_info(data, "Create visited");
	data->matrix.end_len = 0;
	return (TRUE);
}

int		ft_atol(char *line)
{
	size_t	i;
	long	nb;

	i = 0;
	nb = 0;
	while (line[i] == ' ' || (line[i] >= 9 && line[i] <= 13))
		i++;
	while (line[i] >= '0' && line[i] <= '9' && nb <= 2147483648)
		nb = ((nb * 10) + (line[i++] - '0'));
	if (nb > 2147483647)
		return (-1);
	return (nb);
}

char	*find_name(t_data *data, int nb)
{
	if (nb == 1 || nb == 0)
		return (!nb ? data->start.name : data->end.name);
	nb -= 2;
	if (nb < data->room_nb)
		return (data->room2[nb]->name);
	return ("null");
}

int		tabintlen(int *tab)
{
	int	i;

	i = -1;
	if (tab)
	{
		while (tab[++i] != -1)
			;
		return (i);
	}
	return (0);
}
