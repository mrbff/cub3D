/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cube.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbozzi <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/31 18:53:31 by mbozzi            #+#    #+#             */
/*   Updated: 2023/04/04 16:25:50 by mbozzi           ###   ########.fr       */
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
	cb->img = malloc(sizeof(t_img));
	if (!cb->img)
		return (3);
	game_init(&cb);
	if (!cb->img->mlx_img)
	{
		cb->img->mlx_img = mlx_new_image(cb->mlx, WIN_WID, WIN_HGT);
		if (!cb->img->mlx_img)
			return (4);
		cb->img->data = mlx_get_data_addr(cb->img->mlx_img,
				&cb->img->bits_per_pixel,
				&cb->img->line_length,
				&cb->img->endian);
        if (!cb->img->data)
            return (5);
    }
	cb->path = ft_strjoin("./Maps/", av[1]);
	if (check_map(&cb, cb->path) == 1)
		return (0);
	mlx_key_hook(cb->mlx_win, ft_key_hook, &cb);
	mlx_loop(cb->mlx);
}

//	TO DO //

/* cb->img = malloc(sizeof(t_img));
	if (!cb->img)
	return (3);
    ////in loop
	if (!cb->img->mlx_img)
	{
		cb->img->mlx_img = mlx_new_image(cb->mlx, WIN_WIDTH, WIN_HEIGHT);
		if (!cb->img->mlx_img)
			return (4);
		cb->img->data = mlx_get_data_addr(cb->img->mlx_img,
				&cb->img->bits_per_pixel,
				&cb->img->line_length,
				&cb->img->endian);
        if (!cb->img->data)
            return (5);
    }
    //create image
    mlx_put_image_to_window(cb->mlx, cb->mlx_win, cb->img->mlx_img, 0, 0);
    ////
    mlx_hook(cb->mlx_win, 2, 1L << 0, ft_key_hook, cb);
	mlx_hook(cb->mlx_win, 17, 0, ft_destroy, cb);
	//mlx_mouse_hook(cb->mlx_win, ft_zoom_hook, cb);
    //////// */