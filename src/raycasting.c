/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   raycasting.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: rharing <rharing@student.42.fr>              +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/03/08 11:43:21 by rharing       #+#    #+#                 */
/*   Updated: 2023/03/09 13:27:48 by rharing       ########   odam.nl         */
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

static double	calc_wall_hit(t_vars *vars)
{
	double	wall_x;

	if (!vars->ray.side)
		wall_x = vars->ray.pos_y + vars->ray.reflect_from_wall * \
				vars->ray.ray_dir_y;
	if (vars->ray.side)
		wall_x = vars->ray.pos_x + vars->ray.reflect_from_wall * \
				vars->ray.ray_dir_x;
	wall_x -= floor(wall_x);
	return (wall_x);
}

void	calc_coord_x_text(t_vars *vars, mlx_texture_t *text)
{
	double	wall_x;

	wall_x = calc_wall_hit(vars);
	vars->ray.texture_x = (int)(wall_x * text->width);
	if (vars->ray.side == 0 && vars->ray.ray_dir_x > 0)
		vars->ray.texture_x = text->width - vars->ray.texture_x - 1;
	if (vars->ray.side == 1 && vars->ray.ray_dir_y < 0)
		vars->ray.texture_x = text->width - vars->ray.texture_x - 1;
	vars->ray.step = 1.0 * text->height / vars->ray.lineheight;
	vars->ray.textpos = (vars->ray.drawstart - HEIGHT / 2 + \
		vars->ray.lineheight / 2) * vars->ray.step;
}


// void	set_texture_to_wall(t_vars *vars, mlx_texture_t *text, int w)
// {
// 	int ocx;
// 	int heighty;
// 	int heightx;
// 	int	y;
// 	int	color;
// 	double wall_x;

// 	ocx = 0;
// 	heighty = vars->ray.drawend - vars->ray.drawstart;
// 	if (heighty > HEIGHT)
// 		ocx = (heighty - HEIGHT) / 2;
// 	heightx = vars->ray.drawend - vars->ray.drawstart;
// 	if (heightx >= HEIGHT)
// 		heightx = HEIGHT - 1;
// 	calc_coord_x_text(vars, text);
// 	y = 0;
// 	while (y < heightx)
// 	{
// 		vars->ray.texture_y = (int)((((float)text->height / \
// 			heighty)) * (y + ocx));
// 		color = *(int*)(&text->pixels[vars->ray.texture_y * \
// 			text->width + vars->ray.texture_x * sizeof(int)]);
// 		color = ((color >> 24) & 0xff) | ((color << 8) & 0xff0000) | \
// 			((color >> 8) & 0xff00) | ((color << 24) & 0xff000000);
// 		mlx_put_pixel(vars->display, w,  (HEIGHT - heightx - 1) / 2 + y, color);
// 		y++;
// 	}
// }



void	set_texture_to_wall(t_vars *vars, mlx_texture_t *text, int w)
{
	int	y;
	int	color;

	int ocx;
	int heighty;
	int heightx;
	double wall_x;

	ocx = 0;
	heighty = vars->ray.drawend - vars->ray.drawstart;
	if (heighty > HEIGHT)
		ocx = (heighty - HEIGHT) / 2;
	heightx = vars->ray.drawend - vars->ray.drawstart;
	if (heightx >= HEIGHT)
		heightx = HEIGHT - 1;
	calc_coord_x_text(vars, text);
	y = 0;
	while (y < heightx)
	{
		vars->ray.texture_y = (int)vars->ray.textpos;
		vars->ray.textpos += vars->ray.step;
		color = *(int *)(&text->pixels[(text->width * vars->ray.texture_y + vars->ray.texture_x) * sizeof(int)]);
		color = ((color >> 24) & 0xff) | ((color << 8) & 0xff0000) | \
			((color >> 8) & 0xff00) | ((color << 24) & 0xff000000);
		mlx_put_pixel(vars->display, w, (HEIGHT - heightx - 1) / 2 + y, color);
		y++;
	}
}


void	raycaster(t_vars *vars)
{
	int	x;
	int	color;

	x = 0;
	setup_display(vars);
	while (x < WIDTH)
	{
		calc_ray_position_direction(vars, x);
		calc_ray_lenght_to_add(vars);
		calc_initial_ray_length(vars);
		dda_algoritm(vars);
		calc_line_back_to_plane(vars);
		get_vertical_line_height(vars);
		wall_side(vars);
		// setcolor(vars->wallside, &color);
		// draw_vertical_line(vars, x, color);
		// calc_coord_x_text(vars, vars->walls.north_t);
		if (vars->wallside == 'N')
			set_texture_to_wall(vars, vars->walls.north_t, x);
		if (vars->wallside == 'S')
			set_texture_to_wall(vars, vars->walls.south_t, x);
		if (vars->wallside == 'W')
			set_texture_to_wall(vars, vars->walls.west_t, x);
		if (vars->wallside == 'E')
		 	set_texture_to_wall(vars, vars->walls.east_t, x);
		x++;
	}
	mlx_image_to_window(vars->mlx, vars->display, 0, 0);
}
