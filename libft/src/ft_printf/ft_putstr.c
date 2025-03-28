/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putstr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sal-kawa <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/10 14:13:41 by sal-kawa          #+#    #+#             */
/*   Updated: 2024/09/10 14:23:53 by sal-kawa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_putstr(char *maguire)
{
	int	x;

	x = 0;
	if (maguire == NULL)
		return (write(1, "(null)", 6));
	while (maguire[x] != 0)
	{
		write(1, &maguire[x], 1);
		x++;
	}
	return (x);
}
