/* Store gameplay parameters affected by difficulty/settings */
/* typedef struct s_game_settings
{
    int     player_health;        // Starting/max health
    float   enemy_speed_mult;     // Enemy speed multiplier
    float   enemy_damage_mult;    // Enemy damage multiplier
    int     enemy_count;          // Number of enemies
    float   resource_mult;        // Resource availability multiplier
}   t_game_settings; */

/* Track current menu selections and navigation state */
// Add t_cub3d structure ???
/* 
t_menu          menu;                 // Menu images and resources
t_game_settings game_settings;        // Game difficulty parameters
int             menu_choice;          // Current main menu selection (0-2)
int             difficulty_choice;    // Selected difficulty (0=Easy, 1=Med, 2=Hard)
int             sensibility_level;    // Mouse sensitivity (0-3)
double          fps_timer;            // Timer for FPS limiting */

/* Add new status states for menu system
 * MODIFY EXISTING enum e_status: */
/* typedef enum e_status
{
    MENU,              // Main menu screen
    DIFFICULTY_LEVEL,  // Difficulty selection
    SKIN_SELECT,       // Character/skin selection (optional)
    CREDITS,           // Credits screen
    GAME,              // Active gameplay
}   t_status; */

/* // Menu initialization
int     init_menu_images(t_cub3d *data);
void    init_menu_state(t_cub3d *data);
void    cleanup_menu(t_cub3d *data); */

/* // Menu rendering
void    render_main_menu(t_cub3d *data);
void    render_difficulty_menu(t_cub3d *data);
void    render_credits(t_cub3d *data);
int     render_game_handler(t_cub3d *data); */

/* // Menu event handling
int     handle_main_menu_keys(int keycode, t_cub3d *data);
int     handle_difficulty_keys(int keycode, t_cub3d *data);
int     menu_key_handler(int keycode, t_cub3d *data); */

/* // Menu utilities
double  get_delta_time(void);
void    apply_difficulty_settings(t_cub3d *data);
void    apply_settings(t_cub3d *data); */
