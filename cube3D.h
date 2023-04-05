/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cube3D.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbozzi <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/31 18:16:05 by mbozzi            #+#    #+#             */
/*   Updated: 2023/04/05 13:07:47 by mbozzi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUBE3D_H
# define CUBE3D_H

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

# define WIN_WID 1200
# define WIN_HGT 720
# define FOV 0.66

# define ESC 65307
# define ARROW_UP 119
# define ARROW_DOWN 115
# define ARROW_LEFT 97
# define ARROW_RIGHT 100

# define PI 3.14159
# define MOVSPEED 0.1
# define ROTSPEED 0.05

/* # define EAST 0
# define NORD PI / 2
# define WEST PI
# define SUD  PI / 2 * 3
 */

typedef struct s_color {
	int			r;
	int			g;
	int			b;
}				t_color;

typedef struct s_dir
{
	double		x;
	double		y;
}				t_dir;

typedef struct s_pos
{
	double		x;
	double		y;
}				t_pos;

typedef struct s_ray {
	t_pos		pos;
	t_dir		dir;
	t_pos		dist;
	t_dir		step;
	double		deltax;
	double		deltay;
	double		wall_dist;
	int			side;
}				t_ray;

typedef struct s_camera {
	t_pos		pos;
	t_dir		dir;
	double		x;
	double		y;
}				t_camera;

typedef struct s_player {
	t_pos		pos;
	double		dir;
}				t_player;

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
	void	*mlx_img;
	char	*data;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}				t_img;

typedef struct s_cube
{
	t_img		*img;
	void		*mlx_win;
	void		*mlx;
	t_matrix	map;
	char		*path;
	t_player	player;
	t_camera	cam;
	t_ray		ray;
}				t_cube;

//				MAP				//

int				ft_matrix(t_cube **cb, char *path);
int				check_map(t_cube **cb, char *path);

//				GAME			//

int				ft_key_hook(int keycode, t_cube **cb);
void			raycasting(t_cube **cb);
void			put_floor_sky(t_cube **cb);
void			ft_draw_pixels(int x, int y, int color, t_cube *cb);

//				UTILS			//

int				ft_destroy(t_cube *ptr);
unsigned int	ft_color_converter(int r, int g, int b);

#endif