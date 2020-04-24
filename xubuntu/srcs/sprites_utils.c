/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprites_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lspiess <lspiess@student.42.us.org>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/22 03:38:33 by lspiess           #+#    #+#             */
/*   Updated: 2020/04/22 18:35:31 by lspiess          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void			ft_reset_sprite_collisions(t_sprite **sprites)
{
	int				i;

	i = 0;
	while ((*(sprites + i)) != NULL)
	{
		(*(sprites + i))->firstx = -1;
		(*(sprites + i))->firstxangle = -1;
		(*(sprites + i))->lastx = -1;
		(*(sprites + i))->lastxangle = -1;
		i++;
	}
}

static void		ft_swap_ptr(t_sprite **a, t_sprite **b)
{
	t_sprite		*swap;

	swap = *a;
	*a = *b;
	*b = swap;
}

/*
** This function takes last element as pivot, sort the array around that
** element (smaller elems before, greater elems after).
*/

static int		ft_sprite_partition(t_sprite **tab, int low, int high)
{
	t_sprite		*pivot;
	int				i;
	int				j;

	pivot = *(tab + high);
	i = low - 1;
	j = low;
	while (j <= high - 1)
	{
		if ((*(tab + j))->dist > pivot->dist)
		{
			i++;
			ft_swap_ptr(&(*(tab + i)), &(*(tab + j)));
		}
		j++;
	}
	ft_swap_ptr(&(*(tab + i + 1)), &(*(tab + high)));
	return (i + 1);
}

/*
** low is first index, high is last index
*/

void			ft_sprite_quicksort(t_sprite **tab, int low, int high)
{
	int				pivot_idx;

	if (low < high)
	{
		pivot_idx = ft_sprite_partition(tab, low, high);
		ft_sprite_quicksort(tab, low, pivot_idx - 1);
		ft_sprite_quicksort(tab, pivot_idx + 1, high);
	}
}
