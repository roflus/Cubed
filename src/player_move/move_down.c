/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   move_down.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: qfrederi <qfrederi@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/02/22 13:07:52 by qfrederi      #+#    #+#                 */
/*   Updated: 2023/02/22 13:09:44 by qfrederi      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void move_down(t_vars *vars)
{
    int i;

    vars->player1->instances[0].x -= vars->player.playdelta_x;
    vars->player1->instances[0].y -= vars->player.playdelta_y;
    i = 0;
    while (i < vars->inst_len)
    {
        vars->line1->instances[i].x -= vars->player.playdelta_x;
        vars->line1->instances[i].y -= vars->player.playdelta_y;
        i++;
    }
    i = 0;
    while (i < vars->line.count)
    {
        vars->linepixel->instances[i].x -= vars->player.playdelta_x;
        vars->linepixel->instances[i].y -= vars->player.playdelta_y;
        i++;
    }
}