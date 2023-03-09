/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   mouse_hook.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: rharing <rharing@student.42.fr>              +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/03/09 15:42:13 by rharing       #+#    #+#                 */
/*   Updated: 2023/03/09 15:47:14 by rharing       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

static void	mouse_look_right(t_vars *vars)
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

static void	mouse_look_left(t_vars *vars)
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
