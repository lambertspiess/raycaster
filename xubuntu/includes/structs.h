/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structs.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lspiess <lspiess@student.42.us.org>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/24 23:50:11 by lspiess           #+#    #+#             */
/*   Updated: 2020/04/24 23:53:06 by lspiess          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTS_H
# define STRUCTS_H
# include "cub3d.h"
# include <pthread.h>

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
	void			*mlx_id;
	void			*mlx_win_id;
	t_image			display;
	t_color			ceilcol;
	t_textures		textures;
	double			*z_buffer;
	double			*camplanexraydirsin_buffer;
	t_image			*curtexp;
	int				winy;
	int				drawnwallheight;
	int				win_beginwall;
	int				win_endwall;
	t_color			floorcol;

	t_xy			camplanevec;
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
	t_render		s;
	double			maxraylength;
	t_keylog		keylog;
	unsigned char	is_change;
}					t_cub3d;

typedef struct		s_id_handler {
	char			*id;
	int				(*ft_handle_id)(t_cub3d *m, char **tokens);
}					t_id_handler;

typedef struct		s_bmp {
	char			header[54];
	unsigned int	pixcount;
	unsigned int	bufsize;
	unsigned int	total_size;
	unsigned int	pix_data_offset;
	unsigned int	header_size;
	int				imagewidth;
	int				imageheight;
	short			color_planes;
	short			bpp;
	int				compression;
	int				total_colors;
}					t_bmp;

#endif
