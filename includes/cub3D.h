/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   cub3D.h                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: rharing <rharing@student.42.fr>              +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/01/11 14:16:12 by rharing       #+#    #+#                 */
/*   Updated: 2023/01/12 13:35:06 by rharing       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include <libft.h>
# include <MLX42/MLX42.h>
# include <fcntl.h>
# include "get_next_line.h"

typedef struct s_map
{
	int		fd;
	char	**data;
	char	**map;
}	t_map;

typedef struct s_vars
{
	int		test;
	t_map	*map;
}	t_vars;

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

/*-------------------------------read_map.c-----------------------------*/

/**
 * @brief Opens map.cub file to read.
 * get_data(vars) -> read first 6 data lines and writes them to
 * char ** vars->map->data.
 * mapinput(vars) -> read the map part of file and writes it to a 
 * string, then splits it to char **vars->map->map
 * @param vars
 * @param map
 */
void	open_map(t_vars *vars, char *map);

#endif