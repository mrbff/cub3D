/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbozzi <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/01 16:09:39 by mbozzi            #+#    #+#             */
/*   Updated: 2023/04/07 18:28:13 by mbozzi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3D.h"

int	lines_controll(t_cube *cb, int x, int y)
{
	cb->in_dir = 0;
	while (cb->map.mat[x])
	{
		y = 0;
		while (cb->map.mat[x][y])
		{
			if (cb->map.mat[x][y] != '0' && cb->map.mat[x][y] != '1' &&
				cb->map.mat[x][y] != 'N' && cb->map.mat[x][y] != 'S' &&
				cb->map.mat[x][y] != 'E' && cb->map.mat[x][y] != 'W' &&
				cb->map.mat[x][y] != 32)
				return (1);
			else if (cb->map.mat[x][y] == 'N' || cb->map.mat[x][y] == 'S'
				|| cb->map.mat[x][y] == 'E' || cb->map.mat[x][y] == 'W')
			{
				if (cb->in_dir)
                    return (1);
				cb->p_pos.x = (double)x;
				cb->p_pos.y = (double)y;
				cb->in_dir = cb->map.mat[x][y];
				cb->map.mat[x][y] = '0';
			}
			y++;
		}
		x++;
	}
	cb->map.lines = x;
	return (0);
}

int	check_map_error(t_cube *cb)
{
	cb->map.x = 0;
	cb->map.y = 0;
	if (lines_controll(cb, 0, 0))
		return (1);
	if (not_fenced(cb->map.mat, cb->p_pos.x, cb->p_pos.y))
		return (1);
	return (0);
}

int	check_map(t_cube *cb, char *path)
{
	if (ft_matrix(cb, path) == 1)
	{
		ft_printf("\033[0;31mError\nInvalid Map\n\033[0;37m");
		return (1);
	}
	if (check_map_error(cb) == 1)
	{
		while (cb->map.lines >= 0)
		{
			free(cb->map.mat[cb->map.lines]);
			cb->map.lines--;
		}
		free(path);
		free(cb->map.mat);
		ft_printf("\033[0;31mError\nMap Error\n\033[0;37m");
		return (1);
	}
	return (0);
}
