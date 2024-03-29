/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   clean_project.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: rharing <rharing@student.42.fr>              +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/03/30 09:53:45 by qfrederi      #+#    #+#                 */
/*   Updated: 2023/03/31 12:31:50 by rharing       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

static void	clean_map_data(t_map *map)
{
	freesplit(map->map);
	freesplit(map->data);
}

static void	clean_textures_wall(t_walls walls)
{
	if (walls.north_t)
		mlx_delete_texture(walls.north_t);
	if (walls.east_t)
		mlx_delete_texture(walls.east_t);
	if (walls.south_t)
		mlx_delete_texture(walls.south_t);
	if (walls.west_t)
		mlx_delete_texture(walls.west_t);
}

static void	clean_images(t_vars *vars)
{
	if (vars->walls.north_img)
		mlx_delete_image(vars->mlx, vars->walls.north_img);
	if (vars->walls.east_img)
		mlx_delete_image(vars->mlx, vars->walls.east_img);
	if (vars->walls.south_img)
		mlx_delete_image(vars->mlx, vars->walls.south_img);
	if (vars->walls.west_img)
		mlx_delete_image(vars->mlx, vars->walls.west_img);
	if (vars->minimap.minimap)
		mlx_delete_image(vars->mlx, vars->minimap.minimap);
	if (vars->display)
		mlx_delete_image(vars->mlx, vars->minimap.minimap);
}

int	clean_project(t_vars *vars, int exit_code)
{
	clean_map_data(&vars->map);
	clean_textures_wall(vars->walls);
	clean_images(vars);
	if (vars->mlx)
		mlx_terminate(vars->mlx);
	return (exit_code);
}
