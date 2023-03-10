/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   init_minimap.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: rharing <rharing@student.42.fr>              +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/02/20 09:26:32 by qfrederi      #+#    #+#                 */
/*   Updated: 2023/03/10 16:42:30 by rharing       ########   odam.nl         */
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
				mlx_image_to_window(vars->mlx, vars->wall, (k * 15), (i * 15));
			else if (vars->map.map[i][k] == '0')
				mlx_image_to_window(vars->mlx, vars->empty, (k * 15), (i * 15));
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
	while (i < 10)
	{
		k = 0;
		while (k < 10)
		{
			mlx_put_pixel(vars->wall, k, i, 255255255);
			k++;
		}
		i++;
	}
}

static void draw_empty(t_vars *vars)
{
	int i;
	int k;

	i = 0;
	while (i < 10)
	{
		k = 0;
		while (k < 10)
		{
			mlx_put_pixel(vars->empty, k, i, 267833369);
			k++;
		}
		i++;
	}
}

void	create_images_minimap(t_vars *vars)
{
	vars->wall = mlx_new_image(vars->mlx, MAPPIXEL, MAPPIXEL);
	vars->empty = mlx_new_image(vars->mlx, MAPPIXEL, MAPPIXEL);
	vars->player1 = mlx_new_image(vars->mlx, 12, 12);
	draw_player(vars);
	draw_wall(vars);
	draw_empty(vars);
	draw_map(vars);
	// mlx_image_to_window(vars->mlx, vars->player1, (vars->player.player_x * MAPPIXEL + 32), (vars->player.player_y * MAPPIXEL + 32));
	mlx_image_to_window(vars->mlx, vars->player1, 10, 10);
}
