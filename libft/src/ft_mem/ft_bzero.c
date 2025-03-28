/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bzero.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sal-kawa <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/05 14:59:57 by sal-kawa          #+#    #+#             */
/*   Updated: 2024/09/05 15:00:01 by sal-kawa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_bzero(void *s, size_t n)
{
	ft_memset(s, 0, n);
}
/*int main ()
{
	char buffer[5];
	int i = 0;
	bzero(buffer,5);


	while (i < 5)
	{
		printf("%d ",buffer[i++]);
	}
	return (0);
}*/
