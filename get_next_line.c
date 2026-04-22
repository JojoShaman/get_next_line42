/* ************************************************************************** */
/*                                                                            */
/*                                                       :::      ::::::::    */
/*   get_next_line.c                                   :+:      :+:    :+:    */
/*                                                   +:+ +:+         +:+      */
/*   By: srosu <srosu@student.42belgium.be>        #+#  +:+       +#+         */
/*                                               +#+#+#+#+#+   +#+            */
/*   Created: 2026/04/22 01:00:45 by srosu            #+#    #+#              */
/*   Updated: 2026/04/22 15:30:14 by srosu           ###   ########.fr        */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static char	*read_to_stash(int fd, char *stash)
{
	char	*buff;
	char	*tmp;
	int		bytes_read;

	buff = malloc(BUFFER_SIZE + 1);
	if (!buff)
		return (NULL);
	bytes_read = 1;
	while (bytes_read > 0)
	{
		bytes_read = read(fd, buff, BUFFER_SIZE);
		if (bytes_read < 0)
		{
			free(buff);
			return (NULL);
		}
		if (bytes_read == 0)
			break ;
		buff[bytes_read] = '\0';
		tmp = ft_strjoin(stash, buff);
		free(stash);
		stash = tmp;
		if (!stash)
		{
			free(buff);
			return (NULL);
		}
		if (ft_strchr(stash, '\n'))
			break ;
	}
	free(buff);
	return (stash);
}

static char	*extract(char *stash)
{
	size_t	i;

	i = 0;
	while (stash[i] && stash[i] != '\n')
		i++;
	if (stash[i] == '\n')
		i++;
	return (ft_substr(stash, 0, i));
}

static char	*update_stash(char *stash)
{
	size_t	i;
	char	*new_stash;

	i = 0;
	while (stash[i] && stash[i] != '\n')
		i++;
	if (stash[i] == '\n')
		i++;
	if (!stash[i])
	{
		free(stash);
		return (NULL);
	}
	new_stash = ft_substr(stash, i, ft_strlen(stash) - i);
	free(stash);
	return (new_stash);
}

char	*get_next_line(int fd)
{
	static char	*stash;
	char		*line;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	if (!stash)
		stash = ft_strdup("");
	if (!stash)
		return (NULL);
	stash = read_to_stash(fd, stash);
	if (!stash || !stash[0])
	{
		free(stash);
		stash = NULL;
		return (NULL);
	}
	line = extract(stash);
	stash = update_stash(stash);
	return (line);
}
