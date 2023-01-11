/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   get_next_line.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: rharing <rharing@student.42.fr>              +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/01/20 13:30:17 by rharing       #+#    #+#                 */
/*   Updated: 2022/02/16 14:14:38 by rharing       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

#define BUFFER_SIZE 1000000

static char	*copy_input(char *string)
{
	int		i;
	int		length;
	char	*result;

	i = 0;
	length = ft_strchr(string, '\n') - string;
	result = malloc(sizeof(char) * (length + 2));
	if (!result)
		return (0);
	while (i < length)
	{
		result[i] = string[i];
		i++;
	}
	result[i] = '\n';
	result[i + 1] = '\0';
	return (result);
}

static char	*dup_remainder(char *string)
{
	char	*temp;

	temp = ft_strchr(string, '\n') + 1;
	if (*temp)
	{
		temp = ft_strdup(temp);
		if (!temp)
			return (0);
		free (string);
		return (temp);
	}
	free(string);
	return (0);
}

static char	*find_nextline(int fd, char **string, int ret)
{
	char	*temp;

	if (ft_strchr(*string, '\n'))
	{
		temp = copy_input(*string);
		if (!temp)
			return (0);
		*string = dup_remainder(*string);
		return (temp);
	}
	else if (ret != 0)
		return (get_next_line(fd));
	temp = *string;
	*string = 0;
	return (temp);
}

static char	*fill_string(int fd, char **string, int ret, char *buf)
{
	char	*temp;

	if (*string == NULL && ret == 0)
		return (0);
	if (*string == NULL && ret)
	{
		*string = ft_strdup(buf);
		if (!*string)
			return (0);
	}
	else
	{
		temp = ft_strjoin(*string, buf);
		if (!temp)
			return (0);
		free(*string);
		*string = temp;
	}
	return (find_nextline(fd, &*string, ret));
}

char	*get_next_line(int fd)
{
	static char		*string;
	char			buf[BUFFER_SIZE + 1];
	int				ret;

	ret = read(fd, buf, BUFFER_SIZE);
	if (ret < 0 || fd < 0)
		return (0);
	buf[ret] = '\0';
	return (fill_string(fd, &string, ret, buf));
}
