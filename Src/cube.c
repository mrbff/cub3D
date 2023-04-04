/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cube.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbozzi <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/31 18:53:31 by mbozzi            #+#    #+#             */
/*   Updated: 2023/04/04 18:37:51 by mbozzi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cube3D.h"

int	game_init(t_cube *cb)
{
	cb->mlx = mlx_init();
//	if (!cb->mlx)
//		return (1);
	cb->mlx_win = mlx_new_window(cb->mlx, WIN_WID, WIN_HGT, "cube3D");
//	if (!cb->mlx_win)
//		return (2);
	cb->img->mlx_img = mlx_new_image(cb->mlx, WIN_WID, WIN_HGT);
	if (!cb->img->mlx_img)
		return (3);
	cb->img->data = mlx_get_data_addr(cb->img->mlx_img,
			&cb->img->bits_per_pixel,
			&cb->img->line_length,
			&cb->img->endian);
	if (!cb->img->data)
		return (4);
	return (0);
}

int	ft_init(t_cube *cb)
{
	cb->img = malloc(sizeof(t_img));
//	if (!cb->img || game_init(cb))
//		return (EXIT_FAILURE);
	
	cb->pos.x = 12;//da fare dinamici
	cb->pos.y = 5;//
	cb->dir.x = -1;
	cb->dir.y = 0;
	cb->plane.x = 0;
	cb->plane.y = 0.66;
	return (0);
}

int	main(int ac, char **av)
{
	t_cube	*cb;
	
	cb = malloc(sizeof(t_cube));
	(void)ac;
	ft_init(cb);
	cb->path = ft_strjoin("./Maps/", av[1]);
	if (check_map(&cb, cb->path) == 1)
		return (EXIT_FAILURE);
	write(1,cb->path, 5);
//	mlx_key_hook(cb->mlx_win, ft_key_hook, &cb);
	mlx_hook(cb->mlx_win, 17, 0, ft_destroy, &cb);
	mlx_loop(cb->mlx);
}

/*
int	main(int ac, char **av)
{
	t_cube	*cb;

	(void)ac;
	cb = malloc(sizeof(t_cube));
	(cb)->ray.dir.x = -1;
		(cb)->ray.dir.y = 0;
	cb->plane.x = 0;
	cb->plane.y = FOV;
	cb->img = malloc(sizeof(t_img));
	if (!cb->img || game_init(&cb))
		return (EXIT_FAILURE);
	cb->path = ft_strjoin("./Maps/", av[1]);
	if (check_map(&cb, cb->path) == 1)
		return (EXIT_FAILURE);
	mlx_key_hook(cb->mlx_win, ft_key_hook, &cb);
	mlx_hook(cb->mlx_win, 17, 0, ft_destroy, cb);
	mlx_loop(cb->mlx);
}*/
