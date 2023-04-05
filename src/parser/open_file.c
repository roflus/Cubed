/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   open_file.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: qfrederi <qfrederi@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/01/11 14:40:40 by rharing       #+#    #+#                 */
/*   Updated: 2023/04/05 11:04:14 by qfrederi      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

static void	init(t_vars *vars)
{
	ft_memset(vars, 0, sizeof(vars));
	vars->map.data = ft_calloc(7, sizeof(char *));
	if (!vars->map.data)
		ft_error("Map Data is NULL", clean_project(vars, 1));
	vars->mlx = mlx_init(WIDTH, HEIGHT, "Cub3D", false);
	if (!vars->mlx)
		ft_error("MLX Failed", clean_project(vars, 1));
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
