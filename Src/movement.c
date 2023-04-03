/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbozzi <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/01 15:59:46 by mbozzi            #+#    #+#             */
/*   Updated: 2023/04/03 14:21:28 by mbozzi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cube3D.h"

int	ft_key_hook(int keycode, t_cube **cb)
{
	ft_printf("keycode = %d\n", keycode);
/*	else if (keycode == KEY_C || keycode == KEY_Z || keycode == KEY_R)
		ft_color(keycode, ptr);*/
	if (keycode == ARROW_UP)
		(*cb)->player.pos.x += 1;
	else if (keycode == ARROW_DOWN)
		(*cb)->player.pos.x -= 1;
	/*else if (keycode == ARROW_LEFT)
		ptr->x_min = ptr->x_min - ptr->display_shift;
	else if (keycode == ARROW_RIGHT)
		ptr->x_min = ptr->x_min + ptr->display_shift;
	else if (keycode == KEY_I)
		ptr->incr_iter = !ptr->incr_iter;
//	ft_put_image_to_window(ptr);*/
	return (0);
}
