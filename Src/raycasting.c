/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbozzi <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/03 11:33:45 by mbozzi            #+#    #+#             */
/*   Updated: 2023/04/04 18:34:07 by mbozzi           ###   ########.fr       */
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

void	verLine(t_cube *cb, int x, int y1, int y2, int color)
{
	int	y;
	y = y1;
	while (y <= y2)
	{
	//	mlx_pixel_put(cb->mlx, cb->mlx_win, x, y, color);
		ft_draw_pixels(x, y, color, cb);
		y++;
	}
}

void	raycasting(t_cube *cb)
{
int	x;
x = 0;
put_floor_sky(cb);
while (x < WIN_WID)
{
	double cameraX = 2 * x / (double)WIN_WID - 1;
	double rayDirX = cb->dir.x + cb->plane.x * cameraX;
	double rayDirY = cb->dir.y + cb->plane.y * cameraX;

	int mapX = (int)cb->pos.x;
	int mapY = (int)cb->pos.y;

	//length of ray from current position to next x or y-side
	double sideDistX;
	double sideDistY;

	 //length of ray from one x or y-side to next x or y-side
	double deltaDistX = fabs(1 / rayDirX);
	double deltaDistY = fabs(1 / rayDirY);
	double perpWallDist;

	//what direction to step in x or y-direction (either +1 or -1)
	int stepX;
	int stepY;

	int hit = 0; //was there a wall hit?
	int side; //was a NS or a EW wall hit?

	if (rayDirX < 0)
	{
		stepX = -1;
		sideDistX = (cb->pos.x - mapX) * deltaDistX;
	}
	else
	{
		stepX = 1;
		sideDistX = (mapX + 1.0 - cb->pos.x) * deltaDistX;
	}
	if (rayDirY < 0)
	{
		stepY = -1;
		sideDistY = (cb->pos.y - mapY) * deltaDistY;
	}
	else
	{
		stepY = 1;
		sideDistY = (mapY + 1.0 - cb->pos.y) * deltaDistY;
	}

	while (hit == 0)
	{
		//jump to next map square, OR in x-direction, OR in y-direction
		if (sideDistX < sideDistY)
		{
			sideDistX += deltaDistX;
			mapX += stepX;
			side = 0;
		}
		else
		{
			sideDistY += deltaDistY;
			mapY += stepY;
			side = 1;
		}
		//Check if ray has hit a wall
		if (cb->map.mat[mapX][mapY] > '0' && cb->map.mat[mapX][mapY] != 'N')
			hit = 1;
	}
	if (side == 0)
		perpWallDist = (mapX - cb->pos.x + (1 - stepX) / 2) / rayDirX;
	else
		perpWallDist = (mapY - cb->pos.y + (1 - stepY) / 2) / rayDirY;

	//Calculate height of line to draw on screen
	int lineHeight = (int)(WIN_HGT / perpWallDist);

	//calculate lowest and highest pixel to fill in current stripe
	int drawStart = -lineHeight / 2 + WIN_HGT / 2;
	if(drawStart < 0)
		drawStart = 0;
	int drawEnd = lineHeight / 2 + WIN_HGT / 2;
	if(drawEnd >= WIN_HGT)
		drawEnd = WIN_HGT - 1;

	int	color = 0;
	if (cb->map.mat[mapY][mapX] == '1')
		color = 0xFF0000;
	verLine(cb, x, drawStart, drawEnd, color);
/*	else if (cb->map.mat[mapY][mapX] == '2')
		color = 0x00FF00;
	else if (cb->map.mat[mapY][mapX] == '3')
		color = 0x0000FF;
	else if (cb->map.mat[mapY][mapX] == '4')
		color = 0xFFFFFF;*/
//	else
//		color = 0xFFFF00;

//	if (side == 1)
//		color = color / 2;

	

	x++;
}
mlx_put_image_to_window(cb->mlx, cb->mlx_win, cb->img->mlx_img, 0, 0);
}





/*
void	drawline(t_cube **cb, int col)
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
		ft_draw_pixels(col, (index / WIN_WID), 0xFFFF0000, *cb);
		index += WIN_WID;
		i++;
	}
}

void	ray_dist(t_cube **cb, int x, int y)
{
	while (cb->map.mat[x][y] == '0' || cb->map.mat[x][y] == 'N')
	{
		if (cb->ray.distx < cb->ray.disty)
		{
			cb->ray.distx += cb->ray.deltax;
			x += cb->ray.stepx;
			cb->ray.side = 0;
		}
		else
		{
			cb->ray.disty += cb->ray.deltay;
			y += cb->ray.stepy;
			cb->ray.side = 1;
		}
	}
	if (cb->ray.side == 0)
		cb->ray.wall_dist = (x - cb->player.pos.x
				+ (1 - cb->ray.stepx) / 2) / cb->ray.dir.x;
	else
		cb->ray.wall_dist = (y -cb->player.pos.y
				+ (1 - cb->ray.stepy) / 2) / cb->ray.dir.y;
}

void	ray_dir(t_cube **cb, int x, int y)
{
	if (cb->ray.dir.x < 0)
	{
		cb->ray.stepx = -1;
		cb->ray.distx = (cb->player.pos.x - x) * cb->ray.deltax;
	}
	else
	{
		cb->ray.stepx = 1;
		cb->ray.distx = (x - cb->player.pos.x + 1) * cb->ray.deltax;
	}
	if (cb->ray.dir.y < 0)
	{
		cb->ray.stepy = -1;
		cb->ray.disty = (cb->player.pos.y - y) * cb->ray.deltay;
	}
	else
	{
		cb->ray.stepy = 1;
		cb->ray.disty = (y - cb->player.pos.y + 1) * cb->ray.deltay;
	}
}

void	raycasting(t_cube *cb)
{
	int	col;
	int	x;
	int	y;

	col = -1;
	put_floor_sky(cb);
	while (++col < WIN_WID)
	{
		cb->cam.x = 2 * col / (double)WIN_WID - 1;
		cb->ray.dir.x = cb->ray.dir.x + cb->plane.x * cb->cam.x;
		cb->ray.dir.y = cb->ray.dir.y + cb->plane.y * cb->cam.x;
		cb->ray.deltax = fabs(1 / cb->ray.dir.x);
		cb->ray.deltay = fabs(1 / cb->ray.dir.y);
	//	x = (int)cb->player.pos.x;
	//	y = (int)cb->player.pos.y;
		ray_dir(cb, x, y);
		ray_dist(cb, x, y);
		drawline(cb, col);
	}
	mlx_put_image_to_window(cb->mlx, cb->mlx_win, cb->img->mlx_img, 0, 0);
}
*/