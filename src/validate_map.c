#include "cub3d.h"

static int	is_valid_tile(char tile)
{
    return (tile == '0' || tile == '1' || tile == ' ' ||
        tile == 'N' || tile == 'S' || tile == 'E' || tile == 'W');
}

static int	check_first_last_row(t_map *map)
{
    int	j;

    j = 0;
    while (j < map->col_count)
    {
        if (map->map[0][j] != '1' && map->map[0][j] != ' ')
            return (0);
        j++;
    }
    j = 0;
    while (j < map->col_count)
    {
        if (map->map[map->row_count - 1][j] != '1' && 
            map->map[map->row_count - 1][j] != ' ')
            return (0);
        j++;
    }
    return (1);
}

static int	check_first_last_col(t_map *map)
{
    int	i;

    i = 0;
    while (i < map->row_count)
    {
        if (map->map[i][0] != '1' && map->map[i][0] != ' ')
            return (0);
        i++;
    }
    i = 0;
    while (i < map->row_count)
    {
        if (map->map[i][map->col_count - 1] != '1' && 
            map->map[i][map->col_count - 1] != ' ')
            return (0);
        i++;
    }
    return (1);
}

static int	check_wall_integrity(t_map *map)
{
    int	i;
    int	j;

    i = 1;
    while (i < map->row_count - 1)
    {
        j = 1;
        while (j < map->col_count - 1)
        {
            if (map->map[i][j] == '0' || map->map[i][j] == 'N' ||
                map->map[i][j] == 'S' || map->map[i][j] == 'E' || 
                map->map[i][j] == 'W')
            {
                if (map->map[i-1][j] == ' ' || map->map[i+1][j] == ' ' ||
                    map->map[i][j-1] == ' ' || map->map[i][j+1] == ' ')
                    return (0);
            }
            j++;
        }
        i++;
    }
    return (1);
}

int	validate_map(t_map *map)
{
    int	i;
    int	j;

    if (!map || !map->map)
        return (0);
    i = 0;
    while (i < map->row_count)
    {
        j = 0;
        while (j < map->col_count)
        {
            if (!is_valid_tile(map->map[i][j]))
                return (0);
            j++;
        }
        i++;
    }
    if (!check_first_last_row(map))
        return (0);
    if (!check_first_last_col(map))
        return (0);
    if (!check_wall_integrity(map))
        return (0);
    return (1);
}
