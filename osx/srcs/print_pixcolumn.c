/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_pixcolumn.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lspiess <lspiess@student.42.us.org>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/22 03:38:10 by lspiess           #+#    #+#             */
/*   Updated: 2020/04/22 04:13:48 by lspiess          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void			ft_set_mlx_img_pixel(int x, int y, t_cub3d *m, t_color color)
{
	m->display.img_data_addr[y * m->display.img_line_size \
							+ x * m->display.img_bpp_by8] = color.b;
	m->display.img_data_addr[y * m->display.img_line_size \
							+ x * m->display.img_bpp_by8 + 1] = color.g;
	m->display.img_data_addr[y * m->display.img_line_size \
							+ x * m->display.img_bpp_by8 + 2] = color.r;
}

static t_image	*ft_determine_wallhitside(t_cub3d *m, double xraydir, int side)
{
	if (side == 0)
	{
		if (180 < xraydir && xraydir < 360)
			return (&(m->textures.southwall));
		else
			return (&(m->textures.northwall));
	}
	else
	{
		if (90 < xraydir && xraydir <= 270)
			return (&(m->textures.westwall));
		else
			return (&(m->textures.eastwall));
	}
}

static void		ft_draw_texture_vertical_line_to_image(\
				t_cub3d *m, t_image tex, int endwall)
{
	int				itexy;
	double			texystep;
	t_color			pixcolor;
	int				texidx;
	int				winidx;

	texystep = (double)(tex.height) / (double)(m->drawnwallheight);
	tex.y = (m->win_beginwall - m->halfres + (0.5 * m->drawnwallheight)) \
			* texystep;
	while (m->winy <= endwall)
	{
		itexy = (int)(tex.y) & (tex.height - 1);
		tex.y += texystep;
		texidx = itexy * tex.img_line_size + ((int)tex.x) * tex.img_bpp / 8;
		pixcolor.r = tex.img_data_addr[texidx];
		pixcolor.g = tex.img_data_addr[texidx + 1];
		pixcolor.b = tex.img_data_addr[texidx + 2];
		winidx = m->winy * m->display.img_line_size \
					+ m->s.x * m->display.img_bpp / 8;
		m->display.img_data_addr[winidx] = pixcolor.r;
		m->display.img_data_addr[winidx + 1] = pixcolor.g;
		m->display.img_data_addr[winidx + 2] = pixcolor.b;
		m->winy++;
	}
}

static void		init(t_cub3d *m, double *hitcoordp, t_render *s)
{
	if (m->s.cam.planewalldist < 0.0001)
		m->s.cam.planewalldist = 0.01;
	m->drawnwallheight = (int)(m->res.y / m->s.cam.planewalldist);
	if ((m->win_beginwall = m->halfres - 0.5 * m->drawnwallheight) < 0)
		m->win_beginwall = 0;
	if ((m->win_endwall = m->halfres + 0.5 * m->drawnwallheight) >= m->res.y)
		m->win_endwall = m->res.y - 1;
	m->winy = 0;
	while (m->winy <= m->win_beginwall)
	{
		ft_set_mlx_img_pixel(s->x, m->winy, m, m->ceilcol);
		m->winy++;
	}
	m->curtexp = ft_determine_wallhitside(m, s->xraydir, s->side);
	if (s->side == 0)
		*hitcoordp = m->playerpos.x + s->xeuclidwalldist \
						* cos(s->xraydir * RAD_MUL);
	else
		*hitcoordp = m->playerpos.y - s->xeuclidwalldist \
						* sin(s->xraydir * RAD_MUL);
}

/*
** For a given x-coordinate pixel column on the display window :
** - beginwall : the y pixel coordinate of the end of the beginning of the wall
** - endwall : the y pixel coordinate of the end of the wall
*/

void			ft_print_pixcolumn(t_cub3d *m, t_render *s)
{
	double			hitcoord;
	int				inv;

	init(m, &hitcoord, s);
	inv = hitcoord < 0 ? 1 : 0;
	hitcoord = hitcoord < 0 ? -hitcoord : hitcoord;
	if (inv)
		m->curtexp->x = m->curtexp->width - m->curtexp->width * floor(hitcoord);
	else
		m->curtexp->x = m->curtexp->width;
	hitcoord = fabs(hitcoord);
	hitcoord -= floor(hitcoord);
	if (inv == 0)
		m->curtexp->x = (hitcoord * ((double)(m->curtexp->width)));
	else
		m->curtexp->x = (double)(m->curtexp->width) * (1 - hitcoord);
	ft_draw_texture_vertical_line_to_image(m, *(m->curtexp), m->win_endwall);
	while (m->winy < m->res.y)
	{
		ft_set_mlx_img_pixel(s->x, m->winy, m, m->floorcol);
		m->winy++;
	}
}
