/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbozzi <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/03 11:33:45 by mbozzi            #+#    #+#             */
/*   Updated: 2023/04/05 17:45:51 by mbozzi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cube3D.h"

void	put_floor_sky(t_cube *cb)
{
	int	i;
	int	col;

	i = -1;
 	while (++i < WIN_HGT / 2)
	{
		col = -1;
		while (++col < WIN_WID)
			ft_draw_pixels(col, i, 0x0000FFFF, cb);
	}
	while (++i < WIN_HGT)
	{
		col = -1;
		while (++col < (WIN_WID))
			ft_draw_pixels(col, i, 0x00606060, cb);
	}
}

void	drawline(t_cube *cb, int col)
{
	int	col_hgt;
	int	cropup;
	int	cropdown;
	int	index;
	int	i;

	cropup = 0;
	cropdown = 0;
	col_hgt = abs((int)(WIN_HGT / cb->ray.wall_dist));
	if (col_hgt > WIN_HGT)
	{
		index = col;
		cropup = (col_hgt - WIN_HGT) / 2;
		cropdown = cropup + 1;
	}
	else
		index = ((WIN_HGT - col_hgt) / 2) * WIN_WID;
	i = cropup;
	while (i < (col_hgt - cropdown))
	{
		ft_draw_pixels(col, (index / WIN_WID), ft_get_pixels(col, (index / WIN_WID), cb->tex1), cb);
		index += WIN_WID;
		i++;
	}
}

void	ray_dist(t_cube *cb, int x, int y)
{
	while (cb->map.mat[x][y] != '1')
	{
		if (cb->ray.dist.x < cb->ray.dist.y)
		{
			cb->ray.dist.x += cb->ray.delta.x;
			x += cb->ray.step.x;
			cb->ray.side = 0;
		}
		else
		{
			cb->ray.dist.y += cb->ray.delta.y;
			y += cb->ray.step.y;
			cb->ray.side = 1;
		}
	}
	if (cb->ray.side == 0)
		cb->ray.wall_dist = fabs((x - cb->p_pos.x \
	+ (1 - cb->ray.step.x) / 2) / cb->ray.dir.x);
	else
		cb->ray.wall_dist = fabs((y - cb->p_pos.y \
	+ (1 - cb->ray.step.y) / 2) / cb->ray.dir.y);
}

void	ray_dir(t_cube *cb, int x, int y)
{
	if (cb->ray.dir.x < 0)
	{
		cb->ray.step.x = -1;
		cb->ray.dist.x = (cb->ray.pos.x - x) * cb->ray.delta.x;
	}
	else
	{
		cb->ray.step.x = 1;
		cb->ray.dist.x = (x - cb->ray.pos.x + 1) * cb->ray.delta.x;
	}
	if (cb->ray.dir.y < 0)
	{
		cb->ray.step.y = -1;
		cb->ray.dist.y = (cb->ray.pos.y - y) * cb->ray.delta.y;
	}
	else
	{
		cb->ray.step.y = 1;
		cb->ray.dist.y = (y - cb->ray.pos.y + 1) * cb->ray.delta.y;
	}
}

void	raycasting(t_cube *cb)
{
	double	camera;
	int		col;
	int		x;
	int		y;

	col = -1;
	put_floor_sky(cb);
	while (++col < WIN_WID)
	{
		x = (int)cb->p_pos.x;
		y = (int)cb->p_pos.y;
		camera = 2 * col / (double)WIN_WID - 1;
		cb->ray.pos.x = cb->p_pos.x;
		cb->ray.pos.y = cb->p_pos.y;
		cb->ray.dir.x = cb->p_dir.x + cb->cam.x * camera;
		cb->ray.dir.y = cb->p_dir.y + cb->cam.y * camera;
		cb->ray.delta.x = delta(cb, 'x');
		cb->ray.delta.y = delta(cb, 'y');
		ray_dir(cb, x, y);
		ray_dist(cb, x, y);
		drawline(cb, col);
	}
	mlx_put_image_to_window(cb->mlx, cb->mlx_win,
		cb->img->mlx_img, 0, 0);
}
