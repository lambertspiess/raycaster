/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movlook.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lspiess <lspiess@student.42.us.org>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/22 03:37:28 by lspiess           #+#    #+#             */
/*   Updated: 2020/04/22 16:32:17 by lspiess          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

#define STEP 1
#define RAD 0.01745329251994329576

static void		ft_determine_direction(t_keylog k, int *horp, int *vecp)
{
	if (k.mov_left && !k.mov_right)
		*horp = -1;
	else if (!k.mov_left && k.mov_right)
		*horp = 1;
	if (k.mov_up && !k.mov_down)
		*vecp = -1;
	else if (!k.mov_up && k.mov_down)
		*vecp = 1;
}

static double	ft_compute_dirangle(t_keylog k, double playerdir, \
										int hor, int vec)
{
	ft_determine_direction(k, &hor, &vec);
	if (vec == -1 && hor == -1)
		return (ft_setangle(playerdir + 45.0));
	else if (vec == -1 && hor == 0)
		return (playerdir);
	else if (vec == -1 && hor == 1)
		return (ft_setangle(playerdir - 45.0));
	else if (vec == 0 && hor == -1)
		return (ft_setangle(playerdir + 90.0));
	else if (vec == 0 && hor == 1)
		return (ft_setangle(playerdir - 90.0));
	else if (vec == 1 && hor == -1)
		return (ft_setangle(playerdir + 135.0));
	else if (vec == 1 && hor == 0)
		return (ft_setangle(playerdir + 180.0));
	else if (vec == 1 && hor == 1)
		return (ft_setangle(playerdir - 135.0));
	return (0.0);
}

static void		ft_move(t_keylog k, t_cub3d *m)
{
	double			dirangle;
	double			radangle;
	t_xy			expected;
	double			cosine;
	double			sine;

	dirangle = ft_compute_dirangle(k, m->playerdir, 0, 0);
	radangle = dirangle * RAD_MUL;
	cosine = cos(radangle);
	sine = sin(radangle);
	expected.x = m->playerpos.x + (0.1 * cosine);
	expected.y = m->playerpos.y - (0.1 * sine);
	if (expected.x >= 0.0 && expected.x <= m->wid \
		&& expected.y >= 0.0 && expected.y <= m->rows)
	{
		if ((*(m->map + (int)(expected.y)))[(int)(expected.x)] == '0')
			m->playerpos = expected;
		else
		{
			ft_scrape_wall(m, dirangle);
		}
	}
}

static void		ft_turn(t_keylog k, t_cub3d *m)
{
	if (k.look_right && !k.look_left)
		m->playerdir = ft_setangle(m->playerdir - 2.5);
	else if (k.look_left && !k.look_right)
		m->playerdir = ft_setangle(m->playerdir + 2.5);
}

int				ft_handle_hooks(t_cub3d *m)
{
	t_keylog		k;

	m->is_change = 0;
	k = m->keylog;
	if (k.mov_up || k.mov_left || k.mov_right || k.mov_down)
	{
		m->is_change = 1;
		ft_move(k, m);
	}
	if (k.look_right || k.look_left)
	{
		m->is_change = 1;
		ft_turn(k, m);
	}
	if (m->is_change)
	{
		ft_render(m);
		ft_display_image(m, m->display);
	}
	return (1);
}
