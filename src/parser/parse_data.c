/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parse_data.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: qfrederi <qfrederi@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/01/26 18:19:31 by rharing       #+#    #+#                 */
/*   Updated: 2023/03/31 14:56:10 by qfrederi      ########   odam.nl         */
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
		ft_error("File is empty", clean_project(vars, 1));
	while (temp1)
	{
		if (ft_strncmp(temp1, "\n", 1) != 0)
		{
			vars->map.data[k] = ft_strdup(temp1);
			if (k == 5)
			{
				free(temp1);
				vars->map.data[6] = ft_strdup("\0");
				return ;
			}
			k++;
		}
		free(temp1);
		temp1 = get_next_line(vars->map.fd);
		if (temp1 == NULL)
			ft_error("File is incomplete", clean_project(vars, 1));
	}
	free(temp1);
	vars->map.data[k] = ft_strdup("\0");
}
