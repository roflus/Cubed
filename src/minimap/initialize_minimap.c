/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   initialize_minimap.c                               :+:    :+:            */
/*                                                     +:+                    */
/*   By: qfrederi <qfrederi@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/02/20 09:26:32 by qfrederi      #+#    #+#                 */
/*   Updated: 2023/02/20 12:48:47 by qfrederi      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void draw_map(t_vars *vars)
{
	int i;
	int k;

	i = 0;
	while (vars->map.map[i] != NULL)
	{
		k = 0;
		while (k < ft_strlen(vars->map.map[i]))
		{
			if (vars->map.map[i][k] == '1')
				mlx_image_to_window(vars->mlx, vars->wall, (k * MAPPIXEL), (i * MAPPIXEL));
			else if (vars->map.map[i][k] == '0')
				mlx_image_to_window(vars->mlx, vars->empty, (k * MAPPIXEL), (i * MAPPIXEL));
			k++;
		}
		i++;
	}
}

static void draw_player(t_vars *vars)
{
	int i;
	int k;

	i = 0;
	while (i < 12)
	{
		k = 0;
		while (k < 12)
		{
			mlx_put_pixel(vars->player1, k, i, 0x7D2AFA);
			k++;
		}
		i++;
	}
}

static void draw_wall(t_vars *vars)
{
	int i;
	int k;

	i = 0;
	while (i < 64)
	{
		k = 0;
		while (k < 64)
		{
			mlx_put_pixel(vars->wall, k, i, 267833369);
			k++;
		}
		i++;
	}	
}

void create_images_minimap(t_vars *vars)
{
	vars->player1 = mlx_new_image(vars->mlx, 12, 12);
	vars->wall = mlx_new_image(vars->mlx, MAPPIXEL, MAPPIXEL);
	vars->empty = mlx_new_image(vars->mlx, MAPPIXEL, MAPPIXEL);
	draw_player(vars);
	draw_wall(vars);
}