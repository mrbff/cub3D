/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbozzi <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/03 11:33:45 by mbozzi            #+#    #+#             */
/*   Updated: 2023/04/04 16:56:12 by mbozzi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cube3D.h"

void	put_floor_sky(t_cube **cb)
{
	int	i;
	int	col;

	i = -1;
	while (++i < WIN_HGT / 2)
	{
		col = -1;
		while (++col < WIN_WID)
			ft_draw_pixels(col, i, 0x0000FFFF, *cb);
	}
	while (++i < WIN_HGT)
	{
		col = -1;
		while (++col < (WIN_WID))
			ft_draw_pixels(col, i, 0x00606060, *cb);
	}
}

void	drawcol(t_cube **cb, int col)
{
	int	start;
	int	end;
	int	height;

	height = (int)(WIN_HGT / (*cb)->ray.wall_dist);
	start = -height / 2 + WIN_HGT / 2;
	if (start < 0)
		start = 0;
	end = height / 2 + WIN_HGT / 2;
	if (end >= WIN_HGT)
		end = WIN_HGT - 1;
	while (start <= end)
	{
		ft_draw_pixels(col, start, 0xFFFF0000, *cb);
		start++;
	}
}

void	ray_dist(t_cube **cb, int x, int y)
{
	while ((*cb)->map.mat[x][y] == '0' || (*cb)->map.mat[x][y] == 'N')
	{
		if ((*cb)->ray.distx < (*cb)->ray.disty)
		{
			(*cb)->ray.distx += (*cb)->ray.deltax;
			x += (*cb)->ray.stepx;
			(*cb)->ray.side = 0;
		}
		else
		{
			(*cb)->ray.disty += (*cb)->ray.deltay;
			y += (*cb)->ray.stepy;
			(*cb)->ray.side = 1;
		}
	}
	if ((*cb)->ray.side == 0)
		(*cb)->ray.wall_dist = (x - (*cb)->player.pos.x
				+ (1 - (*cb)->ray.stepx) / 2) / (*cb)->ray.dir.x;
	else
		(*cb)->ray.wall_dist = (y -(*cb)->player.pos.y
				+ (1 - (*cb)->ray.stepy) / 2) / (*cb)->ray.dir.y;
}

void	ray_dir(t_cube **cb, int x, int y)
{
	if ((*cb)->ray.dir.x < 0)
	{
		(*cb)->ray.stepx = -1;
		(*cb)->ray.distx = ((*cb)->player.pos.x - x) * (*cb)->ray.deltax;
	}
	else
	{
		(*cb)->ray.stepx = 1;
		(*cb)->ray.distx = (x - (*cb)->player.pos.x + 1) * (*cb)->ray.deltax;
	}
	if ((*cb)->ray.dir.y < 0)
	{
		(*cb)->ray.stepy = -1;
		(*cb)->ray.disty = ((*cb)->player.pos.y - y) * (*cb)->ray.deltay;
	}
	else
	{
		(*cb)->ray.stepy = 1;
		(*cb)->ray.disty = (y - (*cb)->player.pos.y + 1) * (*cb)->ray.deltay;
	}
}

void	raycasting(t_cube **cb)
{
	int	col;
	int	x;
	int	y;

	col = -1;
	put_floor_sky(cb);
	while (++col < WIN_WID)
	{
		(*cb)->cam.x = 2 * col / (double)WIN_WID - 1;
		(*cb)->ray.pos.x = -0.5;
		(*cb)->ray.pos.y = 0;
		(*cb)->ray.dir.x = (*cb)->ray.pos.x + 0 * (*cb)->cam.x;
		(*cb)->ray.dir.y = (*cb)->ray.pos.y + FOV * (*cb)->cam.x;
		(*cb)->ray.deltax = fabs(1 / (*cb)->ray.dir.x);
		(*cb)->ray.deltay = fabs(1 / (*cb)->ray.dir.y);
		x = (int)(*cb)->player.pos.x;
		y = (int)(*cb)->player.pos.y;
		ray_dir(cb, x, y);
		ray_dist(cb, x, y);
		drawcol(cb, col);
	}
	mlx_put_image_to_window((*cb)->mlx, (*cb)->mlx_win,
		(*cb)->img->mlx_img, 0, 0);
}
