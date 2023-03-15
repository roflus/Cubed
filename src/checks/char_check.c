/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   char_check.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: rharing <rharing@student.42.fr>              +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/01/26 17:56:21 by rharing       #+#    #+#                 */
/*   Updated: 2023/03/15 13:37:34 by rharing       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

static bool	check_player_count(t_vars *vars, int i, int k)
{
	char	pos;

	if (vars->map.map[i][k] == 'N' || vars->map.map[i][k] == 'E' || \
		vars->map.map[i][k] == 'S' || vars->map.map[i][k] == 'W')
	{
		pos = vars->map.map[i][k];
		vars->map.pos = pos;
		vars->player.player_x = k;
		vars->player.player_y = i;
		vars->ray.pos_x = i + 0.5;
		vars->ray.pos_y = k + 0.5;
		vars->map.map[i][k] = '0';
		return (true);
	}
	return (false);
}

bool	check_char_map(t_vars *vars)
{
	int	i;
	int	k;

	i = 1;
	while (i < vars->map.array_count)
	{
		k = 0;
		while (vars->map.map[i][k] != '\0')
		{
			if (vars->map.map[i][k] != '1' && vars->map.map[i][k] != '0' &&
				vars->map.map[i][k] != ' ')
			{
				if (check_player_count(vars, i, k) == true)
					vars->playercount++;
				else
					return (false);
			}
			k++;
		}
		i++;
	}
	if (vars->playercount != 1)
		ft_error("Player Count incorrect", 2);
	return (true);
}

static bool	check_pos_char(t_vars *vars, int i, size_t k)
{
	if (k > (ft_strlen(vars->map.map[i + 1]) - 1))
		return (false);
	if (k > (ft_strlen(vars->map.map[i - 1]) - 1))
		return (false);
	if (vars->map.map[i + 1][k] == ' ')
		return (false);
	if (vars->map.map[i - 1][k] == ' ')
		return (false);
	if (vars->map.map[i][k + 1] == ' ')
		return (false);
	if (vars->map.map[i][k - 1] == ' ')
		return (false);
	return (true);
}

bool	check_empty(t_vars *vars)
{
	int	i;
	int	k;

	i = 0;
	while (i < vars->map.array_count)
	{
		k = 0;
		while (vars->map.map[i][k] != '\0')
		{
			if (vars->map.map[i][k] == '0' ||
				vars->map.map[i][k] == vars->map.pos)
			{
				if (check_pos_char(vars, i, k) == false)
					return (false);
			}
			k++;
		}
		i++;
	}
	return (true);
}
