/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   minimap.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: rharing <rharing@student.42.fr>              +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/03/10 13:19:28 by rharing       #+#    #+#                 */
/*   Updated: 2023/03/10 18:55:59 by rharing       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

#define TILESIZE 15

int	get_width(char **map)
{
	int		longest;
	int		len;
	size_t	i;

	longest = ft_strlen(map[0]);
	i = 1;
	while (map[i] != '\0')
	{
		len = ft_strlen(map[i]);
		if (longest < len)
			longest = len;
		i++;
	}
	return (longest);
}

void	draw_square(mlx_image_t *minimap, int start_x, int start_y, int color)
{
	int	end_x;
	int	end_y;
	int	x;
	int	y;

	x = start_x;
	y = start_y;
	end_x = start_x + TILESIZE;
	end_y = start_y + TILESIZE;
	while (y < end_y)
	{
		x = start_x;
		while (x < end_x)
		{
			mlx_put_pixel(minimap, x, y, color);
			x++;
		}
		y++;
	}
}

void	draw_minimap(char **map, mlx_image_t *minimap)
{
	int	i;
	int	k;
	int	x;
	int	y;

	i = 0;
	x = 0;
	y = 0;
	while (map[i] != NULL)
	{
		k = 0;
		x = 0;
		while (k < ft_strlen(map[i]))
		{
			if (map[i][k] == '1')
				draw_square(minimap, x, y, 255255255);
			else if (map[i][k] == '0')
				draw_square(minimap, x, y, 267833369);
			k++;
			x += TILESIZE;
		}
		y += TILESIZE;
		i++;
	}
}

static void draw_player(t_vars *vars)
{
	int i;
	int k;

	i = vars->player.player_y * TILESIZE;
	while (i < (vars->player.player_y * TILESIZE + 15))
	{
		k = (vars->player.player_x * TILESIZE);
		while (k < (vars->player.player_x * TILESIZE + 15))
		{
			mlx_put_pixel(vars->display, k, i, 0xFF0000FF);
			k++;
		}
		i++;
	}
}

// void	create_minimap(t_vars *vars)
// {
// 	if (vars->minimap.width == 0)
// 		vars->minimap.width = get_width(vars->map.map);
// 	if (vars->minimap.height == 0)
// 		vars->minimap.height = vars->map.array_count + 2;
// 	mlx_delete_image(vars->mlx, vars->minimap.minimap);
// 	vars->minimap.minimap = mlx_new_image(vars->mlx, \
// 		(vars->minimap.width * TILESIZE + vars->minimap.width), (vars->minimap.height * TILESIZE + vars->minimap.height));
// 	if (!vars->minimap.minimap)
// 		ft_error("failed to allocate image", 4);
// 	draw_minimap(vars->map.map, vars->minimap.minimap);
// 	draw_player(vars);
// }

void	create_minimap(t_vars *vars)
{
	// if (vars->minimap.width == 0)
	// 	vars->minimap.width = get_width(vars->map.map);
	// if (vars->minimap.height == 0)
	// 	vars->minimap.height = vars->map.array_count + 2;
	// mlx_delete_image(vars->mlx, vars->minimap.minimap);
	// vars->minimap.minimap = mlx_new_image(vars->mlx, \
	// 	(vars->minimap.width * TILESIZE + vars->minimap.width), (vars->minimap.height * TILESIZE + vars->minimap.height));
	// if (!vars->minimap.minimap)
	// 	ft_error("failed to allocate image", 4);
	draw_minimap(vars->map.map, vars->display);
	draw_player(vars);
}
