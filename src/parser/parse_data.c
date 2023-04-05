/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parse_data.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: qfrederi <qfrederi@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/01/26 18:19:31 by rharing       #+#    #+#                 */
/*   Updated: 2023/04/05 11:03:57 by qfrederi      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

static void	get_data_end(t_vars *vars, char *temp, int pos, bool must_free)
{
	if (must_free == true)
	{
		free(temp);
		vars->map.data[pos] = ft_strdup("\0");
	}
	else
		vars->map.data[pos] = ft_strdup(temp);
	if (!vars->map.data[pos])
		ft_error("Malloc Failed", clean_project(vars, 1));
}

void	get_data(t_vars *vars)
{
	char	*temp;
	int		k;

	k = 0;
	temp = get_next_line(vars->map.fd);
	if (temp == NULL)
		ft_error("File is empty", clean_project(vars, 1));
	while (temp)
	{
		if (ft_strncmp(temp, "\n", 1) != 0)
		{
			get_data_end(vars, temp, k, false);
			if (k == 5)
			{
				get_data_end(vars, temp, 6, true);
				return ;
			}
			k++;
		}
		free(temp);
		temp = get_next_line(vars->map.fd);
		if (temp == NULL)
			ft_error("File is incomplete", clean_project(vars, 1));
	}
	get_data_end(vars, temp, k, true);
}
