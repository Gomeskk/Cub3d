#include "cub3d.h"

void	check_enemy_detection(t_cub3d *data)
{
	int		i;
	double	dx;
	double	dy;
	double	dist;
	double	radius_px;

	i = -1;
	while (++i < data->map.enemy_count)
	{
		if (data->map.enemies[i].chasing)
			continue ;
		dx = data->player.pos_x - data->map.enemies[i].pos_x;
		dy = data->player.pos_y - data->map.enemies[i].pos_y;
		dist = sqrt(dx * dx + dy * dy);
		radius_px = data->map.enemies[i].vision_radius * data->tile;
		if (dist < radius_px)
			data->map.enemies[i].chasing = 1;
	}
}

int	check_enemy_collision(t_cub3d *data)
{
	int		i;
	double	dx;
	double	dy;
	double	dist;
	double	collision_px;

	i = -1;
	while (++i < data->map.enemy_count)
	{
		dx = data->player.pos_x - data->map.enemies[i].pos_x;
		dy = data->player.pos_y - data->map.enemies[i].pos_y;
		dist = sqrt(dx * dx + dy * dy);
		collision_px = ENEMY_COLLISION_RADIUS * data->tile;
		if (dist < collision_px)
			return (1);
	}
	return (0);
}

void	update_enemies(t_cub3d *data, double dt)
{
	int	i;

	i = -1;
	while (++i < data->map.enemy_count)
	{
		if (data->map.enemies[i].chasing)
			chase_player(data, &data->map.enemies[i], dt);
		else
			patrol_enemy(data, &data->map.enemies[i], dt);
	}
}
