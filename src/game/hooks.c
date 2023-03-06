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

#include "/Users/rolfharing/Documents/Codam/thuiswerkenaanschool/cub3d_github/includes/cub3D.h"

void hook(void *param)
{
	t_vars *vars;

	float movespeed = 0.05;
	float rotspeed = 0.05;
	vars = param;
	raycaster(vars);
	// create_images_minimap(vars);
	if (mlx_is_key_down(vars->mlx, MLX_KEY_ESCAPE))
		mlx_close_window(vars->mlx);
	if (mlx_is_key_down(vars->mlx, MLX_KEY_UP))
	{
		// move_up(vars);
		if (vars->map.map[(int)(vars->ray.pos_x + vars->ray.dir_x * movespeed)][(int)vars->ray.pos_y] == '0')
			vars->ray.pos_x += vars->ray.dir_x * movespeed;
		// printf("dir_x: %f\n", vars->ray.dir_x);
		// printf("pos_x:  %f\n", vars->ray.pos_x);
		if (vars->map.map[(int)vars->ray.pos_x][(int)(vars->ray.pos_y + vars->ray.dir_y * movespeed)] == '0')
			vars->ray.pos_y += vars->ray.dir_y * movespeed;
		// printf("cijver, %c\n", vars->map.map[(int)vars->ray.pos_y][(int)(vars->ray.pos_x + vars->ray.dir_x * movespeed)]);
		// printf("vars->ray.pos_y:  %f\n", vars->ray.pos_y);
	}
	if (mlx_is_key_down(vars->mlx, MLX_KEY_DOWN))
	{
		// move_down(vars);
		if (vars->map.map[(int)(vars->ray.pos_x - vars->ray.dir_x * movespeed)][(int)vars->ray.pos_y] == '0')
			vars->ray.pos_x -= vars->ray.dir_x * movespeed;
		if (vars->map.map[(int)vars->ray.pos_x][(int)(vars->ray.pos_y - vars->ray.dir_y * movespeed)] == '0')
			vars->ray.pos_y -= vars->ray.dir_y * movespeed;
	}
	if (mlx_is_key_down(vars->mlx, MLX_KEY_RIGHT))
	{
		// move_right(vars);
		double old_dir_x;
		double old_plane_x;
		old_plane_x = vars->ray.plane_x;
		old_dir_x = vars->ray.dir_x;
		vars->ray.dir_x = vars->ray.dir_x * cos(-rotspeed) - vars->ray.dir_y * sin(-rotspeed);
		vars->ray.dir_y = old_dir_x * sin(-rotspeed) + vars->ray.dir_y * cos(-rotspeed);
		vars->ray.plane_x = vars->ray.plane_x * cos(-rotspeed) - vars->ray.plane_y * sin(-rotspeed);
		vars->ray.plane_y = old_plane_x * sin(-rotspeed) + vars->ray.plane_y * cos(-rotspeed);
	}
	if (mlx_is_key_down(vars->mlx, MLX_KEY_LEFT))
	{
		// move_left(vars);
		double old_dir_x;
		double old_plane_x;
		old_plane_x = vars->ray.plane_x;
		old_dir_x = vars->ray.dir_x;
		vars->ray.dir_x = vars->ray.dir_x * cos(rotspeed) - vars->ray.dir_y * sin(rotspeed);
		vars->ray.dir_y = old_dir_x * sin(rotspeed) + vars->ray.dir_y * cos(rotspeed);
		vars->ray.plane_x = vars->ray.plane_x * cos(rotspeed) - vars->ray.plane_y * sin(rotspeed);
		vars->ray.plane_y = old_plane_x * sin(rotspeed) + vars->ray.plane_y * cos(rotspeed);
	}
}
