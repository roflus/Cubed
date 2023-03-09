/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ray.c                                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: rharing <rharing@student.42.fr>              +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/03/08 11:48:11 by rharing       #+#    #+#                 */
/*   Updated: 2023/03/09 11:30:58 by rharing       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	calc_ray_position_direction(t_vars *vars, int x)
{
	vars->ray.camera_x = 2 * x / (float)WIDTH - 1;
	vars->ray.ray_dir_x = \
		vars->ray.dir_x + vars->ray.plane_x * vars->ray.camera_x;
	vars->ray.ray_dir_y = \
		vars->ray.dir_y + vars->ray.plane_y * vars->ray.camera_x;
	vars->ray.map_x = (int)vars->ray.pos_x;
	vars->ray.map_y = (int)vars->ray.pos_y;
}

void	calc_ray_lenght_to_add(t_vars *vars)
{
	vars->ray.delta_dist_x = sqrt(1 + \
		(vars->ray.ray_dir_y * vars->ray.ray_dir_y) / \
		(vars->ray.ray_dir_x * vars->ray.ray_dir_x));
	vars->ray.delta_dist_y = sqrt(1 + \
		(vars->ray.ray_dir_x * vars->ray.ray_dir_x) / \
		(vars->ray.ray_dir_y * vars->ray.ray_dir_y));
}

void	calc_initial_ray_length(t_vars *vars)
	{
	if (vars->ray.ray_dir_x < 0)
	{
		vars->ray.step_x = -1;
		vars->ray.side_dist_x = \
		(vars->ray.pos_x - vars->ray.map_x) * vars->ray.delta_dist_x;
	}
	else
	{
		vars->ray.step_x = 1;
		vars->ray.side_dist_x = \
		(vars->ray.map_x + 1 - vars->ray.pos_x) * vars->ray.delta_dist_x;
	}
	if (vars->ray.ray_dir_y < 0)
	{
		vars->ray.step_y = -1;
		vars->ray.side_dist_y = \
		(vars->ray.pos_y - vars->ray.map_y) * vars->ray.delta_dist_y;
	}
	else
	{
		vars->ray.step_y = 1;
		vars->ray.side_dist_y = \
		(vars->ray.map_y + 1 - vars->ray.pos_y) * vars->ray.delta_dist_y;
	}
}
