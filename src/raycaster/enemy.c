#include "cub3d.h"

static int	scan_patrol_min(t_cub3d *data, int grid_y, int grid_x)
{
	int	x;

	x = grid_x - 1;
	while (x >= 0 && data->map.grid[grid_y][x] != '1'
		&& data->map.grid[grid_y][x] != 'D'
		&& data->map.grid[grid_y][x] != ' ')
		x--;
	return (x + 1);
}

static int	scan_patrol_max(t_cub3d *data, int grid_y, int grid_x)
{
	int	x;

	x = grid_x + 1;
	while (x < data->map.col_count && data->map.grid[grid_y][x] != '1'
		&& data->map.grid[grid_y][x] != 'D'
		&& data->map.grid[grid_y][x] != ' ')
		x++;
	return (x - 1);
}

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

static int	enemy_can_move(t_cub3d *data, double px, double py)
{
	int	gx;
	int	gy;

	gx = (int)(px / data->tile);
	gy = (int)(py / data->tile);
	if (gx < 0 || gx >= data->map.col_count
		|| gy < 0 || gy >= data->map.row_count)
		return (0);
	if (data->map.grid[gy][gx] == '1' || data->map.grid[gy][gx] == 'D')
		return (0);
	return (1);
}

static void	chase_player(t_cub3d *data, t_enemy *enemy, double dt)
{
	double	dx;
	double	dy;
	double	dist;
	double	speed;
	double	new_x;
	double	new_y;

	dx = data->player.pos_x - enemy->pos_x;
	dy = data->player.pos_y - enemy->pos_y;
	dist = sqrt(dx * dx + dy * dy);
	if (dist < 0.001)
		return ;
	speed = enemy->speed * (ENEMY_CHASE_SPEED_MULT * data->game_settings.difficulty_mult);
	new_x = enemy->pos_x + (dx / dist) * speed * dt;
	new_y = enemy->pos_y + (dy / dist) * speed * dt;
	if (enemy_can_move(data, new_x, enemy->pos_y))
		enemy->pos_x = new_x;
	if (enemy_can_move(data, enemy->pos_x, new_y))
		enemy->pos_y = new_y;
}

static void	patrol_enemy(t_cub3d *data, t_enemy *enemy, double dt)
{
	double	new_x;
	double	speed;
	double	min_px;
	double	max_px;

	speed = enemy->speed;
	new_x = enemy->pos_x + enemy->dir * speed * dt;
	min_px = (enemy->patrol_min + 0.5) * data->tile;
	max_px = (enemy->patrol_max + 0.5) * data->tile;
	if (new_x <= min_px || new_x >= max_px)
	{
		enemy->dir *= -1.0;
		if (new_x <= min_px)
			new_x = min_px;
		else
			new_x = max_px;
	}
	enemy->pos_x = new_x;
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
