/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lspiess <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/22 17:30:20 by lspiess           #+#    #+#             */
/*   Updated: 2020/04/24 23:53:39 by lspiess          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include <mlx.h>
# include <pthread.h>
# include <sys/types.h>
# include <fcntl.h>
# include <unistd.h>
# include <math.h>
# include <stdio.h>
# include "gnl.h"
# include "ft_printf.h"
# include "libft.h"
# include "defines.h"
# include "time.h"
# include "stdio.h"
# include "./structs.h"

# define RAD_MUL 0.01745329251994329576
# define DEG_MUL 57.2957795
# define FOV 66
# define HALFOV 33

# define NORTH_EAST 1
# define NORTH_WEST 2
# define SOUTH_WEST 3
# define SOUTH_EAST 4
# define NORTH 5
# define EAST 6
# define SOUTH 7
# define WEST 8

# define MAP_DWELLERS "02NSEW"

# define ORAN 16744448
# define MORAN 666633333
# define NORTHCOL 16754448
# define EASTCOL 36754448
# define SOUTHCOL 56754448
# define WESTCOL 76754448
# define CEILCOLOR 204000000
# define FLOORCOLOR 502142110

# define TEX_NUMBER 5

void				ft_free_and_exit(t_cub3d *m, char *err_msg, int ret);

void				ft_store_pos(t_cub3d *m);
void				ft_parse(int ac, char **av, t_cub3d *m);
int					ft_is_unsigned_triplet(char *s);
int					ft_is_unsigned(char *s);
int					ft_rt_atoi(const char *str);
int					ft_extract_color(char *s, t_color *color);

int					ft_store_res(t_cub3d *m, char **tok);
int					ft_store_floor_color(t_cub3d *m, char **tok);
int					ft_store_ceiling_color(t_cub3d *m, char **tok);
int					ft_store_texture(t_cub3d *m, char **tok);
int					ft_check_single_line(char *s, t_cub3d *m, int i);
int					ft_store_map(char *line, int calls, t_cub3d *m);
int					ft_parse_map_columns(t_cub3d *m);
void				ft_store_sprites(t_cub3d *m, char **map, int i);

double				ft_setangle(double angle);
void				ft_initialize_mlx_image(t_cub3d *m);

void				ft_display_image(t_cub3d *m, t_image img);

void				ft_set_mlx_img_pixel(int x, int y, t_cub3d *m, \
					t_color color);
void				ft_reset_sprite_collisions(t_sprite **sprites);
void				ft_render(t_cub3d *m);
void				ft_digital_differential_analizer(t_cub3d *m, t_xy pos, \
					t_render *s);
void				ft_print_pixcolumn(t_cub3d *m, t_render *s);
void				ft_render_sprites(t_cub3d *m, t_sprite **sprites, \
					t_sprite **tab);
void				ft_sprite_quicksort(t_sprite **tab, int low, int high);
void				ft_print_sprites(t_cub3d *m, t_sprite **tab);

int					ft_minimize(int key, t_cub3d *m);
int					ft_red_cross(int key, t_cub3d *m);
int					ft_keypress(int key, t_cub3d *m);
int					ft_keyrelease(int key, t_cub3d *m);
void				ft_scrape_wall(t_cub3d *m, double dirangle);
int					ft_handle_hooks(t_cub3d *m);

void				ft_compute_textures_uv_steps(t_cub3d *m);

void				ft_save_bmp(t_cub3d *m);

#endif
