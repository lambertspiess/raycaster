/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lspiess <lspiess@student.42.us.org>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/22 03:37:13 by lspiess           #+#    #+#             */
/*   Updated: 2020/04/22 03:42:03 by lspiess          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void		ft_initialize_cub3d(int ac, char **av, t_cub3d *m)
{
	if (!(m->mlx_id = mlx_init()))
		ft_free_and_exit(m, "Error,\nFailed to initialize mlx_id\n", -1);
	ft_parse(ac, av, m);
	if (!(m->mlx_win_id = mlx_new_window(m->mlx_id, m->res.x, m->res.y, "42")))
		ft_free_and_exit(m, "Error,\nFailed to initialize mlx_win_id\n", -1);
	if (ac > 2 && ft_strequ(*(av + 2), "--save") == 1)
		m->save_bmp = 1;
}

void		*ft_play_music(void *arg)
{
	(void)(arg);
	system("sh cub3dmusic.sh -a cub3d_background_music &");
	pthread_exit(NULL);
}

int			main(int ac, char **av)
{
	t_cub3d		m;

	ft_memset((void *)(&m), 0, sizeof(t_cub3d));
	ft_initialize_cub3d(ac, av, &m);
	pthread_create(&m.thread_id, NULL, ft_play_music, NULL);
	ft_render(&m);
	if (m.save_bmp)
		ft_save_bmp(&m);
	mlx_hook(m.mlx_win_id, 2, 1L << 0, ft_keypress, &m);
	mlx_hook(m.mlx_win_id, 3, 1L << 1, ft_keyrelease, &m);
	mlx_hook(m.mlx_win_id, 17, 1L << 17, ft_red_cross, &m);
	mlx_loop_hook(m.mlx_id, ft_handle_hooks, &m);
	mlx_loop(m.mlx_id);
	ft_free_and_exit(&m, "Exiting\n", 0);
	return (0);
}
