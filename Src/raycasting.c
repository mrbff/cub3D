/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbozzi <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/03 11:33:45 by mbozzi            #+#    #+#             */
/*   Updated: 2023/04/07 14:41:41 by mbozzi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cube3D.h"

static int	y_tex(int i, int col_hgt)
{
	int	r;

	r = ((int)(((double)i / (double)col_hgt) * IMG_HGT));
	return (r % IMG_HGT);
}

static void	drawline(t_cube *cb, int col)
{
	int	col_hgt;
	int	c_up;
	int	c_down;
	int	index;

	col_hgt = abs((int)(WIN_HGT / cb->ray.wall_dist));
	c_up = 0;
	c_down = 0;
	if (col_hgt > WIN_HGT)
	{
		index = col;
		c_up = (col_hgt - WIN_HGT) / 2;
		c_down = c_up + 1;
	}
	else
		index = ((WIN_HGT - col_hgt) / 2) * WIN_WID;
	while (c_up < (col_hgt - c_down))
	{
		wall_selector(cb, col, index, y_tex(c_up, col_hgt));
		index += WIN_WID;
		c_up++;
	}
}

static void	ray_dist(t_cube *cb, int x, int y)
{
	while (cb->map.mat[x][y] != '1')
	{
		if (cb->ray.dist.x < cb->ray.dist.y)
		{
			cb->ray.side = 0;
			cb->ray.dist.x += cb->ray.delta.x;
			x += cb->ray.step.x;
		}
		else
		{
			cb->ray.side = 1;
			cb->ray.dist.y += cb->ray.delta.y;
			y += cb->ray.step.y;
		}
	}
	if (cb->ray.side == 0)
		cb->ray.wall_dist = fabs((x - cb->p_pos.x \
	+ (1 - cb->ray.step.x) / 2) / cb->ray.dir.x);
	else
		cb->ray.wall_dist = fabs((y - cb->p_pos.y \
	+ (1 - cb->ray.step.y) / 2) / cb->ray.dir.y);
	offset(cb, x, y);
}

static void	ray_dir(t_cube *cb, int x, int y)
{
	double	garbage;

	cb->ray.step.y = 1;
	cb->ray.step.x = 1;
	if (cb->ray.dir.x < 0)
	{
		cb->ray.step.x = -1;
		cb->ray.dist.x = (modf(cb->ray.pos.x, &garbage)) * cb->ray.delta.x;
	}
	else
		cb->ray.dist.x = (x - cb->ray.pos.x + 1) * cb->ray.delta.x;
	if (cb->ray.dir.y < 0)
	{
		cb->ray.step.y = -1;
		cb->ray.dist.y = (modf(cb->ray.pos.y, &garbage)) * cb->ray.delta.y;
	}
	else
		cb->ray.dist.y = (y - cb->ray.pos.y + 1) * cb->ray.delta.y;
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
		x = (int)(cb->p_pos.x);
		y = (int)(cb->p_pos.y);
		cb->ray.pos.x = cb->p_pos.x;
		cb->ray.pos.y = cb->p_pos.y;
		camera = 2 * col / (double)WIN_WID - 1;
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
