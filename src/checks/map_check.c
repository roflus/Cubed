/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   map_check.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: rharing <rharing@student.42.fr>              +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/01/12 12:33:23 by rharing       #+#    #+#                 */
/*   Updated: 2023/03/02 17:32:11 by rharing       ########   odam.nl         */
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

void	check_map(t_vars *vars)
{
	if (check_char_map(vars) == false)
		ft_error("Invalid Char in Map", 2);
	if (check_first_last(vars) == false)
		ft_error("First or Last Line of Map not valid", 2);
	if (check_walls(vars) == false)
		ft_error("WALLS ERROR", 2);
	if (check_empty(vars) == false)
		ft_error("EMPTY ERROR", 2);
}
