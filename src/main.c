/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: rharing <rharing@student.42.fr>              +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/01/11 13:05:43 by rharing       #+#    #+#                 */
/*   Updated: 2023/03/03 15:55:44 by rharing       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

static void check_player_position(t_vars *vars)
{
	// Get Player X and Y
	// Check if we see a wall
	// Make sure player can not walk in wall
	// Place this function inside the up and down movement functions
	printf("This is player X = %d\n", vars->player1->instances[0].x);
	printf("This is player Y = %d\n\n", vars->player1->instances[0].y);
}

bool arg_check(char **argv)
{
	if (ft_strlen(argv[1]) <= 4)
		return (false);
	if (argv[1][ft_strlen(argv[1]) - 1] == 'b' &&
		argv[1][ft_strlen(argv[1]) - 2] == 'u' &&
		argv[1][ft_strlen(argv[1]) - 3] == 'c' &&
		argv[1][ft_strlen(argv[1]) - 4] == '.')
		return (true);
	return (false);
}

void test_textures(t_vars *vars)
{
	mlx_image_to_window(vars->mlx, vars->walls.north_img, 0, 0);
	mlx_image_to_window(vars->mlx, vars->walls.east_img, 20, 20);
	mlx_image_to_window(vars->mlx, vars->walls.south_img, 40, 40);
	mlx_image_to_window(vars->mlx, vars->walls.west_img, 60, 60);
}

void init(t_vars *vars)
{
	ft_memset(vars, 0, sizeof(vars));
	vars->map.data = (char **)malloc(7 * sizeof(char *));
	if (vars->map.data == NULL)
		ft_error("malloc failed", 1);
	vars->mlx = mlx_init(WIDTH, HEIGHT, "Cub3D", false);
	if (!vars->mlx)
		exit(EXIT_FAILURE);
}

void parser(t_vars *vars, char *file)
{
	open_file(vars, file);
	// get_textures(vars);
	get_colors(vars);
}

void init_ray(t_vars *vars)
{
	// x and y start position is declared in char_check
	// initial direction vector
	vars->ray.dir_x = -1;
	vars->ray.dir_y = 0;
	// vector of camera plane
	vars->ray.plane_x = 0;
	vars->ray.plane_y = 0.66;
	// vars->ray.pos_x = 2;
	// vars->ray.pos_y = 2;
}

int main(int argc, char **argv)
{
	t_vars vars;

	if (argc != 2)
		ft_error("Wrong amount of arguments", 2);
	if (arg_check(argv) == false)
		ft_error("File is not .cub", 2);
	init(&vars);
	parser(&vars, argv[1]);
	start_direction(&vars);
	// check_player_position(&vars);
	// create_images_minimap(&vars);
	// vars.inst_len = 3;
	// create_points_line(&vars);
	// display_game(&vars);
	// test_textures(&vars);
	init_ray(&vars);
	// system("leaks cub3D");
	// raycaster(&vars);
	mlx_loop_hook(vars.mlx, &hook, &vars);
	mlx_loop(vars.mlx);
	mlx_terminate(vars.mlx);
	return (EXIT_SUCCESS);
}
