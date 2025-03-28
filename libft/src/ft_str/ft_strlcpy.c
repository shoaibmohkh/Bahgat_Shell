/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sal-kawa <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/05 15:24:38 by sal-kawa          #+#    #+#             */
/*   Updated: 2024/09/05 15:24:41 by sal-kawa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcpy(char *dst, const char *src, size_t size)
{
	const char	*s;
	size_t		length;

	s = src;
	length = 0;
	while (*s++)
		length++;
	if (size == 0)
		return (length);
	while (*src != 0 && --size)
		*dst++ = *src++;
	*dst = 0;
	return (length);
}
/*int main() {
    char dst[6];
    const char *src = "Hello, World!";
    size_t result;

    result = ft_strlcpy(dst, src, sizeof(dst));

    printf("Destination: %s\n", dst);
    printf("Source Length: %zu\n", result);

    return (0);
}*/
