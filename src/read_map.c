/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   read_map.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: qfrederi <qfrederi@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/01/11 14:40:40 by rharing       #+#    #+#                 */
/*   Updated: 2023/01/19 17:02:36 by qfrederi      ########   odam.nl         */
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
	vars->map->array_count = nlcount(mapline);
	vars->map->map = ft_split(mapline, '\n');
	if (vars->map->map == NULL)
		ft_error("Error\nMalloc map failed", 2);
}

static void	mapinput(t_vars *vars)
{
	char	*temp;
	char	*mapline;
	char	*newmapline;

	mapline = ft_calloc(1, 1);
	if (mapline == NULL)
		ft_error("Error\nMalloc failed", 2);
	while (1)
	{
		temp = get_next_line(vars->map->fd);
		if (ft_strncmp(temp, "\n", 1) != 0)
		{
			mapline = ft_strdup(temp);
			free(temp);
			break;
		}
		free(temp);
	}
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
		ft_error("Error\nMalloc error", 2);
	while (1)
	{
		temp1 = get_next_line(vars->map->fd);
		if (ft_strncmp(temp1, "\n", 1) != 0)
		{
			vars->map->data[k] = ft_strdup(temp1);
			if (k == 5)
			{
				free(temp1);
				break;
			}
			k++;
		}
		free(temp1);
		i++;
	}
	if (check_data(vars) == false)
		ft_error("Cardinal Data not valid", 2);
}

void	open_map(t_vars *vars, char *map)
{
	int 	i;
	i = 0;

	vars->map->fd = open(map, O_RDONLY);
	if (vars->map->fd < 0)
		ft_error("Error\nCan't open file", 2);
	get_data(vars);
	mapinput(vars);
	check_map(vars);
}
