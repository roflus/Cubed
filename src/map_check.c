/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   map_check.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: qfrederi <qfrederi@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/01/12 12:33:23 by rharing       #+#    #+#                 */
/*   Updated: 2023/01/19 14:41:03 by qfrederi      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

bool	check_empty_line_map(char *mapline)
{
	int	i;
	int	length;

	i = 0;
	length = ft_strlen(mapline);
	while (mapline[i] != '\0')
	{
		if (mapline[length - 1] == '\n')
			return (false);
		if (mapline[0] == '\n')
			return (false);
		if (mapline[i] == '\n')
		{
			if (mapline[i + 1] == '\n')
				return (false);
		}
		i++;
	}
	return (true);
}

bool check_map(t_vars *vars)
{
	int i;
	int k;
	int player_count;

	i = 0;
	k = 0;
	player_count = 0;
	// check first only space and 1
	// check last only space and 1 (Same function?)

	// check on space, 1, 0 and NSEW
	// check if space and 1 come for 0 and there is no 0 after last one
	// count player, if NSEW= 2 map fails


	while (vars->map->map[i] != '\0')
	{
		if (vars->map->map[i])
	}
}