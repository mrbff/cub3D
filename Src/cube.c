/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cube.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbozzi <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/31 18:53:31 by mbozzi            #+#    #+#             */
/*   Updated: 2023/04/07 10:46:01 by mabaffo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cube3D.h"

static void	we(t_cube *cb)
{
	if (cb->in_dir == 'E')
	{
		cb->cam.x = FOV;
		cb->cam.y = 0;
		cb->p_dir.x = 0;
		cb->p_dir.y = 1;
	}
	else if (cb->in_dir == 'W')
	{
		cb->cam.x = -FOV;
		cb->cam.y = 0;
		cb->p_dir.x = 0;
		cb->p_dir.y = -1;
	}
}

static void	init_dir(t_cube *cb)
{
	if (cb->in_dir == 'N')
	{
		cb->cam.x = 0;
		cb->cam.y = FOV;
		cb->p_dir.x = -1;
		cb->p_dir.y = 0;
	}
	else if (cb->in_dir == 'S')
	{
		cb->cam.x = 0;
		cb->cam.y = -FOV;
		cb->p_dir.x = 1;
		cb->p_dir.y = 0;
	}
	else
		we(cb);
}

static int	game_init(t_cube *cb)
{
	cb->mlx = mlx_init();
	cb->mlx_win = mlx_new_window(cb->mlx, WIN_WID, WIN_HGT, "cube3D");
	cb->img->mlx_img = mlx_new_image(cb->mlx, WIN_WID, WIN_HGT);
	if (!cb->img->mlx_img)
		return (1);
	cb->img->data = mlx_get_data_addr(cb->img->mlx_img,
			&cb->img->bits_per_pixel,
			&cb->img->line_length,
			&cb->img->endian);
	if (!cb->img->data)
		return (1);
	return (0);
}

int	main(int ac, char **av)
{
	t_cube	*cb;

	(void)ac;
	cb = malloc(sizeof(t_cube));
	cb->img = malloc(sizeof(t_img));
	if (!cb->img || game_init(cb))
		return (EXIT_FAILURE);
	cb->path = ft_strjoin("./Maps/", av[1]);
	if (check_map(cb, cb->path) == 1)
		return (EXIT_FAILURE);
	init_dir(cb);
	texture_init(cb);
	raycasting(cb);
	mlx_key_hook(cb->mlx_win, ft_key_hook, cb);
	mlx_hook(cb->mlx_win, 17, 0, ft_destroy, cb);
	mlx_loop(cb->mlx);
}
