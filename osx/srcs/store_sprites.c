/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   store_sprites.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lspiess <lspiess@student.42.us.org>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/22 03:38:49 by lspiess           #+#    #+#             */
/*   Updated: 2020/04/22 21:33:40 by lspiess          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void		ft_store_sprite_info(t_cub3d *m, int i, t_xy pos, char c)
{
	(*(m->sprites + i))->pos.x = pos.x + 0.5;
	(*(m->sprites + i))->pos.y = pos.y + 0.5;
	(*(m->sprites + i))->firstx = -1;
	(*(m->sprites + i))->lastx = -1;
	if (c == '2')
		(*(m->sprites + i))->img = &(m->textures.pillar);
}

void			ft_store_sprites(t_cub3d *m, char **map, int i)
{
	t_xy			pos;

	if (!(m->sprites = malloc(sizeof(t_sprite *) * (m->spritesnb + 1))) \
		|| !(m->sptab = malloc(sizeof(t_sprite *) * (m->spritesnb + 1))))
		ft_free_and_exit(m, "failed to allocate for sprites array\n", -1);
	pos.y = 0;
	while (pos.y < m->rows)
	{
		pos.x = 0;
		while (pos.x < m->wid)
		{
			if ((*(map + (int)pos.y))[(int)pos.x] == '2')
			{
				if (((*(m->sprites + i)) = malloc(sizeof(t_sprite))) == NULL)
					ft_free_and_exit(m, "failed to allocate for sprite\n", -1);
				ft_store_sprite_info(m, i, pos,
						(*(map + (int)pos.y))[(int)pos.x]);
				i++;
			}
			pos.x++;
		}
		pos.y++;
	}
	*(m->sprites + i) = NULL;
}
