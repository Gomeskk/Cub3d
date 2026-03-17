#include "cub3d.h"

int	circle_intersects_rectangle(t_cub3d *data,
	t_circle_center center, int row, int col)
{
	double	rect_x;
	double	rect_y;
	double	dx;
	double	dy;

	rect_x = (double)col * (double)data->tile;
	rect_y = (double)row * (double)data->tile;
	if (center.x < rect_x)
		dx = rect_x;
	else if (center.x > rect_x + (double)data->tile)
		dx = rect_x + (double)data->tile;
	else
		dx = center.x;
	if (center.y < rect_y)
		dy = rect_y;
	else if (center.y > rect_y + (double)data->tile)
		dy = rect_y + (double)data->tile;
	else
		dy = center.y;
	dx = center.x - dx;
	dy = center.y - dy;
	return (dx * dx + dy * dy
		<= (double)data->player.radius * (double)data->player.radius);
}

void	get_col_range(t_cub3d *data, t_circle_center center,
	int *col_range)
{
	col_range[0] = (int)floor((center.x - data->player.radius)
			/ (double)data->tile);
	col_range[1] = floor((center.x + data->player.radius) / (double)data->tile);
	if (col_range[0] < 0)
		col_range[0] = 0;
	if (col_range[1] >= data->map.col_count)
		col_range[1] = data->map.col_count - 1;
}

int	row_has_collision(t_cub3d *data, t_circle_center center,
	int row, int *col_range)
{
	int	col;

	col = col_range[0];
	while (col <= col_range[1])
	{
		if (is_blocking_cell(data, row, col))
			if (circle_intersects_rectangle(data, center, row, col))
				return (1);
		col++;
	}
	return (0);
}

int	check_collision_range(t_cub3d *data,
	t_circle_center center, int start_row, int end_row)
{
	int	row;
	int	col_range[2];

	get_col_range(data, center, col_range);
	if (start_row > end_row || col_range[0] > col_range[1])
		return (0);
	row = start_row;
	while (row <= end_row)
	{
		if (row_has_collision(data, center, row, col_range))
			return (1);
		row++;
	}
	return (0);
}

int	circle_collides_wall(t_cub3d *data, double cx, double cy)
{
	int				start_row;
	int				end_row;
	t_circle_center	center;

	if (cx + data->player.radius < 0
		|| cx - data->player.radius >= data->map.col_count * data->tile
		|| cy + data->player.radius < 0
		|| cy - data->player.radius >= data->map.row_count * data->tile)
		return (1);
	start_row = (int)floor((cy - data->player.radius) / (double)data->tile);
	end_row = (int)floor((cy + data->player.radius) / (double)data->tile);
	center.x = cx;
	center.y = cy;
	if (start_row < 0)
		start_row = 0;
	if (end_row >= data->map.row_count)
		end_row = data->map.row_count - 1;
	return (check_collision_range(data, center, start_row, end_row));
}
