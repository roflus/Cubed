/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parse_map.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: rharing <rharing@student.42.fr>              +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/01/26 18:20:29 by rharing       #+#    #+#                 */
/*   Updated: 2023/01/26 18:39:41 by rharing       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

static int	nlcount(char *mapline)
{
	int	f;
	int	count;

	f = 0;
	count = 0;
	while (mapline[f] != '\0')
	{
		if (mapline[f] == '\n')
			count++;
		f++;
	}
	return (count);
}

static void	create_map(t_vars *vars, char *mapline)
{
	if (check_empty_line_map(mapline) == false)
		ft_error("Error\nNo newline in map", 2);
	vars->map.array_count = nlcount(mapline);
	vars->map.map = ft_split(mapline, '\n');
	if (vars->map.map == NULL)
		ft_error("Error\nMalloc map failed", 2);
}

char	*get_map_utils(t_vars *vars)
{
	char	*mapline;
	char	*temp;

	while (1)
	{
		temp = get_next_line(vars->map.fd);
		if (ft_strncmp(temp, "\n", 1) != 0)
		{
			mapline = ft_strdup(temp);
			free(temp);
			return (mapline);
		}
		free(temp);
	}
}

void	get_map(t_vars *vars)
{
	char	*temp;
	char	*mapline;
	char	*newmapline;

	mapline = ft_calloc(1, 1);
	if (mapline == NULL)
		ft_error("Error\nMalloc failed", 2);
	mapline = get_map_utils(vars);
	while (mapline)
	{
		temp = get_next_line(vars->map.fd);
		if (!temp)
			break ;
		newmapline = mapline;
		mapline = ft_strjoin(newmapline, temp);
		free(newmapline);
		free(temp);
	}
	create_map(vars, mapline);
	free(mapline);
}
