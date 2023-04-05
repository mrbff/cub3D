/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbozzi <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/01 15:59:46 by mbozzi            #+#    #+#             */
/*   Updated: 2023/04/05 14:29:10 by mbozzi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cube3D.h"

int	ft_key_hook(int keycode, t_cube *cb)
{
	if (keycode == ARROW_UP && cb->map.mat[(int)cb->p_pos.x - 1][(int)cb->p_pos.y] != '1')
		cb->p_pos.x += cb->ray.dir.x * MOVSPEED;
	else if (keycode == ARROW_DOWN && cb->map.mat[(int)cb->p_pos.x + 1][(int)cb->p_pos.y] != '1')
		cb->p_pos.x -= cb->ray.dir.x * MOVSPEED;
	else
		return 0;
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
