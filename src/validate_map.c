
#include "cub3d.h"

static int	check_row_all_ones(char *row)
{
	int	i;

	if (!row)
		return (0);
	i = 0;
	while (row[i])
	{
		if (row[i] != '1' && row[i] != '\n')
			return (0);
		i++;
	}
	return (1);
}

int	validate_map(t_map *map)
{
	int	i;
	int	len;

	if (!map || !map->map)
		return (0);
	len = map->col_count;
	if (!check_row_all_ones(map->map[0])
		|| !check_row_all_ones(map->map[map->row_count - 1]))
		return (0);
	i = 0;
	while (i < map->row_count)
	{
		if ((int)strlen(map->map[i]) != len)
			return (0);
		if (map->map[i][0] != '1' || map->map[i][len - 1] != '1')
			return (0);
		i++;
	}
	return (1);
}
