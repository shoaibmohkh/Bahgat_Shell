/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sal-kawa <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/09 17:28:58 by sal-kawa          #+#    #+#             */
/*   Updated: 2024/09/09 18:52:11 by sal-kawa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_messi(char t, va_list aguero)
{
	int	x;

	x = 0;
	if (t == 'c')
		x += ft_putchar(va_arg(aguero, int));
	else if (t == 'd' || t == 'i')
		x += ft_putnbr(va_arg(aguero, int));
	else if (t == 's')
		x += ft_putstr(va_arg(aguero, char *));
	else if (t == 'u')
		x += ft_unsigned(va_arg(aguero, unsigned int));
	else if (t == 'x')
		x += ft_hexa_sm(va_arg(aguero, unsigned int));
	else if (t == 'X')
		x += ft_hexatwo(va_arg(aguero, unsigned int));
	else if (t == 'p')
		x += ft_pointer(va_arg(aguero, void *));
	else if (t == '%')
		x += ft_putchar('%');
	return (x);
}

int	ft_printf(const char *str, ...)
{
	va_list	args;
	int		i;
	int		count;

	va_start(args, str);
	count = 0;
	i = 0;
	while (str[i] != 0)
	{
		if (str[i] == '%')
		{
			i++;
			count += ft_messi(str[i], args);
		}
		else
		{
			write (1, &str[i], 1);
			count++;
		}
		i++;
	}
	va_end(args);
	return (count);
}
