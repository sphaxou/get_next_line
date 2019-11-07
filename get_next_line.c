/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vgallois <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/22 04:30:48 by vgallois          #+#    #+#             */
/*   Updated: 2019/11/07 00:42:58 by vgallois         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <sys/types.h>
#include <sys/uio.h>
#include <unistd.h>

int			findbn(char *s, int size)
{
	int				i;

	i = 0;
	while (i < size)
	{
		if (s[i] == '\n')
			return (i);
		i++;
	}
	return (i);
}

int			do_stuff(t_gnl *gnl, int i, char **line)
{
	int				res;

	res = (*line)[i] == '\n' ? 1 : 0;
	(*line)[i] = 0;
	ft_memmove((*gnl).content, *line + i + 1, (*gnl).size - i);
	(*gnl).size -= i + res;
	return (res);
}

int			assign_line(t_gnl *gnl, char **line)
{
	int				ret;
	int				i;

	*line = ft_memdup((*gnl).content, (*gnl).size);
	i = findbn(*line, (*gnl).size);
	if (i < (*gnl).size)
		return (do_stuff(gnl, i, line));
	while ((ret = read((*gnl).fd, (*gnl).content, BUFFER_SIZE)))
	{
		if (ret == -1)
			return (-1);
		*line = ft_expand(*line, (*gnl).content, (*gnl).size, ret);
		(*gnl).size += ret;
		i = findbn(*line, (*gnl).size);
		if (i < (*gnl).size || ret < BUFFER_SIZE)
			return (do_stuff(gnl, i, line));
	}
	if ((*gnl).size > 0)
		return (do_stuff(gnl, i, line));
	return (0);
}

int			get_next_line(int fd, char **line)
{
	static t_gnl	tab[MAX_FD];

	if (fd < 0 || fd > MAX_FD)
		return (-1);
	tab[fd].fd = fd;
	return (assign_line(tab + fd, line));
}
