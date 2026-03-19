#include "cub3d.h"

/*
** Draws a horizontal border line at the specified y position.
** Fills the entire width with black pixels.
*/
static void    draw_horizontal_line(t_cub3d *data, int y)
{
    int    x;

    x = 0;
    while (x < data->current_width)
    {
        pixel_put(&data->img, x, y, 0x800080);
        x++;
    }
}

/*
** Draws the top and bottom borders of the screen.
** Border thickness defined by BORDER_THICKNESS.
*/
static void    draw_horizontal_borders(t_cub3d *data)
{
    int    y;

    y = 0;
    while (y < BORDER_THICKNESS)
    {
        draw_horizontal_line(data, y);
        y++;
    }
    y = data->current_height - BORDER_THICKNESS;
    while (y < data->current_height)
    {
        draw_horizontal_line(data, y);
        y++;
    }
}

/*
** Draws the left and right borders at the specified y position.
** Only draws the vertical edges, not the full width.
*/
static void    draw_vertical_edges(t_cub3d *data, int y)
{
    int    x;

    x = 0;
    while (x < BORDER_THICKNESS)
    {
        pixel_put(&data->img, x, y, 0x800080);
        x++;
    }
    x = data->current_width - BORDER_THICKNESS;
    while (x < data->current_width)
    {
        pixel_put(&data->img, x, y, 0x800080);
        x++;
    }
}

/*
** Draws a black border around the entire screen during gameplay.
** Border thickness defined by BORDER_THICKNESS.
** Draws top, bottom, left, and right borders as solid black rectangles.
*/
void    draw_screen_border(t_cub3d *data)
{
    int    y;

    draw_horizontal_borders(data);
    y = BORDER_THICKNESS;
    while (y < data->current_height - BORDER_THICKNESS)
    {
        draw_vertical_edges(data, y);
        y++;
    }
}