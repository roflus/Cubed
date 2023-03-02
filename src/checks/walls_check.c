/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   walls_check.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: rharing <rharing@student.42.fr>              +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/01/26 17:47:12 by rharing       #+#    #+#                 */
/*   Updated: 2023/03/02 17:37:50 by rharing       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

static bool	check_walls_start(t_vars *vars, int i)
{
	int	k;

	k = 0;
	while (k < ft_strlen(vars->map.map[i]))
	{
		if (vars->map.map[i][k] != '1')
		{
			if (vars->map.map[i][k] == '0')
				return (false);
		}
		else
			break ;
		k++;
	}
	return (true);
}

static bool	check_walls_end(t_vars *vars, int i)
{
	int	k;

	k = ft_strlen(vars->map.map[i]);
	while (1)
	{
		if (vars->map.map[i][k] != '1')
		{
			if (vars->map.map[i][k] == '0')
				return (false);
		}
		else
			break ;
		k--;
	}
	return (true);
}

bool	check_walls(t_vars *vars)
{
	int		i;
	size_t	k;

	i = 1;
	while (i < vars->map.array_count)
	{
		if (check_walls_start(vars, i) == false)
			return (false);
		if (check_walls_end(vars, i) == false)
			return (false);
		i++;
	}
	return (true);
}

bool	check_first_last(t_vars *vars)
{
	int	i;

	i = 0;
	while (vars->map.map[0][i] != '\0')
	{
		if (vars->map.map[0][i] != ' ' && vars->map.map[0][i] != '1')
			return (false);
		i++;
	}
	i = 0;
	while (vars->map.map[vars->map.array_count][i] != '\0')
	{
		if (vars->map.map[vars->map.array_count][i] != ' ' \
		&& vars->map.map[vars->map.array_count][i] != '1')
			return (false);
		i++;
	}
	return (true);
}
