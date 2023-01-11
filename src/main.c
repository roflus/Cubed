/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: rharing <rharing@student.42.fr>              +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/01/11 13:05:43 by rharing       #+#    #+#                 */
/*   Updated: 2023/01/11 16:52:35 by rharing       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <memory.h>
#define WIDTH 256
#define HEIGHT 256

mlx_image_t	*g_img;

void	hook(void *param)
{
	mlx_t	*mlx;

	mlx = param;
	if (mlx_is_key_down(mlx, MLX_KEY_ESCAPE))
		mlx_close_window(mlx);
	if (mlx_is_key_down(mlx, MLX_KEY_UP))
		g_img->instances[0].y -= 5;
	if (mlx_is_key_down(mlx, MLX_KEY_DOWN))
		g_img->instances[0].y += 5;
	if (mlx_is_key_down(mlx, MLX_KEY_LEFT))
		g_img->instances[0].x -= 5;
	if (mlx_is_key_down(mlx, MLX_KEY_RIGHT))
		g_img->instances[0].x += 5;
}

bool	check_empty_line_map(char *mapline)
{
	int	i;
	int	length;

	i = 0;
	length = ft_strlen(mapline);
	while (mapline[i] != '\0')
	{
		if (mapline[length - 1] == '\n')
			return (false);
		if (mapline[0] == '\n')
			return (false);
		if (mapline[i] == '\n')
		{
			if (mapline[i + 1] == '\n')
				return (false);
		}
		i++;
	}
	return (true);
}

void	create_map(t_vars *vars, char *mapline)
{
	if (check_empty_line_map(mapline) == false)
		ft_error("No newline in map", 2);
	vars->map->map = ft_split(mapline, '\n');
	if (vars->map->map == NULL)
		ft_error("Malloc map failed", 2);
}

void	mapinput(t_vars *vars)
{
	char	*temp;
	char	*mapline;
	char	*newmapline;

	mapline = ft_calloc(1, 1);
	if (mapline == NULL)
		ft_error("Malloc failed", 2);
	while (mapline)
	{
		temp = get_next_line(vars->map->fd);
		if (!temp)
			break ;
		newmapline = mapline;
		mapline = ft_strjoin(newmapline, temp);
		free(newmapline);
		free(temp);
	}
	create_map(vars, mapline);
	free(mapline);
}

void get_data(t_vars *vars)
{
	char *temp1;
	int i;
	int k;

	i = 0;
	k = 0;
	vars->map->data = ft_calloc(6, sizeof(char *));
	if (vars->map->data == NULL)
		ft_error("Malloc error", 2);
	while (i < 8)
	{
		temp1 = get_next_line(vars->map->fd);
		if (ft_strncmp(temp1, "\n", 1) != 0)
		{
			vars->map->data[k] = ft_strdup(temp1);
			k++;
		}
		free(temp1);
		i++;
	}
}

void open_map(t_vars *vars, char *map)
{
	vars->map->fd = open(map, O_RDONLY);
	if (vars->map->fd < 0)
		ft_error("Can't open map oh .. file", 2);
	get_data(vars);
	mapinput(vars);
	printf("\n%s\n%s\n", vars->map->map[2], vars->map->map[6]);
}

bool arg_check(char **argv)
{
	if (ft_strlen(argv[1]) <= 4)
		return (false);
	if (argv[1][ft_strlen(argv[1]) - 1] == 'b' && argv[1][ft_strlen(argv[1]) - 2] == 'u' \
		&& argv[1][ft_strlen(argv[1]) - 3] == 'c' && argv[1][ft_strlen(argv[1]) - 4] == '.')
		return (true);
	return (false);
}

int	main(int argc, char **argv)
{
	mlx_t	*mlx;
	t_vars	*vars;

	if (argc != 2)
		ft_error("Wrong amount of arguments", 2);
	if (arg_check(argv)	== false)
		ft_error("File is not .cub", 2);
	vars = ft_calloc(1, sizeof(vars));
	vars->map = ft_calloc(1, sizeof(vars->map));
	open_map(vars, argv[1]);
	mlx = mlx_init(WIDTH, HEIGHT, "cub3D", true);
	if (!mlx)
		exit(EXIT_FAILURE);
	g_img = mlx_new_image(mlx, 128, 128);
	memset(g_img->pixels, 255, g_img->width * g_img->height * sizeof(int));
	mlx_image_to_window(mlx, g_img, 0, 0);
	mlx_loop_hook(mlx, &hook, mlx);
	mlx_loop(mlx);
	mlx_terminate(mlx);
	return (EXIT_SUCCESS);
}
