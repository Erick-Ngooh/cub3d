/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser3.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: engooh <engooh@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/19 12:58:43 by engooh            #+#    #+#             */
/*   Updated: 2022/10/24 11:30:28 by engooh           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"
#include <unistd.h>

char	*skip_line_empty(char *file, int mode)
{
	if (!file)
		return (NULL);
	if (mode && *file == '\n')
	{
		while (*file && (*file >= '\t' && *file <= '\r'))
		{
			file++;
			if (*file == '\n' && !(*file >= '\t' && *file <= '\r'))
				return (NULL);
		}
		return (file);
	}
	while (*file && (*file>= '\t' && *file <= '\r'))
		file++;
	return (file);
}

char *parse_one_line(char *file, int start_or_end)
{
	while (*file && *file == '1' && *file != '\n')
	{
		file++;
		while (*file >= '\t' && *file <= '\r' && *file != '\n')
			file++;
	}
	if (!(start_or_end && *file == '\n') || !(!start_or_end && !*file))
		return (NULL);
	return (file);
}

char	*parse_map_line(char *file, int *c, int nbr)
{
	(void)c;
	(void)nbr;
	file = skip_line_empty(file, 1); 
	if (!file)
		return (NULL);
	while (*file && (*file == '1' || *file == '0') && *file != '\n')
	{
		file++;
		while (*file >= '\t' && *file <= '\r' && *file != '\n')
			file++;
	}
	if (!(*file == '\n' || !*file))
		return (NULL);
	return (file);
}

char	*parse_map(char *file)
{
	char	*res;
	int		charset;

	res = NULL;
	charset = 1;
	(void)charset;
	(void)res;
	skip_line_empty(file, 0);
	return (file);
}
