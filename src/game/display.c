/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   display.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: rharing <rharing@student.42.fr>              +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/03/02 16:47:54 by rharing       #+#    #+#                 */
/*   Updated: 2023/03/02 18:33:09 by rharing       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void draw_background(mlx_image_t *display, int height, int start, int color)
{
	int x;
	int y;

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

void display_game(t_vars *vars)
{
	vars->display = mlx_new_image(vars->mlx, WIDTH, HEIGHT);
	if (!vars->display)
		ft_error("failed to allocate image", 4);
	draw_background(vars->display, HEIGHT / 2, 0, vars->ceiling_rgb);
	draw_background(vars->display, HEIGHT, 500, vars->floor_rgb);
	mlx_image_to_window(vars->mlx, vars->display, 0, 0);
}
