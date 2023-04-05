/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbozzi <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/03 11:33:45 by mbozzi            #+#    #+#             */
/*   Updated: 2023/04/05 13:08:23 by mbozzi           ###   ########.fr       */
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

void	drawline(t_cube **cb, int col)
{
	int	col_hgt;
	int	cropup;
	int	cropdown;
	int	index;

	cropup = 0;
	cropdown = 0;
	col_hgt = abs((int)(WIN_HGT / (*cb)->ray.wall_dist));
	if (col_hgt > WIN_HGT)
	{
		index = col;
		cropup = (col_hgt - WIN_HGT) / 2;
		cropdown = cropup + 1;
	}
	else
		index = (WIN_HGT - col_hgt) / 2;
	while (cropup < (col_hgt - cropdown))
	{
		ft_draw_pixels(col, index, 0xFFFF0000, *cb);
		cropup++;
		index++;
	}
}

void	ray_dist(t_cube **cb, int x, int y)
{
	while ((*cb)->map.mat[x][y] == '0' || (*cb)->map.mat[x][y] == 'N')
	{
		if ((*cb)->ray.dist.x < (*cb)->ray.dist.y)
		{
			(*cb)->ray.dist.x += (*cb)->ray.deltax;
			x += (*cb)->ray.step.x;
			(*cb)->ray.side = 0;
		}
		else
		{
			(*cb)->ray.dist.y += (*cb)->ray.deltay;
			y += (*cb)->ray.step.y;
			(*cb)->ray.side = 1;
		}
	}
	if ((*cb)->ray.side == 0)
		(*cb)->ray.wall_dist = (x - (*cb)->player.pos.x
				+ (1 - (*cb)->ray.step.x) / 2) / (*cb)->ray.dir.x;
	else
		(*cb)->ray.wall_dist = (y -(*cb)->player.pos.y
				+ (1 - (*cb)->ray.step.y) / 2) / (*cb)->ray.dir.y;
}

void	ray_dir(t_cube **cb, int x, int y)
{
	if ((*cb)->ray.dir.x < 0)
	{
		(*cb)->ray.step.x = -1;
		(*cb)->ray.dist.x = ((*cb)->player.pos.x - x) * (*cb)->ray.deltax;
	}
	else
	{
		(*cb)->ray.step.x = 1;
		(*cb)->ray.dist.x = (x - (*cb)->player.pos.x + 1) * (*cb)->ray.deltax;
	}
	if ((*cb)->ray.dir.y < 0)
	{
		(*cb)->ray.step.y = -1;
		(*cb)->ray.dist.y = ((*cb)->player.pos.y - y) * (*cb)->ray.deltay;
	}
	else
	{
		(*cb)->ray.step.y = 1;
		(*cb)->ray.dist.y = (y - (*cb)->player.pos.y + 1) * (*cb)->ray.deltay;
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
		x = (int)(*cb)->player.pos.x;
		y = (int)(*cb)->player.pos.y;
		(*cb)->cam.x = 2 * col / (double)WIN_WID - 1;
		(*cb)->ray.pos.x = -1;
		(*cb)->ray.pos.y = 0;
		(*cb)->ray.dir.x = (*cb)->ray.pos.x + 0 * (*cb)->cam.x;
		(*cb)->ray.dir.y = (*cb)->ray.pos.y + FOV * (*cb)->cam.x;
		(*cb)->ray.deltax = fabs(1 / (*cb)->ray.dir.x);
		(*cb)->ray.deltay = fabs(1 / (*cb)->ray.dir.y);
		ray_dir(cb, x, y);
		ray_dist(cb, x, y);
		drawline(cb, col);
	}
	mlx_put_image_to_window((*cb)->mlx, (*cb)->mlx_win,
		(*cb)->img->mlx_img, 0, 0);
}
