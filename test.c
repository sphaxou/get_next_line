/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vgallois <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/17 09:29:08 by vgallois          #+#    #+#             */
/*   Updated: 2019/11/05 20:02:08 by vgallois         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>

int	main(int ac, char **av)
{
	int		i;
	char	*line;
	int		fd;
	int		j;

	j = 0;
	ac = 0;
	i = 1;
	while (av[i])
	{
		fd = open(av[i], O_RDONLY);
		while ((get_next_line(fd, &line) > 0))
		{
			printf("%s\n", line);
			free(line);
		}
		i++;
		printf("%s\n", line);
		free(line);
	}
	return (0);
}
