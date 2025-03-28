/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sal-kawa <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/05 15:00:21 by sal-kawa          #+#    #+#             */
/*   Updated: 2024/09/05 15:00:26 by sal-kawa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t nmemb, size_t size)
{
	unsigned char	*ptr;
	size_t			total;
	size_t			i;

	total = nmemb * size;
	ptr = malloc(total);
	i = 0;
	if (ptr == NULL)
		return (NULL);
	while (i < total)
		ptr[i++] = 0;
	return (ptr);
}
/*int main() {
    size_t num_elements = 5;
    
    int *array = (int*) calloc(num_elements, sizeof(int));
    
    if (array == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        return (1);
    }
    for (size_t i = 0; i < num_elements; i++) {
        printf("array[%zu] = %d\n", i, array[i]);
    }
    
    free(array);
    return (0);
}*/
