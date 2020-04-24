/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lspiess <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/06 19:18:29 by lspiess           #+#    #+#             */
/*   Updated: 2020/04/22 18:07:52 by lspiess          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	ft_get_quarter(double xraydir)
{
	if (0 < xraydir && xraydir <= 90)
		return (NORTH_EAST);
	else if (90 < xraydir && xraydir <= 180)
		return (NORTH_WEST);
	else if (180 < xraydir && xraydir <= 270)
		return (SOUTH_WEST);
	else if (((270 < xraydir && xraydir <= 360)) || (xraydir == 0))
		return (SOUTH_EAST);
	return (0);
}

static void	ft_get_mapsteps(t_render *s)
{
	if (s->quarter == NORTH_EAST || s->quarter == SOUTH_EAST)
		s->hmapstep = 1;
	else
		s->hmapstep = -1;
	if (s->quarter == NORTH_EAST || s->quarter == NORTH_WEST)
		s->vmapstep = -1;
	else
		s->vmapstep = 1;
}

static void	ft_compute_offsets_and_steps(t_cub3d *m, t_render *s, \
												double theta)
{
	s->invsinmul = 1 / sin(theta);
	s->invcosmul = 1 / cos(theta);
	if (s->quarter == NORTH_EAST || s->quarter == NORTH_WEST)
		s->h0 = fabs(s->deltay * s->invsinmul);
	else
		s->h0 = fabs((1 - s->deltay) * s->invsinmul);
	if (s->quarter == NORTH_EAST || s->quarter == SOUTH_EAST)
		s->v0 = fabs((1 - s->deltax) * s->invcosmul);
	else
		s->v0 = fabs(s->deltax * s->invcosmul);
	s->h0 = (s->h0 > m->maxraylength ? m->maxraylength : s->h0);
	s->v0 = (s->v0 > m->maxraylength ? m->maxraylength : s->v0);
	s->hstep = fabs(s->invsinmul);
	s->vstep = fabs(s->invcosmul);
	s->hstep = (s->hstep > m->maxraylength ? m->maxraylength : s->hstep);
	s->vstep = (s->vstep > m->maxraylength ? m->maxraylength : s->vstep);
}

void		ft_render(t_cub3d *m)
{
	ft_initialize_mlx_image(m);
	ft_reset_sprite_collisions(m->sprites);
	m->s.x = 0;
	m->s.xraydir = ft_setangle(m->playerdir + HALFOV);
	m->s.deltax = m->playerpos.x - floor(m->playerpos.x);
	m->s.deltay = m->playerpos.y - floor(m->playerpos.y);
	m->s.cam.planestart = ft_setangle(m->playerdir - 90.0);
	while (m->s.x < m->res.x)
	{
		m->camplanexraydirsin_buffer[m->s.x] = sin(ft_setangle(m->s.xraydir \
											- m->s.cam.planestart) * RAD_MUL);
		m->s.quarter = ft_get_quarter(m->s.xraydir);
		ft_get_mapsteps(&(m->s));
		ft_compute_offsets_and_steps(m, &(m->s), m->s.xraydir * RAD_MUL);
		ft_digital_differential_analizer(m, m->playerpos, &(m->s));
		m->s.cam.planewalldist = fabs(m->camplanexraydirsin_buffer[m->s.x] \
									* m->s.xeuclidwalldist);
		*(m->z_buffer + m->s.x) = m->s.cam.planewalldist;
		ft_print_pixcolumn(m, &(m->s));
		m->s.x++;
		m->s.xraydir = ft_setangle(m->s.xraydir - m->s.xrayoffset);
	}
	ft_render_sprites(m, m->sprites, m->sptab);
	ft_display_image(m, m->display);
}
