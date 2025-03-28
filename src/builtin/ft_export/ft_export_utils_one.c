/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export_utils_one.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/12 06:45:16 by marvin            #+#    #+#             */
/*   Updated: 2025/03/12 06:45:16 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_valid_identifier(const char *str)
{
	int	i;

	i = 0;
	if (!str)
		return (0);
	if (!(ft_isalpha(str[0]) || str[0] == '_'))
		return (0);
	while (str[i] && str[i] != '=')
	{
		if (!(ft_isalnum(str[i]) || str[i] == '_'))
			return (0);
		i++;
	}
	return (1);
}

char	*get_name_from_env(const char *str)
{
	int		i;
	char	*name;

	i = 0;
	while (str[i] && str[i] != '=')
		i++;
	name = malloc(i + 1);
	if (!name)
		return (NULL);
	i = 0;
	while (str[i] && str[i] != '=')
	{
		name[i] = str[i];
		i++;
	}
	name[i] = '\0';
	return (name);
}

char	*get_invalid_identifier(const char *str)
{
	int	i;

	if (!str)
		return (ft_strdup(""));
	if (str[0] != '=')
		return (ft_strdup(str));
	i = 1;
	while (str[i])
	{
		if (str[i] == '=')
			break ;
		i++;
	}
	return (ft_substr(str, 0, i + 1));
}

int	count_array(char **arr)
{
	int	count;

	count = 0;
	while (arr && arr[count])
		count++;
	return (count);
}

int	copy_array(char **src, char **dest, int j)
{
	int	i;

	i = 0;
	while (src && src[i])
	{
		dest[j] = ft_strdup(src[i]);
		if (!dest)
			handle_malloc_error();
		j++;
		i++;
	}
	return (j);
}
