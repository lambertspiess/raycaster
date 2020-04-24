/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   store_floor_ceiling_colors.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lspiess <lspiess@student.42.us.org>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/22 03:38:36 by lspiess           #+#    #+#             */
/*   Updated: 2020/04/22 03:38:36 by lspiess          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int					ft_store_floor_color(t_cub3d *m, char **tok)
{
	if (tok[1] == NULL)
		return (FAILURE);
	if (ft_is_unsigned_triplet(tok[1]) == FALSE)
		return (FAILURE);
	if (ft_extract_color(tok[1], &(m->floorcol)) == FAILURE)
		return (FAILURE);
	return (SUCCESS);
}

int					ft_store_ceiling_color(t_cub3d *m, char **tok)
{
	if (tok[1] == NULL)
		return (FAILURE);
	if (ft_is_unsigned_triplet(tok[1]) == FALSE)
		return (FAILURE);
	if (ft_extract_color(tok[1], &(m->ceilcol)) == FAILURE)
		return (FAILURE);
	return (SUCCESS);
}
