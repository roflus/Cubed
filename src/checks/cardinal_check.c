/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   cardinal_check.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: rharing <rharing@student.42.fr>              +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/01/19 13:33:17 by qfrederi      #+#    #+#                 */
/*   Updated: 2023/03/02 19:03:16 by rharing       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

bool	check_intsize(char **colors)
{
	if (ft_atoi(colors[0]) > 255 || ft_atoi(colors[0]) < 0)
		return (false);
	if (ft_atoi(colors[1]) > 255 || ft_atoi(colors[1]) < 0)
		return (false);
	if (ft_atoi(colors[2]) > 255 || ft_atoi(colors[2]) < 0)
		return (false);
	else
		return (true);
}

static bool	check_fcdata(char *string)
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

static bool	check_color(char **mapdata, char c)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (i < 6)
	{
		if (mapdata[i][0] == c && mapdata[i][1] == ' ')
		{
			if (check_fcdata(mapdata[i]) == true)
				count++;
		}
		i++;
	}
	if (count == 1)
		return (true);
	return (false);
}

static bool	check_cardinal(char **mapdata, char first, char second)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (i < 6)
	{
		if (mapdata[i][0] == first && mapdata[i][1] == second \
			&& mapdata[i][2] == ' ')
			count++;
		i++;
	}
	if (count == 1)
		return (true);
	return (false);
}

bool	check_data(char **mapdata)
{
	if (check_cardinal(mapdata, 'N', 'O') == false)
		return (false);
	if (check_cardinal(mapdata, 'E', 'A') == false)
		return (false);
	if (check_cardinal(mapdata, 'S', 'O') == false)
		return (false);
	if (check_cardinal(mapdata, 'W', 'E') == false)
		return (false);
	if (check_color(mapdata, 'F') == false)
		return (false);
	if (check_color(mapdata, 'C') == false)
		return (false);
	return (true);
}
