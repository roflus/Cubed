/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   floor_ceiling_check.c                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: rharing <rharing@student.42.fr>              +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/01/26 17:17:31 by rharing       #+#    #+#                 */
/*   Updated: 2023/01/26 17:21:59 by rharing       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

bool	check_floor(t_vars *vars)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (i < 6)
	{
		if (vars->map.data[i][0] == 'F' && vars->map.data[i][1] == ' ')
			count++;
		i++;
	}
	if (count == 1)
		return (true);
	return (false);
}

bool	check_ceiling(t_vars *vars)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (i < 6)
	{
		if (vars->map.data[i][0] == 'C' && vars->map.data[i][1] == ' ')
			count++;
		i++;
	}
	if (count == 1)
		return (true);
	return (false);
}
