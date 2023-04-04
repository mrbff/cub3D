/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_draw_pixel.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbozzi <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/03 16:00:25 by mabaffo           #+#    #+#             */
/*   Updated: 2023/04/04 16:19:14 by mbozzi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cube3D.h"

void	ft_draw_pixels(int x, int y, int color, t_cube *cb)
{
	int	i;
	int	*ptr2;

	if (x >= 0 && x < WIN_WID && y >= 0 && y < WIN_HGT)
	{
		i = y * cb->img->line_length + x * cb->img->bits_per_pixel / 8;
		ptr2 = (int *)&cb->img->data[i];
		*ptr2 = color;
	}
}

//mlx_put_image_to_window(ptr->mlx_ptr, ptr->mlx_win, ptr->img->mlx_img, 0, 0);
