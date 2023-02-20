/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   draw_line.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: qfrederi <qfrederi@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/02/20 13:07:14 by qfrederi      #+#    #+#                 */
/*   Updated: 2023/02/20 15:13:03 by qfrederi      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

// Kleiner maken
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

void set_line_start_end(t_vars *vars)
{
    vars->line.x_start = (vars->player1->instances[0].x + 6);
	vars->line.y_start = (vars->player1->instances[0].y + 6);
	vars->line.x_end = (vars->line1->instances[(vars->inst_len) - 1].x);
	vars->line.y_end = (vars->line1->instances[(vars->inst_len) - 1].y);
}

void drawline(t_vars *vars)
{
    vars->line.diffx = make_int_positive(vars->line.x_start - vars->line.x_end);
    vars->line.diffy = make_int_positive(vars->line.y_start - vars->line.y_end);
    vars->line.increase_x = dir_axis(vars->line.x_start, vars->line.x_end);
    vars->line.increase_y = dir_axis(vars->line.y_start, vars->line.y_end);
    vars->line.current_x = vars->line.x_end;
    vars->line.current_y = vars->line.y_end;
    vars->line.boundary = 2 * (vars->line.diffy - vars->line.diffx);
    while (1)
    {
        mlx_image_to_window(vars->mlx, vars->linepixel, vars->line.current_x, vars->line.current_y);
        if (vars->line.current_x == vars->line.x_start && vars->line.current_y == vars->line.y_start)
            break;
        if (vars->line.boundary >= 0)
        {
            vars->line.current_y += vars->line.increase_y;
            vars->line.boundary -= 2 * vars->line.diffx;
        }
        if (vars->line.boundary < 0)
        {
            vars->line.current_x += vars->line.increase_x;
            vars->line.boundary += 2 * vars->line.diffy;
        }
    }
}