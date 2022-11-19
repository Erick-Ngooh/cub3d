/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: engooh <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/11 19:16:10 by engooh            #+#    #+#             */
/*   Updated: 2022/09/29 07:46:35 by engooh           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../../include/cub3d.h"

char	*ft_get_line(char *cache)
{
	char	*line;
	long	l;
	long	i;

	l = -1;
	while (cache && cache[++l])
		if (cache[l] == '\n' && ++l)
			break ;
	line = ft_malloc(sizeof(char), (l + 2));
	if (!line)
		return (NULL);
	i = -1;
	while (++i < l)
		line[i] = cache[i];
	line[i] = '\0';
	return (line);
}

char	*ft_get_cache(char *cache)
{
	size_t	l;
	size_t	i;
	char	*p;
	size_t	size;

	l = -1;
	while (cache[++l])
		if (cache[l] == '\n' && ++l)
			break ;
	size = ft_strlen(cache) - l;
	if (size == 0)
		return (NULL);
	p = ft_malloc(sizeof(char), (size + 1));
	if (!p)
		return (NULL);
	i = -1;
	while (++i + l < ft_strlen(cache) && cache[i + l])
		p[i] = cache[i + l];
	p[i] = '\0';
	return (p);
}
