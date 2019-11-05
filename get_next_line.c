/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vgallois <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/22 04:30:48 by vgallois          #+#    #+#             */
/*   Updated: 2019/11/05 19:56:01 by vgallois         ###   ########.fr       */
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
	while ((ret = read((*gnl).fd, (*gnl).content, BUFFER_SIZE)))
	{
		if (ret == -1)
			return (-1);
		*line = ft_expand(*line, (*gnl).content, (*gnl).size, ret);
		(*gnl).size += ret;
		i = findbn(*line, (*gnl).size);
		if (i < (*gnl).size)
			return (do_stuff(gnl, i, line));
	}
	if ((*gnl).size > 0)
	{
		i = findbn(*line, (*gnl).size);
		return (do_stuff(gnl, i, line));
	}
	return (0);
}
/*
t_gnl		*init(t_gnl *tab)
{
	int				i;

	if (!(tab = (t_gnl *)malloc(sizeof(*tab) * (MAX_FD + 1))))
		return (NULL);
	i = 0;
	while (i < MAX_FD)
	{
		if (!(tab[i].content = malloc(1)))
			return (NULL);
		((char *)tab[i].content)[0] = 0;
		tab[i].size = 0;
		tab[i].fd = i;
		i++;
	}
	return (tab);
}
*/
int			get_next_line(int fd, char **line)
{
	static t_gnl	tab[MAX_FD];

	if (fd < 0)
		return (-1);
	tab[fd].fd = fd;
	return (assign_line(tab + fd, line));
}
