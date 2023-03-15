/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   strafe.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: rharing <rharing@student.42.fr>              +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/03/09 11:36:46 by rharing       #+#    #+#                 */
/*   Updated: 2023/03/15 13:33:29 by rharing       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	strafe_right(t_vars *vars)
{
	vars->player.player_x = vars->ray.pos_y;
	vars->player.player_y = vars->ray.pos_x;
	if (vars->map.map[(int)(vars->ray.pos_x + vars->ray.plane_x * MOVESPEED)] \
			[(int)vars->ray.pos_y] == '0')
	{
		vars->ray.pos_x += vars->ray.plane_x * MOVESPEED;
	}
	if (vars->map.map[(int)vars->ray.pos_x] \
		[(int)(vars->ray.pos_y + vars->ray.plane_y * MOVESPEED)] == '0')
	{
		vars->ray.pos_y += vars->ray.plane_y * MOVESPEED;
	}
}

void	strafe_left(t_vars *vars)
{
	vars->player.player_x = vars->ray.pos_y;
	vars->player.player_y = vars->ray.pos_x;
	if (vars->map.map[(int)(vars->ray.pos_x - vars->ray.plane_x * MOVESPEED)] \
		[(int)vars->ray.pos_y] == '0')
	{
		vars->ray.pos_x -= vars->ray.plane_x * MOVESPEED;
	}
	if (vars->map.map[(int)vars->ray.pos_x] \
		[(int)(vars->ray.pos_y - vars->ray.plane_y * MOVESPEED)] == '0')
	{
		vars->ray.pos_y -= vars->ray.plane_y * MOVESPEED;
	}
}
