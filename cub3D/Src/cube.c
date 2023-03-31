/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cube.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbozzi <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/31 18:53:31 by mbozzi            #+#    #+#             */
/*   Updated: 2023/03/31 19:05:40 by mbozzi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cube3D.h"

int	ft_destroy(t_cube *ptr)
{
	mlx_destroy_image(ptr->mlx_ptr, ptr->img->mlx_img);
	mlx_destroy_window(ptr->mlx_ptr, ptr->mlx_win);
	mlx_destroy_display(ptr->mlx_ptr);
	free(ptr->img);
	free(ptr->mlx_ptr);
	free(ptr);
	exit(0);
	return (0);
}

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

int main(void)
{
	t_cube	*ptr;

	ptr = malloc(sizeof(t_cube));
	ptr->mlx_ptr = mlx_init();
	if (!ptr->mlx_ptr)
		return (1);
	ptr->mlx_win = mlx_new_window(ptr->mlx_ptr, WIN_WIDTH, WIN_HEIGHT, "cube3D");
	if (!ptr->mlx_ptr)
		return (2);
	ptr->img = malloc(sizeof(t_img));
	if (!ptr->img)
	return (3);
    ////in loop
	if (!ptr->img->mlx_img)
	{
		ptr->img->mlx_img = mlx_new_image(ptr->mlx_ptr, WIN_WIDTH, WIN_HEIGHT);
		if (!ptr->img->mlx_img)
			return (4);
		ptr->img->data = mlx_get_data_addr(ptr->img->mlx_img,
				&ptr->img->bits_per_pixel,
				&ptr->img->line_length,
				&ptr->img->endian);
        if (!ptr->img->data)
            return (5);
    }
    //create image
    mlx_put_image_to_window(ptr->mlx_ptr, ptr->mlx_win, ptr->img->mlx_img, 0, 0);
    ////
    mlx_hook(ptr->mlx_win, 2, 1L << 0, ft_key_hook, ptr);
	mlx_hook(ptr->mlx_win, 17, 0, ft_destroy, ptr);
	//mlx_mouse_hook(ptr->mlx_win, ft_zoom_hook, ptr);
	mlx_loop(ptr->mlx_ptr);
    ////////
}
