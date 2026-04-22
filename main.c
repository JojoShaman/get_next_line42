/* ************************************************************************** */
/*                                                                            */
/*                                                       :::      ::::::::    */
/*   main.c                                            :+:      :+:    :+:    */
/*                                                   +:+ +:+         +:+      */
/*   By: srosu <srosu@student.42belgium.be>        #+#  +:+       +#+         */
/*                                               +#+#+#+#+#+   +#+            */
/*   Created: 2026/04/22 15:30:02 by srosu            #+#    #+#              */
/*   Updated: 2026/04/22 15:30:03 by srosu           ###   ########.fr        */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int	main(int argc, char **argv)
{
	int		fd;
	int		count;
	char	*line;
	char	file_name[50];

	count = 0;
	if (argc != 2)
	{
		printf("Usage : ./GNL <file_name>\n");
		return (1);
	}
	fd = open(argv[1], O_RDONLY);
	if (fd == -1)
	{
		printf("Error: could not open file\n");
		return (1);
	}
	while (1)
	{
		line = get_next_line(fd);
		if (!line)
			break ;
		printf("[%d] %s", count, line);
		free(line);
		count++;
	}
	close(fd);
	return (0);
}
