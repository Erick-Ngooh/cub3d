/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: engooh <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/11 13:44:05 by engooh            #+#    #+#             */
/*   Updated: 2022/09/29 07:44:35 by engooh           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../../include/cub3d.h"

char	*ft_read(int fd, char *cache, long reader)
{
	char	*buffer;

	buffer = ft_malloc(sizeof(char), (BUFFER_SIZE + 1));
	if (!buffer)
		return (NULL);
	while (!cache || (*cache && !ft_strchr(cache, '\n') && reader))
	{
		reader = read(fd, buffer, BUFFER_SIZE);
		if (reader == -1 || (!cache && !reader))
			return (NULL);
		buffer[reader] = '\0';
		cache = ft_strjoin(cache, buffer);
	}
	return (cache);
}

char	*get_next_line(int fd)
{
	static char	*cache;
	char		*line;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	cache = ft_read(fd, cache, 1);
	if (!cache || (cache && !*cache))
		return (NULL);
	line = ft_get_line(cache);
	cache = ft_get_cache(cache);
	return (line);
}
