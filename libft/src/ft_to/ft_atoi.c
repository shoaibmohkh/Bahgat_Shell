/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/05 14:59:18 by sal-kawa          #+#    #+#             */
/*   Updated: 2025/03/12 07:08:35 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <limits.h>

int	ft_handle_spaces_sign(const char *nptr, int *sign)
{
	int	i;

	i = 0;
	*sign = 1;
	while (ft_isspace(nptr[i]))
		i++;
	if (nptr[i] == '+' || nptr[i] == '-')
	{
		if (nptr[i] == '-')
			*sign = -1;
		i++;
	}
	return (i);
}

long long	ft_atoi(const char *nptr)
{
	int			i;
	int			sign;
	long long	result;

	result = 0;
	i = ft_handle_spaces_sign(nptr, &sign);
	while (nptr[i] >= '0' && nptr[i] <= '9')
	{
		if (result > (LLONG_MAX - (nptr[i] - '0')) / 10)
		{
			if (sign == 1)
				return (LLONG_MAX);
			else
				return (LLONG_MIN);
		}
		result = result * 10 + (nptr[i] - '0');
		i++;
	}
	return (result * sign);
}
