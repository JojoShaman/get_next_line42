/* ************************************************************************** */
/*                                                                            */
/*                                                       :::      ::::::::    */
/*   get_next_line_utils.c                             :+:      :+:    :+:    */
/*                                                   +:+ +:+         +:+      */
/*   By: srosu <srosu@student.42belgium.be>        #+#  +:+       +#+         */
/*                                               +#+#+#+#+#+   +#+            */
/*   Created: 2026/04/22 00:14:28 by srosu            #+#    #+#              */
/*   Updated: 2026/04/22 14:07:35 by srosu           ###   ########.fr        */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

size_t	ft_strlen(const char *str)
{
	size_t	len;

	len = 0;
	while (str[len])
		len++;
	return (len);
}

char	*ft_strchr(const char *str, int c)
{
	while (*str)
	{
		if (*str == (char) c)
			return ((char *) str);
		str++;
	}
	return (NULL);
}

char	*ft_strjoin(const char *s1, const char *s2)
{
	size_t	s1_len;
	size_t	s2_len;
	char	*new_str;
	char	*ptr;

	if (!s1 || !s2)
		return (NULL);
	s1_len = ft_strlen(s1);
	s2_len = ft_strlen(s2);
	new_str = malloc(((s1_len + s2_len) + 1) * sizeof(*new_str));
	if (!new_str)
		return (NULL);
	ptr = new_str;
	while (*s1)
		*new_str++ = *s1++;
	while (*s2)
		*new_str++ = *s2++;
	*new_str = '\0';
	return (ptr);
}

char	*ft_strdup(char *str)
{
	char	*copy;
	char	*ptr;

	if (!str)
		return (NULL);
	copy = malloc((ft_strlen(str) + 1) * sizeof(*copy));
	if (!copy)
		return (NULL);
	ptr = copy;
	while (*str)
		*copy++ = *str++;
	*copy = '\0';
	return (ptr);
}

char	*ft_substr(char *str, size_t start, size_t size)
{
	char	*new_str;
	char	*ptr;

	if (!str)
		return (NULL);
	if (start >= ft_strlen(str))
		return (ft_strdup(""));
	new_str = malloc(size + 1);
	if (!new_str)
		return (NULL);
	ptr = new_str;
	while (size-- && str[start])
		*new_str++ = str[start++];
	*new_str = '\0';
	return (ptr);
}
