/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mov_scrape_wall.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lspiess <lspiess@student.42.us.org>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/22 15:56:10 by lspiess           #+#    #+#             */
/*   Updated: 2020/04/22 16:04:42 by lspiess          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void		first(t_cub3d *m)
{
	if ((*(m->map + (int)(m->playerpos.y - 0.1)))[(int)(m->playerpos.x)] \
			== '0')
		m->playerpos.y -= 0.1;
	if ((*(m->map + (int)(m->playerpos.y)))[(int)(m->playerpos.x + 0.1)] \
			== '0')
		m->playerpos.x += 0.1;
}

static void		second(t_cub3d *m)
{
	if ((*(m->map + (int)(m->playerpos.y - 0.1)))[(int)(m->playerpos.x)] \
			== '0')
		m->playerpos.y -= 0.1;
	if ((*(m->map + (int)(m->playerpos.y)))[(int)(m->playerpos.x - 0.1)] \
			== '0')
		m->playerpos.x -= 0.1;
}

static void		third(t_cub3d *m)
{
	if ((*(m->map + (int)(m->playerpos.y + 0.1)))[(int)(m->playerpos.x)] \
			== '0')
		m->playerpos.y += 0.1;
	if ((*(m->map + (int)(m->playerpos.y)))[(int)(m->playerpos.x - 0.1)] \
			== '0')
		m->playerpos.x -= 0.1;
}

static void		fourth(t_cub3d *m)
{
	if ((*(m->map + (int)(m->playerpos.y + 0.1)))[(int)(m->playerpos.x)] \
			== '0')
		m->playerpos.y += 0.1;
	if ((*(m->map + (int)(m->playerpos.y)))[(int)(m->playerpos.x + 0.1)] \
			== '0')
		m->playerpos.x += 0.1;
}

void			ft_scrape_wall(t_cub3d *m, double dirangle)
{
	if (0 < dirangle && dirangle < 90)
		first(m);
	else if (90 < dirangle && dirangle < 180)
		second(m);
	else if (180 < dirangle && dirangle < 270)
		third(m);
	else if (270 < dirangle && dirangle < 360)
		fourth(m);
}
