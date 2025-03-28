/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstlast.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sal-kawa <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/05 15:10:31 by sal-kawa          #+#    #+#             */
/*   Updated: 2024/09/05 15:10:34 by sal-kawa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstlast(t_list *lst)
{
	t_list	*t;

	if (lst == NULL)
		return (NULL);
	t = lst;
	while (t->next != NULL)
	{
		t = t->next;
	}
	return (t);
}
