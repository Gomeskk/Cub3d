
#ifndef CUB3D_H
# define CUB3D_H

# include <mlx.h>
# include <stdlib.h>

# define HEIGHT 1080
# define WIDTH 1920
# define TILE_SIZE 64
# define FPS 60

typedef struct s_player
{
    double  x;
    double  y;
    double  angle;
    int     turn_dir;   // -1 left, 1 right
    int     walk_dir;   // -1 back, 1 front
    double  move_speed;
    double  rot_speed;
}   t_player;

typedef struct s_map
{
    char    **lines;
    int     width;
    int     height;
}   t_map;

typedef struct s_game
{
    void    *mlx_ptr; // connection to MLX
    void    *win_ptr; // window reference
    t_player player;
    t_map   map;
}   t_game;

#endif
