/* ************************************************************************** */
/*	*/
/*	::::::::	*/
/*   get_colors.c	   :+:	:+:	*/
/*	 +:+	*/
/*   By: rharing <rharing@student.42.fr>	  +#+	 */
/*	   +#+	  */
/*   Created: 2023/02/15 12:02:58 by rharing	   #+#	#+#	 */
/*   Updated: 2023/02/15 18:08:14 by rharing	   ########   odam.nl	 */
/*	*/
/* ************************************************************************** */

#include "cub3D.h"

void	freesplit(char **split)
{
	int	i;

	i = 0;
	while (split[i] != NULL)
	{
		free(split[i]);
		i++;
	}
	free(split);
}

char	*get_ceiling(t_vars *vars)
{
	int		i;
	char	*string;

	i = 0;
	while (vars->map.data[i] != '\0')
	{
		if (vars->map.data[i][0] == 'C' && vars->map.data[i][1] == ' ')
		{
			string = ft_substr(vars->map.data[i], 2, \
								ft_strlen(vars->map.data[i]) - 3);
			break ;
		}
		i++;
	}
	return (string);
}

char	*get_floor(t_vars *vars)
{
	int		i;
	char	*string;

	i = 0;
	while (vars->map.data[i] != '\0')
	{
		if (vars->map.data[i][0] == 'F' && vars->map.data[i][1] == ' ')
		{
			string = ft_substr(vars->map.data[i], 2, \
								ft_strlen(vars->map.data[i]) - 3);
			break ;
		}
		i++;
	}
	return (string);
}

void	ceiling_atoi(t_vars *vars, char *ceiling)
{
	char	**temp;

	temp = ft_split(ceiling, ',');
	if (!temp)
		ft_error("malloc failed", 1);
	vars->ceiling_rgb = calloc(3, sizeof(int *));
	if (!vars->ceiling_rgb)
	{
		freesplit(temp);
		ft_error("malloc failed", 1);
	}
	vars->ceiling_rgb[0] = ft_atoi(temp[0]);
	vars->ceiling_rgb[1] = ft_atoi(temp[1]);
	vars->ceiling_rgb[2] = ft_atoi(temp[2]);
	free(ceiling);
	freesplit(temp);
}

void	floor_atoi(t_vars *vars, char *floor)
{
	char	**temp;

	temp = ft_split(floor, ',');
	if (!temp)
		ft_error("malloc failed", 1);
	vars->floor_rgb = calloc(3, sizeof(int *));
	if (!vars->floor_rgb)
	{
		freesplit(temp);
		ft_error("malloc failed", 1);
	}
	vars->floor_rgb[0] = ft_atoi(temp[0]);
	vars->floor_rgb[1] = ft_atoi(temp[1]);
	vars->floor_rgb[2] = ft_atoi(temp[2]);
	free(floor);
	freesplit(temp);
}

void	get_colors(t_vars *vars)
{
	char	*ceiling;
	char	*floor;

	ceiling = get_ceiling(vars);
	ceiling_atoi(vars, ceiling);
	floor = get_floor(vars);
	floor_atoi(vars, floor);
}
