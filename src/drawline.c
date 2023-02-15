#include "cub3D.h"
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <memory.h>
#include <math.h>
// Kleine maken
// Delete line per keer
// Controleren op out of bounces for map/widht/height

static int make_int_positive(int n)
{
    if (n < 0)
		return (n * -1);
	return (n);
}


static int dir_axis(int start, int end)
{
    if (end < start)
        return (1);
    else
        return (-1);
}

void drawline(int x_start, int y_start, int x_end, int y_end, t_vars *vars)
{
    int diffx;
    int diffy;
    int boundary;
    int current_x;
    int current_y;
    int increase_x;
    int increase_y;


    diffx = make_int_positive(x_start - x_end);
    diffy = make_int_positive(y_start - y_end);
    increase_x = dir_axis(x_start, x_end);
    increase_y = dir_axis(y_start, y_end);

    current_x = x_end;
    current_y = y_end;

    boundary = 2 * (diffy - diffx);

    while (1)
    {
        mlx_image_to_window(vars->mlx, vars->linepixel, current_x, current_y);
        if (current_x == x_start && current_y == y_start)
            break;
        if (boundary >= 0)
        {
            current_y += increase_y;
            boundary -= 2 * diffx;
        }
        if (boundary < 0)
        {
            current_x += increase_x;
            boundary += 2 * diffy;
        }
    }
}