/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_dda.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lspiess <lspiess@student.42.us.org>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/22 15:18:25 by lspiess           #+#    #+#             */
/*   Updated: 2020/04/22 18:09:15 by lspiess          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	ft_store_spriteinfo(t_cub3d *m, t_sprite *sp)
{
	if (sp->firstx == -1)
	{
		sp->firstx = m->s.x;
		sp->firstxangle = m->s.xraydir;
	}
	sp->lastx = m->s.x;
}

static int	ft_check_square(t_cub3d *m, t_xy curpos)
{
	char			c;
	int				i;

	c = (*(m->map + (int)(curpos.y)))[(int)(curpos.x)];
	if (c == '1')
		return (1);
	else if (c == '2')
	{
		i = 0;
		while (*(m->sprites + i) != NULL)
		{
			if ((int)((*(m->sprites + i))->pos.x) == (int)curpos.x \
				&& (int)((*(m->sprites + i))->pos.y) == (int)curpos.y)
			{
				ft_store_spriteinfo(m, *(m->sprites + i));
				break ;
			}
			i++;
		}
	}
	return (0);
}

/*
** side == 0 means a horizontal line was hit, side == 1 a vertical line.
*/

void		ft_digital_differential_analizer(t_cub3d *m, t_xy pos, t_render *s)
{
	double		hn;
	double		vn;

	hn = s->h0;
	vn = s->v0;
	while (1)
	{
		if (hn < vn)
		{
			pos.y += s->vmapstep;
			s->side = 0;
			if (ft_check_square(m, pos) == 1)
				break ;
			hn += s->hstep;
		}
		else
		{
			pos.x += s->hmapstep;
			s->side = 1;
			if (ft_check_square(m, pos) == 1)
				break ;
			vn += s->vstep;
		}
	}
	s->xeuclidwalldist = (hn < vn ? hn : vn);
}
