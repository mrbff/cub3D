/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbozzi <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/01 16:09:39 by mbozzi            #+#    #+#             */
/*   Updated: 2023/04/06 17:05:02 by mbozzi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cube3D.h"

int	wall_controll(t_cube **cb, int x, int y, int flag)
{
	if (flag == 1)
	{
		if ((*cb)->map.mat[x][y + 1] == '1' && (*cb)->map.mat[x][y - 1] == '1'\
		&& (*cb)->map.mat[x + 1][y] == '1' && (*cb)->map.mat[x - 1][y] == '1')
			return (1);
	}
	if (flag == 0)
	{
		while ((*cb)->map.mat[x][y])
		{
			if ((*cb)->map.mat[x][y] != '1')
				return (1);
			y++;
		}
	}
	return (0);
}

int	lines_controll(t_cube **cb, int x, int y, int len)
{
	while (x < (*cb)->map.lines - 1)
	{
		if ((*cb)->map.mat[x][0] != '1' || (*cb)->map.mat[x][len - 1] != '1')
			return (1);
		while ((*cb)->map.mat[x][y] != '\0')
		{
			if ((*cb)->map.mat[x][y] != '0' && (*cb)->map.mat[x][y] != '1' &&
				(*cb)->map.mat[x][y] != 'N' && (*cb)->map.mat[x][y] != 'S' &&
				(*cb)->map.mat[x][y] != 'E' && (*cb)->map.mat[x][y] != 'W')
				return (1);
			else if ((*cb)->map.mat[x][y] == 'N' || (*cb)->map.mat[x][y] == 'S'
				|| (*cb)->map.mat[x][y] == 'E' || (*cb)->map.mat[x][y] == 'W')
			{
				(*cb)->p_pos.x = (double)x;
				(*cb)->p_pos.y = (double)y;
				(*cb)->map.mat[x][y] = '0';
			}
			y++;
		}
		x++;
		y = 0;
	}
	if (wall_controll(cb, x, y, 0) == 1)
		return (1);
	return (0);
}

int	check_map_error(t_cube **cb)
{
	(*cb)->map.x = 0;
	(*cb)->map.y = 0;
	if (wall_controll(cb, (*cb)->map.x, (*cb)->map.y, 0) == 1)
		return (1);
	(*cb)->map.x++;
	if (lines_controll(cb, (*cb)->map.x, (*cb)->map.y,
			ft_strlen((*cb)->map.mat[0])) == 1)
		return (1);
	return (0);
}

int	check_map(t_cube **cb, char *path)
{
	if (ft_matrix(cb, path) == 1)
	{
		ft_printf("\033[0;31mError\nInvalid Map\n\033[0;37m");
		return (1);
	}
	if (check_map_error(cb) == 1)
	{
		while ((*cb)->map.lines >= 0)
		{
			free((*cb)->map.mat[(*cb)->map.lines]);
			(*cb)->map.lines--;
		}
		free(path);
		free((*cb)->map.mat);
		ft_printf("\033[0;31mError\nMap Error\n\033[0;37m");
		return (1);
	}
	return (0);
}
