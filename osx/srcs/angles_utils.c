/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   angles_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lspiess <lspiess@student.42.us.org>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/22 03:27:05 by lspiess           #+#    #+#             */
/*   Updated: 2020/04/22 03:27:11 by lspiess          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

double		ft_setangle(double angle)
{
	if (angle < 0.0)
		return (360.0 + angle);
	else if (angle >= 360.0)
		return (angle - 360.0);
	else
		return (angle);
}
