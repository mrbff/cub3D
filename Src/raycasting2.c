/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbozzi <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/06 15:23:26 by mbozzi            #+#    #+#             */
/*   Updated: 2023/04/06 16:08:05 by mbozzi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cube3D.h"

void	wall_selector(t_cube *cb, int col, int index)
{
	if (cb->ray.side == 0 && cb->ray.dir.x < 0)
		ft_draw_pixels(col, (index / WIN_WID), ft_get_pixels(cb->ray.offset, ((index / WIN_WID) % IMG_WID), cb->tex[0]), cb);
	else if (cb->ray.side == 0 && cb->ray.dir.x > 0)
		ft_draw_pixels(col, (index / WIN_WID), ft_get_pixels(cb->ray.offset, ((index / WIN_WID) % IMG_WID), cb->tex[1]), cb);
	else if (cb->ray.side == 1 && cb->ray.dir.y > 0)
		ft_draw_pixels(col, (index / WIN_WID), ft_get_pixels(cb->ray.offset, ((index / WIN_WID) % IMG_WID), cb->tex[2]), cb);
	else if (cb->ray.side == 1 && cb->ray.dir.y < 0)
		ft_draw_pixels(col, (index / WIN_WID), ft_get_pixels(cb->ray.offset, ((index / WIN_WID) % IMG_WID), cb->tex[3]), cb);
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
