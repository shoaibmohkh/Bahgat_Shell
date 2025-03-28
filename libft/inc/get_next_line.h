/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sal-kawa <sal-kawa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/16 19:31:39 by sal-kawa          #+#    #+#             */
/*   Updated: 2024/12/24 14:55:08 by sal-kawa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 20
# endif

# include <fcntl.h>
# include <stddef.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>

char	*get_next_line(int fd);
char	*ft_strchrr(const char *s, int c);
size_t	ft_strlenn(const char *s);
char	*ft_strdupp(char *s);
char	*ft_strjoinn(char *s, char *a);
void	fill_str(char *res, char *s, char *a);
char	*ft_substrr(char const *s, unsigned int start, size_t len);

#endif
