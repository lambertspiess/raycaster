/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map_columns.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lspiess <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/04 20:13:17 by lspiess           #+#    #+#             */
/*   Updated: 2020/04/22 21:00:02 by lspiess          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	ft_handle_error(t_cub3d *m, int col, int row, char *errmsg)
{
	int			i;
	int			j;

	ft_printf("Error in column %d row %d : %s\n", col, row, errmsg);
	i = 0;
	while (i < m->rows)
	{
		j = 0;
		while (j < m->wid)
		{
			if (j != col)
				ft_printf("%c", (*(m->map + i))[j]);
			else
				ft_printf(ANSI_COLOR_RED"%c"ANSI_COLOR_RESET, \
														(*(m->map + i))[j]);
			j++;
		}
		ft_printf("\n");
		i++;
	}
	ft_free_and_exit(m, "Exiting\n", -1);
}

static void	ft_check_if_col_vertically_bound(t_cub3d *m, int *row, int col)
{
	if (*row == 0)
		ft_handle_error(m, col, *row, "zero at the top of the map");
	if ((*(m->map + *row - 1))[col] == ' ')
		ft_handle_error(m, col, *row, "space directly above zero");
	(*row)++;
	while ((*row) < m->rows)
	{
		if ((*(m->map + *row))[col] == '1')
			return ;
		if ((*(m->map + *row))[col] == ' ')
			ft_handle_error(m, col, *row, "space directly below zero");
		(*row)++;
	}
	ft_handle_error(m, *row, col, "zero at the bottom of the map");
}

int			ft_parse_map_columns(t_cub3d *m)
{
	int			row;
	int			col;

	col = 0;
	while (col < m->wid)
	{
		row = 0;
		while (row < m->rows)
		{
			if (ft_strchr("02NSEW", (*(m->map + row))[col]) != NULL)
				ft_check_if_col_vertically_bound(m, &row, col);
			else
				row++;
		}
		col++;
	}
	if (m->ispos == 0)
		ft_free_and_exit(m, "No player position found\n", -1);
	return (1);
}
