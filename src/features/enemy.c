#include "cub3d.h"

void	init_enemies(t_cub3d *data)
{
	int	y;
	int	x;

	data->map.enemy_count = 0;
	y = -1;
	while (++y < data->map.row_count)
	{
		x = -1;
		while (++x < data->map.col_count && data->map.grid[y][x])
		{
			if (data->map.grid[y][x] == 'F')
				data->map.enemy_count++;
		}
	}
	if (data->map.enemy_count == 0)
	{
		data->map.enemies = NULL;
		return ;
	}
	data->map.enemies = malloc(sizeof(t_enemy) * data->map.enemy_count);
	if (!data->map.enemies)
		data->map.enemy_count = 0;
}

void	store_enemy_positions(t_cub3d *data)
{
	int	y;
	int	x;
	int	i;
	int	min_x;
	int	max_x;

	i = 0;
	y = -1;
	while (++y < data->map.row_count)
	{
		x = -1;
		while (++x < data->map.col_count && data->map.grid[y][x])
		{
			if (data->map.grid[y][x] != 'F')
				continue ;
			data->map.enemies[i].grid_x = x;
			data->map.enemies[i].grid_y = y;
			data->map.enemies[i].dir = 1.0;
			min_x = scan_patrol_min(data, y, x);
			max_x = scan_patrol_max(data, y, x);
			data->map.enemies[i].patrol_min = (double)min_x;
			data->map.enemies[i].patrol_max = (double)max_x;
			data->map.enemies[i].speed = ENEMY_SPEED_BASE * data->game_settings.difficulty_mult;
			data->map.enemies[i].vision_radius = ENEMY_VISION_RADIUS * data->game_settings.difficulty_mult;
			data->map.enemies[i].chasing = 0;
			data->map.grid[y][x] = '0';
			i++;
		}
	}
}

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
