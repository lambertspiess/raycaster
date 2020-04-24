/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lspiess <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/22 17:30:20 by lspiess           #+#    #+#             */
/*   Updated: 2020/04/22 21:37:25 by lspiess          ###   ########.fr       */
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
# include <stdio.h> //REMOVE ME
# include <GLUT/glut.h>
# include "gnl.h"
# include "ft_printf.h"
# include "libft.h"
# include "defines.h"
# include "time.h"

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

typedef struct		s_xy {
	double			x;
	double			y;
}					t_xy;

typedef struct		s_color {
	int				r;
	int				g;
	int				b;
}					t_color;

typedef struct		s_cam {
	double			planestart;
	double			planexraydir;
	double			planewalldist;
}					t_cam;

typedef struct		s_keylog {
	unsigned char	mov_up;
	unsigned char	mov_down;
	unsigned char	mov_right;
	unsigned char	mov_left;
	unsigned char	look_right;
	unsigned char	look_left;
	unsigned char	look_up;
	unsigned char	look_down;
}					t_keylog;

typedef struct		s_image {
	void			*img_ptr;
	char			*img_data_addr;
	int				img_bpp;
	int				img_bpp_by8;
	int				img_line_size;
	int				endianess;
	int				width;
	int				height;
	double			x;
	double			y;
}					t_image;

typedef struct		s_textures {
//	t_image			sky;
	t_image			northwall;
	t_image			westwall;
	t_image			southwall;
	t_image			eastwall;
	t_image			pillar;
}					t_textures;

typedef struct		s_render {
	int				x;
	double			xraydir;
	t_cam			cam;
	double			camplanedir;
	double			xeuclidwalldist;
	int				side;
	double			camplanedist;
	double			xrayoffset;
	int				quarter;
	int				hmapstep;
	int				vmapstep;
	double			h0;
	double			v0;
	double			hstep;
	double			vstep;
	double			invsinmul;
	double			invcosmul;
	double			deltax;
	double			deltay;
}					t_render;

typedef struct		s_sprite {
	t_image			*img;
	t_xy			pos;
	int				firstx;
	double			firstxangle;
	int				lastx;
	double			lastxangle;
	int				centerx;
	double			radcenterangle;
	double			centerangle;
	double			deltax;
	double			deltay;
	double			dist;
	double			camplanedist;
	int				drawnspriteheight;
	int				drawnspritewid;
	int				xoffset;
	int				yoffset;
	int				rightoffset;
	int				begindrawnspritey;
	int				enddrawnspritey;
	double			spriteystep;
	int				begindrawnspritex;
	int				enddrawnspritex;
	double			spritexstep;
	t_xy			coord;
	double			begincoordy;
	int				ispritex;
	int				ispritey;
	int				spritepixidx;
	t_color			pixcolor;
}					t_sprite;

/*
** Main struct
*/

typedef struct		s_cub3d {
	int				fd;
	char			filename[100];
	pthread_t		thread_id;
	int				save_bmp;
/*
** minilibx utilities 
*/
	void			*mlx_id;
	void			*mlx_win_id;
	t_image			display;
/*
** textures, sprites and colors
*/
	t_color			ceilcol;
	t_textures		textures;
	double			*z_buffer;
	double			*camplanexraydirsin_buffer;
	t_image			*curtexp;
	int				winy;
	int				drawnwallheight;
	int				win_beginwall;
	int				win_endwall;
//	unsigned int	floorcolor;
	t_color			floorcol;
	t_xy			camplanevec;
/*
** display res, map and parsing utilities
*/
	t_xy			res;
	double			halfres;
	char			**map;
	int				rows;
	int				wid;
	int				ispos;
	t_xy			playerpos;
	double			playerdir;
	double			azimut;
	int				hitwalldir;
	int				spritesnb;
	t_sprite		**sprites;
	t_sprite		**sptab;
/*
** DDA utilities
*/
	t_render		s;
	double			maxraylength;
/*
** keys and movement 
*/
	t_keylog		keylog;
	unsigned char	is_change;
}					t_cub3d;

typedef struct		s_id_handler {
	char			*id;
	int				(*ft_handle_id)(t_cub3d *m, char **tokens);
}					t_id_handler;

void		ft_free_and_exit(t_cub3d *m, char *err_msg, int ret);

void		ft_store_pos(t_cub3d *m);
void		ft_parse(int ac, char **av, t_cub3d *m);
int			ft_is_unsigned_triplet(char *s);
int			ft_is_unsigned(char *s);
int			ft_rt_atoi(const char *str);
int			ft_extract_color(char *s, t_color *color);

int			ft_store_res(t_cub3d *m, char **tok);
int			ft_store_floor_color(t_cub3d *m, char **tok);
int			ft_store_ceiling_color(t_cub3d *m, char **tok);
int			ft_store_texture(t_cub3d *m, char **tok);
int			ft_check_single_line(char *s, t_cub3d *m, int i);
int			ft_store_map(char *line, int calls, t_cub3d *m);
int			ft_parse_map_columns(t_cub3d *m);
void		ft_store_sprites(t_cub3d *m, char **map, int i);

double		ft_setangle(double angle);
void		ft_initialize_mlx_image(t_cub3d *m);

void		ft_display_image(t_cub3d *m, t_image img);

void		ft_set_mlx_img_pixel(int x, int y, t_cub3d *m, t_color color);
void		ft_reset_sprite_collisions(t_sprite **sprites);
void		ft_render(t_cub3d *m);
void		ft_digital_differential_analizer(t_cub3d *m, t_xy pos,t_render *s);
void		ft_print_pixcolumn(t_cub3d *m, t_render *s);
void		ft_render_sprites(t_cub3d *m, t_sprite **sprites, t_sprite **tab);
void		ft_sprite_quicksort(t_sprite **tab, int low, int high);
void		ft_print_sprites(t_cub3d *m, t_sprite **tab);

int			ft_red_cross(int key, t_cub3d *m);
int			ft_keypress(int key, t_cub3d *m);
int			ft_keyrelease(int key, t_cub3d *m);
void		ft_scrape_wall(t_cub3d *m, double dirangle);
int			ft_handle_hooks(t_cub3d *m);

void		ft_compute_textures_uv_steps(t_cub3d *m);

typedef struct		s_bmp {
	char			header[54];
	unsigned int	pixcount;
	unsigned int	bufsize;
	unsigned int	total_size;
	unsigned int	pix_data_offset;
	unsigned int	header_size;
	int				imagewidth;
	int				imageheight;
	uint16_t		color_planes;
	uint16_t		bpp;
	int				compression;
	int				total_colors;
}					t_bmp;

void		ft_save_bmp(t_cub3d *m);

#endif
