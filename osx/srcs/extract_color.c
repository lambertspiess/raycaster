/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   extract_color.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lspiess <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/16 20:45:33 by lspiess           #+#    #+#             */
/*   Updated: 2020/04/22 03:41:19 by lspiess          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	ft_check_colorvalues(t_color *color)
{
	if (color->r < 0 || color->r > 255)
		return (FAILURE);
	if (color->g < 0 || color->g > 255)
		return (FAILURE);
	if (color->b < 0 || color->b > 255)
		return (FAILURE);
	return (SUCCESS);
}

int			ft_extract_color(char *s, t_color *color)
{
	size_t		i;

	color->r = ft_rt_atoi(s);
	i = 0;
	while (s[i] && s[i] != ',')
		i++;
	i++;
	color->g = ft_rt_atoi(s + i);
	while (s[i] && s[i] != ',')
		i++;
	i++;
	color->b = ft_rt_atoi(s + i);
	if (ft_check_colorvalues(color) == FAILURE)
		return (FAILURE);
	return (SUCCESS);
}
