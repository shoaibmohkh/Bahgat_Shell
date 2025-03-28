/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sal-kawa <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/05 15:15:03 by sal-kawa          #+#    #+#             */
/*   Updated: 2024/09/05 15:15:07 by sal-kawa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void *s, int c, size_t n)
{
	unsigned char	*p;
	unsigned char	value;

	p = s;
	value = (unsigned char)c;
	while (n--)
	{
		*p++ = value;
	}
	return (s);
}
/*int main ()
{
	char buffer[18];
	int i = 0;
	memset(buffer,'I',sizeof(char)*3);
	memset(buffer + 3,'S',sizeof(char)*3);
	memset(buffer + 6,'M',sizeof(char)*3);
	memset(buffer + 9,'A',sizeof(char)*3);
	memset(buffer + 12,'I',sizeof(char)*3);
	memset(buffer + 15,'L',sizeof(char)*3);

	while (i < 18)
	{
		printf("%c ",buffer[i++]);
	}
	return (0);
}*/
