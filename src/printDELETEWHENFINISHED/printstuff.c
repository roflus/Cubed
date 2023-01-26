/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   printstuff.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: rharing <rharing@student.42.fr>              +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/01/26 18:14:26 by rharing       #+#    #+#                 */
/*   Updated: 2023/01/26 18:18:13 by rharing       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	print_map(t_vars *vars)
{
	int	i;

	i = 0;
	while (vars->map.map[i] != '\0')
	{
		printf("%s\n", vars->map.map[i]);
		i++;
	}
}

void	print_mapdata(t_vars *vars)
{
	int	i;

	i = 0;
	while (vars->map.data[i] != '\0')
	{
		printf("%s\n", vars->map.data[i]);
		i++;
	}
}
