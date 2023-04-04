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

int	ft_key_hook(int keycode, t_cube **cb)
{
	double	oldx;

	oldx = (*cb)->ray.dir.x;
	
	if (keycode == ARROW_UP && (*cb)->map.mat[(int)(*cb)->player.pos.x - 1][(int)(*cb)->player.pos.y] != '1')
		(*cb)->player.pos.x -= 1 * MOVSPEED;
	else if (keycode == ARROW_DOWN && (*cb)->map.mat[(int)(*cb)->player.pos.x + 1][(int)(*cb)->player.pos.y] != '1')
		(*cb)->player.pos.x += 1 * MOVSPEED;
	else if (keycode == 97)
	{
		(*cb)->ray.dir.x = (*cb)->ray.dir.x * cos(ROTSPEED) - (*cb)->ray.dir.y * sin(ROTSPEED);
		(*cb)->ray.dir.y = oldx * sin(ROTSPEED) + (*cb)->ray.dir.y * cos(ROTSPEED);
		oldx = (*cb)->plane.x;
		(*cb)->plane.x = (*cb)->plane.x * cos(ROTSPEED) - (*cb)->plane.y * sin(ROTSPEED);
		(*cb)->plane.y = oldx * sin(ROTSPEED) + (*cb)->plane.y * cos(ROTSPEED);
	}
	else if (keycode == 100)
	{
		(*cb)->ray.dir.x = (*cb)->ray.dir.x * cos(-ROTSPEED) - (*cb)->ray.dir.y * sin(-ROTSPEED);
		(*cb)->ray.dir.y = oldx * sin(-ROTSPEED) + (*cb)->ray.dir.y * cos(-ROTSPEED);
		oldx = (*cb)->plane.x;
		(*cb)->plane.x = (*cb)->plane.x * cos(-ROTSPEED) - (*cb)->plane.y * sin(-ROTSPEED);
		(*cb)->plane.y = oldx * sin(-ROTSPEED) + (*cb)->plane.y * cos(-ROTSPEED);
	}
/*	else if (keycode == 65361)
	{
		(*cb)->player.pos.x = (*cb)->player.pos.x * cos(ROTSPEED) - (*cb)->player.pos.y * sin(ROTSPEED);
		(*cb)->player.pos.y = (*cb)->player.pos.x * sin(ROTSPEED) + (*cb)->player.pos.y * cos(ROTSPEED);
	}
	else if (keycode == 65363)
	{
		(*cb)->player.pos.x = (*cb)->player.pos.x * cos(ROTSPEED) + (*cb)->player.pos.y * sin(ROTSPEED);
		(*cb)->player.pos.y = (*cb)->player.pos.x * sin(ROTSPEED) - (*cb)->player.pos.y * cos(ROTSPEED);
	}*/
	/*else if (keycode == ARROW_LEFT)
		ptr->x_min = ptr->x_min - ptr->display_shift;
	else if (keycode == ARROW_RIGHT)
		ptr->x_min = ptr->x_min + ptr->display_shift;
	else if (keycode == KEY_I)
		ptr->incr_iter = !ptr->incr_iter;
//	ft_put_image_to_window(ptr);*/
	raycasting(cb);
	ft_printf("keycode = %d\n", keycode);
	return (0);
}
