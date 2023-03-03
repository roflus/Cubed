/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: rharing <rharing@student.42.fr>              +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/01/11 13:05:43 by rharing       #+#    #+#                 */
/*   Updated: 2023/03/03 14:10:59 by rharing       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

static void check_player_position(t_vars *vars)
{
	//Get Player X and Y
	//Check if we see a wall
	//Make sure player can not walk in wall
	//Place this function inside the up and down movement functions
	printf("This is player X = %d\n", vars->player1->instances[0].x);
    printf("This is player Y = %d\n\n", vars->player1->instances[0].y);
}

void	hook(void *param)
{
	t_vars	*vars;

	vars = param;
	if (mlx_is_key_down(vars->mlx, MLX_KEY_ESCAPE))
		mlx_close_window(vars->mlx);
	if (mlx_is_key_down(vars->mlx, MLX_KEY_UP))
	{
		move_up(vars);
		check_player_position(vars);
	}
	if (mlx_is_key_down(vars->mlx, MLX_KEY_DOWN))
	{
		move_down(vars);
		check_player_position(vars);
	}
	if (mlx_is_key_down(vars->mlx, MLX_KEY_LEFT))
	{
		move_left(vars);
	}	
	if (mlx_is_key_down(vars->mlx, MLX_KEY_RIGHT))
	{
		move_right(vars);
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
	t_vars			vars;

	if (argc != 2)
		ft_error("Wrong amount of arguments", 2);
	if (arg_check(argv) == false)
		ft_error("File is not .cub", 2);
	ft_memset(&vars, 0, sizeof(vars));
	vars.map.data = (char **)malloc(7 * sizeof(char *));
	vars.mlx = mlx_init(WIDTH, HEIGHT, "Cub3D", false);
	if (!vars.mlx)
		exit(EXIT_FAILURE);
	open_file(&vars, argv[1]);
	get_textures(&vars);
	get_colors(&vars);
	start_direction(&vars);
	create_images_minimap(&vars);
	vars.inst_len = 3;
	create_points_line(&vars);


	// // display_game(&vars);
	// test_textures(&vars);
	system("leaks cub3D");
	mlx_loop_hook(vars.mlx, &hook, &vars);
	mlx_loop(vars.mlx);
	mlx_terminate(vars.mlx);
	return (EXIT_SUCCESS);
}
