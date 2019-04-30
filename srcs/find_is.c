/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   find_is.c                                        .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: rgermain <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/03/18 15:41:56 by rgermain     #+#   ##    ##    #+#       */
/*   Updated: 2019/04/25 11:08:47 by loiberti    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "lem_in.h"

static int	is_xy(t_data *data, char *line, int *i, char c)
{
	int		word;
	char	check;

	word = 0;
	if (line[*i] == '-')
		(*i)++;
	check = *i;
	while (line[*i] && line[*i] != ' ')
	{
		if (!ft_isdigit(line[*i]))
			display_error(data, 1);
		(*i)++;
	}
	if (check != *i && line[*i] == c)
	{
		(*i)++;
		word++;
	}
	return (word);
}

t_bool		is_room(t_data *data, char *line)
{
	int		i;
	char	check;
	int		word;

	i = 0;
	check = 0;
	word = 0;
	if (data->b.pipe == 1 || line[i] == 'L')
		return (FALSE);
	while (line[i] && line[i] != ' ')
	{
		if (line[i] == '-')
			return (FALSE);
		i++;
	}
	if (i && line[i] == ' ')
	{
		i++;
		word++;
	}
	word += is_xy(data, line, &i, ' ');
	word += is_xy(data, line, &i, '\0');
	return (word == 3 ? TRUE : FALSE);
}

t_bool		is_command(t_data *data, char *line)
{
	if ((!ft_strcmp(line, "##start") && !data->b.start) ||
				(!ft_strcmp(line, "##end") && !data->b.end))
		return (TRUE);
	else if (!ft_strcmp(line, "##oriented"))
		set_bit(&(data->matrix.oriented), 1);
	return (FALSE);
}

t_bool		is_pipe(t_data *data, char **line)
{
	int	i;
	int	pipe;
	int	j;

	i = 0;
	pipe = 0;
	j = 0;
	if (!data->b.start || !data->b.end)
		return (FALSE);
	while ((*line)[i] != '\0')
	{
		if ((*line)[i] == '-')
		{
			pipe++;
			j = i;
		}
		i++;
	}
	if (pipe != 1 || !find_nopipe(data, line, j))
		return (FALSE);
	return (TRUE);
}
