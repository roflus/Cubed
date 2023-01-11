/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   cub3D.h                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: rharing <rharing@student.42.fr>              +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/01/11 14:16:12 by rharing       #+#    #+#                 */
/*   Updated: 2023/01/11 16:47:04 by rharing       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

#include <libft.h>
#include <MLX42/MLX42.h>
#include <fcntl.h>
#include "get_next_line.h"

typedef struct s_map
{
    int     fd;
    char    **data;
    char    **map;
}   t_map;


typedef struct s_vars
{
    
    int     test;
    t_map   *map;
}      t_vars;


#endif