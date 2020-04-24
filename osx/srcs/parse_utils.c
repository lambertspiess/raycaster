/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lspiess <lspiess@student.42.us.org>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/22 16:34:24 by lspiess           #+#    #+#             */
/*   Updated: 2020/04/22 18:07:41 by lspiess          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static double	ft_store_playerdir(char c)
{
	if (c == 'N')
		return (90.0);
	else if (c == 'E')
		return (0.0);
	else if (c == 'W')
		return (180.0);
	else
		return (270.0);
}

void			ft_store_pos(t_cub3d *m)
{
	int			row;
	int			col;
	char		*c;

	row = 0;
	while (row < m->rows)
	{
		col = 0;
		while (col < m->wid)
		{
			if ((c = ft_strchr("NSEW", (*(m->map + row))[col])) != NULL)
			{
				m->playerpos.y = (double)(row + 0.5);
				m->playerpos.x = (double)(col + 0.5);
				m->playerdir = ft_store_playerdir(*c);
				(*(m->map + row))[col] = '0';
			}
			col++;
		}
		row++;
	}
}
