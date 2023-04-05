/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbozzi <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/01 16:02:18 by mbozzi            #+#    #+#             */
/*   Updated: 2023/04/05 19:23:47 by mbozzi           ###   ########.fr       */
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

int		ft_get_pixels(int x, int y, t_img *img)
{
	int	i;
	int	*ptr2;
	int color;

	color = 0;
	//x = x * 255 / WIN_WID;
	//y = y * 255 / WIN_HGT;
	if (x >= 0 && x < WIN_WID && y >= 0 && y < WIN_HGT)
	{
		i = y * img->line_length + x * img->bits_per_pixel / 8;
		ptr2 = (int *)&img->data[i];
		color = *ptr2;
	}
	return (color);
}

int	ft_destroy(t_cube *ptr)
{
	int	i;

	i = -1;
	while (ptr->map.mat[++i])
		free(ptr->map.mat[i]);
	free(ptr->map.mat);
	mlx_destroy_image(ptr->mlx, ptr->img->mlx_img);
	mlx_destroy_window(ptr->mlx, ptr->mlx_win);
	mlx_destroy_display(ptr->mlx);
	free(ptr->img);
	free(ptr->mlx);
	free(ptr->tex1);
	free(ptr);
	exit(0);
	return (0);
}

unsigned int	ft_color_converter(int r, int g, int b)
{
	return (r << 16 | g << 8 | b);
}

double	delta(t_cube *cb, char flag)
{
	if (flag == 'x')
		return (sqrt(1 + pow(cb->ray.dir.y, 2) / pow(cb->ray.dir.x, 2)));
	else if (flag == 'y')
		return (sqrt(1 + pow(cb->ray.dir.x, 2) / pow(cb->ray.dir.y, 2)));
	return (0);
}
