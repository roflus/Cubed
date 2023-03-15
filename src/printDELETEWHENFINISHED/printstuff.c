/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   printstuff.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: rharing <rharing@student.42.fr>              +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/01/26 18:14:26 by rharing       #+#    #+#                 */
/*   Updated: 2023/03/15 11:27:11 by rharing       ########   odam.nl         */
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

int	get_width(char **map)
{
	int		longest;
	int		len;
	size_t	i;

	longest = ft_strlen(map[0]);
	i = 1;
	while (map[i] != '\0')
	{
		len = ft_strlen(map[i]);
		if (longest < len)
			longest = len;
		i++;
	}
	return (longest);
}
