/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   parser.c                                         .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: loiberti <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/03/14 13:40:11 by loiberti     #+#   ##    ##    #+#       */
/*   Updated: 2019/04/25 10:57:37 by loiberti    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "lem_in.h"

static void	put_ants(t_data *data, char *line)
{
	if (!(ft_atol(line)) || (data->ants_nb = ft_atoi(line)) < 1)
		display_error(data, 1);
	data->b.ants = TRUE;
}

static void	put_comment(t_data *data, char *line)
{
	if (!ft_strncmp(line, "#Here is the number of lines required:", 38))
		data->info.line_indice = ft_atoi(line + 39);
}

void		is_valid(t_data *data)
{
	if (!data->b.start || !data->b.end || !data->b.ants || !data->b.pipe)
		display_error(data, 1);
	data->b.general = FALSE;
}

int			parse_line(t_data *data, char **line)
{
	if (!(data->b.ants))
		put_ants(data, (*line));
	else if (is_command(data, (*line)))
		put_command(data, line);
	else if (line && (*line)[0] == '#')
	{
		put_comment(data, (*line));
		ft_memdel((void**)(line));
		return (1);
	}
	else if (is_room(data, (*line)))
		put_room(data, line);
	else if (is_pipe(data, line))
		put_pipe(data, line);
	else
		is_valid(data);
	return (0);
}
