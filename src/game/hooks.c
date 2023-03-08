/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   hooks.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: rharing <rharing@student.42.fr>              +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/03/03 15:42:11 by rharing       #+#    #+#                 */
/*   Updated: 2023/03/08 13:45:59 by rharing       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	move_forward(t_vars *vars, double movespeed)
{
	if (vars->map.map[(int)(vars->ray.pos_x + vars->ray.dir_x * movespeed)] \
		[(int)vars->ray.pos_y] == '0')
	{
		vars->ray.pos_x += vars->ray.dir_x * movespeed;
	}
	if (vars->map.map[(int)vars->ray.pos_x] \
		[(int)(vars->ray.pos_y + vars->ray.dir_y * movespeed)] == '0')
	{
		vars->ray.pos_y += vars->ray.dir_y * movespeed;
	}
}

void	move_backwards(t_vars *vars, double movespeed)
{
	if (vars->map.map[(int)(vars->ray.pos_x - vars->ray.dir_x * movespeed)] \
		[(int)vars->ray.pos_y] == '0')
	{
		vars->ray.pos_x -= vars->ray.dir_x * movespeed;
	}
	if (vars->map.map[(int)vars->ray.pos_x] \
		[(int)(vars->ray.pos_y - vars->ray.dir_y * movespeed)] == '0')
	{
		vars->ray.pos_y -= vars->ray.dir_y * movespeed;
	}
}

void	turn_right(t_vars *vars, double rotspeed)
{
	double	old_dir_x;
	double	old_plane_x;

	old_plane_x = vars->ray.plane_x;
	old_dir_x = vars->ray.dir_x;
	vars->ray.dir_x = \
		vars->ray.dir_x * cos(-rotspeed) - vars->ray.dir_y * sin(-rotspeed);
	vars->ray.dir_y = \
		old_dir_x * sin(-rotspeed) + vars->ray.dir_y * cos(-rotspeed);
	vars->ray.plane_x = \
		vars->ray.plane_x * cos(-rotspeed) - vars->ray.plane_y * sin(-rotspeed);
	vars->ray.plane_y = \
		old_plane_x * sin(-rotspeed) + vars->ray.plane_y * cos(-rotspeed);
}

void	turn_left(t_vars *vars, double rotspeed)
{
	double	old_dir_x;
	double	old_plane_x;

	old_plane_x = vars->ray.plane_x;
	old_dir_x = vars->ray.dir_x;
	vars->ray.dir_x = \
		vars->ray.dir_x * cos(rotspeed) - vars->ray.dir_y * sin(rotspeed);
	vars->ray.dir_y = \
		old_dir_x * sin(rotspeed) + vars->ray.dir_y * cos(rotspeed);
	vars->ray.plane_x = \
		vars->ray.plane_x * cos(rotspeed) - vars->ray.plane_y * sin(rotspeed);
	vars->ray.plane_y = \
		old_plane_x * sin(rotspeed) + vars->ray.plane_y * cos(rotspeed);
}

void	hook(void *param)
{
	t_vars	*vars;

	vars = param;
	raycaster(vars);
	if (mlx_is_key_down(vars->mlx, MLX_KEY_ESCAPE))
		mlx_close_window(vars->mlx);
	if (mlx_is_key_down(vars->mlx, MLX_KEY_UP))
		move_forward(vars, MOVESPEED);
	if (mlx_is_key_down(vars->mlx, MLX_KEY_DOWN))
		move_backwards(vars, MOVESPEED);
	if (mlx_is_key_down(vars->mlx, MLX_KEY_RIGHT))
		turn_right(vars, ROTSPEED);
	if (mlx_is_key_down(vars->mlx, MLX_KEY_LEFT))
		turn_left(vars, ROTSPEED);
}
