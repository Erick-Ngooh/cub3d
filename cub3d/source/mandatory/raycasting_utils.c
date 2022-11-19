
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycating_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: engooh <engooh@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/19 00:54:28 by engooh            #+#    #+#             */
/*   Updated: 2022/11/19 01:08:54 by engooh           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

unsigned int get_color_pixel(t_global *g, void *img, int x, int y)
{
	char	*src;
	int	color;

	color = 0xFFFFFF;
	if (x + (y * HRES) < (HRES*VRES))
	{
		g->tmp.addr = mlx_get_data_addr(img, &g->tmp.bits_per_pixel, &g->tmp.line_length, &g->tmp.endian);
		src = g->tmp.addr + (y * g->tmp.line_length + x * (g->tmp.bits_per_pixel / 8));
		color = *(unsigned int *)src;
	}
	return (color);
}

int	get_horizontal_pixel(int direction, int x, int y)
{
	if (!direction)
		return (x % SIZE_PIXEL);
	else if (direction == 1)
		return (SIZE_PIXEL - (x % SIZE_PIXEL));
	else if (direction == 2)
		return (SIZE_PIXEL - (y % SIZE_PIXEL));
	return (y % SIZE_PIXEL);
}

float	get_math_ray(t_global *g, int i)
{
	float	mult;

	g->ray[i].slice = SIZE_PIXEL * VRES / g->ray[i].finaldistance;
	if (g->ray[i].slice > VRES)
		g->ray[i].slice = VRES;
	else if (g->ray[i].slice < 1)
		g->ray[i].slice = 0;
	g->ray[i].curr = 0;
	mult = 1.0 / VRES * g->ray[i].slice;
	g->ray[i].offset = (VRES - g->ray[i].slice) / 2;
	if (g->ray[i].slice)
		g->ray[i].next = SIZE_PIXEL / g->ray[i].slice;
	else
		g->ray[i].next = 0;
	g->ray[i].modulo_pixel = get_horizontal_pixel(g->ray[i].direction, g->ray[i].finaldistancex, g->ray[i].finaldistancey);
	return (mult);
}

int	get_color(int color, float mult)
{
	int r;
	int g;
	int b;

	r = ((color >> 16) & 0xFF) * mult;
	g = ((color >> 8) & 0xFF) * mult;
	b = (color & 0xFF) * mult;
	return (r << 16 | g << 8 | b);
}


void    put_ray_1(t_global *g, int x, int i)
{
    int z;

    z = 0;
	//printf("offset %d\n", g->ray[i].offset);
    while (z < g->ray[i].offset)
    {
        my_mlx_pixel_put(&g->data, x, z, 0x000000);
		my_mlx_pixel_put(&g->data, x + 1, z, 0x000000);
		my_mlx_pixel_put(&g->data, x + 2, z, 0x000000);
		my_mlx_pixel_put(&g->data, x + 3, z, 0x000000);
        z++;
    }
}

void    put_ray_2(t_global *g, int x, int i, float mult)
{
    int color;

    while (g->ray[i].iter < g->ray[i].slice)
	{
		color = get_color(get_color_pixel(g, g->txt[g->ray[i].direction].img, g->ray[i].modulo_pixel, g->ray[i].curr), mult);
		my_mlx_pixel_put(&g->data, x, g->ray[i].iter + g->ray[i].offset, color);
		my_mlx_pixel_put(&g->data, x + 1, g->ray[i].iter + g->ray[i].offset, color);
		my_mlx_pixel_put(&g->data, x + 2, g->ray[i].iter + g->ray[i].offset, color);
		my_mlx_pixel_put(&g->data, x + 3, g->ray[i].iter + g->ray[i].offset, color);
		g->ray[i].curr += g->ray[i].next;
		g->ray[i].iter++;
		x += 4;
	}
}

void    put_ray_3(t_global *g, int x, int i)
{
    int color;

    color = 0xB8B09A;
	while (g->ray[i].iter + g->ray[i].offset < VRES)
	{
		my_mlx_pixel_put(&g->data, x, g->ray[i].iter + g->ray[i].offset, color);
		my_mlx_pixel_put(&g->data, x + 1, g->ray[i].iter + g->ray[i].offset, color);
		my_mlx_pixel_put(&g->data, x + 2, g->ray[i].iter + g->ray[i].offset, color);
		my_mlx_pixel_put(&g->data, x + 3, g->ray[i].iter + g->ray[i].offset, color);
		g->ray[i].iter++;
	}
}

int	put_ray(t_global *g)
{
	int     i;
	int     x;
	int     color;
	float	mult;

	i = 0;
	x = 0;
	while (i < NUM_RAYS)
	{
		color = 0x00FF00;
		g->ray[i].iter = 0;
		mult = get_math_ray(g, i);
        put_ray_1(g, x, i);
	    color = get_color(color, mult);
        put_ray_1(g, x, i);
        put_ray_2(g, x, i, mult);
        put_ray_3(g, x, i);
	    i++;
	    x += 4;
	}
	mlx_put_image_to_window(g->mlx, g->mlx_win, g->data.img, 0, 0);
	return (1);
}