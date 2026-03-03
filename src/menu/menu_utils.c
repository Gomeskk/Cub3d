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
	(void)data;
/* 	switch data->difficulty_choice:
	    case 0: // Easy
	        data->game_settings.player_health = 150;
	        data->game_settings.enemy_speed_mult = 0.75;
	        data->game_settings.enemy_damage_mult = 0.75;
	        break;
	    case 1: // Medium
	        data->game_settings.player_health = 100;
	        data->game_settings.enemy_speed_mult = 1.0;
	        data->game_settings.enemy_damage_mult = 1.0;
	        break;
	    case 2: // Hard
	        data->game_settings.player_health = 75;
	        data->game_settings.enemy_speed_mult = 1.5;
	        data->game_settings.enemy_damage_mult = 1.5;
	        break; */
}

