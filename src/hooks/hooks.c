/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   hooks.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: rharing <rharing@student.42.fr>              +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/03/03 15:42:11 by rharing       #+#    #+#                 */
/*   Updated: 2023/03/10 18:38:07 by rharing       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	hook(void *param)
{
	t_vars	*vars;

	vars = param;
	keyhook(vars);
	mousehook(vars);
	raycaster(vars);
	// create_minimap(vars);
	// mlx_image_to_window(vars->mlx, vars->minimap.minimap, 0, 0);
}
