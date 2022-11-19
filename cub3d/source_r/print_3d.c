
#include "../include/cub3d.h"

unsigned int get_color_pixel(t_global *g, void *img, int x, int y)
{
	char	*src;
	int		color;

	color = 0xFFFFFF;
	if (x < 0 || y < 0 || x > HRES || y > VRES)
		return (color);
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

float	fisheye_fix(float angle, float diff, float slice)
{
	angle = secure_radians(angle, -diff);
	return (slice * cos(angle));
}

float	get_math_ray(t_global *g, int i)
{
	float	mult;
	float	offpx;
	float 	og;

	offpx = 0;
	g->ray[i].finaldistance = fisheye_fix(g->player_s.rotation_angle,
		g->ray[i].rayAngle, g->ray[i].finaldistance);
	g->ray[i].slice = SIZE_PIXEL * VRES / g->ray[i].finaldistance;
	og = g->ray[i].slice;
	if (g->ray[i].slice > VRES)
	{
		offpx = (g->ray[i].slice - VRES) / 2;
		g->ray[i].slice = VRES;
	}
	mult = 1.0 / VRES * g->ray[i].slice;
	g->ray[i].offset = (VRES - g->ray[i].slice) / 2;
	//g->ray[i].next = (float)SIZE_PIXEL / g->ray[i].slice;
	g->ray[i].next = (float)SIZE_PIXEL / og;
	g->ray[i].curr = g->ray[i].next * offpx;
	g->ray[i].modulo_pixel = get_horizontal_pixel(g->ray[i].direction, g->ray[i].finaldistancex, g->ray[i].finaldistancey);
	g->mult = mult;
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

void	draw_sky(t_global *g, int x, int i, int color)
{
	int z;

	z = 0;
	while (z < g->ray[i].offset)
	{
			my_mlx_pixel_put(&g->data, x, z, color);
			my_mlx_pixel_put(&g->data, x + 1, z, color);
			my_mlx_pixel_put(&g->data, x + 2, z, color);
			my_mlx_pixel_put(&g->data, x + 3, z, color);
			z++;
	}
}

void	draw_walls(t_global *g, int i, int x, int color)
{
	while (g->ray[i].iter < g->ray[i].slice)
		{
			color = get_color(get_color_pixel(g, g->txt[g->ray[i].direction].img,
				g->ray[i].modulo_pixel, g->ray[i].curr), g->mult);
			my_mlx_pixel_put(&g->data, x, g->ray[i].iter + g->ray[i].offset, color);
			my_mlx_pixel_put(&g->data, x + 1, g->ray[i].iter + g->ray[i].offset, color);
			my_mlx_pixel_put(&g->data, x + 2, g->ray[i].iter + g->ray[i].offset, color);
			my_mlx_pixel_put(&g->data, x + 3, g->ray[i].iter + g->ray[i].offset, color);
			g->ray[i].curr += g->ray[i].next;
			g->ray[i].iter++;
		}
}

int	put_ray(t_global *g, int i, int x, int color)
{
	while (i < NUM_RAYS)
	{

		g->ray[i].iter = 0;
		get_math_ray(g, i);
		draw_sky(g, x, i, 0x000000);
		draw_walls(g, i, x, 0x000000);
		color = 0xB8B09A;
		while (g->ray[i].iter + g->ray[i].offset < VRES)
		{
			my_mlx_pixel_put(&g->data, x, g->ray[i].iter + g->ray[i].offset, color);
			my_mlx_pixel_put(&g->data, x + 1, g->ray[i].iter + g->ray[i].offset, color);
			my_mlx_pixel_put(&g->data, x + 2, g->ray[i].iter + g->ray[i].offset, color);
			my_mlx_pixel_put(&g->data, x + 3, g->ray[i].iter + g->ray[i].offset, color);
			g->ray[i].iter++;
		}
		i++;
		x += 4;
	}
	mlx_put_image_to_window(g->mlx, g->mlx_win, g->data.img, 0, 0);
	return (1);
}
