/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parse_data.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: rharing <rharing@student.42.fr>              +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/01/26 18:19:31 by rharing       #+#    #+#                 */
/*   Updated: 2023/01/26 18:21:10 by rharing       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	get_data(t_vars *vars)
{
	char	*temp1;
	int		k;

	k = 0;
	while (1)
	{
		temp1 = get_next_line(vars->map.fd);
		if (ft_strncmp(temp1, "\n", 1) != 0)
		{
			vars->map.data[k] = ft_strdup(temp1);
			if (k == 5)
			{
				free(temp1);
				vars->map.data[6] = "\0";
				return ;
			}
			k++;
		}
		free(temp1);
	}
}
