/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbozzi <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/01 15:59:46 by mbozzi            #+#    #+#             */
/*   Updated: 2023/04/07 14:23:44 by mbozzi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cube3D.h"

static void	ft_back_n_forth(int keycode, t_cube *cb)
{
	if (keycode == KEY_W)
	{
		if (cb->map.mat[(int)(cb->p_pos.x + cb->p_dir.x * MOVSPEED)]
				[(int)cb->p_pos.y] == 48)
			cb->p_pos.x += cb->p_dir.x * MOVSPEED;
		if (cb->map.mat[(int)cb->p_pos.x]
			[(int)(cb->p_pos.y + cb->p_dir.x * MOVSPEED)] == 48)
			cb->p_pos.y += cb->p_dir.y * MOVSPEED;
	}
	else if (keycode == KEY_S)
	{
		if (cb->map.mat[(int)(cb->p_pos.x - cb->p_dir.x * MOVSPEED)]
			[(int)cb->p_pos.y] == 48)
			cb->p_pos.x -= cb->p_dir.x * MOVSPEED;
		if (cb->map.mat[(int)cb->p_pos.x]
			[(int)(cb->p_pos.y - cb->p_dir.x * MOVSPEED)] == 48)
			cb->p_pos.y -= cb->p_dir.y * MOVSPEED;
	}
}

static void	ft_left_n_right(int keycode, t_cube *cb)
{
	if (keycode == KEY_A)
	{
		if (cb->map.mat[(int)(cb->p_pos.x - cb->p_dir.y * MOVSPEED)]
			[(int)cb->p_pos.y] == 48)
			cb->p_pos.x -= cb->p_dir.y * MOVSPEED;
		if (cb->map.mat[(int)cb->p_pos.x]
			[(int)(cb->p_pos.y + cb->p_dir.x * MOVSPEED)] == 48)
			cb->p_pos.y += cb->p_dir.x * MOVSPEED;
	}
	else if (keycode == KEY_D)
	{
		if (cb->map.mat[(int)(cb->p_pos.x + cb->p_dir.y * MOVSPEED)]
			[(int)cb->p_pos.y] == 48)
			cb->p_pos.x += cb->p_dir.y * MOVSPEED;
		if (cb->map.mat[(int)cb->p_pos.x]
			[(int)(cb->p_pos.y - cb->p_dir.x * MOVSPEED)] == 48)
			cb->p_pos.y -= cb->p_dir.x * MOVSPEED;
	}
}

static void	ft_rotate(int keycode, t_cube *cb)
{
	double	old;

	old = cb->p_dir.x;
	if (keycode == ARROW_LETF)
	{
		cb->p_dir.x = cb->p_dir.x * cos(ROTSPEED) - cb->p_dir.y * sin(ROTSPEED);
		cb->p_dir.y = old * sin(ROTSPEED) + cb->p_dir.y * cos(ROTSPEED);
		old = cb->cam.x;
		cb->cam.x = cb->cam.x * cos(ROTSPEED) - cb->cam.y * sin(ROTSPEED);
		cb->cam.y = old * sin(ROTSPEED) + cb->cam.y * cos(ROTSPEED);
	}
	else if (keycode == ARROW_RIGHT)
	{
		cb->p_dir.x = cb->p_dir.x * cos(-ROTSPEED)
			- cb->p_dir.y * sin(-ROTSPEED);
		cb->p_dir.y = old * sin(-ROTSPEED) + cb->p_dir.y * cos(-ROTSPEED);
		old = cb->cam.x;
		cb->cam.x = cb->cam.x * cos(-ROTSPEED) - cb->cam.y * sin(-ROTSPEED);
		cb->cam.y = old * sin(-ROTSPEED) + cb->cam.y * cos(-ROTSPEED);
	}
}

int	ft_key_hook(int keycode, t_cube *cb)
{	
	if (keycode == ESC)
		ft_destroy(cb);
	else if (keycode == KEY_W || keycode == KEY_S)
		ft_back_n_forth(keycode, cb);
	else if (keycode == KEY_A || keycode == KEY_D)
		ft_left_n_right(keycode, cb);
	else if (keycode == ARROW_LETF || keycode == ARROW_RIGHT)
		ft_rotate(keycode, cb);
	raycasting(cb);
	ft_printf("keycode = %d\n", keycode);
	return (0);
}
