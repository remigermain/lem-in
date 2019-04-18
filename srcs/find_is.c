/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   find_is.c                                        .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: rgermain <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/03/18 15:41:56 by rgermain     #+#   ##    ##    #+#       */
/*   Updated: 2019/04/18 19:31:13 by loiberti    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "lem_in.h"

static char	is_room_word(char *line, size_t *i)
{
	if (line[(*i)] != ' ' && line[(*i)] != '-' && line[(*i)] != '\0')
	{
		while (line[(*i)] != ' ' && line[(*i)] != '-' && line[(*i)] != '\0')
			(*i)++;
		return (1);
	}
	return (0);
}

static void	is_room_space(char *line, size_t *i, size_t *len, char index)
{
	if ((line[(*i)] == ' ' || line[(*i)] == '\t') &&
			line[(*i)] != '\0' && ((*i)++))
	{
		if (index == 1)
			(*len)++;
		while ((line[(*i)] == ' ' || line[(*i)] == '\t') &&
				line[(*i)] != '\0')
			(*i)++;
	}
}

t_bool		is_room(t_data *data, char *line)
{
	size_t	i;
	size_t	len;

	i = 0;
	len = 0;
	if (data->b.pipe == 1)
		return (FALSE);
	is_room_space(line, &i, &len, 0);
	if (line[i] == 'L')
		return (FALSE);
	is_room_word(line, &i);
	is_room_space(line, &i, &len, 1);
	if (ft_atol(line + i) == -1)
		return (FALSE);
	is_room_word(line, &i);
	is_room_space(line, &i, &len, 1);
	if (ft_atol(line + i) == -1)
		return (FALSE);
	is_room_word(line, &i);
	is_room_space(line, &i, &len, 0);
	if (line[i] == '\0' && len == 2)
		return (TRUE);
	return (FALSE);
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
