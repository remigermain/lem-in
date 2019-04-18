/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   main.c                                           .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: loiberti <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/03/26 19:20:05 by loiberti     #+#   ##    ##    #+#       */
/*   Updated: 2019/04/18 19:23:37 by rgermain    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "lem_in.h"

static void	put_flags(t_data *data, int argc, char **argv)
{
	int i;

	i = 1;
	while (i < argc)
	{
		if (!ft_strcmp(argv[i], "-i"))
		{
			set_bit(&(data->info.flags), 1);
			if (i < (argc - 1))
				data->info.time = ft_atoi(argv[i + 1]);
		}
		else if (!ft_strcmp(argv[i], "-p"))
			set_bit(&(data->info.flags), 2);
		else if (!ft_strcmp(argv[i], "-o"))
			set_bit(&(data->info.flags), 3);\
		else if (!ft_strcmp(argv[i], "-f"))
		{
			if (argc < (i + 1) ||
				(data->info.fd = open(argv[++i], O_RDONLY)) < 0)
				ft_dprintf(2, "%1@", "error", "lem_in", "can't open file");
		}
		else
			data->info.fd = 0;
		i++;
	}
}

int			main(int argc, char **argv)
{
	char	*line;
	t_data	data;

	ft_bzero(&data, sizeof(t_data));
	data.b.general = TRUE;
	put_flags(&data, argc, argv);
	while (data.b.general && get_next_line(data.info.fd, &line) == 1)
	{
		parse_line(&data, &line);
		put_line(&data, &line);
	}
	is_valid(&data);
	if (test_bit(&(data.info.flags), 2))
		ft_printf("\n");
	lemin_info(&data, "Finish to take info");
	algo(&data);
	nb_ants_by_path(&data, &data.soluce.good_path, data.soluce.path_cost);
	print_ants(&data);
	lemin_free(&data);
	return (0);
}
