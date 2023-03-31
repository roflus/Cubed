/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   get_colors.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: qfrederi <qfrederi@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/03/30 13:07:51 by qfrederi      #+#    #+#                 */
/*   Updated: 2023/03/31 10:44:10 by qfrederi      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

char	*get_color(t_vars *vars, char c)
{
	int		i;
	char	*string;
	char	*trimmed;

	i = 0;
	string = NULL;
	while (vars->map.data[i] != NULL)
	{
		if (vars->map.data[i][0] == c && vars->map.data[i][1] == ' ')
		{
			string = ft_substr(vars->map.data[i], 2, \
								ft_strlen(vars->map.data[i]) - 3);
			break ;
		}
		i++;
	}
	trimmed = ft_strtrim(string, " ");
	free(string);
	return (trimmed);
}

static int	get_rgba(int r, int g, int b, int a)
{
	return (r << 24 | g << 16 | b << 8 | a);
}

static bool	set_colors(int *colors, char *rgb)
{
	char	**temp;

	temp = ft_split(rgb, ',');
	free(rgb);
	if (!temp)
		return (false);
	if (check_intsize(temp) == false)
	{
		freesplit(temp);
		return (false);
	}
	*colors = get_rgba(ft_atoi(temp[0]), ft_atoi(temp[1]), \
						ft_atoi(temp[2]), 0x000000FF);
	freesplit(temp);
	return (true);
}

void	get_colors(t_vars *vars)
{
	char	*ceiling;
	char	*floor;

	ceiling = get_color(vars, 'C');
	if (ceiling == NULL || check_fcdata(ceiling) == false)
		ft_error("Ceiling color error", clean_project(vars, 1));
	if (set_colors(&vars->ceiling_rgb, ceiling) == false)
		ft_error("Set Ceiling Colors Failed", clean_project(vars, 1));
	floor = get_color(vars, 'F');
	if (floor == NULL || check_fcdata(floor) == false)
		ft_error("Floor color error", clean_project(vars, 1));
	if (set_colors(&vars->floor_rgb, floor) == false)
		ft_error("Set Floor Colors Failed", clean_project(vars, 1));
}
