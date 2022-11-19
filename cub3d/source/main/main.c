
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: engooh <engooh@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/15 01:20:42 by engooh            #+#    #+#             */
/*   Updated: 2022/11/19 01:26:13 by engooh           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

t_gc	*get_gc(void)
{
	static t_gc	gc;

	return (&gc);
}

int	init_stuct_global(t_global *g, char **av)
{
	g->map.fd = open_file(av[1]);
	if (g->map.fd < 0)
		return (0);
	g->map.map = NULL;
	g->map.len_map = 0;
	g->elem.rgb_sol[0] = 0;
	g->elem.rgb_sol[1] = 0;
	g->elem.rgb_sol[2] = 0;
	g->elem.rgb_plafond[0] = 0;
	g->elem.rgb_plafond[1] = 0;
	g->elem.rgb_plafond[2] = 0;
	g->elem.west_texture = NULL;
	g->elem.east_texture = NULL;
	g->elem.north_texture = NULL;
	g->elem.south_texture = NULL;
	return (1);
}

int	main(int ac, char **av, char **envp)
{
	t_global	g;

	if (ac != 2 || !envp)
		return (1);
	if (!init_stuct_global(&g, av))
		ft_exit(1);
	if (!init_struct_element(&g.elem, &g.map) && printf("ERROR: fail parse elem\n"))
		ft_exit(1);
	if (!init_struct_map(&g, &g.map) && printf("ERROR: fail parse map\n"))
		ft_exit(1);
	ft_cub2d(&g);
	print_map(g.map.map);
	ft_exit(0);
	return (0);
}
