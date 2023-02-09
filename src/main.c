/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: qfrederi <qfrederi@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/01/11 13:05:43 by rharing       #+#    #+#                 */
/*   Updated: 2023/02/09 18:13:03 by qfrederi      ########   odam.nl         */
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

void	hook(void *param)
{
	t_vars *vars;

	//N = 3*PI/2
	//S = PI/2
	//W = PI
	//E = 0
	vars = param;
	if (mlx_is_key_down(vars->mlx, MLX_KEY_ESCAPE))
		mlx_close_window(vars->mlx);
	if (mlx_is_key_down(vars->mlx, MLX_KEY_UP))
	{
		vars->player1->instances[0].x += vars->player.playdeltaX;
		vars->player1->instances[0].y += vars->player.playdeltaY;
		int i = 0;
		while (i < 4)
		{
			vars->line1->instances[i].x += vars->player.playdeltaX;
			vars->line1->instances[i].y += vars->player.playdeltaY;
			i++;
		}
	}
	if (mlx_is_key_down(vars->mlx, MLX_KEY_DOWN))
	{
		vars->player1->instances[0].x -= vars->player.playdeltaX;
		vars->player1->instances[0].y -= vars->player.playdeltaY;
		int i = 0;
		while (i < 4)
		{
			vars->line1->instances[i].x -= vars->player.playdeltaX;
			vars->line1->instances[i].y -= vars->player.playdeltaY;
		}
	}
	if (mlx_is_key_down(vars->mlx, MLX_KEY_LEFT))
	{
		vars->player.playerAngel -= 0.1;
		if (vars->player.playerAngel < 0)
		{
			vars->player.playerAngel += (2*PI);
		}
		vars->player.playdeltaX = cos(vars->player.playerAngel) * 5;
		vars->player.playdeltaY = sin(vars->player.playerAngel) * 5;
		
		mlx_delete_image(vars->mlx, vars->line1);
		vars->line1 = mlx_new_image(vars->mlx, 6, 6);
		
		int i = 0;
		int k = 0;
		while (i < 6)
		{
			k = 0;
			while (k < 6)
			{
				mlx_put_pixel(vars->line1, k, i, 0x7D2AFA);
				k++;
			}
			i++;
		}
		i = 0;
		while (i < 4)
		{
			mlx_image_to_window(vars->mlx, vars->line1, (vars->player1->instances[0].x + 6) + (vars->player.playdeltaX * (5 + (i * 5))), ((vars->player1->instances[0].y + 6) + (vars->player.playdeltaY * (5 + (i * 5)))));
			i++;
		}
		//printf("This is Angle = %f\n", vars->player.playerAngel);
	}	
	if (mlx_is_key_down(vars->mlx, MLX_KEY_RIGHT))
	{
		vars->player.playerAngel += 0.1;
		if (vars->player.playerAngel > (2*PI))
		{
			vars->player.playerAngel -= (2*PI);
		}

		mlx_delete_image(vars->mlx, vars->line1);
		vars->line1 = mlx_new_image(vars->mlx, 1000, 1000);
		vars->player.playdeltaX = cos(vars->player.playerAngel) * 5;
		vars->player.playdeltaY = sin(vars->player.playerAngel) * 5;
		int i = 0;
		int k = 0;
		while (i < 6)
		{
			k = 0;
			while (k < 6)
			{
				mlx_put_pixel(vars->line1, k, i, 0x7D2AFA);
				k++;
			}
			i++;
		}
		i = 0;
		while (i < 4)
		{
			mlx_image_to_window(vars->mlx, vars->line1, (vars->player1->instances[0].x + 6) + (vars->player.playdeltaX * (5 + (i * 5))), ((vars->player1->instances[0].y + 6) + (vars->player.playdeltaY * (5 + (i * 5)))));
			i++;
		}
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
	vars->test = 0;
	vars->playercount = 0;
	vars->map.array_count = 0;
	vars->map.data = NULL;
	vars->map.fd = 0;
	vars->map.map = NULL;
	vars->map.pos = 0;
	vars->map.data = (char **)malloc(7 * sizeof(char *));
	vars->player.playerAngel = (3*PI/2);
	vars->player.playdeltaX = cos(vars->player.playerAngel) * 5;
	vars->player.playdeltaY = sin(vars->player.playerAngel) * 5;
	vars->player.playerX = 0;
	vars->player.playerY = 0;
	if (vars->map.data == NULL)
		ft_error("Error\nMalloc error", 2);
}

static void draw_map(t_vars *vars)
{
	int i = 0;
	int k;

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
	vars.player1 = mlx_new_image(vars.mlx, 12, 12);
	vars.line = mlx_new_image(vars.mlx, 2, 100);
	vars.wall = mlx_new_image(vars.mlx, MAPPIXEL, MAPPIXEL);
	vars.empty = mlx_new_image(vars.mlx, MAPPIXEL, MAPPIXEL);
	memset(vars.empty->pixels, 255, vars.empty->width * vars.empty->height * sizeof(int));
	//memset(vars.player1->pixels, 255, vars.player1->width * vars.player1->height * sizeof(int));
	draw_map(&vars);

	int i = 0;
	int k = 0;
	while (i < 12)
	{
		k = 0;
		while (k < 12)
		{
			mlx_put_pixel(vars.player1, k, i, 0x7D2AFA);
			k++;
		}
		i++;
	}
	i = 0;
	k = 0;
	while (i < 64)
	{
		k = 0;
		while (k < 64)
		{
			mlx_put_pixel(vars.wall, k, i, 267833369);
			k++;
		}
		i++;
	}
	vars.line1 = mlx_new_image(vars.mlx, 6, 6);

	i = 0;
	k = 0;
	while (i < 6)
	{
		k = 0;
		while (k < 6)
		{
			mlx_put_pixel(vars.line1, k, i, 0x7D2AFA);
			k++;
		}
		i++;
	}
	mlx_image_to_window(vars.mlx, vars.player1, (vars.player.playerX * MAPPIXEL + 32), (vars.player.playerY * MAPPIXEL + 32));
	i = 0;
	while (i < 4)
	{
		mlx_image_to_window(vars.mlx, vars.line1, (vars.player1->instances[0].x + 6) + (vars.player.playdeltaX * (5 + (i * 5))), ((vars.player1->instances[0].y + 6) + (vars.player.playdeltaY * (5 + (i * 5)))));
		i++;
	}

	mlx_loop_hook(vars.mlx, &hook, &vars);
	mlx_loop(vars.mlx);
	mlx_terminate(vars.mlx);
	return (EXIT_SUCCESS);
}
