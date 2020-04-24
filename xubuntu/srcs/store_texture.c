/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   store_texture.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lspiess <lspiess@student.42.us.org>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/22 03:38:52 by lspiess           #+#    #+#             */
/*   Updated: 2020/04/22 21:35:44 by lspiess          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int				ft_store_texture(t_cub3d *m, char **tokens)
{
	t_image			*dest;

	if (ft_strequ(tokens[0], "NO"))
		dest = &(m->textures.northwall);
	else if (ft_strequ(tokens[0], "WE"))
		dest = &(m->textures.westwall);
	else if (ft_strequ(tokens[0], "EA"))
		dest = &(m->textures.eastwall);
	else if (ft_strequ(tokens[0], "S"))
		dest = &(m->textures.pillar);
	else
		dest = &(m->textures.southwall);
	if (!(dest->img_ptr = mlx_xpm_file_to_image(m->mlx_id, (char *)(tokens[1]),
											&(dest->width), &(dest->height))))
	{
		ft_printf("Failed to load texture path : %s\n", tokens[1]);
		return (0);
	}
	dest->img_data_addr = mlx_get_data_addr(dest->img_ptr, \
		&(dest->img_bpp), &(dest->img_line_size), &(dest->endianess));
	return (1);
}
