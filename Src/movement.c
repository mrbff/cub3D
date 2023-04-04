/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbozzi <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/01 15:59:46 by mbozzi            #+#    #+#             */
/*   Updated: 2023/04/04 16:26:55 by mbozzi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cube3D.h"

int	ft_key_hook(int keycode, t_cube **cb)
{
/*	else if (keycode == KEY_C || keycode == KEY_Z || keycode == KEY_R)
		ft_color(keycode, ptr);*/
	if (keycode == ARROW_UP && (*cb)->map.mat[(int)(*cb)->player.pos.x - 1][(int)(*cb)->player.pos.y] != '1')
		(*cb)->player.pos.x -= 1 * MOVSPEED;
	else if (keycode == ARROW_DOWN && (*cb)->map.mat[(int)(*cb)->player.pos.x + 1][(int)(*cb)->player.pos.y] != '1')
		(*cb)->player.pos.x += 1 * MOVSPEED;
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
