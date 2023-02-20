/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   initialize_minimap.c                               :+:    :+:            */
/*                                                     +:+                    */
/*   By: qfrederi <qfrederi@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/02/20 09:26:32 by qfrederi      #+#    #+#                 */
/*   Updated: 2023/02/20 09:26:39 by qfrederi      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void draw_map(t_vars *vars)
{
	int i = 0;
	int k;

	while (vars->map.map[i] != NULL)
	{
		k = 0;
		while (k < ft_strlen(vars->map.map[i]))
		{
			if (vars->map.map[i][k] == '1')
				mlx_image_to_window(vars->mlx, vars->wall, (k * MAPPIXEL), (i * MAPPIXEL));
			else if (vars->map.map[i][k] == '0')
				mlx_image_to_window(vars->mlx, vars->empty, (k * MAPPIXEL), (i * MAPPIXEL));
			k++;
		}
		i++;
	}
}

//void create_images_minimap(t_vars *vars)
//{

//}