/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: qfrederi <qfrederi@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/01/11 13:05:43 by rharing       #+#    #+#                 */
/*   Updated: 2023/02/20 14:49:23 by qfrederi      ########   odam.nl         */
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
		vars->player1->instances[0].x += vars->player.playdelta_x;
		vars->player1->instances[0].y += vars->player.playdelta_y;
		int i = 0;
		while (i < vars->inst_len)
		{
			vars->line1->instances[i].x += vars->player.playdelta_x;
			vars->line1->instances[i].y += vars->player.playdelta_y;
			i++;
		}
	}
	if (mlx_is_key_down(vars->mlx, MLX_KEY_DOWN))
	{
		vars->player1->instances[0].x -= vars->player.playdelta_x;
		vars->player1->instances[0].y -= vars->player.playdelta_y;
		int i = 0;
		while (i < vars->inst_len)
		{
			vars->line1->instances[i].x -= vars->player.playdelta_x;
			vars->line1->instances[i].y -= vars->player.playdelta_y;
			i++;
		}
	}
	if (mlx_is_key_down(vars->mlx, MLX_KEY_LEFT))
	{
		vars->player.player_angle -= 0.1;
		if (vars->player.player_angle < 0)
		{
			vars->player.player_angle += (2*PI);
		}
		vars->player.playdelta_x = cos(vars->player.player_angle) * 5;
		vars->player.playdelta_y = sin(vars->player.player_angle) * 5;
		
		mlx_delete_image(vars->mlx, vars->line1);
		mlx_delete_image(vars->mlx, vars->linepixel);
		create_points_line(vars);
		vars->linepixel = mlx_new_image(vars->mlx, 1, 1);
		mlx_put_pixel(vars->linepixel, 0, 0, 0x7D2AFA);
		int x_start = (vars->player1->instances[0].x + 6);
		int y_start = (vars->player1->instances[0].y + 6);
		int x_end = (vars->line1->instances[2].x);
		int y_end = (vars->line1->instances[2].y);

		drawline(x_start, y_start, \
					x_end, y_end, vars);
	}	
	if (mlx_is_key_down(vars->mlx, MLX_KEY_RIGHT))
	{
		vars->player.player_angle += 0.1;
		if (vars->player.player_angle > (2*PI))
		{
			vars->player.player_angle -= (2*PI);
		}
		mlx_delete_image(vars->mlx, vars->line1);
		mlx_delete_image(vars->mlx, vars->linepixel);
		create_points_line(vars);
		vars->player.playdelta_x = cos(vars->player.player_angle) * 5;
		vars->player.playdelta_y = sin(vars->player.player_angle) * 5;
		vars->linepixel = mlx_new_image(vars->mlx, 1, 1);
		mlx_put_pixel(vars->linepixel, 0, 0, 0x7D2AFA);
		int x_start = (vars->player1->instances[0].x + 6);
		int y_start = (vars->player1->instances[0].y + 6);
		int x_end = (vars->line1->instances[2].x);
		int y_end = (vars->line1->instances[2].y);

		drawline(x_start, y_start, \
					x_end, y_end, vars);
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

void	init_vars(t_vars *vars)
{
	vars->inst_len = 0;
	vars->playercount = 0;
	vars->map.array_count = 0;
	vars->map.data = NULL;
	vars->map.fd = 0;
	vars->map.map = NULL;
	vars->map.pos = 0;
	vars->map.data = (char **)malloc(7 * sizeof(char *));
	vars->player.player_angle = (0);
	vars->player.playdelta_x = cos(vars->player.player_angle) * 5;
	vars->player.playdelta_y = sin(vars->player.player_angle) * 5;
	vars->player.player_x = 0;
	vars->player.player_y = 0;
	if (vars->map.data == NULL)
		ft_error("Error\nMalloc error", 2);
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

	vars.linepixel = mlx_new_image(vars.mlx, 1, 1);
	mlx_put_pixel(vars.linepixel, 0, 0, 0x7D2AFA);

	int x_start = (vars.player1->instances[0].x + 6);
	int y_start = (vars.player1->instances[0].y + 6);
	int x_end = (vars.line1->instances[2].x);
	int y_end = (vars.line1->instances[2].y);

	drawline(x_start, y_start, \
				x_end, y_end, &vars);

	mlx_loop_hook(vars.mlx, &hook, &vars);
	mlx_loop(vars.mlx);
	mlx_terminate(vars.mlx);
	return (EXIT_SUCCESS);
}
