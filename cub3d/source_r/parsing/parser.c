/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: engooh <engooh@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/11 14:27:21 by engooh            #+#    #+#             */
/*   Updated: 2022/10/24 14:52:09 by engooh           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

int	check_file(char *path_file)
{
	int		len;

	if (!path_file)
		return (0);
	len = ft_strlen(path_file);
	if (len == 4 || (len == 5 && path_file[0] == '.'))
		return (0);
	if (len > 4 && ft_strncmp(path_file + len - 4, ".cub", 4))
		return (0);
	return (1);
}

int	open_file(char	*path_file)
{
	int	fd;

	if (!check_file(path_file))
		return (-1);
	fd = open(path_file, O_DIRECTORY, O_RDONLY);
	if (fd >= 0)
		return (close(fd), -1);
	fd = open(path_file, O_NOFOLLOW, O_RDONLY);
	if (fd < 0)
		return (close(fd), -1);
	return (fd);
}

char	*ft_read(char *path_file)
{
	int		fd;
	int		size;
	int		size_max;
	char	*file;
	char	buf[BUFFER_SIZE];

	size = 1;
	file = NULL;
	size_max = 0;
	fd = open_file(path_file);
	if (fd < 0)
		return (NULL);
	while (size)
	{
		file = ft_strjoin2(file, buf, size_max);
		size = read(fd, buf, BUFFER_SIZE);
		if (size < 0)
			return (NULL);
		buf[size] = 0;
		size_max += size;
	}
	return (file);
}
