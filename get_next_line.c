/* ************************************************************************** */
/*                                                                            */
/*                                                       :::      ::::::::    */
/*   get_next_line.c                                   :+:      :+:    :+:    */
/*                                                   +:+ +:+         +:+      */
/*   By: srosu <srosu@student.42belgium.be>        #+#  +:+       +#+         */
/*                                               +#+#+#+#+#+   +#+            */
/*   Created: 2026/04/22 19:06:57 by srosu            #+#    #+#              */
/*   Updated: 2026/04/22 23:17:10 by srosu           ###   ########.fr        */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static int	read_and_append(int fd, char **stash, char *buff)
{
	int		bytes_read;
	char	*tmp;

	bytes_read = read(fd, buff, BUFFER_SIZE);
	if (bytes_read < 0)
		return (-1);
	if (bytes_read == 0)
		return (0);
	buff[bytes_read] = '\0';
	tmp = ft_strjoin(*stash, buff);
	free(*stash);
	*stash = tmp;
	if (!*stash)
		return (-1);
	if (ft_strchr(*stash, '\n'))
		return (0);
	return (1);
}

static char	*read_to_stash(int fd, char *stash)
{
	char	*buff;
	int		check;

	buff = malloc(BUFFER_SIZE + 1);
	if (!buff)
		return (NULL);
	while (1)
	{
		check = read_and_append(fd, &stash, buff);
		if (check <= 0)
			break ;
	}
	if (check < 0)
	{
		free(buff);
		return (NULL);
	}
	free(buff);
	return (stash);
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

char	*get_next_line(int fd)
{
	static char	*stash;
	char		*line;

	if (fd == -1 || BUFFER_SIZE <= 0)
		return (NULL);
	if (!stash)
		stash = (ft_strdup(""));
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
