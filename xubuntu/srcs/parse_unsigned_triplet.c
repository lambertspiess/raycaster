/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_unsigned_triplet.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lspiess <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/16 22:54:00 by lspiess           #+#    #+#             */
/*   Updated: 2020/04/22 03:38:07 by lspiess          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/*
** Checks if a string is a valid triplet of comma-separated integers
*/

int			ft_is_unsigned_triplet(char *s)
{
	size_t		i;
	unsigned	nbcount;

	nbcount = 0;
	i = 0;
	while (s[i])
	{
		if (ft_is_unsigned(s) == FALSE)
			return (FALSE);
		nbcount++;
		while (s[i] && s[i] != ',')
			i++;
		if (s[i] == ',')
			i++;
	}
	if (nbcount == 3)
		return (TRUE);
	else
		return (FALSE);
}
