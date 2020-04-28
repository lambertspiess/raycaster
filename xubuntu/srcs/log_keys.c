/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   log_keys.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lspiess <lspiess@student.42.us.org>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/22 03:37:09 by lspiess           #+#    #+#             */
/*   Updated: 2020/04/22 23:46:28 by lspiess          ###   ########.fr       */
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
	if (key == LEFT && m->keylog.look_left)
		m->keylog.look_left = 0;
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
	if (key == LEFT)
		m->keylog.look_left = 1;
	if (key == RIGHT)
		m->keylog.look_right = 1;
	if (key == ESC_KEY)
	{
		system(\
		"pkill -f cub3d_background_music &>/dev/null && pkill aplay");
		mlx_destroy_window(m->mlx_id, m->mlx_win_id);
		ft_free_and_exit(m, "Exiting", -1);
	}
	return (1);
}

int			ft_minimize(int key, t_cub3d *m)
{
	ft_printf("sfsg\n");
}

int			ft_red_cross(int key, t_cub3d *m)
{
	(void)key;
	(void)m;
	system("pkill -f cub3d_background_music &>/dev/null && pkill aplay");
	system("pkill -f aplay &>/dev/null");
	exit(-1);
	return (1);
}
