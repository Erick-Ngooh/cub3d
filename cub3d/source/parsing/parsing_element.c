/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_element.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: engooh <engooh@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/29 02:09:57 by engooh            #+#    #+#             */
/*   Updated: 2022/11/19 17:31:03 by engooh           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

int	ft_exist_file(char *path_file)
{
	int	fd;

	fd = open(path_file, O_DIRECTORY, O_DIRECTORY);
	if (fd > 0)
	{
		close(fd);
		return (-1);
	}
	fd = open(path_file, O_NOFOLLOW, O_RDONLY);
	if (fd >= 0)
		close(fd);
	return (fd);
}

int	set_texture_elem(char *line, t_elem *elem, int flag)
{
	char	*end;

	if (line && *line && line + 1 && *(line + 1) && (line + 2) && *(line + 2))
		line += 2;
	line = ft_skip_withspace(line);
	if (line && !*line)
		return (-1);
	end = line;
	while (end && *end && !ft_strchr("\b\t\r\n ", *end))
		end++;
	*end = '\0';
	if (ft_exist_file(line) < 0)
		return (0);
	if (flag == 1 && !elem->north_texture)
		elem->north_texture = line;
	else if (flag == 2 && !elem->south_texture)
		elem->south_texture = line;
	else if (flag == 3 && !elem->west_texture)
		elem->west_texture = line;
	else if (flag == 4 && !elem->east_texture)
		elem->east_texture = line;
	else
		return (0);
	return (1);
}

int	set_rgb_elem(char *line, t_elem *elem, int flag)
{
	int		i;
	char	**tabs_nbr;

	if (line && *line && line + 1 && *(line + 1))
		line++;
	line = ft_skip_withspace(line);
	ft_strchr_and_replace(line, '\n', '\0');
	if (line && !*line)
		return (-1);
	tabs_nbr = ft_split(line, ',');
	if ((!tabs_nbr || !*tabs_nbr) && printf("PAR LA BAS\n"))
		return (0);
	i = -1;
	while (++i < 3 && tabs_nbr[i])
	{
		if (tabs_nbr[i] && flag == 'C' && ft_str_isdigit(tabs_nbr[i]))
			elem->rgb_plafond[i] = ft_atoi(tabs_nbr[i]);
		else if (tabs_nbr[i] && flag == 'F' && ft_str_isdigit(tabs_nbr[i]))
			elem->rgb_sol[i] = ft_atoi(tabs_nbr[i]);
		else if (flag == 'F')
			elem->rgb_sol[i] = -1;
		else if (flag == 'C')
			elem->rgb_plafond[i] = -1;
		if ((elem->rgb_sol[i] < 0 || elem->rgb_sol[i] > 255
			|| elem->rgb_plafond[i] < 0 || elem->rgb_plafond[i] > 255) && printf("PAR LA\n"))
			return (0);
	}
	return (1);
}

int	parse_line_element(char	*line, t_elem *elem)
{
	int	res;

	line = ft_skip_withspace(line);
	if (line && !*line)
		return (-1);
	res = 0;
	if (line && *line && !ft_strncmp("NO", line, 2) && printf("ici 1 "))
		res = set_texture_elem(line, elem, 1);
	else if (line && *line && !ft_strncmp("SO", line, 2) && printf("ici 2 "))
		res = set_texture_elem(line, elem, 2);
	else if (line && *line && !ft_strncmp("WE", line, 2) && printf("ici 3 "))
		res = set_texture_elem(line, elem, 3);
	else if (line && *line && !ft_strncmp("EA", line, 2) && printf("ici 4 "))
		res = set_texture_elem(line, elem, 4);
	else if (line && *line && !ft_strncmp("F", line, 1) && printf("ici 5 "))
		res = set_rgb_elem(line, elem, 'F');
	else if (line && *line && !ft_strncmp("C", line, 1) && printf("ici 6 "))
		res = set_rgb_elem(line, elem, 'C');
	return (res);
}

int	init_struct_element(t_elem *elem, t_map *map)
{
	int		res;
	char	*buf;
	int		limit;

	limit = 6;
	buf = "42";
	while (buf && limit)
	{
		buf = get_next_line(map->fd);
		res = parse_line_element(buf, elem);
		if (!res)
			return (0);
		if (res > 0)
			limit--;
	}
	//printf("%d limit\n", limit);
	if (limit && printf("limit %d\n", limit))
		return (0);
	//printf("%d limit\n", limit);
	return (1);
}
