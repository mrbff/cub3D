/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbozzi <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/01 16:02:18 by mbozzi            #+#    #+#             */
/*   Updated: 2023/04/01 16:02:37 by mbozzi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cube3D.h"

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
