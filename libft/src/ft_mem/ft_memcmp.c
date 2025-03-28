/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sal-kawa <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/05 15:12:27 by sal-kawa          #+#    #+#             */
/*   Updated: 2024/09/05 15:12:31 by sal-kawa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	const unsigned char	*p1;
	const unsigned char	*p2;

	p1 = s1;
	p2 = s2;
	while (n--)
	{
		if (*p1 != *p2)
			return (*p1 - *p2);
		p1++;
		p2++;
	}
	return (0);
}
/*int main() {
    char buffer1[] = "Hello, world!";
    char buffer2[] = "Hello, wrld!";

    int result = ft_memcmp(buffer1, buffer2, sizeof(buffer1));

    if (result == 0) {
        printf("The memory blocks are equal.\n");
    } else if (result > 0) {
        printf("The first memory block is greater than the second.\n");
    } else {
        printf("The first memory block is less than the second.\n");
    }

    return (0);
}*/
