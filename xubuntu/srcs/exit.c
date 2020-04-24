/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lspiess <lspiess@student.42.us.org>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/22 03:33:26 by lspiess           #+#    #+#             */
/*   Updated: 2020/04/22 23:46:43 by lspiess          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	ft_free_map(t_cub3d *m)
{
	int		i;

	i = 0;
	while (m->map[i] != NULL)
	{
		free(*(m->map + i));
		i++;
	}
	free(m->map);
}

static void	ft_free_sprites(t_cub3d *m)
{
	int			i;

	i = 0;
	while ((*(m->sprites + i)) != NULL)
	{
		free(*(m->sprites + i));
		i++;
	}
	free(m->sprites);
}

void		ft_free_and_exit(t_cub3d *m, char *err_msg, int ret)
{
	ft_printf("%s", err_msg);
	if (m->map != NULL)
		ft_free_map(m);
	if (m->display.img_ptr != NULL)
		mlx_destroy_image(m->mlx_id, m->display.img_ptr);
	if (m->z_buffer != NULL)
		free(m->z_buffer);
	if (m->camplanexraydirsin_buffer != NULL)
		free(m->camplanexraydirsin_buffer);
	if (m->sprites != NULL)
		ft_free_sprites(m);
	if (m->sptab != NULL)
		free(m->sptab);
	system("pkill -f cub3d_background_music &>/dev/null && killall aplay");
	pthread_join(m->thread_id, NULL);
	exit(ret);
}
