/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sal-kawa <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/05 15:17:46 by sal-kawa          #+#    #+#             */
/*   Updated: 2024/09/05 15:17:49 by sal-kawa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *s, int c)
{
	while (*s != '\0')
	{
		if (*s == (char)c)
			return ((char *)s);
		s++;
	}
	if (*s == (char)c)
		return ((char *)s);
	return (NULL);
}
/*int main () 
{
   const char str[] = "Ismail";
   const char ch = 'i';
   char *ret;
   ret = ft_strchr(str, ch);
   printf("String after |%c| is - |%s|\n", ch, ret);
   return(0);
}*/
