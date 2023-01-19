/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   cardinal_check.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: qfrederi <qfrederi@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/01/19 13:33:17 by qfrederi      #+#    #+#                 */
/*   Updated: 2023/01/19 14:31:05 by qfrederi      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

static bool check_floor(t_vars *vars)
{
	int i;
	int count;

	i = 0;
	count = 0;
	while (i < 6)
	{
		if (vars->map->data[i][0] == 'F' && vars->map->data[i][1] == ' ')
			count++;
		i++;
	}
	if (count == 1)
		return (true);
	return (false);
	
}

static bool check_ceiling(t_vars *vars)
{
	int i;
	int count;

	i = 0;
	count = 0;
	while (i < 6)
	{
		if (vars->map->data[i][0] == 'C' && vars->map->data[i][1] == ' ')
			count++;
		i++;
	}
	if (count == 1)
		return (true);
	return (false);
	
}

static bool check_north(t_vars *vars)
{
	int i;
	int count;

	i = 0;
	count = 0;
	while (i < 6)
	{
		if (vars->map->data[i][0] == 'N' && vars->map->data[i][1] == 'O' && vars->map->data[i][2] == ' ')
			count++;
		i++;
	}
	if (count == 1)
		return (true);
	return (false);
	
}

static bool check_south(t_vars *vars)
{
	int i;
	int count;

	i = 0;
	count = 0;
	while (i < 6)
	{
		if (vars->map->data[i][0] == 'S' && vars->map->data[i][1] == 'O' && vars->map->data[i][2] == ' ')
			count++;
		i++;
	}
	if (count == 1)
		return (true);
	return (false);
	
}

static bool check_east(t_vars *vars)
{
	int i;
	int count;

	i = 0;
	count = 0;
	while (i < 6)
	{
		if (vars->map->data[i][0] == 'E' && vars->map->data[i][1] == 'A' && vars->map->data[i][2] == ' ')
			count++;
		i++;
	}
	if (count == 1)
		return (true);
	return (false);
	
}

static bool check_west(t_vars *vars)
{
	int i;
	int count;

	i = 0;
	count = 0;
	while (i < 6)
	{
		if (vars->map->data[i][0] == 'W' && vars->map->data[i][1] == 'E' && vars->map->data[i][2] == ' ')
			count++;
		i++;
	}
	if (count == 1)
		return (true);
	return (false);
	
}

bool check_data(t_vars *vars)
{
	if (check_north(vars) == false)
        return (false);
    if (check_west(vars) == false)
        return (false);
	if (check_east(vars) == false)
        return (false);
	if (check_south(vars) == false)
        return (false);
	if (check_floor(vars) == false)
        return (false);
	if (check_ceiling(vars) == false)
        return (false);
	return (true);
}