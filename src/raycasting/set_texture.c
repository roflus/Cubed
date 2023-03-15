/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   set_texture.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: rharing <rharing@student.42.fr>              +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/03/09 16:02:01 by rharing       #+#    #+#                 */
/*   Updated: 2023/03/15 11:46:26 by rharing       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

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

static void	calc_coord_x_text(t_vars *vars, mlx_texture_t *text)
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

static void	set_texture_to_wall(t_vars *vars, mlx_texture_t *text, int w)
{
	int		y;
	int		color;
	int		heightx;

	heightx = vars->ray.drawend - vars->ray.drawstart;
	if (heightx >= HEIGHT)
		heightx = HEIGHT - 1;
	calc_coord_x_text(vars, text);
	y = 0;
	while (y < heightx)
	{
		vars->ray.texture_y = (int)vars->ray.textpos;
		vars->ray.textpos += vars->ray.step;
		color = *(int *)(&text->pixels[(text->width * \
			vars->ray.texture_y + vars->ray.texture_x) * sizeof(int)]);
		color = ((color >> 24) & 0xff) | ((color << 8) & 0xff0000) | \
			((color >> 8) & 0xff00) | ((color << 24) & 0xff000000);
		mlx_put_pixel(vars->display, w, (HEIGHT - heightx - 1) / 2 + y, color);
		y++;
	}
}

void	choose_texture(t_vars *vars, int x)
{
	if (vars->wallside == 'N')
		set_texture_to_wall(vars, vars->walls.north_t, x);
	if (vars->wallside == 'S')
		set_texture_to_wall(vars, vars->walls.south_t, x);
	if (vars->wallside == 'W')
		set_texture_to_wall(vars, vars->walls.west_t, x);
	if (vars->wallside == 'E')
		set_texture_to_wall(vars, vars->walls.east_t, x);
}
