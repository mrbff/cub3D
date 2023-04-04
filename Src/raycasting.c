/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbozzi <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/03 11:33:45 by mbozzi            #+#    #+#             */
/*   Updated: 2023/04/04 16:29:17 by mbozzi           ###   ########.fr       */
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
			ft_draw_pixels(col, i , 0x0000FFFF, *cb);
	}
	while (++i < WIN_HGT)
	{
		col = -1;
		while (++col < (WIN_WID))
			ft_draw_pixels(col, i , 0x00606060, *cb);
	}
}

void	drawcol(t_cube **cb, int col)
{
	int start;
	int end;
	int height;
	
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
		//mlx_pixel_put((*cb)->mlx, (*cb)->mlx_win, col, start, );
		start++;
	}
}

int	raycasting(t_cube **cb)
{
	int	col;
	
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
		int mapx = (int)(*cb)->player.pos.x;
		int mapy = (int)(*cb)->player.pos.y;
		if ((*cb)->ray.dir.x < 0)
		{
			(*cb)->ray.stepx = -1;
			(*cb)->ray.distx = ((*cb)->player.pos.x - mapx) * (*cb)->ray.deltax;
		}
		else
		{
			(*cb)->ray.stepx = 1;
			(*cb)->ray.distx = (mapx - (*cb)->player.pos.x + 1) * (*cb)->ray.deltax;
		}
		if ((*cb)->ray.dir.y < 0)
		{
			(*cb)->ray.stepy = -1;
			(*cb)->ray.disty = ((*cb)->player.pos.y - mapy) * (*cb)->ray.deltay;
		}
		else
		{
			(*cb)->ray.stepy = 1;
			(*cb)->ray.disty = (mapy - (*cb)->player.pos.y + 1) * (*cb)->ray.deltay;
		}
		while ((*cb)->map.mat[mapx][mapy] == '0' || (*cb)->map.mat[mapx][mapy] == 'N')
		{
			if ((*cb)->ray.distx < (*cb)->ray.disty)
			{
				(*cb)->ray.distx += (*cb)->ray.deltax;
				mapx += (*cb)->ray.stepx;
				(*cb)->ray.side = 0;
			}
			else
			{
				(*cb)->ray.disty += (*cb)->ray.deltay;
				mapy += (*cb)->ray.stepy;
				(*cb)->ray.side = 1;
			}
		}
		if ((*cb)->ray.side == 0)
			(*cb)->ray.wall_dist = (mapx - (*cb)->player.pos.x + (1 - (*cb)->ray.stepx) / 2) / (*cb)->ray.dir.x;
		else
			(*cb)->ray.wall_dist = (mapy -(*cb)->player.pos.y + (1 - (*cb)->ray.stepy) / 2) / (*cb)->ray.dir.y;
		drawcol(cb, col);
	}
	mlx_put_image_to_window((*cb)->mlx, (*cb)->mlx_win, (*cb)->img->mlx_img, 0, 0);
	return (0);
}