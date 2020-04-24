/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_sprites.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lspiess <lspiess@student.42.us.org>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/22 03:38:16 by lspiess           #+#    #+#             */
/*   Updated: 2020/04/22 03:39:57 by lspiess          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/*
** If the pixel at the current column of the current sprite is not black,
** light the corresponding pixel on the image to be displayed
*/

static void		ft_set_display_pixcolor(t_cub3d *m, t_sprite *sp, \
											int *x, int *y)
{
	int				winidx;

	if (!sp->pixcolor.r && !sp->pixcolor.g && !sp->pixcolor.b)
	{
		(*y)++;
		sp->coord.y += sp->spriteystep;
		return ;
	}
	winidx = *y * m->display.img_line_size \
				+ *x * m->display.img_bpp_by8;
	m->display.img_data_addr[winidx] = sp->pixcolor.r;
	m->display.img_data_addr[winidx + 1] = sp->pixcolor.g;
	m->display.img_data_addr[winidx + 2] = sp->pixcolor.b;
	(*y)++;
	sp->coord.y += sp->spriteystep;
}

/*
** Extract the rgb value of the sprite pixel at the current index of the
** current column
*/

static void		ft_get_pixcolor(t_sprite *sp)
{
	sp->spritepixidx = sp->ispritey * sp->img->img_line_size \
						+ sp->ispritex * sp->img->img_bpp / 8;
	sp->pixcolor.r = sp->img->img_data_addr[sp->spritepixidx];
	sp->pixcolor.g = sp->img->img_data_addr[sp->spritepixidx + 1];
	sp->pixcolor.b = sp->img->img_data_addr[sp->spritepixidx + 2];
}

/*
** For a given sprite, draw it on the display column by column. The variable
** firstx and lastx, set during the DDA step, correspond to the x indices
** (on the display) of the beginning and end of the visible region of the
** sprite.
*/

static void		ft_print_sprite(t_cub3d *m, t_sprite *sp)
{
	int				x;
	int				y;

	x = sp->begindrawnspritex;
	sp->coord.x = sp->xoffset ? (double)sp->xoffset \
	/ (double)sp->drawnspritewid * (double)sp->img->width : 0;
	while (x <= sp->enddrawnspritex && x < m->res.x)
	{
		if (sp->firstx <= x && x <= sp->lastx)
		{
			sp->ispritex = (int)(sp->coord.x) & (sp->img->width - 1);
			sp->coord.y = sp->begincoordy;
			y = sp->begindrawnspritey;
			while (y <= sp->enddrawnspritey)
			{
				sp->ispritey = (int)(sp->coord.y) & (sp->img->height - 1);
				ft_get_pixcolor(sp);
				ft_set_display_pixcolor(m, sp, &x, &y);
			}
		}
		x++;
		sp->coord.x += sp->spritexstep;
	}
}

static void		ft_initialize_sprite_drawing_bounds(t_cub3d *m, t_sprite *sp)
{
	sp->drawnspriteheight = (int)(m->res.y / sp->camplanedist);
	sp->yoffset = 0;
	sp->begincoordy = 0;
	if ((sp->begindrawnspritey = m->halfres \
								- 0.4 * sp->drawnspriteheight) < 0)
	{
		sp->yoffset = abs(sp->begindrawnspritey);
		sp->begindrawnspritey = 0;
		sp->begincoordy = (int)((double)sp->yoffset\
			/ (double)sp->drawnspriteheight * (double)sp->img->height);
	}
	if ((sp->enddrawnspritey = m->halfres \
								+ 0.6 * sp->drawnspriteheight) >= m->res.y)
		sp->enddrawnspritey = m->res.y - 1;
	sp->spriteystep = (double)sp->img->height \
						/ (double)sp->drawnspriteheight;
}

/*
** For every visible sprite, determine its height (in pixels) on the display
** image (drawnspriteheight), where we begin (begindrawnspritey) and stop
** (enddrawnspritey) to draw vertically, and the same thing horizontally
** (respectively drawnspritewid, begindrawnspritex, enddrawnspritex).
** The variable xoffset is useful  when the sprite is only partially
** visible (when cut by the edges of the display or by a wall).
*/

void			ft_print_sprites(t_cub3d *m, t_sprite **tab)
{
	int				i;
	t_sprite		*sp;

	i = 0;
	sp = NULL;
	while ((sp = *(tab + i)) != 0)
	{
		if (sp->camplanedist < 0.0001)
			sp->camplanedist = 0.0001;
		ft_initialize_sprite_drawing_bounds(m, sp);
		sp->drawnspritewid = (int)(0.7 * m->res.x / sp->camplanedist);
		sp->xoffset = 0;
		if ((sp->begindrawnspritex = (int)(sp->centerx \
										- 0.5 * sp->drawnspritewid)) < 0)
		{
			sp->xoffset = abs(sp->begindrawnspritex);
			sp->begindrawnspritex = 0;
		}
		sp->enddrawnspritex = (int)(sp->centerx + 0.5 * sp->drawnspritewid);
		sp->spritexstep = (double)sp->img->width / (double)sp->drawnspritewid;
		ft_print_sprite(m, sp);
		i++;
	}
}
