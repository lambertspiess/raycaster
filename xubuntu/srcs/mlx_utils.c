/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lspiess <lspiess@student.42.us.org>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/22 03:37:22 by lspiess           #+#    #+#             */
/*   Updated: 2020/04/22 15:54:20 by lspiess          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void		ft_initialize_mlx_image(t_cub3d *m)
{
	if (m->display.img_ptr != NULL)
	{
		mlx_destroy_image(m->mlx_id, m->display.img_ptr);
		m->display.img_ptr = NULL;
	}
	if (!(m->display.img_ptr = mlx_new_image(m->mlx_id, m->res.x, m->res.y))
	|| !(m->display.img_data_addr = mlx_get_data_addr(m->display.img_ptr,\
												&(m->display.img_bpp),\
												&(m->display.img_line_size),\
												&(m->display.endianess))))
		ft_free_and_exit(m, "Failed to initialize mlx_new_image\n", -1);
	m->display.img_bpp_by8 = m->display.img_bpp / 8;
}

void		ft_display_image(t_cub3d *m, t_image img)
{
	mlx_put_image_to_window(m->mlx_id, m->mlx_win_id, img.img_ptr, 0, 0);
}
