/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   read_map.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: rharing <rharing@student.42.fr>              +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/01/11 14:40:40 by rharing       #+#    #+#                 */
/*   Updated: 2023/01/12 13:39:35 by rharing       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

static void	create_map(t_vars *vars, char *mapline)
{
	if (check_empty_line_map(mapline) == false)
		ft_error("No newline in map", 2);
	vars->map->map = ft_split(mapline, '\n');
	if (vars->map->map == NULL)
		ft_error("Malloc map failed", 2);
}

static void	mapinput(t_vars *vars)
{
	char	*temp;
	char	*mapline;
	char	*newmapline;

	mapline = ft_calloc(1, 1);
	if (mapline == NULL)
		ft_error("Malloc failed", 2);
	while (mapline)
	{
		temp = get_next_line(vars->map->fd);
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

static void	get_data(t_vars *vars)
{
	char	*temp1;
	int		i;
	int		k;

	i = 0;
	k = 0;
	vars->map->data = ft_calloc(6, sizeof(char *));
	if (vars->map->data == NULL)
		ft_error("Malloc error", 2);
	while (i < 8)
	{
		temp1 = get_next_line(vars->map->fd);
		if (ft_strncmp(temp1, "\n", 1) != 0)
		{
			vars->map->data[k] = ft_strdup(temp1);
			k++;
		}
		free(temp1);
		i++;
	}
}

void	open_map(t_vars *vars, char *map)
{
	vars->map->fd = open(map, O_RDONLY);
	if (vars->map->fd < 0)
		ft_error("Can't open file", 2);
	get_data(vars);
	mapinput(vars);
}
