/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbozzi <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/01 16:02:18 by mbozzi            #+#    #+#             */
/*   Updated: 2023/04/04 16:55:53 by mbozzi           ###   ########.fr       */
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

int	ft_destroy(t_cube *ptr)
{
	mlx_destroy_image(ptr->mlx, ptr->img->mlx_img);
	mlx_destroy_window(ptr->mlx, ptr->mlx_win);
	mlx_destroy_display(ptr->mlx);
	free(ptr->img);
	free(ptr->mlx);
	free(ptr);
	exit(0);
	return (0);
}
