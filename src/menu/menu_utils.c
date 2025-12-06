#include "../../inc/cub3d.h"
#include <sys/time.h>

double	get_delta_time(void)
{
/* 	static struct timeval last_time;
	static int first_call = 1;
	struct timeval current_time;
	double delta;
	gettimeofday(&current_time, NULL);
	if first_call:
	    last_time = current_time;
	    first_call = 0;
	    return 0.0;
	Calculate delta in seconds
	delta = (current_time.tv_sec - last_time.tv_sec)
	      + (current_time.tv_usec - last_time.tv_usec) / 1000000.0;
	last_time = current_time;
	return delta;
	return (0.0); */
}

void	apply_difficulty_settings(t_cub3d *data)
{
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

void	apply_settings(t_cub3d *data)
{
/* 	Apply mouse sensibility
	float sensibility_values[] = {0.0, 0.5, 1.5, 2.0};
	data->mouse.sensitivity = sensibility_values[data->sensibility_level]; */
}
