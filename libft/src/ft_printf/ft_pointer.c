/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pointer.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sal-kawa <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/10 19:29:03 by sal-kawa          #+#    #+#             */
/*   Updated: 2024/09/10 19:41:16 by sal-kawa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	ft_hexa_s(unsigned long h)
{
	int		i;
	char	*num;

	num = "0123456789abcdef";
	i = 0;
	if (h >= 16)
		i += ft_hexa_s(h / 16);
	ft_putchar(num[h % 16]);
	return (i + 1);
}

int	ft_pointer(void *x)
{
	int	i;

	if (x == NULL)
		return (write(1, "(nil)", 5));
	ft_putchar('0');
	ft_putchar('x');
	i = ft_hexa_s((unsigned long)x);
	return (i + 2);
}
