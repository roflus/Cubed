/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   set_dir.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: rharing <rharing@student.42.fr>              +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/02/20 15:16:44 by qfrederi      #+#    #+#                 */
/*   Updated: 2023/03/22 11:41:52 by rharing       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

static void	setdirection_sw(t_vars *vars)
{
	if (vars->map.pos == 'S')
	{
		vars->ray.dir_x = 1;
		vars->ray.dir_y = 0;
		vars->ray.plane_x = 0;
		vars->ray.plane_y = -0.66;
	}
	else if (vars->map.pos == 'W')
	{
		vars->ray.dir_x = 0;
		vars->ray.dir_y = -1;
		vars->ray.plane_x = -0.66;
		vars->ray.plane_y = 0;
	}
}

static void	setdirection_ne(t_vars *vars)
{
	if (vars->map.pos == 'N')
	{
		vars->ray.dir_x = -1;
		vars->ray.dir_y = 0;
		vars->ray.plane_x = 0;
		vars->ray.plane_y = 0.66;
	}
	else if (vars->map.pos == 'E')
	{
		vars->ray.dir_x = 0;
		vars->ray.dir_y = 1;
		vars->ray.plane_x = 0.66;
		vars->ray.plane_y = 0;
	}
}

void	set_direction(t_vars *vars)
{
	setdirection_ne(vars);
	setdirection_sw(vars);
}
