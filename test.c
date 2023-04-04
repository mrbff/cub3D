#include "minilibx-linux/mlx.h"
#include <math.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#define X_EVENT_KEY_PRESS	2
#define X_EVENT_KEY_EXIT	17
#define mapWidth 24
#define mapHeight 24
#define WIN_WID 1200
#define WIN_HGT 720
#define MOVSPEED  0.1
#define ROTSPEED  0.05

void	verLine(t_cube *cb, int x, int y1, int y2, int color)
{
int	y;
y = y1;
while (y <= y2)
{
//	mlx_pixel_put(cb->mlx, cb->mlx_win, x, y, color);
	ft_drawpixel(x, y, color, cb);
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
		if (cb->map[mapX][mapY] > 0) hit = 1;
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

	int	color;
	if (cb->map[mapY][mapX] == 1)
		color = 0xFF0000;
	else if (cb->map[mapY][mapX] == 2)
		color = 0x00FF00;
	else if (cb->map[mapY][mapX] == 3)
		color = 0x0000FF;
	else if (cb->map[mapY][mapX] == 4)
		color = 0xFFFFFF;
	else
		color = 0xFFFF00;

	if (side == 1)
		color = color / 2;

	verLine(cb, x, drawStart, drawEnd, color);

	x++;
}
mlx_put_image_to_window(cb->mlx, cb->mlx_win, cb->img->mlx_img, 0, 0);
}
/*
int	main_loop(t_cube *cb)
{
calc(cb);
//mlx_put_image_to_window(cb->mlx, cb->win, &cb->img, 0, 0);
return (0);

}*/
/*
int	key_press(int key, t_cube *cb)
{
//mlx_clear_window(cb->mlx, cb->mlx_win);
if (key == 119)
{
if (!worldMap[(int)(cb->pos.x + cb->dir.x * MOVSPEED)][(int)(cb->pos.y)])
cb->pos.x += cb->dir.x * MOVSPEED;
if (!worldMap[(int)(cb->pos.x)][(int)(cb->pos.y + cb->dir.y * MOVSPEED)])
cb->pos.y += cb->dir.y * MOVSPEED;
}
//move backwards if no wall behind you
if (key == 115)
{
if (!worldMap[(int)(cb->pos.x - cb->dir.x * MOVSPEED)][(int)(cb->pos.y)])
cb->pos.x -= cb->dir.x * MOVSPEED;
if (!worldMap[(int)(cb->pos.x)][(int)(cb->pos.y - cb->dir.y * MOVSPEED)])
cb->pos.y -= cb->dir.y * MOVSPEED;
}
//rotate to the right
if (key == 100)
{
//both camera direction and camera plane must be rotated
double oldDirX = cb->dir.x;
cb->dir.x = cb->dir.x * cos(-ROTSPEED) - cb->dir.y * sin(-ROTSPEED);
cb->dir.y = oldDirX * sin(-ROTSPEED) + cb->dir.y * cos(-ROTSPEED);
double oldPlaneX = cb->plane.x;
cb->plane.x = cb->plane.x * cos(-ROTSPEED) - cb->plane.y * sin(-ROTSPEED);
cb->plane.y = oldPlaneX * sin(-ROTSPEED) + cb->plane.y * cos(-ROTSPEED);
}
//rotate to the left
if (key == 97)
{
//both camera direction and camera plane must be rotated
double oldDirX = cb->dir.x;
cb->dir.x = cb->dir.x * cos(ROTSPEED) - cb->dir.y * sin(ROTSPEED);
cb->dir.y = oldDirX * sin(ROTSPEED) + cb->dir.y * cos(ROTSPEED);
double oldPlaneX = cb->plane.x;
cb->plane.x = cb->plane.x * cos(ROTSPEED) - cb->plane.y * sin(ROTSPEED);
cb->plane.y = oldPlaneX * sin(ROTSPEED) + cb->plane.y * cos(ROTSPEED);
}
if (key == 65307)
exit(0);
return (0);
}
*/
/*
int	game_init(t_cube *cb)
{
	cb->mlx = mlx_init();
	if (!cb->mlx)
		return (1);
	cb->mlx_win = mlx_new_window(cb->mlx, WIN_WID, WIN_HGT, "cube3D");
	if (!cb->mlx_win)
		return (2);
	cb->img->mlx_img = mlx_new_image(cb->mlx, WIN_WID, WIN_HGT);
	if (!cb->img->mlx_img)
		return (3);
	cb->img->data = mlx_get_data_addr(cb->img->mlx_img,
			&cb->img->bits_per_pixel,
			&cb->img->line_length,
			&cb->img->endian);
	if (!cb->img->data)
		return (4);
	return (0);
}

int	ft_init(t_cube *cb, char **av)
{
	cb->img = malloc(sizeof(t_img));
	if (!cb->img || game_init(&cb))
		return (EXIT_FAILURE);
	cb->path = ft_strjoin("./Maps/", av[1]);
	if (check_map(&cb, cb->path) == 1)
		return (EXIT_FAILURE);
	cb->pos.x = 12;
	cb->pos.y = 5;
	cb->dir.x = -1;
	cb->dir.y = 0;
	cb->plane.x = 0;
	cb->plane.y = 0.66;
}

int	main(int ac, char **av)
{
	t_cube	cb;
	
	(void)ac;
	ft_init(&cb, av);

	mlx_key_hook(cb.mlx_win, key_press, &cb);
	mlx_hook(cb.mlx_win, 17, 0, ft_destroy, &cb);
	mlx_loop(cb.mlx);
}*/