/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   cub3D.h                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: qfrederi <qfrederi@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/01/11 14:16:12 by rharing       #+#    #+#                 */
/*   Updated: 2023/02/20 13:04:12 by qfrederi      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include <libft.h>
# include <MLX42/MLX42.h>
# include <fcntl.h>
# include "get_next_line.h"
# include <stdlib.h>
# include <stdio.h>
# include <unistd.h>
# include <memory.h>
# include <math.h>
# define MAPPIXEL 64

typedef struct s_map
{
	int		fd;
	int		array_count;
	char	pos;
	char	**data;
	char	**map;
}	t_map;

typedef struct s_player
{
	int		player_x;
	int		player_y;
	float	playdelta_x;
	float	playdelta_y;
	float	player_angle;
}	t_player;

typedef struct s_walls
{
	mlx_image_t		*north_img;
	mlx_image_t		*east_img;
	mlx_image_t		*south_img;
	mlx_image_t		*west_img;
	mlx_texture_t	*north_t;
	mlx_texture_t	*east_t;
	mlx_texture_t	*south_t;
	mlx_texture_t	*west_t;
}	t_walls;

typedef struct s_vars
{
	int			inst_len;
	int			playercount;
	int			*ceiling_rgb;
	int			*floor_rgb;
	mlx_t		*mlx;
	mlx_image_t	*player1;
	mlx_image_t	*empty;
	mlx_image_t	*wall;
	mlx_image_t	*line1;
	mlx_image_t	*linepixel;

	t_walls		walls;
	t_map		map;
	t_player	player;
}	t_vars;

/*-------------------------------open_file.c----------------------------*/

void	get_colors(t_vars *vars);
bool	check_floor_intsize(t_vars *vars);
bool	check_ceiling_intsize(t_vars *vars);

/**
 * @brief Get the textures object for every cardinal.
 * 
 * @param vars 
 */
void	get_textures(t_vars *vars);
/*-------------------------------open_file.c----------------------------*/

/**
 * @brief Opens map.cub file to read.
 * get_data(vars) -> read first 6 data lines and writes them to
 * char ** vars->map->data.
 * get_map(vars) -> read the map part of file and writes it to a 
 * string, then splits it to char **vars->map->map
 * @param vars
 * @param map
 */
void	open_file(t_vars *vars, char *map);

/*-------------------------------parse_data.c---------------------------*/

/**
 * @brief get_data(vars) -> read first 6 data lines and writes them to
 * char ** vars->map->data.
 * 
 * @param vars 
 */
void	get_data(t_vars *vars);

/*-------------------------------parse_map.c----------------------------*/

/**
 * @brief read the map part of file and writes it to a 
 * string, then splits it to char **vars->map->map
 * 
 * @param vars 
 */
void	get_map(t_vars *vars);

/*-------------------------------map_check.c----------------------------*/

/**
 * @brief The map cannot have any newline's inbetween.
 * Checks the string for to many newline's, returns false if it found
 * extra newline. Returns true if no extra newline's have been found.
 * 
 * @param mapline 
 * @return true 
 * @return false 
 */
bool	check_empty_line_map(char *mapline);

/**
 * @brief Check if the map is valid without errors
 * Start with checking the first and last line
 * Check if their are not any invalid characters in the map
 * Check if there is 1 player
 * Check is the map is closed with walls
 * @param vars 
 */
void	check_map(t_vars *vars);

/*-------------------------------cardinal_check.c-----------------------*/

/**
 * @brief Check Cardinal Data in map
 * Loop through first 4 lines of vars->map->data
 * To check for NO, SO  WE and EA
 * And check for F(floor) and C(ceiling).
 * @param vars 
 * @return true 
 * @return false 
 */
bool	check_data(t_vars *vars);

/*-------------------------------char_check.c---------------------------*/

/**
 * @brief Loop trough map and check if every character is either a 1, 0
 * ' ' or N,E,S,W. Also checks for only one starting position.
 * 
 * @param vars 
 * @return true 
 * @return false 
 */
bool	check_char_map(t_vars *vars);

/**
 * @brief Check if every 0 and player starting pos is surrounded by either
 * another 0 or 1.
 * 
 * @param vars
 * @return true 
 * @return false 
 */
bool	check_empty(t_vars *vars);

/*---------------------------floor_ceiling_check.c----------------------*/

/**
 * @brief Check if Floor data is parsed correctly.
 * 
 * @param vars 
 * @return true 
 * @return false 
 */
bool	check_floor(t_vars *vars);

/**
 * @brief Check if Ceiling data is parsed correctly.
 * 
 * @param vars 
 * @return true 
 * @return false 
 */
bool	check_ceiling(t_vars *vars);

/*-------------------------------walls_check.c--------------------------*/

/**
 * @brief Map must be surrounded by walls, checks every string if map begins
 * and ends with a 1(wall).
 * @param vars 
 * @return true 
 * @return false 
 */
bool	check_walls(t_vars *vars);

/**
 * @brief Map must be surrounded by walls, checks first and last string of map,
 * if it consist only of 1's(walls) of ' '(space) returns true.
 * @param vars 
 * @return true 
 * @return false 
 */
bool	check_first_last(t_vars *vars);



/*-------------------------------DELETEWHENFINISHED--------------------------*/
void	print_mapdata(t_vars *vars);
void	print_map(t_vars *vars);

void drawline(int x_start, int y_start, int x_end, int y_end, t_vars *vars);
void draw_map(t_vars *vars);
void create_images_minimap(t_vars *vars);

#endif