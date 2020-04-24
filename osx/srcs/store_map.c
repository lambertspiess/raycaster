/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   store_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lspiess <lspiess@student.42.us.org>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/22 03:38:39 by lspiess           #+#    #+#             */
/*   Updated: 2020/04/22 21:15:13 by lspiess          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/*
** Add padding to the line so we have a rectangular array of strings
*/

static char		*ft_pad_line(char *line, int maxwid)
{
	char		*new;
	int			i;

	new = ft_mmalloc(maxwid + 1);
	i = 0;
	while (line[i])
	{
		new[i] = line[i];
		i++;
	}
	while (i < maxwid)
	{
		new[i] = ' ';
		i++;
	}
	free(line);
	return (new);
}

/*
** Reads the fd till the end of the map in order to know the number of rows.
** Then resets the fd to where it was previously.
*/

static void		ft_reset_fd(t_cub3d *m, int calls)
{
	int			i;
	char		*line;

	close(m->fd);
	m->fd = open(m->filename, O_RDONLY);
	i = 0;
	while (i < calls)
	{
		get_next_line(&line, m->fd);
		free(line);
		i++;
	}
}

static void		ft_allocate_map(t_cub3d *m, int wid, int rows)
{
	int			i;

	if ((m->map = ft_mmalloc(sizeof(char *) * (rows + 1))) == NULL)
		ft_free_and_exit(m, "Failed to allocate memory for rows\n", -1);
	i = 0;
	while (i < rows)
	{
		if ((*(m->map + i) = ft_mmalloc(sizeof(char) * (wid + 1))) == NULL)
			ft_free_and_exit(m, "Failed to allocate memory for columns\n", -1);
		i++;
	}
}

static void		ft_count_rows(int calls, t_cub3d *m)
{
	int			ret;
	char		*line;
	int			wid;

	m->rows = 1;
	while (1)
	{
		ret = get_next_line(&line, m->fd);
		wid = ft_strlen(line);
		if (wid > m->wid)
			m->wid = wid;
		if (line[0] == '0' || line[0] == '1' || line[0] == ' ')
			m->rows++;
		free(line);
		if (ret == 0)
			break ;
	}
	ft_reset_fd(m, calls);
	ft_allocate_map(m, m->wid, m->rows);
}

/*
**static void		ft_print_map(t_cub3d *m)
**{
**	int			i;
**	int			j;
**
**	i = 0;
**	while (i < m->rows)
**	{
**		j = 0;
**		ft_printf("row %d\t", i, *(m->map + i));
**		while (j < m->wid)
**		{
**			if (ft_strchr("NSEW", (*(m->map + i))[j]) == NULL)
**				ft_printf("%c", (*(m->map + i))[j]);
**			else
**				ft_printf(ANSI_COLOR_CYAN"%c"ANSI_COLOR_RESET,
**						(*(m->map + i))[j]);
**			j++;
**		}
**		ft_printf("|\n");
**		i++;
**	}
**	return ;
**}
*/

int				ft_store_map(char *line, int calls, t_cub3d *m)
{
	int			ret;
	int			stop;
	int			row_idx;

	ft_count_rows(calls, m);
	stop = 0;
	row_idx = 0;
	while (!stop)
	{
		if (!ft_check_single_line(line, m, 0))
		{
			ft_printf("Invalid line found in map : %s\n", line);
			free(line);
			ft_free_and_exit(m, "", -1);
		}
		m->map[row_idx++] = ft_pad_line(line, m->wid);
		ret = get_next_line(&line, m->fd);
		if (*line == '\0')
		{
			free(line);
			break ;
		}
	}
	return (ft_parse_map_columns(m));
}
