#include "../../inc/cub3d.h"
#include <sys/time.h>

// Convert menu sensibility level (0-4) to multiplier
double	get_sensibility_multiplier(int level)
{
	static const double multipliers[] = {0.0, 0.5, 1.0, 1.5, 2.0};
	
	if (level < 0 || level > 4)
		return (1.0);
	return (multipliers[level]);
}

void	apply_difficulty_settings(t_cub3d *data)
{
	int	i;

	if (data->menu.difficulty_choice == DIFF_EASY)
		data->game_settings.difficulty_mult = 0.60;
	else if (data->menu.difficulty_choice == DIFF_MEDIUM)
		data->game_settings.difficulty_mult = 1.0;
	else if (data->menu.difficulty_choice == DIFF_HARD)
		data->game_settings.difficulty_mult = 1.25;
	
	// Update all existing enemies with new difficulty values
	i = 0;
	while (i < data->map.enemy_count)
	{
		data->map.enemies[i].speed = ENEMY_SPEED_BASE * data->game_settings.difficulty_mult;
		data->map.enemies[i].vision_radius = ENEMY_VISION_RADIUS * data->game_settings.difficulty_mult;
		i++;
	}
}
