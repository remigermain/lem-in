/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_freetabi.c                                    .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: rgermain <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/02/01 10:42:01 by rgermain     #+#   ##    ##    #+#       */
/*   Updated: 2019/03/23 20:11:11 by rgermain    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "libft.h"

void	ft_freetabi(int **tab, size_t len)
{
	size_t	count;

	count = 0;
	if (tab)
	{
		while (count < len)
			ft_memdel((void**)&(tab[count++]));
		ft_memdel((void**)&tab);
	}
}
