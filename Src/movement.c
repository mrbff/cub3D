/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbozzi <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/01 15:59:46 by mbozzi            #+#    #+#             */
/*   Updated: 2023/04/01 16:01:16 by mbozzi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cube3D.h"

int	ft_key_hook(int keycode, t_cube *ptr)
{
	ft_printf("keycode = %d\n", keycode);
	if (keycode == ESC)
		ft_destroy(ptr);
/*	else if (keycode == KEY_C || keycode == KEY_Z || keycode == KEY_R)
		ft_color(keycode, ptr);
	else if (keycode == ARROW_UP)
		ptr->y_min = ptr->y_min - ptr->display_shift;
	else if (keycode == ARROW_DOWN)
		ptr->y_min = ptr->y_min + ptr->display_shift;
	else if (keycode == ARROW_LEFT)
		ptr->x_min = ptr->x_min - ptr->display_shift;
	else if (keycode == ARROW_RIGHT)
		ptr->x_min = ptr->x_min + ptr->display_shift;
	else if (keycode == KEY_I)
		ptr->incr_iter = !ptr->incr_iter;*/
//	ft_put_image_to_window(ptr);
	return (0);
}
