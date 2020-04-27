/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   save_bmp.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lspiess <lspiess@student.42.us.org>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/22 03:38:29 by lspiess           #+#    #+#             */
/*   Updated: 2020/04/22 18:18:31 by lspiess          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void				ft_init_bmp(t_bmp *bmp, t_cub3d *m)
{
	bmp->pixcount = (unsigned)(m->res.x * m->res.y);
	bmp->bufsize = (unsigned)(bmp->pixcount * 4);
	bmp->total_size = bmp->bufsize + 54;
	bmp->pix_data_offset = 54;
	bmp->header_size = 40;
	bmp->imagewidth = (int)(m->res.x);
	bmp->imageheight = (int)(m->res.y);
	bmp->color_planes = 1;
	bmp->bpp = 32;
	bmp->total_colors = 2835;
}

static void				ft_fill_bmp_header(t_bmp *bmp)
{
	ft_memset(&(bmp->header), 0, 54);
	bmp->header[0] = 'B';
	bmp->header[1] = 'M';
	ft_memcpy(&(bmp->header[2]), &(bmp->total_size), sizeof(unsigned int));
	ft_memcpy(&(bmp->header[10]), &(bmp->pix_data_offset),\
														sizeof(unsigned int));
	ft_memcpy(&(bmp->header[14]), &(bmp->header_size), sizeof(unsigned int));
	ft_memcpy(&(bmp->header[18]), &(bmp->imagewidth), sizeof(int));
	ft_memcpy(&(bmp->header[22]), &(bmp->imageheight), sizeof(int));
	ft_memcpy(&(bmp->header[26]), &(bmp->color_planes), sizeof(short));
	ft_memcpy(&(bmp->header[28]), &(bmp->bpp), sizeof(short));
	ft_memcpy(&(bmp->header[34]), &(bmp->bufsize), sizeof(short));
	ft_memcpy(&(bmp->header[38]), &(bmp->total_colors), sizeof(int));
	ft_memcpy(&(bmp->header[42]), &(bmp->total_colors), sizeof(int));
}

void					ft_save_bmp(t_cub3d *m)
{
	t_bmp			bmp;
	int				fd;
	char			*data;

	if (!(fd = open("snapshot_cub3d.bmp", O_RDWR | O_CREAT, 77777)))
	{
		ft_putstr("Failed to create bmp snapshot\n");
		return ;
	}
	ft_init_bmp(&bmp, m);
	ft_fill_bmp_header(&bmp);
	write(fd, bmp.header, 54);
	if ((data = (char *)(m->display.img_data_addr)) != NULL)
		write(fd, data, (int)(m->res.x * m->res.y * 4));
	ft_free_and_exit(m, "Saved snapshot_cub3d.bmp\n", -1);
}
