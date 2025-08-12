
#include "cub3d.h"

static int	count_lines(char *file)
{
	int		fd;
	int		count;
	char	*line;

	fd = open(file, O_RDONLY);
	if (fd < 0)
		return (-1);
	count = 0;
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

static void	trim_newline(char *line)
{
	int	len;

	len = ft_strlen(line);
	if (len > 0 && line[len - 1] == '\n')
		line[len - 1] = '\0';
}

static int	read_lines(t_map *map, int fd, int lines)
{
	int		i;
	char	*line;

	(void)lines;
	i = 0;
	line = get_next_line(fd);
	while (line)
	{
		trim_newline(line);
		map->map[i++] = ft_strdup(line);
		free(line);
		line = get_next_line(fd);
	}
	map->map[i] = NULL;
	map->col_count = ft_strlen(map->map[0]);
	return (0);
}

int	load_map(t_map *map, char *file)
{
	int	lines;
	int	fd;

	lines = count_lines(file);
	if (lines <= 0)
		return (1);
	fd = open(file, O_RDONLY);
	if (fd < 0)
		return (1);
	map->map = malloc(sizeof(char *) * (lines + 1));
	if (!map->map)
		return (close(fd), 1);
	map->row_count = lines;
	read_lines(map, fd, lines);
	close(fd);
	return (0);
}

void	free_map(t_map *map)
{
	int	i;

	if (!map || !map->map)
		return ;
	i = 0;
	while (map->map[i])
		free(map->map[i++]);
	free(map->map);
	map->map = NULL;
}
