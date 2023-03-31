/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   get_textures.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: qfrederi <qfrederi@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/02/10 14:55:06 by rharing       #+#    #+#                 */
/*   Updated: 2023/03/31 10:44:23 by qfrederi      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

static bool	gettexture(char **mapdata, mlx_texture_t **cardinal, \
						char first, char second)
{
	char	*path;
	char	*trimmed;
	int		i;

	i = 0;
	path = NULL;
	while (mapdata[i] != NULL)
	{
		if (mapdata[i][0] == first && mapdata[i][1] == second)
		{
			path = ft_substr(mapdata[i], 3, \
			ft_strlen(mapdata[i]) - 4);
			break ;
		}
		i++;
	}
	trimmed = ft_strtrim(path, " ");
	free(path);
	*cardinal = mlx_load_png(trimmed);
	free(trimmed);
	if (*cardinal == NULL)
		return (false);
	return (true);
}

void	get_textures(t_vars *vars)
{
	if (gettexture(vars->map.data, &vars->walls.north_t, 'N', 'O') == false)
		ft_error("Can't load texture", clean_project(vars, 1));
	vars->walls.north_img = \
		mlx_texture_to_image(vars->mlx, vars->walls.north_t);
	if (!vars->walls.north_img)
		ft_error("Can't convert texture to image", 1);
	if (gettexture(vars->map.data, &vars->walls.east_t, 'E', 'A') == false)
		ft_error("Can't load texture", clean_project(vars, 1));
	vars->walls.east_img = mlx_texture_to_image(vars->mlx, vars->walls.east_t);
	if (!vars->walls.east_img)
		ft_error("Can't convert texture to image", 1);
	if (gettexture(vars->map.data, &vars->walls.south_t, 'S', 'O') == false)
		ft_error("Can't convert texture to image", 1);
	vars->walls.south_img = \
		mlx_texture_to_image(vars->mlx, vars->walls.south_t);
	if (!vars->walls.south_img)
		ft_error("Can't convert texture to image", 1);
	if (gettexture(vars->map.data, &vars->walls.west_t, 'W', 'E') == false)
		mlx_texture_to_image(vars->mlx, vars->walls.south_t);
	vars->walls.west_img = mlx_texture_to_image(vars->mlx, vars->walls.west_t);
	if (!vars->walls.west_img)
		ft_error("Can't convert texture to image", 1);
}
