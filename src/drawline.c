#include "cub3D.h"
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <memory.h>
#include <math.h>

void drawline(int x_start, int y_start, int x_end, int y_end, t_vars *vars)
{
    int dirx;
    int diry;
    int p;
    int x;
    int y;
    int count;

    count = 0;

    dirx = x_end - x_start;
    diry = y_end - y_start;

    x = x_start;
    y = y_start;

    p = 2 * diry - dirx;

    while (x < x_end)
    {
        if (p >= 0)
        {
            mlx_image_to_window(vars->mlx, vars->linepixel, x, y);
            y = y + 1;
            p = p + 2 * diry - 2 * dirx;
        }
        else
        {
            mlx_image_to_window(vars->mlx, vars->linepixel, x, y);
            p = p + 2 * diry;
        }
        x = x + 1;
    }
}