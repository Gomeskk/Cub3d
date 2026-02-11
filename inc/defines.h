#ifndef DEFINES_H
# define DEFINES_H

///          GAME SETTINGS          ///
# define HEIGHT 1080
# define WIDTH 1920
# define FPS 60
# define DIAGONAL_FACTOR 0.70710678  // 1v2 for diagonal movement normalization
# define MOUSE_SENSITIVITY 0.002
# define MOUSE_HIDE 1
# define M_PI           3.14159265358979323846  /* pi */

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
# define WRONG_CHAR "\033[1;35mcub3d:\033[1;0m map should contain only 'NSEW01' and spaces/tabs."
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