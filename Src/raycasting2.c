/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbozzi <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/06 15:23:26 by mbozzi            #+#    #+#             */
/*   Updated: 2023/04/07 16:03:04 by mbozzi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cube3D.h"

void	put_floor_sky(t_cube *cb)
{
	int	i;
	int	col;

	i = -1;
	while (++i < WIN_HGT / 2)
	{
		col = -1;
		while (++col < WIN_WID)
			ft_draw_pixels(col, i, cb->ceil, cb);
	}
	while (++i < WIN_HGT)
	{
		col = -1;
		while (++col < (WIN_WID))
			ft_draw_pixels(col, i, cb->floor, cb);
	}
}

void	wall_selector(t_cube *cb, int col, int index, int y)
{
	if (cb->ray.side == 0 && cb->ray.dir.x < 0)
		ft_draw_pixels(col, (index / WIN_WID),
			ft_get_pixels(cb->ray.offset, y, cb->tex[0]), cb);
	else if (cb->ray.side == 0 && cb->ray.dir.x > 0)
		ft_draw_pixels(col, (index / WIN_WID),
			ft_get_pixels(cb->ray.offset, y, cb->tex[1]), cb);
	else if (cb->ray.side == 1 && cb->ray.dir.y < 0)
		ft_draw_pixels(col, (index / WIN_WID),
			ft_get_pixels(cb->ray.offset, y, cb->tex[2]), cb);
	else if (cb->ray.side == 1 && cb->ray.dir.y > 0)
		ft_draw_pixels(col, (index / WIN_WID),
			ft_get_pixels(cb->ray.offset, y, cb->tex[3]), cb);
}

void	offset(t_cube *cb, int x, int y)
{
	if (cb->ray.side == 1)
		cb->ray.wall = cb->ray.pos.x + ((y - cb->p_pos.y \
	+ (1 - cb->ray.step.y) / 2) / cb->ray.dir.y) * cb->ray.dir.x;
	else
		cb->ray.wall = cb->ray.pos.y + ((x - cb->p_pos.x \
	+ (1 - cb->ray.step.x) / 2) / cb->ray.dir.x) * cb->ray.dir.y;
	cb->ray.wall -= floor(cb->ray.wall);
	cb->ray.offset = (int)(cb->ray.wall * (double)IMG_WID);
	if (cb->ray.side == 0 && cb->ray.dir.x > 0)
		cb->ray.offset = IMG_WID - cb->ray.offset - 1;
	if (cb->ray.side == 1 && cb->ray.dir.y < 0)
		cb->ray.offset = IMG_WID - cb->ray.offset - 1;
}

char	*extr_num(char	*s)
{
	while (*s && !ft_isdigit(*s))
		s++;
	return (s);
}

double	delta(t_cube *cb, char flag)
{
	if (flag == 'x')
		return (sqrt(1 + pow(cb->ray.dir.y, 2) / pow(cb->ray.dir.x, 2)));
	else if (flag == 'y')
		return (sqrt(1 + pow(cb->ray.dir.x, 2) / pow(cb->ray.dir.y, 2)));
	return (0);
}
