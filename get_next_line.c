/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vgallois <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/22 04:30:48 by vgallois          #+#    #+#             */
/*   Updated: 2019/10/22 07:09:20 by vgallois         ###   ########.fr       */
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
	*line = ft_memdup((*gnl).content, i);
	(*gnl).content =
		ft_memmove((*gnl).content, (*gnl).content + i + 1, (*gnl).size - i);
	(*gnl).size -= i + 1;
	return (1);
}

int			assign_line(t_gnl *gnl, char **line)
{
	char			buff[BUFFER_SIZE];
	int				ret;
	char			*tmp;
	int				i;

	while ((ret = read((*gnl).fd, buff, BUFFER_SIZE)))
	{
		if (ret == -1)
			return (-1);
		(*gnl).content = ft_expand((*gnl).content, buff, (*gnl).size, ret);
		(*gnl).size += ret;
		i = findbn((*gnl).content, (*gnl).size);
		if (i < (*gnl).size)
			return (do_stuff(gnl, i, line));
	}
	if ((*gnl).size > 0)
	{
		i = findbn((*gnl).content, (*gnl).size);
		return (do_stuff(gnl, i, line));
	}
	*line = NULL;
	return (0);
}

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

int			get_next_line(int fd, char **line)
{
	static t_gnl	*tab = NULL;
	int				i;

	if (!tab)
		tab = init(tab);
	if (!tab || fd < 0)
		return (-1);
	return (assign_line(tab + fd, line));
}
