/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   init_structs.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: qfrederi <qfrederi@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/02/20 15:16:44 by qfrederi      #+#    #+#                 */
/*   Updated: 2023/02/20 15:34:34 by qfrederi      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

static void init_line(t_vars *vars)
{
	vars->line.x_start = 0;
	vars->line.x_end = 0;
	vars->line.y_start = 0;
	vars->line.y_end = 0;
	vars->line.diffx = 0;
    vars->line.diffy = 0;
    vars->line.boundary = 0;
    vars->line.current_x = 0;
    vars->line.current_y = 0;
    vars->line.increase_x = 0;
    vars->line.increase_y = 0;
    vars->line.count = 0;
}

static void init_player(t_vars *vars)
{
    vars->player.player_angle = (0);
	vars->player.playdelta_x = cos(vars->player.player_angle) * 5;
	vars->player.playdelta_y = sin(vars->player.player_angle) * 5;
	vars->player.player_x = 0;
	vars->player.player_y = 0;
}

void	init_vars(t_vars *vars)
{
	vars->inst_len = 0;
	vars->playercount = 0;
	vars->map.array_count = 0;
	vars->map.data = NULL;
	vars->map.fd = 0;
	vars->map.map = NULL;
	vars->map.pos = 0;
	vars->map.data = (char **)malloc(7 * sizeof(char *));
	if (vars->map.data == NULL)
		ft_error("Error\nMalloc error", 2);
    init_player(vars);    
	init_line(vars);
}