#include "cub3d.h"

static void	fill_enemy_distances(t_cub3d *data, int *order, double *dist)
{
	int	i;

	i = -1;
	while (++i < data->map.enemy_count)
	{
		order[i] = i;
		dist[i] = (data->player.pos_x / data->tile
				- data->map.enemies[i].pos_x / data->tile)
			* (data->player.pos_x / data->tile
				- data->map.enemies[i].pos_x / data->tile)
			+ (data->player.pos_y / data->tile
				- data->map.enemies[i].pos_y / data->tile)
			* (data->player.pos_y / data->tile
				- data->map.enemies[i].pos_y / data->tile);
	}
}

static void	sort_enemy_arrays(t_cub3d *data, int *order, double *dist)
{
	int		i;
	int		j;
	int		tmp_i;
	double	tmp_d;

	i = -1;
	while (++i < data->map.enemy_count - 1)
	{
		j = i;
		while (++j < data->map.enemy_count)
		{
			if (dist[i] < dist[j])
			{
				tmp_d = dist[i];
				dist[i] = dist[j];
				dist[j] = tmp_d;
				tmp_i = order[i];
				order[i] = order[j];
				order[j] = tmp_i;
			}
		}
	}
}

void	sort_enemies_by_dist(t_cub3d *data, int *order, double *dist)
{
	fill_enemy_distances(data, order, dist);
	sort_enemy_arrays(data, order, dist);
}
