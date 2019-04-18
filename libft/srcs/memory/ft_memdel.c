/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_memdel.c                                      .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: rgermain <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/10/04 14:34:30 by rgermain     #+#   ##    ##    #+#       */
/*   Updated: 2019/03/23 20:11:37 by rgermain    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "libft.h"

void	ft_memdeltab(char **ap)
{
	size_t count;

	count = 0;
	if (ap)
	{
		while (ap[count])
		{
			free(ap[count]);
			ap[count++] = NULL;
		}
		free(ap);
	}
}

void	ft_memdel(void **ap)
{
	if (ap)
	{
		free(*ap);
		*ap = NULL;
	}
}
