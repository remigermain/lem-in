/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   lem_in.h                                         .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: loiberti <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/03/26 19:20:21 by loiberti     #+#   ##    ##    #+#       */
/*   Updated: 2019/04/18 20:14:26 by rgermain    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#ifndef LEM_IN_H
# define LEM_IN_H
# include "../libft/includes/libft.h"
# define TRUE	1
# define FALSE	0
# define ROOM_START 0
# define ROOM_END 1

typedef struct	s_algostar
{
	int	*hs;
	int	*cost;
	int	*olst;
	int	o_startlen;
	int	o_endlen;
	int	*clst;
	int	c_startlen;
	int	c_endlen;
}				t_algostar;

typedef struct	s_algo
{
	int	i;
	int	l;
	int	*file;
	int	*nb_file;
}				t_algo;

typedef struct	s_tabsoluce
{
	int	**tab;
	int	nb_soluce;
	int	*path_cost;
	int	*good_path;
}				t_tabsoluce;

typedef struct	s_soluce
{
	int	i;
	int	j;
	int	l;
	int	pos;
	int	len;
	int	*path;
}				t_soluce;

typedef	struct	s_info
{
	char	flags;
	int		fd;
	int		line_nb;
	int		time;
	int		line;
}				t_info;

typedef struct	s_pipe
{
	int	p1;
	int	p2;
}				t_pipe;

typedef struct	s_matrix
{
	char	**tab;
	char	*visited;
	char	oriented;
	int		pipe1;
	int		pipe2;
	int		end_len;
}				t_matrix;

typedef struct	s_booleen
{
	t_bool	start;
	t_bool	end;
	t_bool	ants;
	t_bool	room;
	t_bool	pipe;
	t_bool	general;
}				t_booleen;

typedef struct	s_room
{
	char			*name;
	int				x;
	int				y;
	struct s_room	*next;
}				t_room;

typedef struct	s_data
{
	int			ants_nb;
	int			room_nb;
	int			pipe_nb;
	int			line;
	t_booleen	b;
	t_info		info;
	t_room		start;
	t_room		end;
	t_room		*room;
	t_room		**room2;
	t_matrix	matrix;
	t_tabsoluce	soluce;
}				t_data;

/*
** ERROR && DEBUG
*/
void			display_error(t_data *data, char index);
void			lemin_info(t_data *data, char *str);

/*
**	ALGO  algo_lemin.c
*/
void			algo(t_data *data);
int				algo_astar(t_data *data, t_algostar *st, t_algo *al);
void			put_soluceastar(t_data *data, t_algo *al);

/*
** ALGO path
*/
void			nb_ants_by_path(t_data *data, int **good_path, int *path_cost);
void			print_ants(t_data *data);

/*
**	fonction qui check si c'est une room/pipe/commande ..
*/
t_bool			is_room(t_data *data, char *line);
void			is_valid(t_data *data);
t_bool			is_pipe(t_data *data, char **line);
t_bool			is_command(t_data *data, char *line);

/*
**	PUT_IN STRUCTS
*/
void			parse_line(t_data *data, char **line);
void			put_command(t_data *data, char **line);
void			put_room(t_data *data, char *line);
void			put_line(t_data *data, char **line);
void			put_pipe(t_data *data, char **line);
t_bool			find_nopipe(t_data *data, char **line, int j);

/*
**	FREE
*/
void			lemin_free(t_data *data);

/*
**	UTILS
*/
char			*find_name(t_data *data, int nb);
int				tabintlen(int *tab);
int				ft_atol(char *line);
int				to_malloc(int nb);
void			set_or_clear_bit(char *bit, int bit_nb, int mode);
t_bool			test_bit(char *bit, int bit_nb);
void			set_bit(char *bit, int bit_nb);
void			clear_bit(char *bit, int bit_nb);
void			putint(t_data *data, int *tab, int mod);
void			putdbint(t_data *data, int **tab, int limit, int mod);
#endif
