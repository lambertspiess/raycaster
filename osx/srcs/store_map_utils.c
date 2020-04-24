/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   store_map_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lspiess <lspiess@student.42.us.org>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/22 21:03:09 by lspiess           #+#    #+#             */
/*   Updated: 2020/04/22 21:28:42 by lspiess          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/*
** Verifies that a substring begins and ends with a one
*/

static int		ft_check_if_line_horizontally_bound(char *s, int idx)
{
	if (idx == 0)
		return (0);
	if (s[idx - 1] != '1')
		return (0);
	while (s[idx] && ft_strchr("02NSEW", s[idx]))
		idx++;
	if (s[idx] != '1')
		return (0);
	return (1);
}

/*
** Check if a given line is coherent (edges and whitespaces bound by walls)
** Everytime we meet a char that should be inside the map, we make sure that
** char/substring is surrounded by ones.
*/

int				ft_check_single_line(char *s, t_cub3d *m, int i)
{
	while (s[i])
	{
		if ((ft_strchr("02NSEW", s[i])) != NULL)
		{
			if (ft_check_if_line_horizontally_bound(s, i) == 0)
				return (0);
			while (s[i] && (ft_strchr("02NSEW", s[i]) != NULL))
			{
				if (ft_strchr("NSEW", s[i]) != NULL)
				{
					if (m->ispos == 1)
						ft_free_and_exit(m, "Player duplicate found\n", -1);
					else
						m->ispos = 1;
				}
				if (ft_strchr("2", s[i]) != NULL)
					m->spritesnb++;
				i++;
			}
		}
		i++;
	}
	return (1);
}
