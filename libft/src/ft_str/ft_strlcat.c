/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sal-kawa <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/05 15:19:09 by sal-kawa          #+#    #+#             */
/*   Updated: 2024/09/05 15:19:19 by sal-kawa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t	dest_len;
	size_t	src_len;
	size_t	space_remaining;
	size_t	i;

	dest_len = ft_strlen(dst);
	src_len = ft_strlen(src);
	if (size <= dest_len)
		return (size + src_len);
	space_remaining = size - dest_len - 1;
	i = 0;
	while (i < space_remaining && src[i])
	{
		dst[dest_len + i] = src[i];
		i++;
	}
	dst[dest_len + i] = 0;
	return (dest_len + src_len);
}
/*int main() {
    char dst[20] = "Hello, ";
    const char *src = "World!";
    size_t total_size = sizeof(dst);
    size_t result;
    result = strlcat(dst, src, total_size);
    printf("Final string: %s\n", dst);  
    printf("Total length: %zu\n", result);      
    return (0);
}*/
