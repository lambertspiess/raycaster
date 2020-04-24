/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   store_res.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lspiess <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/16 18:49:41 by lspiess           #+#    #+#             */
/*   Updated: 2020/04/22 21:29:19 by lspiess          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int			ft_store_res(t_cub3d *m, char **tok)
{
	if (tok[1] == NULL || tok[2] == NULL)
		return (FAILURE);
	if (ft_is_unsigned(tok[1]) == FALSE || ft_is_unsigned(tok[2]) == FALSE)
		return (FAILURE);
	m->res.x = (double)(ft_rt_atoi(tok[1]));
	m->res.y = (double)(ft_rt_atoi(tok[2]));
	if (((int)(m->res.x) % 2) == 1)
		m->res.x += 1;
	if ((int)(m->res.y) % 2 == 1)
		m->res.y += 1;
	m->halfres = m->res.y * 0.5;
	if (!(m->z_buffer = malloc(sizeof(double) * m->res.x + 1)))
		ft_free_and_exit(m, "Failed to allocate z_buffer\n", -1);
	ft_memset(m->z_buffer, 0, m->res.x + 1);
	if (!(m->camplanexraydirsin_buffer = malloc(sizeof(double) * m->res.x + 1)))
		ft_free_and_exit(m, "Failed to allocate camplanexraydir_buffer\n", -1);
	ft_memset(m->camplanexraydirsin_buffer, 0, m->res.x + 1);
	return (SUCCESS);
}
