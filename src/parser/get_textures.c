/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   get_textures.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: rharing <rharing@student.42.fr>              +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/02/10 14:55:06 by rharing       #+#    #+#                 */
/*   Updated: 2023/03/02 13:57:11 by rharing       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

static void	getnorth(t_vars *vars)
{
	char	*path;
	int		i;

	i = 0;
	while (vars->map.data[i] != '\0')
	{
		if (vars->map.data[i][0] == 'N' && vars->map.data[i][1] == 'O')
		{
			path = ft_substr(vars->map.data[i], 3, \
			ft_strlen(vars->map.data[i]) - 4);
			break ;
		}
		i++;
	}
	printf("%s\n", path);
	vars->walls.north_t = mlx_load_png(path);
	free(path);
	if (!vars->walls.north_t)
		ft_error("Can't load texture north", 2);
}

static void	geteast(t_vars *vars)
{
	char	*path;
	int		i;

	i = 0;
	while (vars->map.data[i] != '\0')
	{
		if (vars->map.data[i][0] == 'E' && vars->map.data[i][1] == 'A')
		{
			path = ft_substr(vars->map.data[i], 3, \
			ft_strlen(vars->map.data[i]) - 4);
			break ;
		}
		i++;
	}
	printf("test: %s\n", path);
	vars->walls.east_t = mlx_load_png(path);
	free(path);
	if (!vars->walls.east_t)
		ft_error("Can't load texture east", 2);
}

static void	getsouth(t_vars *vars)
{
	char	*path;
	int		i;

	i = 0;
	while (vars->map.data[i] != '\0')
	{
		if (vars->map.data[i][0] == 'S' && vars->map.data[i][1] == 'O')
		{
			path = ft_substr(vars->map.data[i], 3, \
			ft_strlen(vars->map.data[i]) - 4);
			break ;
		}
		i++;
	}
	printf("test: %s\n", path);
	vars->walls.south_t = mlx_load_png(path);
	free(path);
	if (!vars->walls.south_t)
		ft_error("Can't load texture south", 2);
}

static void	getwest(t_vars *vars)
{
	char	*path;
	int		i;

	i = 0;
	while (vars->map.data[i] != '\0')
	{
		if (vars->map.data[i][0] == 'W' && vars->map.data[i][1] == 'E')
		{
			path = ft_substr(vars->map.data[i], 3, \
			ft_strlen(vars->map.data[i]) - 4);
			break ;
		}
		i++;
	}
	printf("test: %s\n", path);
	vars->walls.west_t = mlx_load_png(path);
	free(path);
	if (!vars->walls.west_t)
		ft_error("Can't load texture west", 2);
}

void	get_textures(t_vars *vars)
{
	getnorth(vars);
	// vars->walls.north_img = mlx_new_image(vars->mlx, 512, 512);
	vars->walls.north_img = mlx_texture_to_image(vars->mlx, vars->walls.north_t);
	if (!vars->walls.north_img)
		ft_error("Can't convert texture to image", 3);
	geteast(vars);
	vars->walls.east_img = mlx_texture_to_image(vars->mlx, vars->walls.east_t);
	if (!vars->walls.east_img)
		ft_error("Can't convert texture to image", 3);
	getsouth(vars);
	vars->walls.south_img = \
		mlx_texture_to_image(vars->mlx, vars->walls.south_t);
	if (!vars->walls.south_img)
		ft_error("Can't convert texture to image", 3);
	getwest(vars);
	vars->walls.west_img = mlx_texture_to_image(vars->mlx, vars->walls.west_t);
	if (!vars->walls.west_img)
		ft_error("Can't convert texture to image", 3);
}
