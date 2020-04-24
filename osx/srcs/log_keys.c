/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   log_keys.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lspiess <lspiess@student.42.us.org>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/22 03:37:09 by lspiess           #+#    #+#             */
/*   Updated: 2020/04/22 03:41:41 by lspiess          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int			ft_keyrelease(int key, t_cub3d *m)
{
	if (key == W_KEY && m->keylog.mov_up)
		m->keylog.mov_up = 0;
	if (key == A_KEY && m->keylog.mov_left)
		m->keylog.mov_left = 0;
	if (key == S_KEY && m->keylog.mov_down)
		m->keylog.mov_down = 0;
	if (key == D_KEY && m->keylog.mov_right)
		m->keylog.mov_right = 0;
	if (key == UP && m->keylog.look_up)
		m->keylog.look_up = 0;
	if (key == LEFT && m->keylog.look_left)
		m->keylog.look_left = 0;
	if (key == DOWN && m->keylog.look_down)
		m->keylog.look_down = 0;
	if (key == RIGHT && m->keylog.look_right)
		m->keylog.look_right = 0;
	return (1);
}

int			ft_keypress(int key, t_cub3d *m)
{
	if (key == W_KEY)
		m->keylog.mov_up = 1;
	if (key == A_KEY)
		m->keylog.mov_left = 1;
	if (key == S_KEY)
		m->keylog.mov_down = 1;
	if (key == D_KEY)
		m->keylog.mov_right = 1;
	if (key == UP)
		m->keylog.look_up = 1;
	if (key == LEFT)
		m->keylog.look_left = 1;
	if (key == DOWN)
		m->keylog.look_down = 1;
	if (key == RIGHT)
		m->keylog.look_right = 1;
	if (key == RDEL_KEY || key == ESC_KEY)
	{
		mlx_destroy_window(m->mlx_id, m->mlx_win_id);
		ft_free_and_exit(m, "Exiting", -1);
	}
	return (1);
}

int			ft_red_cross(int key, t_cub3d *m)
{
	(void)key;
	(void)m;
	system("pkill -f cub3d_background_music &>/dev/null && killall afplay");
	exit(-1);
	return (1);
}
