/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_map.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: engooh <engooh@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/29 02:05:50 by engooh            #+#    #+#             */
/*   Updated: 2022/11/19 20:52:11 by engooh           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

int	parse_line_by_line(char *line, int flag)
{
	char	*tmp;

	if (!line || !*line)
		return (-1);
	tmp = line;
	if (flag > 1)
		while (*line)
			if (!ft_strchr("10NSEW\t\n\b\r\v ", *line++))
				return (0);
	if (flag == 1)
		while (*line)
			if (!ft_strchr("1\t\n\b\r\v ", *line++))
				return (0);
	if (!*line && line > tmp)
		line--;
	while (line > tmp && ft_strchr("\t\n\b\r\v ", *line))
		line--;
	while (*tmp && ft_strchr("\t\n\b\r\v ", *tmp))
		tmp++;
	if (*tmp != '1' || *line != '1')
		return (0);
	return (1);
}

char	**set_map(t_map *map_s, int line_fill, int line_empty, int check)
{
	int		start;
	char	*buffer;

	start = 0;
	buffer = "\n";
	while (buffer)
	{
		check = 0;
		line_fill = check_line_empty(buffer);
		if (start < 2 && line_fill)
			start++;
		if (start && !line_fill && !line_empty)
			line_empty = 1;
		if (start && line_fill)
			check = parse_line_by_line(buffer, start);
		if (start && ((!check && line_fill) || (check && line_empty)))
			return (NULL);
		if (start && line_fill)
			map_s->map = tab_join(map_s->map, buffer, ++map_s->len_map);
		buffer = get_next_line(map_s->fd);
	}
	if (start && !parse_line_by_line(map_s->map[map_s->len_map - 1], 1))
		return (NULL);
	return (map_s->map);
}

int	set_pos(t_global *g, int x, int y)
{
	if (!g->player_s.pos[0])
	{
		g->player_s.pos[0] = x * SIZE_PIXEL + SIZE_PIXEL / 2;
		g->player_s.pos[1] = y * SIZE_PIXEL + SIZE_PIXEL / 2;
		return (1);
	}
	else
		if (x * SIZE_PIXEL + SIZE_PIXEL / 2 == g->player_s.pos[0])
			if (y * SIZE_PIXEL + SIZE_PIXEL / 2 == g->player_s.pos[1])
				return (1);
	return (0);
}

int	parse_map_utlis(t_global *g, char **map, int x, int y)
{
	if (map[y][x] == '0' || ft_strchr("NSWE", map[y][x]))
	{
		if (ft_strchr("NSWE", map[y][x]))
			set_pos(g, x, y);
		if (!(map[y][x + 1] && map[y][x - 1] && map[y + 1][x] && map[y - 1][x]))
			return (0);
		if (map[y][x + 1] && ft_strchr("\b\t\n\r ", map[y][x + 1]))
			return (0);
		if (map[y][x - 1] && ft_strchr("\b\t\n\r ", map[y][x - 1]))
			return (0);
		if (map[y + 1][x] && ft_strchr("\b\t\n\r ", map[y + 1][x]))
			return (0);
		if (map[y - 1][x] && ft_strchr("\b\t\n\r ", map[y - 1][x]))
			return (0);
	}
	//printf("before\n");
	if (ft_strchr("NSWE", map[y][x]))
		return (set_pos(g, x, y));
	//printf("VERS LA\n");
	return (1);
}

int	parse_map(t_global *g, char **map)
{
	int	y;
	int	x;

	if (!map || !*map)
		return (0);
	y = -1;
	while (map[++y])
	{
		x = -1;
		while (map[y][++x])
		{
			if (!parse_map_utlis(g, map, x, y))
			{
				//printf("set pos KO\n");
				return (0);
			}
		}
	}
	if (!g->player_s.pos[0])
		return (0);
	return (1);
}

int	init_struct_map(t_global *g, t_map *map)
{
	g->player_s.pos[0] = 0;
	if (!set_map(map, 0, 0, 0) && printf("ZAZA\n"))
		return (0);
	if (!parse_map(g, map->map) && printf("TOTO\n"))
		return (0);
	printf("pos x = %f : pos y = %f\n", g->player_s.pos[0], g->player_s.pos[1]);
	return (1);
}
