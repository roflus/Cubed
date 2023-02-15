/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_freesplit.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: rharing <rharing@student.42.fr>              +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/02/15 18:39:58 by rharing       #+#    #+#                 */
/*   Updated: 2023/02/15 18:43:51 by rharing       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	freesplit(char **split)
{
	int	i;

	i = 0;
	while (split[i] != NULL)
	{
		free(split[i]);
		i++;
	}
	free(split);
}
