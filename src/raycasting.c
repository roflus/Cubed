/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   raycasting.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: rharing <rharing@student.42.fr>              +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/03/08 11:43:21 by rharing       #+#    #+#                 */
/*   Updated: 2023/03/08 11:51:44 by rharing       ########   odam.nl         */
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
	vars->ray.hit = 0;
	while (vars->ray.hit == 0)
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
			vars->ray.hit = 1;
	}
}

void	raycaster(t_vars *vars)
{
	int	x;
	int	w;
	int	color;

	x = 0;
	w = WIDTH;
	setup_display(vars);
	while (x < w)
	{
		calc_ray_position_direction(vars, x, w);
		calc_ray_lenght_to_add(vars);
		calc_initial_ray_length(vars);
		dda_algoritm(vars);
		calc_line_back_to_plane(vars);
		get_vertical_line_height(vars, HEIGHT);
		setcolor(vars->ray.side, &color);
		draw_vertical_line(vars, x, color);
		x++;
	}
	mlx_image_to_window(vars->mlx, vars->display, 0, 0);
}
