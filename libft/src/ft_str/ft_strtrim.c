/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sal-kawa <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/05 15:26:25 by sal-kawa          #+#    #+#             */
/*   Updated: 2024/09/05 15:26:28 by sal-kawa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	is_in_set(char c, const char *set)
{
	while (*set)
	{
		if (c == *set)
			return (1);
		set++;
	}
	return (0);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	size_t	len;
	char	*trimmed_str;

	if (s1 == NULL || set == NULL)
		return (NULL);
	while (*s1 && is_in_set(*s1, set))
		s1++;
	len = ft_strlen(s1);
	while (len > 0 && is_in_set(s1[len - 1], set))
		len--;
	trimmed_str = malloc(len + 1);
	if (trimmed_str == NULL)
		return (NULL);
	ft_strlcpy(trimmed_str, s1, len + 1);
	return (trimmed_str);
}
