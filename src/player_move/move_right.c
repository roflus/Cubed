/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   move_right.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: qfrederi <qfrederi@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/02/22 13:08:00 by qfrederi      #+#    #+#                 */
/*   Updated: 2023/02/22 13:19:04 by qfrederi      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void move_right(t_vars *vars)
{
    vars->player.player_angle += 0.1;
    if (vars->player.player_angle > (2*M_PI))
        vars->player.player_angle -= (2*M_PI);
    vars->player.playdelta_x = cos(vars->player.player_angle) * 5;
    vars->player.playdelta_y = sin(vars->player.player_angle) * 5;
    mlx_delete_image(vars->mlx, vars->line1);
    mlx_delete_image(vars->mlx, vars->linepixel);
    create_points_line(vars);
    set_line_start_end(vars);
    drawline(vars);
}