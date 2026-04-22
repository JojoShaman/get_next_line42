/* ************************************************************************** */
/*                                                                            */
/*                                                       :::      ::::::::    */
/*   get_next_line.h                                   :+:      :+:    :+:    */
/*                                                   +:+ +:+         +:+      */
/*   By: srosu <srosu@student.42belgium.be>        #+#  +:+       +#+         */
/*                                               +#+#+#+#+#+   +#+            */
/*   Created: 2026/04/22 00:13:27 by srosu            #+#    #+#              */
/*   Updated: 2026/04/22 14:49:13 by srosu           ###   ########.fr        */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 7
# endif
# if BUFFER_SIZE <= 0 || BUFFER_SIZE > 0x7ffff000
#  error "Invalid buffer size"
# endif

# include <stdio.h>
# include <string.h>
# include <stdlib.h>
# include <fcntl.h>
# include <unistd.h>

size_t	ft_strlen(const char *str);
char	*ft_strjoin(const char *s1, const char *s2);
char	*ft_strdup(char *str);
char	*ft_substr(char *str, size_t start, size_t size);
char	*ft_strchr(const char *str, int c);
char	*get_next_line(int fd);

#endif
