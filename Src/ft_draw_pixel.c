/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_draw_pixel.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabaffo <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/03 16:00:25 by mabaffo           #+#    #+#             */
/*   Updated: 2023/04/03 16:02:23 by mabaffo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

void	ft_draw_pixels(int x, int y, int color, t_fractol *ptr)
{
	int	i;
	int	*ptr2;

	if (x >= 0 && x < WIN_WIDTH && y >= 0 && y < WIN_HEIGHT)
	{
		i = y * ptr->img->line_length + x * ptr->img->bits_per_pixel / 8;
		ptr2 = (int *)&ptr->img->data[i];
		*ptr2 = color;
	}
}

//mlx_put_image_to_window(ptr->mlx_ptr, ptr->mlx_win, ptr->img->mlx_img, 0, 0);
