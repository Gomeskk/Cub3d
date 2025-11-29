/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bpires-r <bpires-r@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/22 21:21:01 by bpires-r          #+#    #+#             */
/*   Updated: 2025/11/09 16:01:57 by bpires-r         ###   ########.fr       */
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

int	check_map_name(char *map)
{
	int	i;

	i = 0;
	while (map[i] && map[i] != '.')
		i++;
	while (map[i])
	{
		if (!ft_strcmp(&map[i], ".cub") && !map[i + 4])
			return (1);
		i++;
	}
	return (0);	
}
