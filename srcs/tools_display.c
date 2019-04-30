/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   tools.c                                          .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: loiberti <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/03/14 14:36:08 by loiberti     #+#   ##    ##    #+#       */
/*   Updated: 2019/04/23 15:19:10 by rgermain    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "lem_in.h"

void	lemin_info(t_data *data, char *str)
{
	if (!test_bit(&(data->info.flags), 1))
	{
		ft_dprintf(2, "%s--INFO---%s\n ", T_LGREY, T_WHITE);
		ft_dprintf(2, "%s%s%s\n\n", T_BLUE, str, T_WHITE);
		usleep(data->info.time * 10000);
	}
}

void	putint(t_data *data, int *tab, int mod)
{
	int	i;

	i = -1;
	while (tab[++i] != -1)
	{
		if (!mod)
		{
			if (!i || tab[i + 1] == -1)
				ft_printf("|| %d || ", tab[i]);
			else
				ft_printf("[ %d ]", tab[i]);
		}
		else
		{
			if (!i || tab[i + 1] == -1)
				ft_printf("|| %s || ", find_name(data, tab[i]));
			else
				ft_printf("[ %s ]", find_name(data, tab[i]));
		}
	}
	ft_printf("\n\n");
}

void	putdbint(t_data *data, int **tab, int limit, int mod)
{
	int	i;

	i = -1;
	while (++i < limit)
		putint(data, tab[i], mod);
	if (!mod)
		ft_printf("|| START : %d || END: %d ||\n\n", ROOM_START,
				ROOM_END);
	else
		ft_printf("|| START : %s || END: %s ||\n\n", find_name(data,
					ROOM_START), find_name(data, ROOM_END));
}

void	put_line(t_data *data, char **line)
{
	t_line	**tmp;

	data->line++;
	if (!test_bit(&(data->info.flags), 2))
	{
		ft_memdel((void**)line);
		return ;
	}
	tmp = &(data->file);
	while (*tmp != NULL)
		tmp = &((*tmp)->next);
	if (!(*tmp = (t_line*)ft_memalloc(sizeof(t_line))))
		display_error(data, 0);
	(*tmp)->next = NULL;
	(*tmp)->line = (*line);
}

void	print_line(t_line *file)
{
	if (file)
	{
		write(1, file->line, ft_strlen(file->line));
		ft_putchar('\n');
		print_line(file->next);
	}
}
