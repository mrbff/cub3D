/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cube.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbozzi <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/31 18:53:31 by mbozzi            #+#    #+#             */
/*   Updated: 2023/04/01 17:39:42 by mbozzi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cube3D.h"

void	game_init(t_cube **cb)
{
	(*cb)->mlx = mlx_init();
	(*cb)->mlx_win = mlx_new_window((*cb)->mlx, WIN_WID, WIN_HGT, "cube3D");
}

int	main(int ac, char **av)
{
	t_cube	*cb;

	(void)ac;
	cb = malloc(sizeof(t_cube));
	cb->path = ft_strjoin("./Maps/", av[1]);
	if (check_map(&cb, cb->path) == 1)
		return (0);
	game_init(&cb);
	//mlx_loop(ptr->mlx);
}

//	TO DO //

/* ptr->img = malloc(sizeof(t_img));
	if (!ptr->img)
	return (3);
    ////in loop
	if (!ptr->img->mlx_img)
	{
		ptr->img->mlx_img = mlx_new_image(ptr->mlx, WIN_WIDTH, WIN_HEIGHT);
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
    mlx_put_image_to_window(ptr->mlx, ptr->mlx_win, ptr->img->mlx_img, 0, 0);
    ////
    mlx_hook(ptr->mlx_win, 2, 1L << 0, ft_key_hook, ptr);
	mlx_hook(ptr->mlx_win, 17, 0, ft_destroy, ptr);
	//mlx_mouse_hook(ptr->mlx_win, ft_zoom_hook, ptr);
    //////// */