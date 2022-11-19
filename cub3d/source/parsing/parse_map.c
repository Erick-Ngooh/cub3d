/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: engooh <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/15 04:51:43 by engooh            #+#    #+#             */
/*   Updated: 2022/10/02 18:43:47 by engooh           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"
#include <unistd.h>


char	join(char *s1, char *s2, int len_s1, int size_max)
{
	char	*new;

	new = malloc(sizeof() * (len_s1 + len_s2 + 1));
}

char	*ft_read_file(t_global *g, int fd)
{
	int		size_total;
	char	*file;
	int		size;

	size = read(fd, &g->pars->buf, BUFFER_SIZE);
	while (size)
	{
			size_total += size;
			size = read(fd, &g->pars->buf, 32000);
			if (!size)
				break ;
			
	}
	return (file);
}
