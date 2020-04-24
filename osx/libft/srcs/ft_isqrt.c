/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_sqrt.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lspiess <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/20 10:02:42 by lspiess           #+#    #+#             */
/*   Updated: 2019/05/20 10:47:38 by lspiess          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int			ft_isqrt(int n)
{
	int			x;
	int			y;

	x = n;
	y = 1;
	while (x - y > 0)
	{
		x = (x + y) / 2;
		y = n / x;
	}
	return (x);
}
