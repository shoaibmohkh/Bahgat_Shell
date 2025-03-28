/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sal-kawa <sal-kawa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/16 19:27:31 by sal-kawa          #+#    #+#             */
/*   Updated: 2024/12/24 14:57:19 by sal-kawa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

size_t	ft_strlenn(const char *s)
{
	size_t	i;

	i = 0;
	while (s[i] != 0)
		i++;
	return (i);
}

char	*ft_strdupp(char *s)
{
	char			*dest;
	unsigned int	i;

	dest = (char *)malloc(ft_strlenn(s) + 1);
	if (!dest)
		return (NULL);
	i = 0;
	while (s[i])
	{
		dest[i] = s[i];
		i++;
	}
	dest[i] = 0;
	return (dest);
}

char	*ft_substrr(char const *s, unsigned int start, size_t len)
{
	char	*p;
	size_t	i;
	size_t	j;
	size_t	s_len;

	if (s == NULL)
		return (NULL);
	s_len = ft_strlenn(s);
	if (start >= s_len)
		return (ft_strdupp(""));
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

char	*ft_strjoinn(char *s, char *a)
{
	char	*res;

	res = (char *)malloc((ft_strlenn(s) + ft_strlenn(a) + 1) * sizeof(char));
	if (!res)
		return (NULL);
	fill_str(res, s, a);
	return (res);
}

void	fill_str(char *res, char *s, char *a)
{
	unsigned int	i;
	unsigned int	j;

	i = 0;
	j = 0;
	while (s[j])
		res[i++] = s[j++];
	j = 0;
	while (a[j])
		res[i++] = a[j++];
	res[i] = '\0';
}
