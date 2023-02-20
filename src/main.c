/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: qfrederi <qfrederi@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/01/11 13:05:43 by rharing       #+#    #+#                 */
/*   Updated: 2023/02/20 15:46:07 by qfrederi      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <memory.h>
#include <math.h>
#define WIDTH 1000	
#define HEIGHT 1000
#define PI 3.14159265359

	//N = 3*PI/2
	//S = PI/2
	//W = PI
	//E = 0

void	hook(void *param)
{
	t_vars *vars;
	
	vars = param;
	if (mlx_is_key_down(vars->mlx, MLX_KEY_ESCAPE))
		mlx_close_window(vars->mlx);
	if (mlx_is_key_down(vars->mlx, MLX_KEY_UP))
	{
		int i;
		
		vars->player1->instances[0].x += vars->player.playdelta_x;
		vars->player1->instances[0].y += vars->player.playdelta_y;
		i = 0;
		while (i < vars->inst_len)
		{
			vars->line1->instances[i].x += vars->player.playdelta_x;
			vars->line1->instances[i].y += vars->player.playdelta_y;
			i++;
		}
		i = 0;
		while (i < vars->line.count)
		{
			vars->linepixel->instances[i].x += vars->player.playdelta_x;
			vars->linepixel->instances[i].y += vars->player.playdelta_y;
			i++;
		}
	}
	if (mlx_is_key_down(vars->mlx, MLX_KEY_DOWN))
	{
		int i;
		
		vars->player1->instances[0].x -= vars->player.playdelta_x;
		vars->player1->instances[0].y -= vars->player.playdelta_y;
		i = 0;
		while (i < vars->inst_len)
		{
			vars->line1->instances[i].x -= vars->player.playdelta_x;
			vars->line1->instances[i].y -= vars->player.playdelta_y;
			i++;
		}
		i = 0;
		while (i < vars->line.count)
		{
			vars->linepixel->instances[i].x -= vars->player.playdelta_x;
			vars->linepixel->instances[i].y -= vars->player.playdelta_y;
			i++;
		}
	}
	if (mlx_is_key_down(vars->mlx, MLX_KEY_LEFT))
	{
		vars->player.player_angle -= 0.1;
		if (vars->player.player_angle < 0)
			vars->player.player_angle += (2*PI);
		vars->player.playdelta_x = cos(vars->player.player_angle) * 5;
		vars->player.playdelta_y = sin(vars->player.player_angle) * 5;
		mlx_delete_image(vars->mlx, vars->line1);
		mlx_delete_image(vars->mlx, vars->linepixel);
		create_points_line(vars);
		set_line_start_end(vars);
		drawline(vars);
	}	
	if (mlx_is_key_down(vars->mlx, MLX_KEY_RIGHT))
	{
		vars->player.player_angle += 0.1;
		if (vars->player.player_angle > (2*PI))
			vars->player.player_angle -= (2*PI);
		vars->player.playdelta_x = cos(vars->player.player_angle) * 5;
		vars->player.playdelta_y = sin(vars->player.player_angle) * 5;
		mlx_delete_image(vars->mlx, vars->line1);
		mlx_delete_image(vars->mlx, vars->linepixel);
		create_points_line(vars);
		set_line_start_end(vars);
		drawline(vars);
	}
}

bool	arg_check(char **argv)
{
	if (ft_strlen(argv[1]) <= 4)
		return (false);
	if (argv[1][ft_strlen(argv[1]) - 1] == 'b' && \
		argv[1][ft_strlen(argv[1]) - 2] == 'u' && \
		argv[1][ft_strlen(argv[1]) - 3] == 'c' && \
		argv[1][ft_strlen(argv[1]) - 4] == '.')
		return (true);
	return (false);
}

void	test_textures(t_vars *vars)
{
	mlx_image_to_window(vars->mlx, vars->walls.north_img, 0, 0);
	mlx_image_to_window(vars->mlx, vars->walls.east_img, 20, 20);
	mlx_image_to_window(vars->mlx, vars->walls.south_img, 40, 40);
	mlx_image_to_window(vars->mlx, vars->walls.west_img, 60, 60);
}

int	main(int argc, char **argv)
{
	mlx_texture_t* texture;
	t_vars	vars;

	if (argc != 2)
		ft_error("Error\nWrong amount of arguments", 2);
	if (arg_check(argv) == false)
		ft_error("Error\nFile is not .cub", 2);
	init_vars(&vars);
	open_file(&vars, argv[1]);
	vars.mlx = mlx_init(WIDTH, HEIGHT, "cub3D", true);
	if (!vars.mlx)
		exit(EXIT_FAILURE);
	get_textures(&vars);
	get_colors(&vars);
	// test_textures(&vars);
	create_images_minimap(&vars);
	vars.inst_len = 3;
	create_points_line(&vars);
	test_textures(&vars);
	set_line_start_end(&vars);
	drawline(&vars);
	mlx_loop_hook(vars.mlx, &hook, &vars);
	mlx_loop(vars.mlx);
	mlx_terminate(vars.mlx);
	return (EXIT_SUCCESS);
}
