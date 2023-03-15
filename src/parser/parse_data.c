/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parse_data.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: rharing <rharing@student.42.fr>              +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/01/26 18:19:31 by rharing       #+#    #+#                 */
/*   Updated: 2023/03/15 12:28:54 by rharing       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	get_data(t_vars *vars)
{
	char	*temp1;
	int		k;

	k = 0;
	temp1 = get_next_line(vars->map.fd);
	if (temp1 == NULL)
		ft_error("File is empty", 1);
	while (temp1)
	{
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
		temp1 = get_next_line(vars->map.fd);
	}
	free(temp1);
	vars->map.data[k] = "\0";
}
