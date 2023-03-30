/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   open_file.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: qfrederi <qfrederi@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/01/11 14:40:40 by rharing       #+#    #+#                 */
/*   Updated: 2023/03/30 11:27:00 by qfrederi      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	open_file(t_vars *vars, char *map)
{
	int	i;

	i = 0;
	vars->map.fd = open(map, O_RDONLY);
	if (vars->map.fd < 0)
		ft_error("Can't open file", clean_project(vars, 1));
	get_data(vars);
	if (check_data(vars->map.data) == false)
		ft_error("Cardinal Data not valid", clean_project(vars, 1));
	get_map(vars);
	close(vars->map.fd);
	check_map(vars);
}
