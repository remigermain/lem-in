/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   tools.c                                          .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: loiberti <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/03/14 14:36:08 by loiberti     #+#   ##    ##    #+#       */
/*   Updated: 2019/04/23 13:18:41 by loiberti    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "lem_in.h"

int		ft_atol(char *line)
{
	size_t	i;
	size_t	n;
	long	nb;

	i = 0;
	nb = 0;
	n = 0;
	while (line[i] == ' ' || (line[i] >= 9 && line[i] <= 13))
		i++;
	if (line[i] == '-' && (n = 1))
		i++;
	while (line[i] >= '0' && line[i] <= '9' && nb <= 2147483648)
		nb = ((nb * 10) + (line[i++] - '0'));
	if (n)
		nb = -nb;
	if (nb > INT_MAX || nb < INT_MIN)
		return (FALSE);
	return (TRUE);
}

void	realloc_olst(t_data *data, t_algostar *st)
{
	int	*new;

	if (!(new = (int*)ft_memalloc(sizeof(int) * (st->alloc + 1))))
		display_error(data, 0);
	ft_memcpy(new, st->olst, sizeof(int) * st->alloc++);
	ft_memdel((void**)&st->olst);
	st->olst = new;
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

void	display_error(t_data *data, char index)
{
	lemin_info(data, "Error");
	lemin_free(data);
	if (index == 0)
		ft_printf("%1.@", "error", "lem_in");
	else
		ft_dprintf(2, "ERROR\n");
	exit(0);
}
