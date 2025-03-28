/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sal-kawa <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/05 15:21:07 by sal-kawa          #+#    #+#             */
/*   Updated: 2024/09/05 15:21:10 by sal-kawa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*p;
	size_t	i;
	size_t	j;
	size_t	s_len;

	if (s == NULL)
		return (NULL);
	s_len = ft_strlen(s);
	if (start >= s_len)
		return (ft_strdup(""));
	if (len > s_len - start)
		len = s_len - start;
	p = malloc(len + 1);
	if (p == NULL)
		return (NULL);
	i = start;
	j = 0;
	while (j < len && s[i])
		p[j++] = s[i++];
	p[j] = '\0';
	return (p);
}
/*int main()
{
	char string[] = "Ismail Khalil";
	char *result = ft_substr(string, 7, 10);
	printf("%s",result);
	return (0);
}*/
