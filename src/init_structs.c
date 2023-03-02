/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   init_structs.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: rharing <rharing@student.42.fr>              +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/02/20 15:16:44 by qfrederi      #+#    #+#                 */
/*   Updated: 2023/03/02 18:40:00 by rharing       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

	//N = 3*PI/2 || 3*M_PI_2
	//S = PI/2 || M_PI_2
	//W = PI || M_PI
	//E = 0
	// PI = M_PI || https://learn.microsoft.com/en-us/cpp/c-runtime-library/math-constants?view=msvc-170

void	start_direction(t_vars *vars)
{
	if (vars->map.pos == 'N')
		vars->player.player_angle = (3 * M_PI_2);
	else if (vars->map.pos == 'E')
		vars->player.player_angle = (0);
	else if (vars->map.pos == 'S')
		vars->player.player_angle = (M_PI_2);
	else if (vars->map.pos == 'W')
		vars->player.player_angle = (M_PI);
	vars->player.playdelta_x = cos(vars->player.player_angle) * 5;
	vars->player.playdelta_y = sin(vars->player.player_angle) * 5;
}
