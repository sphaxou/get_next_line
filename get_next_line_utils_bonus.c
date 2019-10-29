/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils_bonus.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vgallois <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/17 09:04:23 by vgallois          #+#    #+#             */
/*   Updated: 2019/10/29 13:57:58 by vgallois         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"
#include <stdlib.h>

void	*ft_expand(char *s1, char *s2, int n1, int n2)
{
	int		i;
	int		i2;
	char	*res;

	if (!(res = malloc(sizeof(char) * (n1 + n2 + 1))))
		return (NULL);
	i = -1;
	while (++i < n1)
		res[i] = s1[i];
	i2 = 0;
	while (i2 < n2)
		res[i++] = s2[i2++];
	res[i] = '\0';
	free(s1);
	return (res);
}

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*res;
	size_t	i;
	int		bo;

	i = 0;
	while (s && s[i] && i < start)
		i++;
	bo = (i == start ? 1 : 0);
	if (!s || !(res = malloc(sizeof(char) * ((bo ? len : 0) + 1))))
		return (NULL);
	i = 0;
	while (bo && s[start + i] && i < len)
	{
		res[i] = s[start + i];
		i++;
	}
	res[i] = 0;
	return (res);
}

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	size_t	i;
	int		s;
	char	*res;
	char	*sr;

	if (!dst || !src)
		return ((void *)dst);
	s = (dst < src ? 1 : -1);
	i = (dst < src ? 0 : len - 1);
	res = (char *)dst;
	sr = (char *)src;
	while (len)
	{
		res[i] = sr[i];
		i += s;
		len--;
	}
	return (res);
}

char	*ft_memdup(const void *s, size_t n)
{
	char	*res;
	size_t	i;

	i = 0;
	if (!(res = (char*)malloc(sizeof(char) * n + 1)))
		return (NULL);
	while (i < n)
	{
		res[i] = ((unsigned char *)s)[i];
		i++;
	}
	res[i] = 0;
	return (res);
}
