/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_error.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: rharing <rharing@student.42.fr>              +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/01/11 14:26:04 by rharing       #+#    #+#                 */
/*   Updated: 2023/03/03 14:15:08 by rharing       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_error(char *string, int exit_code)
{
	ft_putendl_fd("Error", 2);
	ft_putendl_fd(string, 2);
	exit(exit_code);
}
