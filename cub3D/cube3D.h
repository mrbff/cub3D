/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cube3D.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbozzi <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/31 18:16:05 by mbozzi            #+#    #+#             */
/*   Updated: 2023/03/31 19:05:53 by mbozzi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUBE3D_H
# define CUBE3D_H

# include "./minilibx-linux/mlx.h"
# include <unistd.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <fcntl.h>
# include <stdlib.h>
# include <stdio.h>
# include <string.h>

# define WIN_WIDTH 1200
# define WIN_HEIGHT 720
# define ESC 65307
# define ARROW_UP 119
# define ARROW_DOWN 115
# define ARROW_LEFT 97
# define ARROW_RIGHT 100


typedef struct s_img
{
	void	*mlx_img;
	char	*data;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}	t_img;

typedef struct s_cube
{
	t_img	*img;
	void	*mlx_win;
	void	*mlx_ptr;
}	t_cube;

#endif