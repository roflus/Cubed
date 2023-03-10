/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: rharing <rharing@student.42.fr>              +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/01/11 13:05:43 by rharing       #+#    #+#                 */
/*   Updated: 2023/03/10 18:36:48 by rharing       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

bool	arg_check(char **argv)
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

void	init(t_vars *vars)
{
	ft_memset(vars, 0, sizeof(vars));
	vars->map.data = (char **)malloc(7 * sizeof(char *));
	if (vars->map.data == NULL)
		ft_error("malloc failed", 1);
	vars->mlx = mlx_init(WIDTH, HEIGHT, "Cub3D", false);
	if (!vars->mlx)
		exit(EXIT_FAILURE);
}

void	parser(t_vars *vars, char *file)
{
	open_file(vars, file);
	get_textures(vars);
	get_colors(vars);
}

int	main(int argc, char **argv)
{
	t_vars	vars;

	if (argc != 2)
		ft_error("Wrong amount of arguments", 2);
	if (arg_check(argv) == false)
		ft_error("File is not .cub", 2);
	init(&vars);
	parser(&vars, argv[1]);
	start_direction(&vars);
	set_direction(&vars);
	// system("leaks cub3D");
	mlx_loop_hook(vars.mlx, &hook, &vars);
	mlx_loop(vars.mlx);
	mlx_terminate(vars.mlx);
	return (EXIT_SUCCESS);
}
