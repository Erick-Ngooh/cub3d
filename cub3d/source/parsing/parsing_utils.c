/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: engooh <engooh@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/29 02:07:47 by engooh            #+#    #+#             */
/*   Updated: 2022/11/19 12:10:52 by engooh           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

int	check_line_empty(char *line)
{
	int		len;
	char	*start;

	start = line;
	len = ft_strlen(line);
	while (*line && ft_strchr("\n\t\b\v\r ", *line))
		line++;
	if (line - start == len)
		return (0);
	return (1);
}

int	open_file(char	*file)
{
	int	fd;

	fd = ft_strlen(file);
	if (fd <= 4 && ft_strncmp(file - 4, ".cub", 4))
		return (-1);
	if (fd == 5 && file[0] == '.')
		return (-1);
	fd = open(file, O_DIRECTORY, O_DIRECTORY);
	if (fd > 0)
	{
		close(fd);
		return (-1);
	}
	return (fd = open(file, O_NOFOLLOW, O_RDONLY));
}

void	print_map(char **map)
{
	int	i;

	i = -1;
	//printf("\n\n\nDEBUG DE LA MAP\n");
	while (map && map[++i])
		printf("value: %s - address: %p - number of line: %d\n\n",
			map[i], map[i], i);
}

char	**tab_join(char **tab, char *str, int size)
{
	int		i;
	char	**new;

	new = ft_malloc(sizeof(char *), (size + 1));
	if (!new)
		return (NULL);
	i = 0;
	while (tab && tab[i])
	{
		new[i] = tab[i];
		i++;
	}
	new[i] = str;
	new[i + 1] = NULL;
	return (new);
}
