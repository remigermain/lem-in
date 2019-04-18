/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   parser.c                                         .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: loiberti <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/03/14 13:40:11 by loiberti     #+#   ##    ##    #+#       */
/*   Updated: 2019/04/18 18:46:34 by rgermain    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "lem_in.h"

static void	put_ants(t_data *data, char *line)
{
	if ((data->ants_nb = ft_atol(line)) <= 0)
		display_error(data, 1);
	data->b.ants = TRUE;
}

void		is_valid(t_data *data)
{
	if (!data->b.start || !data->b.end || !data->b.ants || !data->b.pipe)
		display_error(data, 1);
	data->b.general = FALSE;
}

static void	put_comment(t_data *data, char *line)
{
	if (!ft_strncmp(line, "#Here is the number of lines required:", 38))
		data->info.line_nb = ft_atoi(line + 39);
}

void		parse_line(t_data *data, char **line)
{
	if (!(data->b.ants))
		put_ants(data, (*line));
	else if (is_command(data, (*line)))
		put_command(data, line);
	else if (line && (*line)[0] == '#')
		put_comment(data, (*line));
	else if (is_room(data, (*line)))
		put_room(data, (*line));
	else if (is_pipe(data, line))
		put_pipe(data, line);
	else
		is_valid(data);
}
