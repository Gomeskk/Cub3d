
#include "cub3d.h"

static void rotate_player(t_cub3d *data, double angle)
{
    double old_dirx;
    double old_diry;
    double old_planex;

    old_dirx = data->player.dir_x;
    old_diry = data->player.dir_y;
    old_planex = data->player.plane_x;
    
    data->player.dir_x = old_dirx * cos(angle) - old_diry * sin(angle);
    data->player.dir_y = old_dirx * sin(angle) + old_diry * cos(angle);

    // CRITICAL: Camera plane MUST rotate with direction for raycasting to work
    data->player.plane_x = old_planex * cos(angle) - data->player.plane_y * sin(angle);
    data->player.plane_y = old_planex * sin(angle) + data->player.plane_y * cos(angle);
}

// Keyboard-based rotation control using arrow keys
void update_keyboard_rotation(t_cub3d *data, double dt)
{
    double rotation_speed;
    double pitch_speed;
    double max_pitch_scaled;
    double base_rotation_speed;
    double base_pitch_speed;
    
    // Base speeds for keyboard rotation (adjust these values for desired feel)
    base_rotation_speed = 2.0 * dt;  // radians per second
    base_pitch_speed = 500.0 * dt;   // pixels per second for pitch
    
    // Scale MAX_PITCH based on current resolution height
    max_pitch_scaled = MAX_PITCH * ((double)data->current_height / (double)RES_4_HEIGHT);
    
    // Handle horizontal rotation (yaw) - LEFT and RIGHT arrow keys
    if (data->keys.arrow_left)
    {
        rotation_speed = -base_rotation_speed;  // Negative for left rotation
        rotate_player(data, rotation_speed);
    }
    if (data->keys.arrow_right)
    {
        rotation_speed = base_rotation_speed;   // Positive for right rotation
        rotate_player(data, rotation_speed);
    }
    
    // Handle vertical pitch (looking up/down) - UP and DOWN arrow keys
    if (data->keys.arrow_up)
    {
        pitch_speed = base_pitch_speed;  // Positive for looking up
        data->player.pitch += pitch_speed;
        
        // Constrain pitch to prevent over-rotation
        if (data->player.pitch > max_pitch_scaled)
            data->player.pitch = max_pitch_scaled;
    }
    if (data->keys.arrow_down)
    {
        pitch_speed = -base_pitch_speed;   // Negative for looking down
        data->player.pitch += pitch_speed;
        
        // Constrain pitch to prevent over-rotation
        if (data->player.pitch < -max_pitch_scaled)
            data->player.pitch = -max_pitch_scaled;
    }
}
