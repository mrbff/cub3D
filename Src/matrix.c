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

#include "../cub3D.h"

int	start_controll(char *line)
{
	int	i;

	i = -1;
	if (!line)
		return (0);
	if (line[0] == '\n')
		return (1);
	while (line[++i])
	{
		if ((line[i] != '1' && line[i] != ' '
				&& line[i] != '\n' && line[i] != '\t'))
			return (1);
	}
	return (0);
}

void	get_matrix(t_cube *cb)
{
	static char	*buff;

	if (!buff)
		buff = ft_calloc(sizeof(char), 1);
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

int	ctrl_ext(char *path)
{
	char	**ext;
	int		ret;
	int		i;

	if (!ft_strchr(path, '.'))
		return (1);
	ext = ft_split(path, '.');
	ret = ft_strncmp(ext[1], "cub", 4);
	i = -1;
	while (ext[++i])
		free(ext[i]);
	free(ext);
	return (ret);
}

int	ft_matrix(t_cube *cb, char *path)
{
	cb->map.lines = 0;
	cb->map.fd = open(path, O_RDONLY);
	if (cb->map.fd == -1 || ctrl_ext(path))
	{
		close(cb->map.fd);
		free(path);
		return (1);
	}
	get_matrix(cb);
	return (0);
}
