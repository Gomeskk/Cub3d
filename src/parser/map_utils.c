/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bpires-r <bpires-r@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/01 16:26:03 by bpires-r          #+#    #+#             */
/*   Updated: 2025/12/06 22:55:19 by bpires-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	count_lines(char *map)
{
	char	*line;
	int		count;
	int		fd;

	count = 0;
	fd = open(map, O_RDONLY);
	line = get_next_line(fd);
	while (line)
	{
		free(line);
		count++;
		line = get_next_line(fd);
	}
	close(fd);
	return (count);
}

int	read_map(char *map, t_cub3d *data)
{
	int		fd;
	int		i;
	char	*trim;
	char	*line;

	i = 0;
	fd = open(map, O_RDONLY);
	if (fd < 0)
		return (0);
	data->map.row_count = count_lines(map);
	data->map.map = malloc(sizeof(char *) * (data->map.row_count + 1));
	if (!data->map.map)
		return (close(fd), 0);
	line = get_next_line(fd);
	while (line)
	{
		trim = ft_strtrim(line, "\n");
		data->map.map[i] = ft_strdup(trim);
		free(trim);
		free(line);
		line = get_next_line(fd);
		i++;
	}
	data->map.map[i] = NULL;
	close(fd);
	return (1);
}

void	copy_line(char **dest, char *src, int max_x)
{
	int	i;

	i = 0;
	while (i < max_x)
	{
		if (i < (int)ft_strlen(src))
		{
			if (src[i] == '\t')
				(*dest)[i] = ' ';
			else
				(*dest)[i] = src[i];	
		}
		else
			(*dest)[i] = ' ';
		i++;
	}
	(*dest)[i] = '\0';
}

int	is_map_line(char c)
{
	if (c == ' ')
		return (1);
	return (ft_strchr("NSEW01DBF", c) != NULL);
}
