/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   cub3D.h                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: rharing <rharing@student.42.fr>              +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/01/11 14:16:12 by rharing       #+#    #+#                 */
/*   Updated: 2023/03/08 13:43:49 by rharing       ########   odam.nl         */
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
# define WIDTH 600
# define HEIGHT 600
# define MOVESPEED 0.05
# define ROTSPEED 0.05


typedef struct s_map
{
	int fd;
	int array_count;
	char pos;
	char **data;
	char **map;
} t_map;

typedef struct s_line
{
	int x_start;
	int x_end;
	int y_start;
	int y_end;
	int diffx;
	int diffy;
	int boundary;
	int current_x;
	int current_y;
	int increase_x;
	int increase_y;
	int count;
} t_line;

typedef struct s_player
{
	int player_x;
	int player_y;
	float playdelta_x;
	float playdelta_y;
	float player_angle;
} t_player;

typedef struct s_walls
{
	mlx_image_t	*north_img;
	mlx_image_t	*east_img;
	mlx_image_t *south_img;
	mlx_image_t *west_img;
	mlx_texture_t *north_t;
	mlx_texture_t *east_t;
	mlx_texture_t *south_t;
	mlx_texture_t *west_t;
} t_walls;

typedef struct s_raycast
{
	float pos_x;
	float pos_y;
	float dir_x;
	float dir_y;
	float plane_x;
	float plane_y;
	float time;
	float old_time;
	float camera_x;
	float ray_dir_x;
	float ray_dir_y;
	int map_x;
	int map_y;
	float side_dist_x;
	float side_dist_y;
	float delta_dist_x;
	float delta_dist_y;
	float reflect_from_wall;
	int step_x;
	int step_y;
	int hit;
	int side;
	int lineheight;
	int drawstart;
	int drawend;
} t_raycast;

typedef struct s_vars
{
	int inst_len;
	int playercount;
	int ceiling_rgb;
	int floor_rgb;
	mlx_t *mlx;
	mlx_image_t *player1;
	mlx_image_t *empty;
	mlx_image_t *wall;
	mlx_image_t *line1;
	mlx_image_t *linepixel;
	mlx_image_t *display;

	t_walls walls;
	t_map map;
	t_player player;
	t_line line;
	t_raycast ray;
} t_vars;

void raycaster(t_vars *vars);
void draw_background(mlx_image_t *display, int height, int start, int color);

/*-------------------------------open_file.c----------------------------*/

void get_colors(t_vars *vars);
bool check_intsize(char **colors);

/**
 * @brief Get the textures object for every cardinal.
 *
 * @param vars
 */
void get_textures(t_vars *vars);
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
void open_file(t_vars *vars, char *map);

/*-------------------------------parse_data.c---------------------------*/

/**
 * @brief get_data(vars) -> read first 6 data lines and writes them to
 * char ** vars->map->data.
 *
 * @param vars
 */
void get_data(t_vars *vars);

/*-------------------------------parse_map.c----------------------------*/

/**
 * @brief read the map part of file and writes it to a
 * string, then splits it to char **vars->map->map
 *
 * @param vars
 */
void get_map(t_vars *vars);

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
bool	check_data(char **mapdata);

/*-------------------------------char_check.c---------------------------*/

/**
 * @brief Loop trough map and check if every character is either a 1, 0
 * ' ' or N,E,S,W. Also checks for only one starting position.
 *
 * @param vars
 * @return true
 * @return false
 */
bool check_char_map(t_vars *vars);

/**
 * @brief Check if every 0 and player starting pos is surrounded by either
 * another 0 or 1.
 *
 * @param vars
 * @return true
 * @return false
 */
bool check_empty(t_vars *vars);

/*---------------------------floor_ceiling_check.c----------------------*/

/**
 * @brief Check if the data of floor and ceiling is correct.
 *
 * @param string
 * @return true
 * @return false
 */
bool check_fcdata(char *string);

/*-------------------------------walls_check.c--------------------------*/

/**
 * @brief Map must be surrounded by walls, checks every string if map begins
 * and ends with a 1(wall).
 * @param vars
 * @return true
 * @return false
 */
bool check_walls(t_vars *vars);

/**
 * @brief Map must be surrounded by walls, checks first and last string of map,
 * if it consist only of 1's(walls) of ' '(space) returns true.
 * @param vars
 * @return true
 * @return false
 */
bool check_first_last(t_vars *vars);

/*-------------------------------display.c--------------------------*/

void	setup_display(t_vars *vars);

/*-------------------------------Raycasting--------------------------*/

/**
 * @brief Function that creates a 3D perspective from a 2D map.
 *
 * @param vars 
 */
void	raycaster(t_vars *vars);

/**
 * @brief Calculate ray position and direction.
 *  Also sets the map x and y values using the position x and y of the player.
 * 			
 * @param vars 
 * @param x 
 * @param w 
 */
void	calc_ray_position_direction(t_vars *vars, int x, int w);

/**
 * @brief Calculate the length of ray from one x or y-side to next x or y-side
 * 
 * @param vars 
 */
void	calc_ray_lenght_to_add(t_vars *vars);

/**
 * @brief Calculate step and the distance from the ray starting 
 * position to the first x or y-side.	
 * 
 * @param vars 
 */
void	calc_initial_ray_length(t_vars *vars);

/**
 * @brief Increment ray with 1 square in either x or y direction, 
 * until wall is hit. 
 * 
 * @param vars 
 */
void	dda_algoritm(t_vars *vars);

/**
 * @brief  
 * Calculate distance projected on camera direction. 
 * This is the shortest distance from the point where the wall is
 * hit to the camera plane. To avoid fisheye effect.
 * 
 * @param vars 
 */
void	calc_line_back_to_plane(t_vars *vars);

/**
 * @brief 
 * Calculate heigt of line to draw on screen
 * by calculating lowest and highest pixel to fill.
 * @param vars 
 * @param h 
 */
void	get_vertical_line_height(t_vars *vars, int h);

void	draw_vertical_line(t_vars *vars, int x, int color);
void	setcolor(int side, int *color);


/*-------------------------------DELETEWHENFINISHED--------------------------*/
void print_mapdata(t_vars *vars);
void print_map(t_vars *vars);

// init_structs
void init_vars(t_vars *vars);
void start_direction(t_vars *vars);

// init_minimap
void draw_map(t_vars *vars);
void create_images_minimap(t_vars *vars);

// setup
void create_points_line(t_vars *vars);

// drawline
void set_line_start_end(t_vars *vars);
void drawline(t_vars *vars);

// move_up
void move_up(t_vars *vars);

// move_down
void move_down(t_vars *vars);

// move_left
void move_left(t_vars *vars);

// move_right
void move_right(t_vars *vars);

void hook(void *param);





#endif