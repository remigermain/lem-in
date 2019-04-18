/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_memalloc.c                                    .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: rgermain <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/10/04 14:30:47 by rgermain     #+#   ##    ##    #+#       */
/*   Updated: 2018/11/13 10:33:56 by alepercq    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memalloc(size_t size)
{
	void	*mnew;

	if (size > 2147483647)
		return (NULL);
	if (!(mnew = (void*)malloc(sizeof(void) * size + 1)))
		return (NULL);
	ft_memset(mnew, 0, size);
	return (mnew);
}
