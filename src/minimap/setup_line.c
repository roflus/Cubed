/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   setup_line.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: rharing <rharing@student.42.fr>              +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/02/20 13:12:59 by qfrederi      #+#    #+#                 */
/*   Updated: 2023/03/02 16:08:32 by rharing       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

static void set_point_on_map(t_vars *vars)
{
	int i;

	i = 0;
	while (i < vars->inst_len)
	{
		mlx_image_to_window(vars->mlx, vars->line1, (vars->player1->instances[0].x + 6) + (vars->player.playdelta_x * (5 + (i * 5))), \
			((vars->player1->instances[0].y + 6) + (vars->player.playdelta_y * (5 + (i * 5)))));
		i++;
	}
}

//Only for Testing DELETE WHEN DONE
static void draw_point_on_map(t_vars *vars)
{
    int i;
	int k;

    i = 0;
	while (i < 6)
	{
		k = 0;
		while (k < 6)
		{
			// mlx_put_pixel(vars->line1, k, i, 0x7D2AFA);
			mlx_put_pixel(vars->line1, k, i, 2031460);
			k++;
		}
		i++;
	}
}

void create_points_line(t_vars *vars)
{
    vars->line1 = mlx_new_image(vars->mlx, 6, 6);
    draw_point_on_map(vars);
	set_point_on_map(vars);
	vars->linepixel = mlx_new_image(vars->mlx, 1, 1);
	mlx_put_pixel(vars->linepixel, 0, 0, 0x7D2AFA);
	set_line_start_end(vars);
	drawline(vars);
}
