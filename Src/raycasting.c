/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbozzi <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/03 11:33:45 by mbozzi            #+#    #+#             */
/*   Updated: 2023/04/03 17:32:34 by mbozzi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cube3D.h"

void	put_floor_sky(t_cube **cb)
{
	int i = -1;
	int col;
	while (++i < WIN_HGT / 2)
	{
		col = -1;
		while (++col < WIN_WID)
			mlx_pixel_put((*cb)->mlx, (*cb)->mlx_win, col, i, 0x0000FFFF);
	}
	while (++i < WIN_HGT)
	{
		col = -1;
		while (++col < (WIN_WID))
			mlx_pixel_put((*cb)->mlx, (*cb)->mlx_win, col, i, 0x00606060);
	}
}

void	drawcol(t_cube **cb, int col)
{
	int col_h;
	int cropup;
	int cropdown;
	int index;
	int i;

	col_h = abs(WIN_HGT / (int)(*cb)->ray.wall_dist);
	cropup = 0;
	cropdown = 0;
	index = 0;

	if (col_h > WIN_HGT)
	{
		index = col;
		cropup = (col_h - WIN_HGT) / 2;
		cropdown = cropup + 1;
	}
	else
	{
		index = col + ((WIN_HGT - col_h) / 2) * WIN_WID;
		cropup = 0;
		cropdown = 0;
	}
	i = cropup;
	while (i < (col_h -cropdown))
	{
		mlx_pixel_put((*cb)->mlx, (*cb)->mlx_win, i, index, 0xFFFF0000);
		//index += WIN_WID;
		i++;
	}
}

void	raycasting(t_cube **cb)
{
	int	col;
	
	col = -1;
	put_floor_sky(cb);
	while (++col < WIN_WID)
	{
		(*cb)->cam.x = 2 * col / (double)WIN_WID - 1;
		(*cb)->ray.pos.x = (*cb)->player.pos.x;
		(*cb)->ray.pos.y = (*cb)->player.pos.y;
		(*cb)->ray.dir.x = -1 + (0 * (*cb)->cam.x);
		(*cb)->ray.dir.y = 0 + (FOV * (*cb)->cam.x);
		(*cb)->ray.deltax = fabs(1 / (*cb)->ray.dir.x);
		(*cb)->ray.deltay = fabs(1 / (*cb)->ray.dir.y);
		if ((*cb)->ray.dir.x < 0)
		{
			(*cb)->ray.stepx = -1;
			(*cb)->ray.distx = ((*cb)->ray.pos.x - (int)(*cb)->player.pos.x) * (*cb)->ray.deltax;
		}
		else
		{
			(*cb)->ray.stepx = 1;
			(*cb)->ray.distx = ((int)(*cb)->player.pos.x + 1 - (*cb)->ray.pos.x) * (*cb)->ray.deltax;
		}
		if ((*cb)->ray.dir.y < 0)
		{
			(*cb)->ray.stepy = -1;
			(*cb)->ray.disty = ((*cb)->ray.pos.y - (int)(*cb)->player.pos.y) * (*cb)->ray.deltay;
		}
		else
		{
			(*cb)->ray.stepy = 1;
			(*cb)->ray.disty = ((int)(*cb)->player.pos.y + 1 - (*cb)->ray.pos.y) * (*cb)->ray.deltay;
		}
		while ((*cb)->map.mat[(int)(*cb)->player.pos.x][(int)((*cb)->player.pos.y) * ft_strlen((*cb)->map.mat[0]) ] == 0)
		{
			if ((*cb)->ray.distx < (*cb)->ray.disty)
			{
				(*cb)->ray.distx += (*cb)->ray.deltax;
				(*cb)->player.pos.x += (*cb)->ray.stepx;
				(*cb)->ray.side = 0;
			}
			else
			{
				(*cb)->ray.disty += (*cb)->ray.deltay;
				(*cb)->player.pos.y += (*cb)->ray.stepy;
				(*cb)->ray.side = 1;
			}
		}
		if ((*cb)->ray.side == 0)
			(*cb)->ray.wall_dist = fabs(((*cb)->player.pos.x - (*cb)->ray.pos.x + (1 - (*cb)->ray.stepx) / 2) / (*cb)->ray.dir.x);
		else
			(*cb)->ray.wall_dist = fabs(((*cb)->player.pos.y - (*cb)->ray.pos.y + (1 - (*cb)->ray.stepy) / 2) / (*cb)->ray.dir.y);
		drawcol(cb, col);
	}
}