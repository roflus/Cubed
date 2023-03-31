/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   display.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: qfrederi <qfrederi@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/03/02 16:47:54 by rharing       #+#    #+#                 */
/*   Updated: 2023/03/31 10:50:14 by qfrederi      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	get_vertical_line_height(t_vars *vars)
{
	vars->ray.lineheight = (int)(HEIGHT / vars->ray.reflect_from_wall);
	vars->ray.drawstart = -vars->ray.lineheight / 2 + HEIGHT / 2;
	if (vars->ray.drawstart < 0)
		vars->ray.drawstart = 0;
	vars->ray.drawend = vars->ray.lineheight / 2 + HEIGHT / 2;
	if (vars->ray.drawend >= HEIGHT)
		vars->ray.drawend = HEIGHT - 1;
}

void	draw_background(mlx_image_t *display, int height, int start, int color)
{
	int	x;
	int	y;

	x = 0;
	while (x < WIDTH)
	{
		y = start;
		while (y < height)
		{
			mlx_put_pixel(display, x, y, color);
			y++;
		}
		x++;
	}
}

void	setup_display(t_vars *vars)
{
	mlx_delete_image(vars->mlx, vars->display);
	vars->display = mlx_new_image(vars->mlx, WIDTH, HEIGHT);
	if (!vars->display)
		ft_error("failed to allocate image", clean_project(vars, 4));
	draw_background(vars->display, HEIGHT / 2, 0, vars->ceiling_rgb);
	draw_background(vars->display, HEIGHT, HEIGHT / 2, vars->floor_rgb);
}
