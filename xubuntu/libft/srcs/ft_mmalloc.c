/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_mmalloc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lspiess <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/05 21:33:28 by lspiess           #+#    #+#             */
/*   Updated: 2020/03/04 15:59:40 by lspiess          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void		*ft_mmalloc(int size)
{
	char				*ptr;
	int					i;

	if (!(ptr = malloc(size)))
		return (NULL);
	i = 0;
	while (i < size)
	{
		*(ptr + i) = 0;
		i++;
	}
	return ((void *)(ptr));
}
