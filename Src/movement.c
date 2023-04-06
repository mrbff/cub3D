/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbozzi <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/01 15:59:46 by mbozzi            #+#    #+#             */
/*   Updated: 2023/04/05 15:45:41 by mbozzi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cube3D.h"

#include "../cube3D.h"

int	ft_key_hook(int keycode, t_cube *cb)
{
	double	old;

	old = cb->p_dir.x;
	if (keycode == ESC)
		ft_destroy(cb);
	else if (keycode == KEY_W)//avanti
	{
		if (cb->map.mat[(int)(cb->p_pos.x + cb->p_dir.x * MOVSPEED)][(int)cb->p_pos.y] == 48)
			cb->p_pos.x += cb->p_dir.x * MOVSPEED;
		if (cb->map.mat[(int)cb->p_pos.x][(int)(cb->p_pos.y + cb->p_dir.x * MOVSPEED)] == 48)
			cb->p_pos.y += cb->p_dir.y * MOVSPEED;
	}
	else if (keycode == KEY_S)//dietro
	{
		if (cb->map.mat[(int)(cb->p_pos.x - cb->p_dir.x * MOVSPEED)][(int)cb->p_pos.y] == 48)
			cb->p_pos.x -= cb->p_dir.x * MOVSPEED;
		if (cb->map.mat[(int)cb->p_pos.x][(int)(cb->p_pos.y - cb->p_dir.x * MOVSPEED)] == 48)
			cb->p_pos.y -= cb->p_dir.y * MOVSPEED;
	}
	
	else if (keycode == KEY_A)//left
	{
		if (cb->map.mat[(int)(cb->p_pos.x - cb->p_dir.y * MOVSPEED)][(int)cb->p_pos.y] == 48)
			cb->p_pos.x -= cb->p_dir.y * MOVSPEED;
		if (cb->map.mat[(int)cb->p_pos.x][(int)(cb->p_pos.y + cb->p_dir.x * MOVSPEED)] == 48)
			cb->p_pos.y += cb->p_dir.x * MOVSPEED;
	}
	else if (keycode == KEY_D)//right
	{
		if (cb->map.mat[(int)(cb->p_pos.x + cb->p_dir.y * MOVSPEED)][(int)cb->p_pos.y] == 48)
			cb->p_pos.x += cb->p_dir.y * MOVSPEED;
		if (cb->map.mat[(int)cb->p_pos.x][(int)(cb->p_pos.y - cb->p_dir.x * MOVSPEED)] == 48)
			cb->p_pos.y -= cb->p_dir.x * MOVSPEED;
	}
	else if (keycode == ARROW_LETF)//rotate left
	{
		cb->p_dir.x = cb->p_dir.x * cos(ROTSPEED) - cb->p_dir.y * sin(ROTSPEED);
		cb->p_dir.y = old * sin(ROTSPEED) + cb->p_dir.y * cos(ROTSPEED);
		old = cb->cam.x;
		cb->cam.x = cb->cam.x * cos(ROTSPEED) - cb->cam.y * sin(ROTSPEED);
		cb->cam.y = old * sin(ROTSPEED) + cb->cam.y * cos(ROTSPEED);
	}
	else if (keycode == ARROW_RIGHT)//rotate right
	{
		cb->p_dir.x = cb->p_dir.x * cos(-ROTSPEED) - cb->p_dir.y * sin(-ROTSPEED);
		cb->p_dir.y = old * sin(-ROTSPEED) + cb->p_dir.y * cos(-ROTSPEED);
		old = cb->cam.x;
		cb->cam.x = cb->cam.x * cos(-ROTSPEED) - cb->cam.y * sin(-ROTSPEED);
		cb->cam.y = old * sin(-ROTSPEED) + cb->cam.y * cos(-ROTSPEED);
	}
	raycasting(cb);
	ft_printf("keycode = %d\n", keycode);
	return (0);
}
