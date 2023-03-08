/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   raycasting.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: rharing <rharing@student.42.fr>              +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/03/08 11:43:21 by rharing       #+#    #+#                 */
/*   Updated: 2023/03/08 15:24:29 by rharing       ########   odam.nl         */
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

/*
	if (!ray->side && ray->direction.x >= 0)
		ray->side = 1;
	else if (!ray->side && ray->direction.x < 0)
		ray->side = 3;
	else if (ray->side && ray->direction.y >= 0)
		ray->side = 2;
	else
		ray->side = 0;
		*/

void	testkleur(char side, int *color)
{
	if (side == 'N')
		*color = 0xFF8D00FF;
	else if (side == 'S')
		*color = 0xFF0000FF;
	else if (side == 'W')
		*color = 0x00FF00FF;
	else if (side == 'E')
		*color = 0x0000FFFF;
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
		// setcolor(vars->ray.side, &color);
		if (!vars->ray.side && vars->ray.ray_dir_x >= 0)
			vars->wallside = 'N';
		else if (!vars->ray.side && vars->ray.ray_dir_x < 0)
			vars->wallside = 'S';
		else if (vars->ray.side && vars->ray.ray_dir_y >= 0)
			vars->wallside = 'W';
		else if (vars->ray.side && vars->ray.ray_dir_y < 0)
			vars->wallside = 'E';
		testkleur(vars->wallside, &color);
		draw_vertical_line(vars, x, color);
		x++;
	}
	mlx_image_to_window(vars->mlx, vars->display, 0, 0);
}
