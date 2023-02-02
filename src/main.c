/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: qfrederi <qfrederi@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/01/11 13:05:43 by rharing       #+#    #+#                 */
/*   Updated: 2023/02/02 14:03:18 by qfrederi      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <memory.h>
#define WIDTH 1000	
#define HEIGHT 1000



void	hook(void *param)
{
	t_vars *vars;
	

	vars = param;
	if (mlx_is_key_down(vars->mlx, MLX_KEY_ESCAPE))
		mlx_close_window(vars->mlx);
	if (mlx_is_key_down(vars->mlx, MLX_KEY_UP))
		vars->player1->instances[0].y -= 5;
	if (mlx_is_key_down(vars->mlx, MLX_KEY_DOWN))
		vars->player1->instances[0].y += 5;
	if (mlx_is_key_down(vars->mlx, MLX_KEY_LEFT))
		vars->player1->instances[0].x -= 5;
	if (mlx_is_key_down(vars->mlx, MLX_KEY_RIGHT))
		vars->player1->instances[0].x += 5;
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

	vars->player.playerX = 0;
	vars->player.playerY = 0;
	if (vars->map.data == NULL)
		ft_error("Error\nMalloc error", 2);
}

int	main(int argc, char **argv)
{
	//mlx_t	*mlx;
	mlx_image_t	*empty;
	mlx_image_t	*wall;
	//mlx_image_t	*player;
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
	wall = mlx_new_image(vars.mlx, MAPPIXEL, MAPPIXEL);
	empty = mlx_new_image(vars.mlx, MAPPIXEL, MAPPIXEL);
	memset(vars.player1->pixels, 255, vars.player1->width * vars.player1->height * sizeof(int));
	memset(wall->pixels, 255, wall->width * wall->height * sizeof(int));
	memset(empty->pixels, 255, empty->width * empty->height * sizeof(int));
	mlx_image_to_window(vars.mlx, vars.player1, (vars.player.playerX * MAPPIXEL), (vars.player.playerY * MAPPIXEL));
	mlx_image_to_window(vars.mlx, empty, (0), (0));
	mlx_image_to_window(vars.mlx, wall, (128), (0));
	mlx_loop_hook(vars.mlx, &hook, &vars);
	mlx_loop(vars.mlx);
	mlx_terminate(vars.mlx);
	return (EXIT_SUCCESS);
}
