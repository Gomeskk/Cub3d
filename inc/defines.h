#ifndef DEFINES_H
# define DEFINES_H

///          GAME SETTINGS          ///
# define HEIGHT 1080
# define WIDTH 1920
# define FPS 60
# define DIAGONAL_FACTOR 0.70710678  // 1v2 for diagonal movement normalization
# define MOUSE_SENSITIVITY 0.02
# define MOUSE_HIDE 1
# define MAX_PITCH 1000.0  // Maximum pitch in pixels (looking up/down)
# define SPRINT_MULTIPLIER 1.8  // Sprint speed multiplier when Shift is held
# define CROUCH_MULTIPLIER 0.5  // Crouch speed multiplier when Ctrl is held
# define CROUCH_HEIGHT -150.0  // Camera height offset when crouching (negative = lower)
# define CROUCH_TRANSITION_SPEED 600.0  // Speed of crouch transition
# define JUMP_VELOCITY 280.0  // Initial upward velocity when jumping (slower rise)
# define GRAVITY_RISE 700.0  // Gravity when rising (slower deceleration)
# define GRAVITY_FALL 1400.0  // Gravity when falling (faster fall)
# define MAX_JUMP_HEIGHT 200.0  // Maximum vertical offset from ground
# define FOV_NORMAL 0.66  // Standard field of view
# define FOV_NARROW 0.33  // Zoomed in (narrow FOV)
# define FOV_WIDE 0.90  // Zoomed out (wide FOV)
# define M_PI           3.14159265358979323846

///          ENEMY SETTINGS          ///
# define ENEMY_SPEED_BASE 40.0 // podes usar
# define ENEMY_VISION_RADIUS 2.5 // podes usar
# define ENEMY_CHASE_SPEED_MULT 2.0 // podes usar 
# define ENEMY_COLLISION_RADIUS 0.3


///          MENU SETTINGS          ///
# define KEY_THROTTLE_MS 200
# define VOLUME_MIN 0
# define VOLUME_MAX 14
# define VOLUME_COUNT 15
# define VOLUME_DEFAULT 7
# define SENSIBILITY_MIN 0
# define SENSIBILITY_MAX 4
# define SENSIBILITY_COUNT 5
# define SENSIBILITY_DEFAULT 2
# define RESOLUTION_MIN 0
# define RESOLUTION_MAX 4
# define RESOLUTION_COUNT 5
# define RESOLUTION_DEFAULT 4
# define RES_0_WIDTH 960
# define RES_0_HEIGHT 540
# define RES_1_WIDTH 1280
# define RES_1_HEIGHT 720
# define RES_2_WIDTH 1440
# define RES_2_HEIGHT 810
# define RES_3_WIDTH 1600
# define RES_3_HEIGHT 900
# define RES_4_WIDTH 1920
# define RES_4_HEIGHT 1080
# define VOLUME_IMG_X 203
# define VOLUME_IMG_Y 392
# define SENSIBILITY_IMG_X 197
# define SENSIBILITY_IMG_Y 876
# define SECTION_COUNT 3
# define ARROW_DIRECTION_DOWN -1

