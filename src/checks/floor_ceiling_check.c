/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   floor_ceiling_check.c                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: rharing <rharing@student.42.fr>              +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/02/15 14:11:38 by qfrederi      #+#    #+#                 */
/*   Updated: 2023/02/15 19:01:21 by rharing       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

bool	check_ceiling_intsize(t_vars *vars)
{
	if (vars->ceiling_rgb[0] > 255 || vars->ceiling_rgb[0] < 0)
		return (false);
	if (vars->ceiling_rgb[1] > 255 || vars->ceiling_rgb[1] < 0)
		return (false);
	if (vars->ceiling_rgb[2] > 255 || vars->ceiling_rgb[2] < 0)
		return (false);
	else
		return (true);
}

bool	check_floor_intsize(t_vars *vars)
{
	if (vars->floor_rgb[0] > 255 || vars->floor_rgb[0] < 0)
		return (false);
	if (vars->floor_rgb[1] > 255 || vars->floor_rgb[1] < 0)
		return (false);
	if (vars->floor_rgb[2] > 255 || vars->floor_rgb[2] < 0)
		return (false);
	else
		return (true);
}

bool	check_fcdata(char *string)
{
	int	k;
	int	count;

	count = 0;
	k = 2;
	if ((!ft_isdigit(string[k])) || \
		(!ft_isdigit(string[ft_strlen(string) - 2])))
		return (false);
	while (string[k] != '\n')
	{
		if (!ft_isdigit(string[k]) && string[k] != ',')
			return (false);
		if (string[k] == ',')
		{
			if ((!ft_isdigit(string[k - 1])) \
				|| (!ft_isdigit(string[k + 1])))
				return (false);
			count++;
		}
		k++;
	}
	if (count != 2 || k > 13)
		return (false);
	return (true);
}

bool	check_floor(t_vars *vars)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (i < 6)
	{
		if (vars->map.data[i][0] == 'F' && vars->map.data[i][1] == ' ')
		{
			if (check_fcdata(vars->map.data[i]) == true)
				count++;
		}
		i++;
	}
	if (count == 1)
		return (true);
	return (false);
}

bool	check_ceiling(t_vars *vars)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (i < 6)
	{
		if (vars->map.data[i][0] == 'C' && vars->map.data[i][1] == ' ')
		{
			if (check_fcdata(vars->map.data[i]) == true)
				count++;
		}
		i++;
	}
	if (count == 1)
		return (true);
	return (false);
}
