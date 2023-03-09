/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   hooks.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: rharing <rharing@student.42.fr>              +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/03/03 15:42:11 by rharing       #+#    #+#                 */
/*   Updated: 2023/03/09 15:40:29 by rharing       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

static void	move_forward(t_vars *vars)
{
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
	if (mlx_is_key_down(vars->mlx, MLX_KEY_UP))
		move_forward(vars);
	if (mlx_is_key_down(vars->mlx, MLX_KEY_DOWN))
		move_backwards(vars);
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

void	mouse_look_right(t_vars *vars)
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

void	mouse_look_left(t_vars *vars)
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

void	mousehook(t_vars *vars)
{
	int	cur_x;
	int	cur_y;
	int	mouse_x;

	cur_x = WIDTH / 2;
	mouse_x = cur_x;
	mlx_get_mouse_pos(vars->mlx, &cur_x, &cur_y);
	mlx_set_cursor_mode(vars->mlx, MLX_MOUSE_HIDDEN);
	if (cur_x != mouse_x)
	{
		if (cur_x > mouse_x)
			mouse_look_right(vars);
		else if (cur_x < mouse_x)
			mouse_look_left(vars);
	}
	mlx_set_mouse_pos(vars->mlx, WIDTH / 2, HEIGHT / 2);
	cur_x = WIDTH / 2;
	mouse_x = cur_x;
}

void	hook(void *param)
{
	t_vars	*vars;

	vars = param;
	raycaster(vars);
	keyhook(vars);
	mousehook(vars);
}
