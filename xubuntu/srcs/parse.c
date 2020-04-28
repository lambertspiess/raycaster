/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lspiess <lspiess@student.42.us.org>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/22 03:37:37 by lspiess           #+#    #+#             */
/*   Updated: 2020/04/22 23:36:45 by lspiess          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static t_id_handler		g_idtab[] = {
	{"R", &ft_store_res},
	{"F", &ft_store_floor_color},
	{"C", &ft_store_ceiling_color},
	{"NO", &ft_store_texture},
	{"SO", &ft_store_texture},
	{"WE", &ft_store_texture},
	{"EA", &ft_store_texture},
	{"S", &ft_store_texture},
	{NULL, NULL},
};

static int		ft_find_handler(t_cub3d *m, char **tokens, size_t tabidx,
									int ret)
{
	while (g_idtab[tabidx].id != NULL)
	{
		if (ft_strequ(tokens[0], g_idtab[tabidx].id))
		{
			ret = g_idtab[tabidx].ft_handle_id(m, tokens);
			break ;
		}
		tabidx++;
	}
	ft_free_tokens(&tokens);
	if (g_idtab[tabidx].id == NULL)
	{
		ft_printf("parsing handler not found\n");
		return (FAILURE);
	}
	if (ret == FAILURE)
	{
		return (FAILURE);
	}
	return (SUCCESS);
}

/*
** Tokenize the line and checks if the first token is a valid identifier.
** If so call the corresponding parsing routine from the function pointer
** table
*/

static int		ft_parse_line(char *s, t_cub3d *m)
{
	size_t			tabidx;
	char			**tokens;
	int				ret;

	tabidx = 0;
	ret = SUCCESS;
	if (!(tokens = ft_split_whitespace(s)))
		return (FAILURE);
	if (tokens[0] == NULL)
	{
		ft_free_tokens(&tokens);
		return (SUCCESS);
	}
	return (ft_find_handler(m, tokens, tabidx, ret));
}

/*
** Call a getline-type routine in a loop to read a scene descriptor file
** line by line until end of file. Verify that map lines are coherent and store
** them in an array of pointers to char.
*/

static void		ft_read_scene_file(t_cub3d *m)
{
	int				ret;
	char			*line;
	int				calls;

	calls = 0;
	while (1)
	{
		ret = get_next_line(&line, m->fd);
		if (ret == 0 && *line == '\0')
		{
			free(line);
			break ;
		}
		calls++;
		if (line[0] == '1' || line[0] == '0' || line[0] == ' ')
			ft_store_map(line, calls, m);
		else if (ft_parse_line(line, m) == FAILURE)
		{
			ft_printf("Error\nInvalid line in scene file :\n%s\n", line);
			free(line);
			ft_free_and_exit(m, "Exiting\n", -1);
		}
		if (ret <= 0)
			break ;
	}
}

static int		ft_check_extension(char *s)
{
	int				i;

	i = 0;
	while (s[i])
		i++;
	i--;
	if (s[i--] != 'b')
		return (0);
	if (i < 0)
		return (0);
	if (s[i--] != 'u')
		return (0);
	if (i < 0)
		return (0);
	if (s[i] != 'c')
		return (0);
	return (1);
}

void			ft_parse(int ac, char **av, t_cub3d *m)
{
	m->fd = open(av[1], O_RDONLY);
	if (m->fd < 0 || ac == 1 || ac > 3)
		ft_free_and_exit(m, "Error,\nUsage : ./cub3d map.cub [--save]\n", -1);
	if (ft_check_extension(av[1]) == 0)
		ft_free_and_exit(m, "Error,\nmap file needs \".cub\" extension\n", -1);
	ft_strcpy(&(m->filename[0]), av[1]);
	ft_read_scene_file(m);
	ft_store_pos(m);
	m->maxraylength = sqrt(pow(m->rows + 1, 2) * pow(m->wid + 1, 2));
	m->s.xrayoffset = FOV / m->res.x;
	if (!m->textures.northwall.img_ptr || !m->textures.westwall.img_ptr \
		|| !m->textures.eastwall.img_ptr || !m->textures.southwall.img_ptr \
		|| !m->textures.pillar.img_ptr)
		ft_free_and_exit(m, "Error,\nmissing texture in description\n", -1);
	ft_store_sprites(m, m->map, 0);
}
