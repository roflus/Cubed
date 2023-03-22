/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   raycast.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: rharing <rharing@student.42.fr>              +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/03/08 11:43:21 by rharing       #+#    #+#                 */
/*   Updated: 2023/03/22 12:05:46 by rharing       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	calc_line_back_to_plane(t_vars *vars)
{
	if (vars->ray.side == 0)
		vars->ray.reflect_from_wall = \
			((vars->ray.map_x - vars->ray.pos_x + (1 - vars->ray.step_x) / 2) \
			/ vars->ray.ray_dir_x);
	else
		vars->ray.reflect_from_wall = \
			((vars->ray.map_y - vars->ray.pos_y + (1 - vars->ray.step_y) / 2) \
			/ vars->ray.ray_dir_y);
}

void	dda_algoritm(t_vars *vars)
{
	int	hit;

	hit = 0;
	while (hit == 0)
	{
		if (vars->ray.side_dist_x < vars->ray.side_dist_y)
		{
			vars->ray.side_dist_x += vars->ray.delta_dist_x;
			vars->ray.map_x += vars->ray.step_x;
			vars->ray.side = 0;
		}
		else
		{
			vars->ray.side_dist_y += vars->ray.delta_dist_y;
			vars->ray.map_y += vars->ray.step_y;
			vars->ray.side = 1;
		}
		if (vars->map.map[vars->ray.map_x][vars->ray.map_y] == '1')
			hit = 1;
	}
}

void	wall_side(t_vars *vars)
{
	if (!vars->ray.side && vars->ray.ray_dir_x >= 0)
		vars->wallside = 'N';
	else if (!vars->ray.side && vars->ray.ray_dir_x < 0)
		vars->wallside = 'S';
	else if (vars->ray.side && vars->ray.ray_dir_y >= 0)
		vars->wallside = 'W';
	else if (vars->ray.side && vars->ray.ray_dir_y < 0)
		vars->wallside = 'E';
}

void	raycaster(t_vars *vars)
{
	int	x;

	x = 0;
	setup_display(vars);
	while (x < WIDTH)
	{
		calc_ray_position_direction(vars, x);
		calc_initial_ray_length(vars);
		calc_ray_lenght_to_add(vars);
		dda_algoritm(vars);
		calc_line_back_to_plane(vars);
		get_vertical_line_height(vars);
		wall_side(vars);
		choose_texture(vars, x);
		x++;
	}
	create_minimap(vars);
	mlx_image_to_window(vars->mlx, vars->display, 0, 0);
}
