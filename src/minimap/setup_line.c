/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   setup_line.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: qfrederi <qfrederi@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/02/20 13:12:59 by qfrederi      #+#    #+#                 */
/*   Updated: 2023/02/20 13:30:58 by qfrederi      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"




//Only for Testing DELETE WHEN DONE
static void set_point_on_map(t_vars *vars)
{
    int i;
	int k;

    i = 0;
	while (i < 6)
	{
		k = 0;
		while (k < 6)
		{
			mlx_put_pixel(vars->line1, k, i, 0x7D2AFA);
			k++;
		}
		i++;
	}
}

void create_points_line(t_vars *vars)
{
    vars->line1 = mlx_new_image(vars->mlx, 6, 6);
    set_point_on_map(vars);
}