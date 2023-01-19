/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   map_check.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: qfrederi <qfrederi@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/01/12 12:33:23 by rharing       #+#    #+#                 */
/*   Updated: 2023/01/19 17:28:17 by qfrederi      ########   odam.nl         */
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

static bool check_first_last(t_vars *vars)
{
	int i;

	i = 0;
	while (vars->map->map[0][i] != '\0')
	{
		if (vars->map->map[0][i] != ' ' && vars->map->map[0][i] != '1')
			return (false);
		i++;
	}
	i = 0;
	while (vars->map->map[vars->map->array_count][i] != '\0')
	{
		if (vars->map->map[vars->map->array_count][i] != ' ' \
		&& vars->map->map[vars->map->array_count][i] != '1')
			return (false);
		i++;
	}
	return (true);
}

// Ik heb dit snel geschreven want ik had geen zin meer. Dit kan sowieso makkelijker en anders gesplitst
static bool check_walls(t_vars *vars)
{
	int 	i;
	size_t	k;

	i = 1;
	
	while (i < vars->map->array_count)
	{
		k = 0;
		//Begin string
		while (k < ft_strlen(vars->map->map[i]))
		{
			if (vars->map->map[i][k] != '1')
			{
				if (vars->map->map[i][k] == '0')
					return (false);
			}
			else
				break;
			k++;
		}

		//Eind string
		k = ft_strlen(vars->map->map[i]);
		while (1)
		{
			if (vars->map->map[i][k] != '1')
			{
				if (vars->map->map[i][k] == '0')
					return (false);
			}
			else
				break;
			k--;
		}
		i++;
	}
	return (true);
}

static bool check_player_count(t_vars *vars, int i, int k)
{
	if (vars->map->map[i][k] == 'N' || vars->map->map[i][k] == 'E' \
		|| vars->map->map[i][k] == 'S' || vars->map->map[i][k] == 'W')
		return (true);
	return (false);
}

static bool check_char_map(t_vars *vars)
{
	int i;
	int k;
	int player_count;
	
	player_count = 0;
	i = 1;
	while (i < vars->map->array_count)
	{
		k = 0;
		while (vars->map->map[i][k] != '\0')
		{
			if (vars->map->map[i][k] != '1' && vars->map->map[i][k] != '0' && \
				vars->map->map[i][k] != ' ')
			{
				// Ik heb nu voor makkelijkheid i, k meegegeven. Maar kunnen ook de character meegeven
				if (check_player_count(vars, i, k) == true)
					player_count++;
				else
					return (false);
			}
			k++;
		}
		i++;
	}
	// Heb nu Player_count check hieronder gedaan. Maar mogelijk de int meegeven met check_player_count
	if (player_count != 1)
		ft_error("Player Count incorrect", 2);
	return (true);
}

// We kunnen ook 1 check error message voor check_map doen. Dan wordt het weer een bool ipv void. Voor nu heb ik het gesplits
// zodat we makkelijker qua testen kunnen zien waar het fout gaat
void check_map(t_vars *vars)
{
	if (check_first_last(vars) == false)
		ft_error("First or Last Line of Map not valid", 2);
	if (check_char_map(vars) == false)
		ft_error("Invalid Char in Map", 2);
	if (check_walls(vars) == false)
		ft_error("WALLS ERROR", 2);
}