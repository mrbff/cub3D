/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbozzi <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/01 15:59:46 by mbozzi            #+#    #+#             */
/*   Updated: 2023/04/04 16:56:14 by mbozzi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cube3D.h"

int	ft_key_hook(int keycode, t_cube *cb)
{
	double	old;

	old = cb->dir.x;
	if (keycode == ESC)
		ft_destroy(cb);
	else if (keycode == ARROW_UP)
	{
		if (!cb->map.mat[(int)(cb->pos.x + cb->dir.x * MOVSPEED)][(int)cb->pos.y])
			cb->pos.x += cb->dir.x * MOVSPEED;
		if (!cb->map.mat[(int)cb->pos.x][(int)(cb->pos.y + cb->dir.x * MOVSPEED)])
			cb->pos.y += cb->dir.y * MOVSPEED;
	}
	else if (keycode == ARROW_DOWN)
	{
		if (!cb->map.mat[(int)(cb->pos.x - cb->dir.x * MOVSPEED)][(int)cb->pos.y])
			cb->pos.x -= cb->dir.x * MOVSPEED;
		if (!cb->map.mat[(int)cb->pos.x][(int)(cb->pos.y - cb->dir.x * MOVSPEED)])
			cb->pos.y -= cb->dir.y * MOVSPEED;
	}
	else if (keycode == 97)
	{
		cb->dir.x = cb->dir.x * cos(ROTSPEED) - cb->dir.y * sin(ROTSPEED);
		cb->dir.y = old * sin(ROTSPEED) + cb->dir.y * cos(ROTSPEED);
		old = cb->plane.x;
		cb->plane.x = cb->plane.x * cos(ROTSPEED) - cb->plane.y * sin(ROTSPEED);
		cb->plane.y = old * sin(ROTSPEED) + cb->plane.y * cos(ROTSPEED);
	}
	else if (keycode == 100)
	{
		cb->dir.x = cb->dir.x * cos(-ROTSPEED) - cb->dir.y * sin(-ROTSPEED);
		cb->dir.y = old * sin(-ROTSPEED) + cb->dir.y * cos(-ROTSPEED);
		old = cb->plane.x;
		cb->plane.x = cb->plane.x * cos(-ROTSPEED) - cb->plane.y * sin(-ROTSPEED);
		cb->plane.y = old * sin(-ROTSPEED) + cb->plane.y * cos(-ROTSPEED);
	}
	raycasting(cb);
	ft_printf("keycode = %d\n", keycode);
	return (0);
}