///         ERROR HANDLE            ///
# define WRONG_ARGC "\033[1;35mcub3d:\033[1;0m singular map argument expected."
# define WRONG_MAP_NAME "\033[1;35mcub3d:\033[1;0m .cub argument extended expected."
# define MAP_ERROR "\033[1;35mcub3d:\033[1;0m map error."
# define WRONG_MAP "\033[1;35mcub3d:\033[1;0m non acceptable map."
# define NO_IDENTIFIERS "\033[1;35mcub3d:\033[1;0m non acceptable identifiers."
# define DUP_NO "\033[1;35mcub3d:\033[1;0m duplicated 'NO'."
# define DUP_SO "\033[1;35mcub3d:\033[1;0m duplicated 'SO'."
# define DUP_EA "\033[1;35mcub3d:\033[1;0m duplicated 'EA'."
# define DUP_WE "\033[1;35mcub3d:\033[1;0m duplicated 'WE'."
# define DUP_CEILING "\033[1;35mcub3d:\033[1;0m duplicated 'C'."
# define DUP_FLOOR "\033[1;35mcub3d:\033[1;0m duplicated 'F'."
# define NO_MISSING "\033[1;35mcub3d:\033[1;0m 'NO' path to texture is required."
# define SO_MISSING "\033[1;35mcub3d:\033[1;0m 'SO' path to texture is required."
# define EA_MISSING "\033[1;35mcub3d:\033[1;0m 'EA' path to texture is required."
# define WE_MISSING "\033[1;35mcub3d:\033[1;0m 'WE' path to texture is required."
# define C_MISSING "\033[1;35mcub3d:\033[1;0m 'C' path to texture is required."
# define F_MISSING "\033[1;35mcub3d:\033[1;0m 'F' path to texture is required."
# define TEXTURES "\033[1;37mPlease make sure to add all the textures and place them at the top of the file.\033[1;0m\n"
# define WRONG_CHAR "\033[1;35mcub3d:\033[1;0m map should contain only 'NSEW01D' and spaces/tabs."
# define NON_DIGIT "\033[1;35mcub3d:\033[1;0m C's && F's parameters should contain only digits.\n\
\033[1;37mHere's an Example:\033[1;0m\n\
F 220,100,0 \n\
C 255,0,30"
# define CF_OVERFLOW "\033[1;35mcub3d:\033[1;0m C's && F's parameters should be 3 unsigned char, representing RGB, in a range of 0-255 separated by one comma each.\n\n\
\033[1;37mHere's an Example:\033[1;0m\n\
\033[1;31mR:\033[1;0m 220\n\
\033[1;32mG:\033[1;0m 100\n\
\033[1;34mB:\033[1;0m 0\n\
\033[1;37mF 220,100,0 \033[1;0m\n\
\n\033[1;31mR: \033[1;0m255\n\
\033[1;32mG: \033[1;0m0\n\
\033[1;34mB: \033[1;0m30\n\
\033[1;37mC 255,0,30\033[1;0m"
# define COMMA "\033[1;35mcub3d:\033[1;0m C's && F's parameters should be separated by one comma each any other character is Error. \n\
\033[1;37mHere's an Example:\033[1;0m\n\
F 220,100,0 \n\
C 255,0,30"
# define NO_CLOSED "\033[1;35mcub3d:\033[1;0m map should be closed by walls, 1's, and contain only the characters '0' 'NSEW'." 
# define EXAMPLE "\033[1;37mHere's an Example of a .cub file:\033[1;0m\n\
\033[1;35mNO\033[1;0m ./path_to_the_north_texture \n\
\033[1;35mSO\033[1;0m ./path_to_the_south_texture \n\
\033[1;35mWE\033[1;0m ./path_to_the_west_texture \n\
\033[1;35mEA\033[1;0m ./path_to_the_east_texture \n\
\033[1;35mF \033[1;0m220,100,0 \n\
\033[1;35mC \033[1;0m225,30,0 \n\n\
        1111111111111111111111111 \n\
        1000000000110000000000001 \n\
        1011000001110000000000001 \n\
        1001000000000000000000001 \n\
111111111011000001110000000000001 \n\
100000000011000001110111111111111 \n\
11110111111111011100000010001 \n\
11110111111111011101010010001 \n\
11000000110101011100000010001 \n\
10000000000000001100000010001 \n\
10000000000000001101010010001 \n\
11000001110101011111011110N0111 \n\
11110111 1110101 101111010001 \n\
11111111 1111111 111111111111 \n\
"
# define PLAYER_POINT "\033[1;35mcub3d:\033[1;0m Players starting point should be exactly 1.\n\n\
\033[1;37mHere's an Example:\033[1;0m\n\
 111\n\
10N01\n\
 111"

#endif