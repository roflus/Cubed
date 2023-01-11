/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   get_next_line_utils.c                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: rharing <rharing@student.42.fr>              +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/01/20 13:43:46 by rharing       #+#    #+#                 */
/*   Updated: 2022/01/20 13:43:50 by rharing       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

size_t	ft_strlen(const char *s)
{
	size_t	i;

	i = 0;
	while (s[i] != '\0')
		i++;
	return (i);
}

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	unsigned char		*p;
	unsigned char		*k;
	size_t				i;

	i = 0;
	p = (unsigned char *)dst;
	k = (unsigned char *)src;
	if (!dst && !src)
		return (0);
	while (i < n)
	{
		p[i] = k[i];
		i++;
	}
	return (dst);
}

char	*ft_strdup(const char *s1)
{
	char	*p;
	size_t	len;

	len = ft_strlen((char *)s1) + 1;
	p = malloc(len);
	if (!p)
		return (NULL);
	ft_memcpy(p, s1, len);
	return (p);
}

char	*ft_strjoin(char *s1, char *s2)
{
	char		*comb;
	int			i;
	int			k;

	i = 0;
	k = 0;
	comb = (char *) malloc(sizeof(char) * ft_strlen((char *) s1) \
			+ ft_strlen((char *) s2) + 1);
	if (!comb)
		return (0);
	while (s1[i] != '\0')
	{
		comb[i] = s1[i];
		i++;
	}
	while (s2[k] != '\0')
	{
		comb[i] = s2[k];
		k++;
		i++;
	}
	comb[i] = '\0';
	return (comb);
}

char	*ft_strchr(const char *s, int c)
{
	int	i;

	i = 0;
	while (i >= 0)
	{
		if (s[i] == (unsigned char) c)
			return (&((char *)s)[i]);
		if (s[i] == '\0')
			return (0);
		i++;
	}	
	return (0);
}
