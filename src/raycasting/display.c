/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   display.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: rharing <rharing@student.42.fr>              +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/03/02 16:47:54 by rharing       #+#    #+#                 */
/*   Updated: 2023/03/10 18:33:47 by rharing       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	setcolor(char side, int *color)
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

void	draw_vertical_line(t_vars *vars, int x, int color)
{
	int	i;

	i = vars->ray.drawstart;
	while (i < vars->ray.drawend)
	{
		mlx_put_pixel(vars->display, x, i, color);
		i++;
	}
}

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
		ft_error("failed to allocate image", 4);
	draw_background(vars->display, HEIGHT / 2, 0, vars->ceiling_rgb);
	draw_background(vars->display, HEIGHT, HEIGHT / 2, vars->floor_rgb);
}
