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
	if (!cb->mlx)
		printf("%d\n", 1);
	cb->mlx_win = mlx_new_window(cb->mlx, WIN_WID, WIN_HGT, "cube3D");
	if (!cb->mlx_win)
		printf("%d\n", 2);
	cb->img->mlx_img = mlx_new_image(cb->mlx, WIN_WID, WIN_HGT);
	if (!cb->img->mlx_img)
		printf("%d\n", 3);
	cb->img->data = mlx_get_data_addr(cb->img->mlx_img,
			&cb->img->bits_per_pixel,
			&cb->img->line_length,
			&cb->img->endian);
	if (!cb->img->data)
		printf("%d\n", 4);
	return (0);
}

int	ft_init(t_cube *cb)
{
	cb->img = malloc(sizeof(t_img));
//	if (!cb->img || game_init(cb))
//		return (EXIT_FAILURE);
	game_init(cb);
	cb->pos.x = 3;//da fare dinamici
	cb->pos.y = 2;//
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
	if (ac != 2)
		return (1);
	ft_init(cb);
	cb->path = ft_strjoin("./Maps/", av[1]);
	if (check_map(&cb, cb->path) == 1)
		return (EXIT_FAILURE);
	int d = 0;
	int f = 0;
	while(cb->map.mat[d])
	{
		f = 0;
		while(cb->map.mat[d][f])
		{
			write(1, &cb->map.mat[d][f], 1);
			f++;
		}
		d++;
		write(1, "\n", 1);
	}
//	write(1,cb->path, 5);
	mlx_key_hook(cb->mlx_win, ft_key_hook, cb);
	mlx_hook(cb->mlx_win, 17, 0, ft_destroy, cb);
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
