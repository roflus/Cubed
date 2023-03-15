/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   open_file.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: rharing <rharing@student.42.fr>              +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/01/11 14:40:40 by rharing       #+#    #+#                 */
/*   Updated: 2023/03/15 13:25:21 by rharing       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	open_file(t_vars *vars, char *map)
{
	int	i;

	i = 0;
	vars->map.fd = open(map, O_RDONLY);
	if (vars->map.fd < 0)
		ft_error("Can't open file", 1);
	get_data(vars);
	if (check_data(vars->map.data) == false)
		ft_error("Cardinal Data not valid", 1);
	get_map(vars);
	close(vars->map.fd);
	check_map(vars);
}
