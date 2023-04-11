/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbozzi <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/31 18:16:05 by mbozzi            #+#    #+#             */
/*   Updated: 2023/04/11 15:18:54 by mbozzi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "./minilibx-linux/mlx.h"
# include "Src/MyLib/mylib.h"
# include <unistd.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <fcntl.h>
# include <stdlib.h>
# include <stdio.h>
# include <string.h>
# include <math.h>

//			WIN & IMG		//

# define WIN_WID 1200
# define WIN_HGT 720
# define IMG_WID 256
# define IMG_HGT 256
# define FOV 0.66

//			KEYS			//

# define ESC 65307
# define KEY_W 119
# define KEY_S 115
# define KEY_A 97
# define KEY_D 100
# define ARROW_LETF 65361
# define ARROW_RIGHT 65363

//			MOVEMENT		//

# define MOVSPEED 0.1
# define ROTSPEED 0.05

//			STRUCTS			//

typedef struct s_vector
{
	double		x;
	double		y;
}				t_vector;

typedef struct s_ray {
	t_vector	pos;
	t_vector	dir;
	t_vector	dist;
	t_vector	step;
	t_vector	delta;
	double		wall_dist;
	int			side;
	int			offset;
	double		wall;
}				t_ray;

typedef struct s_matrix {
	char		**mat;
	char		*line;
	int			lines;
	int			fd;
	int			x;
	int			y;
}				t_matrix;

typedef struct s_img
{
	void		*mlx_img;
	char		*data;
	int			bits_per_pixel;
	int			line_length;
	int			endian;
}				t_img;

typedef struct s_cube
{
	t_img		*img;
	t_matrix	map;
	t_vector	p_pos;
	t_vector	p_dir;
	t_vector	cam;
	t_ray		ray;
	t_img		**tex;
	void		*mlx;
	void		*mlx_win;
	char		*path;
	char		**tex_path;
	int			floor;
	int			ceil;
	char		in_dir;
}				t_cube;

//				MAP				//

int				ft_matrix(t_cube *cb, char *path);
int				check_map(t_cube *cb, char *path);
int				not_fenced(char **map, int x, int y);

//				GAME			//

int				ft_key_hook(int keycode, t_cube *cb);
void			raycasting(t_cube *cb);
void			put_floor_sky(t_cube *cb);
void			ft_draw_pixels(int x, int y, int color, t_cube *cb);
void			wall_selector(t_cube *cb, int col, int index, int y);
void			offset(t_cube *cb, int x, int y);
int				texture_init(t_cube *cb);

//				UTILS			//

int				ft_destroy(t_cube *ptr);
unsigned int	ft_color_converter(int r, int g, int b);
double			delta(t_cube *cb, char flag);
int				ft_get_pixels(int x, int y, t_img *img);
char			*extr_num(char	*s);
int				ft_access(t_cube *cb, char *path);

#endif