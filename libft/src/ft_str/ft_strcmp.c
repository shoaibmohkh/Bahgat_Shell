/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shoaib <shoaib@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/05 15:17:46 by sal-kawa          #+#    #+#             */
/*   Updated: 2025/02/24 19:45:35 by shoaib           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strcmp(const char *s1, const char *s2)
{
	const unsigned char	*s_1;
	const unsigned char	*s_2;
	size_t				i;

	i = 0;
	s_1 = (const unsigned char *)s1;
	s_2 = (const unsigned char *)s2;
	while (s_1[i] == s_2[i] && s_1[i])
		i++;
	return (s_1[i] - s_2[i]);
}
