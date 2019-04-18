/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   tools.c                                          .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: loiberti <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/03/14 14:36:08 by loiberti     #+#   ##    ##    #+#       */
/*   Updated: 2019/03/23 19:10:42 by rgermain    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "lem_in.h"

void	set_or_clear_bit(char *bit, int bit_nb, int mode)
{
	if (!mode && !(*bit & (1 << bit_nb)))
		*bit |= (1 << bit_nb);
	else if (mode && (*bit & (1 << bit_nb)))
		*bit ^= (1 << bit_nb);
}

t_bool	test_bit(char *bit, int bit_nb)
{
	return (!(*bit & (1 << bit_nb)) ? TRUE : FALSE);
}

void	set_bit(char *bit, int bit_nb)
{
	*bit |= (1 << bit_nb);
}

void	clear_bit(char *bit, int bit_nb)
{
	*bit ^= (1 << bit_nb);
}
