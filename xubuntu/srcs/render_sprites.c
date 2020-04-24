/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_sprites.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lspiess <lspiess@student.42.us.org>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/22 03:38:26 by lspiess           #+#    #+#             */
/*   Updated: 2020/04/22 18:08:46 by lspiess          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void		ft_get_sprite_center(t_cub3d *m, t_sprite *sp, \
											double dx, double dy)
{
	double			alternate;

	if (dx >= 0)
	{
		sp->radcenterangle = M_PI + atan(dy / dx);
		sp->centerangle = sp->radcenterangle * DEG_MUL - m->playerdir;
		sp->centerx = (int)((0.5 * m->res.x) \
								- (sp->centerangle / m->s.xrayoffset));
		return ;
	}
	else if (dy > 0)
		sp->radcenterangle = 2 * M_PI + atan(dy / dx);
	else
		sp->radcenterangle = atan(dy / dx);
	sp->centerangle = sp->radcenterangle * DEG_MUL - m->playerdir;
	alternate = (sp->centerangle < 0) ? \
				360 + sp->centerangle : 360 - sp->centerangle;
	alternate = m->playerdir < sp->centerangle ? -alternate : alternate;
	sp->centerangle = fabs(alternate) < fabs(sp->centerangle) ? \
						alternate : sp->centerangle;
	sp->centerx = (int)((0.5 * m->res.x) \
						- (sp->centerangle / m->s.xrayoffset));
}

static int		ft_intialize_spritetab(t_cub3d *m, t_sprite **sprites,
											t_sprite **tab)
{
	int				i;
	int				j;
	t_sprite		*sp;

	i = 0;
	j = 0;
	while ((sp = (*(sprites + i))) != NULL)
	{
		if (sp->firstx != -1)
		{
			sp->deltax = m->playerpos.x - sp->pos.x;
			sp->deltay = sp->pos.y - m->playerpos.y;
			sp->dist = sqrt(sp->deltax * sp->deltax + sp->deltay * sp->deltay);
			ft_get_sprite_center(m, sp, sp->deltax, sp->deltay);
			sp->camplanedist = fabs(sin(sp->radcenterangle \
								- m->s.cam.planestart * RAD_MUL) * sp->dist);
			(*(tab + j)) = sp;
			j++;
		}
		i++;
	}
	return (j);
}

void			ft_render_sprites(t_cub3d *m, t_sprite **sprites, \
									t_sprite **tab)
{
	int				i;
	int				visible_sprites_nb;

	ft_bzero(tab, sizeof(t_sprite *) * (m->spritesnb + 1));
	visible_sprites_nb = ft_intialize_spritetab(m, sprites, tab);
	i = 0;
	ft_sprite_quicksort(tab, 0, visible_sprites_nb - 1);
	ft_print_sprites(m, tab);
}
