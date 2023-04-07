/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbozzi <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/01 15:49:54 by mbozzi            #+#    #+#             */
/*   Updated: 2023/04/01 15:54:51 by mbozzi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cube3D.h"

int	start_controll(char *line)
{
	int	i;

	i = -1;
	if (!line || line[0] == '\n')
		return (1);
	while (line[++i])
	{
		if ((line[i] != '1' && line[i] != '\n' && line[i] != ' '))
			return (1);
	}
	return (0);
}

void	get_matrix(t_cube *cb, char *path)
{
	static char	*buff;

	if (!buff)
		buff = ft_calloc(sizeof(char), 1);
	cb->map.fd = open(path, O_RDONLY);
	cb->map.line = get_next_line(cb->map.fd);
	while (start_controll(cb->map.line))
	{
		free(cb->map.line);
		cb->map.line = get_next_line(cb->map.fd);
	}
	while (cb->map.line != NULL)
	{
		buff = ft_strjoin2(buff, cb->map.line);
		free(cb->map.line);
		cb->map.line = get_next_line(cb->map.fd);
	}
	close(cb->map.fd);
	free(cb->map.line);
	cb->map.mat = ft_split(buff, '\n');
	free(buff);
}

int	ft_matrix(t_cube *cb, char *path)
{
	cb->map.lines = 0;
	cb->map.fd = open(path, O_RDONLY);
	if (cb->map.fd == -1)
	{
		close(cb->map.fd);
		free(path);
		return (1);
	}
	cb->map.line = get_next_line(cb->map.fd);
	while (start_controll(cb->map.line))
	{
		free(cb->map.line);
		cb->map.line = get_next_line(cb->map.fd);
	}
	while (cb->map.line != NULL)
	{
		free(cb->map.line);
		cb->map.line = get_next_line(cb->map.fd);
		cb->map.lines++;
	}
	free(cb->map.line);
	close(cb->map.fd);
	get_matrix(cb, path);
	return (0);
}
