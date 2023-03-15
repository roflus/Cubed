/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   key_hook.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: rharing <rharing@student.42.fr>              +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/03/03 15:42:11 by rharing       #+#    #+#                 */
/*   Updated: 2023/03/15 13:33:44 by rharing       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

static void	move_forward(t_vars *vars)
{
	vars->player.player_x = vars->ray.pos_y;
	vars->player.player_y = vars->ray.pos_x;
	if (vars->map.map[(int)(vars->ray.pos_x + vars->ray.dir_x * MOVESPEED)] \
		[(int)vars->ray.pos_y] == '0')
	{
		vars->ray.pos_x += vars->ray.dir_x * MOVESPEED;
	}
	if (vars->map.map[(int)vars->ray.pos_x] \
		[(int)(vars->ray.pos_y + vars->ray.dir_y * MOVESPEED)] == '0')
	{
		vars->ray.pos_y += vars->ray.dir_y * MOVESPEED;
	}
}

static void	move_backwards(t_vars *vars)
{
	vars->player.player_x = vars->ray.pos_y;
	vars->player.player_y = vars->ray.pos_x;
	if (vars->map.map[(int)(vars->ray.pos_x - vars->ray.dir_x * MOVESPEED)] \
		[(int)vars->ray.pos_y] == '0')
	{
		vars->ray.pos_x -= vars->ray.dir_x * MOVESPEED;
	}
	if (vars->map.map[(int)vars->ray.pos_x] \
		[(int)(vars->ray.pos_y - vars->ray.dir_y * MOVESPEED)] == '0')
	{
		vars->ray.pos_y -= vars->ray.dir_y * MOVESPEED;
	}
}

static void	turn_right(t_vars *vars)
{
	double	old_dir_x;
	double	old_plane_x;

	old_plane_x = vars->ray.plane_x;
	old_dir_x = vars->ray.dir_x;
	vars->ray.dir_x = \
		vars->ray.dir_x * cos(-ROTSPEED) - vars->ray.dir_y * sin(-ROTSPEED);
	vars->ray.dir_y = \
		old_dir_x * sin(-ROTSPEED) + vars->ray.dir_y * cos(-ROTSPEED);
	vars->ray.plane_x = \
		vars->ray.plane_x * cos(-ROTSPEED) - vars->ray.plane_y * sin(-ROTSPEED);
	vars->ray.plane_y = \
		old_plane_x * sin(-ROTSPEED) + vars->ray.plane_y * cos(-ROTSPEED);
}

static void	turn_left(t_vars *vars)
{
	double	old_dir_x;
	double	old_plane_x;

	old_plane_x = vars->ray.plane_x;
	old_dir_x = vars->ray.dir_x;
	vars->ray.dir_x = \
		vars->ray.dir_x * cos(ROTSPEED) - vars->ray.dir_y * sin(ROTSPEED);
	vars->ray.dir_y = \
		old_dir_x * sin(ROTSPEED) + vars->ray.dir_y * cos(ROTSPEED);
	vars->ray.plane_x = \
		vars->ray.plane_x * cos(ROTSPEED) - vars->ray.plane_y * sin(ROTSPEED);
	vars->ray.plane_y = \
		old_plane_x * sin(ROTSPEED) + vars->ray.plane_y * cos(ROTSPEED);
}

void	keyhook(t_vars *vars)
{
	if (mlx_is_key_down(vars->mlx, MLX_KEY_ESCAPE))
		mlx_close_window(vars->mlx);
	if (mlx_is_key_down(vars->mlx, MLX_KEY_RIGHT))
		turn_right(vars);
	if (mlx_is_key_down(vars->mlx, MLX_KEY_LEFT))
		turn_left(vars);
	if (mlx_is_key_down(vars->mlx, MLX_KEY_D))
		strafe_right(vars);
	if (mlx_is_key_down(vars->mlx, MLX_KEY_A))
		strafe_left(vars);
	if (mlx_is_key_down(vars->mlx, MLX_KEY_W))
		move_forward(vars);
	if (mlx_is_key_down(vars->mlx, MLX_KEY_S))
		move_backwards(vars);
}
