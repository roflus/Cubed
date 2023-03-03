/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   hooks.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: rharing <rharing@student.42.fr>              +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/03/03 15:42:11 by rharing       #+#    #+#                 */
/*   Updated: 2023/03/03 15:43:26 by rharing       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	hook(void *param)
{
	t_vars	*vars;

	vars = param;
	if (mlx_is_key_down(vars->mlx, MLX_KEY_ESCAPE))
		mlx_close_window(vars->mlx);
	if (mlx_is_key_down(vars->mlx, MLX_KEY_UP))
	{
		move_up(vars);
		// check_player_position(vars);
	}
	if (mlx_is_key_down(vars->mlx, MLX_KEY_DOWN))
	{
		move_down(vars);
		// check_player_position(vars);
	}
	if (mlx_is_key_down(vars->mlx, MLX_KEY_LEFT))
	{
		move_left(vars);
	}	
	if (mlx_is_key_down(vars->mlx, MLX_KEY_RIGHT))
	{
		move_right(vars);
	}
}
