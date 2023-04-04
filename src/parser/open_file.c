/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   open_file.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: rharing <rharing@student.42.fr>              +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/01/11 14:40:40 by rharing       #+#    #+#                 */
/*   Updated: 2023/04/04 15:44:38 by rharing       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

static void	init(t_vars *vars)
{
	int	i;

	i = 0;
	ft_memset(vars, 0, sizeof(vars));
	vars->map.data = ft_calloc(7, sizeof(char *));
	vars->mlx = mlx_init(WIDTH, HEIGHT, "Cub3D", false);
	if (!vars->mlx)
		exit(EXIT_FAILURE);
	vars->use_mouse = false;
}

void	open_file(t_vars *vars, char *map)
{
	vars->map.fd = open(map, O_RDONLY);
	if (vars->map.fd < 0)
		ft_error("Can't open file", 1);
	init(vars);
	get_data(vars);
	if (check_data(vars->map.data) == false)
		ft_error("Cardinal Data not valid", clean_project(vars, 1));
	get_map(vars);
	close(vars->map.fd);
	check_map(vars);
}
