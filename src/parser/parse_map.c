/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parse_map.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: qfrederi <qfrederi@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/01/26 18:20:29 by rharing       #+#    #+#                 */
/*   Updated: 2023/04/05 11:08:11 by qfrederi      ########   odam.nl         */
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
	char	*temptrim;

	temptrim = ft_strtrim(mapline, "\n");
	free(mapline);
	if (check_empty_line_map(temptrim) == false)
		ft_error("File is not correct", clean_project(vars, 1));
	vars->map.array_count = nlcount(temptrim);
	vars->map.map = ft_split(temptrim, '\n');
	free(temptrim);
	if (vars->map.map == NULL)
		ft_error("Malloc map failed", clean_project(vars, 1));
}

char	*get_map_utils(t_vars *vars)
{
	char	*mapline;
	char	*temp;

	mapline = NULL;
	temp = get_next_line(vars->map.fd);
	while (temp)
	{
		if (ft_strncmp(temp, "\n", 1) != 0)
		{
			mapline = ft_strdup(temp);
			free(temp);
			return (mapline);
		}
		free(temp);
		temp = get_next_line(vars->map.fd);
	}
	free(temp);
	return (mapline);
}

void	get_map(t_vars *vars)
{
	char	*temp;
	char	*mapline;
	char	*newmapline;

	mapline = get_map_utils(vars);
	if (mapline == NULL)
		ft_error("no map", clean_project(vars, 2));
	while (mapline)
	{
		temp = get_next_line(vars->map.fd);
		if (!temp)
			break ;
		newmapline = mapline;
		mapline = ft_strjoin(newmapline, temp);
		if (!mapline)
			ft_error("Malloc Failed", clean_project(vars, 1));
		free(newmapline);
		free(temp);
	}
	create_map(vars, mapline);
	free(temp);
}
