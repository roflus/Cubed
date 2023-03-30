/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   minimap.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: qfrederi <qfrederi@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/03/10 13:19:28 by rharing       #+#    #+#                 */
/*   Updated: 2023/03/30 14:01:02 by qfrederi      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

#define TILESIZE 15

static void	draw_square(mlx_image_t *minimap, int start_x, \
						int start_y, int color)
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

static void	draw_minimap(char **map, mlx_image_t *minimap)
{
	int		i;
	size_t	k;
	int		x;
	int		y;

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

static void	draw_player(t_vars *vars)
{
	int	i;
	int	k;

	i = vars->player.player_x * TILESIZE;
	while (i < (vars->player.player_x * TILESIZE + TILESIZE))
	{
		k = (vars->player.player_y * TILESIZE);
		while (k < (vars->player.player_y * TILESIZE + TILESIZE))
		{
			mlx_put_pixel(vars->display, k, i, 0xFF0000FF);
			k++;
		}
		i++;
	}
}

void	create_minimap(t_vars *vars)
{
	if (vars->map.array_count < (HEIGHT / TILESIZE))
	{
		draw_minimap(vars->map.map, vars->display);
		draw_player(vars);
	}
}
