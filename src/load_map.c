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

    if (!line)
        return ;
    len = ft_strlen(line);
    if (len > 0 && line[len - 1] == '\n')
        line[len - 1] = '\0';
}

static int	find_max_width(char **map, int row_count)
{
    int	max_len;
    int	i;
    int	current_len;

    max_len = 0;
    i = 0;
    while (i < row_count)
    {
        current_len = ft_strlen(map[i]);
        if (current_len > max_len)
            max_len = current_len;
        i++;
    }
    return (max_len);
}

static void	normalize_map_row(char **map, int row, int max_len)
{
    char	*new_row;
    int		old_len;
    int		i;

    old_len = ft_strlen(map[row]);
    if (old_len >= max_len)
        return ;
    new_row = (char *)malloc(sizeof(char) * (max_len + 1));
    if (!new_row)
        return ;
    i = 0;
    while (map[row][i])
    {
        new_row[i] = map[row][i];
        i++;
    }
    while (i < max_len)
    {
        new_row[i] = ' ';
        i++;
    }
    new_row[i] = '\0';
    free(map[row]);
    map[row] = new_row;
}

static void	normalize_map(t_map *map)
{
    int	max_width;
    int	i;

    max_width = find_max_width(map->map, map->row_count);
    map->col_count = max_width;
    i = 0;
    while (i < map->row_count)
    {
        normalize_map_row(map->map, i, max_width);
        i++;
    }
}

static int	read_lines(t_map *map, int fd)
{
    int		i;
    char	*line;

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
    normalize_map(map);
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
    read_lines(map, fd);
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
