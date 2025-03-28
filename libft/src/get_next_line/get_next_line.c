/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sal-kawa <sal-kawa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/15 13:49:45 by sal-kawa          #+#    #+#             */
/*   Updated: 2024/12/24 14:55:15 by sal-kawa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char	*ft_free(char *buff, char **save)
{
	if (*save)
	{
		free(*save);
		*save = NULL;
	}
	if (buff)
		free(buff);
	return (NULL);
}

char	*ft_strchrr(const char *s, int c)
{
	while (*s != '\0')
	{
		if (*s == (char)c)
			return ((char *)s);
		s++;
	}
	if (*s == (char)c)
		return ((char *)s);
	return (NULL);
}

char	*readone(int fd, char *buff, char *save)
{
	ssize_t	bytes;
	char	*swap;

	if (!save)
		save = ft_strdupp("");
	while (!ft_strchrr(save, '\n'))
	{
		bytes = read(fd, buff, BUFFER_SIZE);
		if (bytes == -1)
		{
			return (ft_free(buff, &save));
		}
		else if (bytes == 0)
			break ;
		buff[bytes] = '\0';
		swap = save;
		save = ft_strjoinn(swap, buff);
		free(swap);
		if (!save)
			return (ft_free(buff, &save));
	}
	if (buff)
		free(buff);
	return (save);
}

char	*cutof(char **save)
{
	char	*line;
	char	*temp;
	size_t	i;

	i = 0;
	line = NULL;
	while ((*save)[i] != '\0' && (*save)[i] != '\n')
		i++;
	if ((*save)[i])
		i++;
	if (i > 0)
		line = ft_substrr(*save, 0, i);
	temp = ft_strdupp(*save + i);
	free(*save);
	*save = temp;
	return (line);
}

char	*get_next_line(int fd)
{
	char		*buff;
	static char	*save = NULL;
	char		*line;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	buff = malloc(BUFFER_SIZE + 1);
	if (buff == NULL)
		return (NULL);
	save = readone(fd, buff, save);
	if (!save)
		return (NULL);
	line = cutof(&save);
	if (!line && save)
	{
		free(save);
		save = NULL;
	}
	return (line);
}
// int main ()
// {
// 	int x = 0;
// 	x = open("t", O_RDONLY);
// 	int i = 0;
// 	char *str;
// 	while ((str = get_next_line(x)))
// 	{

// 		printf("%s", str);
// 		free(str);
// 		i++;
// 	}
// 	return (0);
// }
