/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: engooh <engooh@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/11 17:27:04 by engooh            #+#    #+#             */
/*   Updated: 2022/10/24 14:52:12 by engooh           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"
#include <stdio.h>

char	*skip_withspace(char *str, int n)
{
	while (*str && *str >= '\t' && *str <= '\r')
	{
		if (n && *str == '\n')
			return (str);
		str++;
	}
	return (str);
}

char	*parse_texture_utils(char *file)
{
	char	*tmp;

	file = skip_withspace(file, 1);
	if (*file == '\n' || !*file)
		return (NULL);
	tmp = file;
	while (*tmp && !ft_strchr("\t\r\b\n ", *tmp))
		tmp++;
	printf("after test path texture %s\n", file);
	return (tmp);
}

char	*parse_color_utils(char *file, int n)
{
	char	*tmp = NULL;
	int		nbr;

	if (n <= 3)
	{
		tmp = file;
		while (*tmp && ft_isdigit(*tmp))
			tmp++;
		if (n < 3 && !(*tmp == ',' && (*(tmp + 1) && ft_isdigit(*(tmp + 1)))))
			return (NULL);
		if (n == 3 && !(*tmp >= '\t' && *tmp <= 'r'))
			return (NULL);
		*tmp = '\0';
		nbr = ft_atoi2(file);
		if (nbr < 0)
			return (NULL);
		if (n != 3)
			*tmp = ',';
		return (parse_color_utils(tmp + 1, n + 1));
	}
	return (tmp);
}

char	*parse_color(char *file)
{
	file = skip_withspace(file, 1);
	if (*file == '\n' || !*file)
		return (NULL);
	file = parse_color_utils(file, 1);
	if (!file)
		return (NULL);
	return (file);
}

char	*parse_texture(char *file, char *charset)
{
	file = skip_withspace(file, 1);
	if (*file == '\n')
		return (file + 1);
	else if (ft_strchr(charset, *file)
		&& *file == 'C' && ft_strchr("\t\r\b ", *(file + 1)))
		charset[5] = 127;
	else if (ft_strchr(charset, *file)
		&& *file == 'F' && ft_strchr("\t\r\b ", *(file + 1)))
		charset[4] = 127;
	else if (ft_strchr(charset, *file)
		&& !ft_strncmp(file, "EA", 2) && ft_strchr("\t\r\b ", *(file + 2)))
		charset[3] = 127;
	else if (ft_strchr(charset, *file)
		&& !ft_strncmp(file, "WE", 2) && ft_strchr("\t\r\b ", *(file + 2)))
		charset[2] = 127;
	else if (ft_strchr(charset, *file)
		&& !ft_strncmp(file, "SO", 2) && ft_strchr("\t\r\b ", *(file + 2)))
		charset[1] = 127;
	else if (ft_strchr(charset, *file)
		&& !ft_strncmp(file, "NO", 2) && ft_strchr("\t\r\b ", *(file + 2)))
		charset[0] = 127;
	else
		return (NULL);
	file = parse_texture_utils(file + 2);
	return (file);
}

int	ft_parsing(char *file)
{
	int		start_parse_map;
	char	charset[7] = "NSWEFC";

	if (!file || !*file)
		return (0);
	while (file && *file)
	{
		file = parse_texture(file, charset);
		if (!file)
			return (printf("LALA \n"), 0);
		start_parse_map = 0;
		while (charset[start_parse_map] && charset[start_parse_map] == 127)
			start_parse_map++;
		if (start_parse_map == 6)
			file = parse_map(file);
	}
	return (1);
}
