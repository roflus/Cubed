/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_freesplit.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: qfrederi <qfrederi@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/02/15 18:39:58 by rharing       #+#    #+#                 */
/*   Updated: 2023/03/30 10:15:46 by qfrederi      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	freesplit(char **split)
{
	int	i;

	i = 0;
	if (!split)
		return ;
	while (split[i] != NULL)
	{
		free(split[i]);
		i++;
	}
	free(split);
}
