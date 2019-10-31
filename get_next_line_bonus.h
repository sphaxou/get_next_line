/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.h                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vgallois <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/17 08:20:54 by vgallois          #+#    #+#             */
/*   Updated: 2019/10/31 20:34:40 by vgallois         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_BONUS_H
# define GET_NEXT_LINE_BONUS_H
# include <stdlib.h>
# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 10000
# endif
# define MAX_FD 590432

typedef struct	s_gnl
{
	char	*content;
	int		size;
	int		fd;
}				t_gnl;

int				get_next_line(int fd, char **line);
void			*ft_expand(char *s1, char *s2, int n1, int n2);
void			*ft_memmove(void *dst, const void *src, size_t len);
char			*ft_memdup(const void *src, size_t len);

#endif
