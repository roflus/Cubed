/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   get_colors.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: rharing <rharing@student.42.fr>              +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/02/15 12:02:58 by rharing       #+#    #+#                 */
/*   Updated: 2023/02/15 16:30:47 by rharing       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"
    /*
        kijken vanaf 2 tot eerst komma, substring in floor;
        ft_atoi dat in int array[0]
        en zo alle 3
        zelfde voor C
    */ 

char    *get_ceiling(t_vars *vars)
{
    int i;
    char *string;

    i = 0;
    while (vars->map.data[i] != '\0')
    {
        if (vars->map.data[i][0] == 'C' && vars->map.data[i][1] == ' ')
        {
            string = ft_substr(vars->map.data[i], 2, ft_strlen(vars->map.data[i]));
            return (string);
        }
        i++;
    }
}

char    *get_floor(t_vars *vars)
{
    int i;
    char *string;

    i = 0;
    while (vars->map.data[i] != '\0')
    {
        if (vars->map.data[i][0] == 'F' && vars->map.data[i][1] == ' ')
        {
            string = ft_substr(vars->map.data[i], 2, ft_strlen(vars->map.data[i]));
            return (string);
        }
        i++;
    }
}

void    get_colors(t_vars *vars)
{
    char *ceiling;
    char *floor;

    ceiling = get_ceiling(vars);
    floor = get_floor(vars);
    printf("hoi");

}