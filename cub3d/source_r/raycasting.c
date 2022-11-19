/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: engooh <engooh@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/03 18:20:57 by engooh            #+#    #+#             */
/*   Updated: 2022/11/19 21:13:56 by engooh           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

int	size_x(t_global *g, int x, int y)
{
	while (g->map_s.map[y][x])
		x++;
	return (x);	
}

int size_y(t_global *g, int y)
{
	while (g->map_s.map[y])
		y++;
	return (y);	
}

int	is_wall(t_global *g, int x_pixel, int y_pixel)
{
	int x;	
	int y;

	x = (x_pixel) / SIZE_PIXEL;
	y = (y_pixel) / SIZE_PIXEL;


	if (x < 0 ||  y < 0)
		return (0);
	if (x_pixel >= size_x(g, g->player_s.pos[0] / SIZE_PIXEL, g->player_s.pos[1] / SIZE_PIXEL) * SIZE_PIXEL || y_pixel >= size_y(g, g->player_s.pos[1] / SIZE_PIXEL) * SIZE_PIXEL)
		return (-1);
	if (g->map_s.map[y][x] == '1')
		return (0);
	return (1);
}

double	ft_distance(float x1, float y1, float x2, float y2)
{
	return(sqrt((x2 - x1) * (x2 -x1)  + (y2 -y1) * (y2 -y1)));
}

void	init_struct_ray(t_global *g, int i)
{
	g->ray[i].x_step = 0;
	g->ray[i].y_step = 0;
	g->ray[i].tan_ray = 0;
	g->ray[i].first_xh = 0;
	g->ray[i].first_yh = 0;
	g->ray[i].first_xv = 0;
	g->ray[i].first_yv = 0;
	g->ray[i].signe_x = 1;
	g->ray[i].signe_y = 1;
	g->ray[i].signe_xv = 1;
	g->ray[i].signe_yv = 1; 
	g->ray[i].east = 1;
	g->ray[i].distancehorz = 0;
	g->ray[i].distancevert = 0;
	g->ray[i].finaldistance = 0;
	g->ray[i].finaldistancex = 0;
	g->ray[i].finaldistancey = 0;
	g->ray[i].see = -1;;
}

void	dda_pi3(t_global *g, float rayangle, int i)
{
	g->ray[i].signe_x = -1;
	g->ray[i].signe_y = -1;
	g->ray[i].signe_xv = 1;
	g->ray[i].signe_yv = 1;
	g->ray[i].tan_ray = tan(rayangle);
	g->ray[i].first_yh = floor(g->player_s.pos[1] / SIZE_PIXEL) * SIZE_PIXEL;
	g->ray[i].first_xh = g->player_s.pos[0] + (g->ray[i].first_yh - g->player_s.pos[1]) / g->ray[i].tan_ray;
	g->ray[i].first_xv = ((floor(g->player_s.pos[0] / SIZE_PIXEL)+ 1)* SIZE_PIXEL);
	g->ray[i].first_yv = g->player_s.pos[1] + (g->ray[i].first_xv - g->player_s.pos[0]) * g->ray[i].tan_ray;
}

void	dda_pi2(t_global *g, float rayangle, int i)
{
	g->ray[i].signe_x = 1;
	g->ray[i].signe_y = 1;
	g->ray[i].signe_xv = 1;
	g->ray[i].signe_yv = 1;
	g->ray[i].tan_ray = tan(rayangle);
	g->ray[i].first_yh = floor(g->player_s.pos[1] / SIZE_PIXEL + 1) * SIZE_PIXEL;
	g->ray[i].first_xh = g->player_s.pos[0] + (g->ray[i].first_yh - g->player_s.pos[1]) / g->ray[i].tan_ray;
	g->ray[i].first_xv = (floor(g->player_s.pos[0] / SIZE_PIXEL)+ 1)* SIZE_PIXEL;
	g->ray[i].first_yv = g->player_s.pos[1] + (g->ray[i].first_xv - g->player_s.pos[0]) * g->ray[i].tan_ray;
}

void	dda_pi_pi2(t_global *g, float rayangle, int i)
{
	g->ray[i].signe_x = 1;
	g->ray[i].signe_y = 1;
	g->ray[i].signe_xv = -1;
	g->ray[i].signe_yv = -1;
	g->ray[i].tan_ray = tan(rayangle);
	g->ray[i].first_yh = floor(g->player_s.pos[1] / SIZE_PIXEL + 1) * SIZE_PIXEL;
	g->ray[i].first_xh = g->player_s.pos[0] + (g->ray[i].first_yh - g->player_s.pos[1]) / g->ray[i].tan_ray;
	g->ray[i].first_xv = (floor(g->player_s.pos[0] / SIZE_PIXEL))  * SIZE_PIXEL;
	g->ray[i].first_yv = g->player_s.pos[1] + (g->ray[i].first_xv - g->player_s.pos[0]) * g->ray[i].tan_ray;
}

void	dda_pi_pi3(t_global *g, float rayangle, int i)
{
	g->ray[i].signe_x = -1;
	g->ray[i].signe_y = -1;
	g->ray[i].signe_xv = -1;
	g->ray[i].signe_yv = -1;
	g->ray[i].tan_ray = tan(rayangle);
	g->ray[i].first_yh = floor(g->player_s.pos[1] / SIZE_PIXEL) * SIZE_PIXEL;
	g->ray[i].first_xh = g->player_s.pos[0] + (g->ray[i].first_yh - g->player_s.pos[1]) / g->ray[i].tan_ray;
	g->ray[i].first_xv = ((floor(g->player_s.pos[0] / SIZE_PIXEL))* SIZE_PIXEL);
	g->ray[i].first_yv = g->player_s.pos[1] + (g->ray[i].first_xv - g->player_s.pos[0]) * g->ray[i].tan_ray;
}

bool	compare_double(float a, float b)
{
	if (b == DPI && a < 1)
		return (a < 0.000001 && a > -0.1);
	return (a - b < 0.000001 && a - b > -0.1);
}

int		cast_ray_horizontal_utils(t_global *g, int ret, int i)
{
		if ((g->ray[i].first_xh < HRES || g->ray[i].first_yh < VRES))
		{
			if (g->ray[i].y_step < 0)
				ret = is_wall(g, g->ray[i].first_xh, g->ray[i].first_yh -32);
			else
				ret = is_wall(g, g->ray[i].first_xh , g->ray[i].first_yh );
			if (!ret)
			{
				g->ray[i].distancehorz = ft_distance(g->player_s.pos[0], g->player_s.pos[1], g->ray[i].first_xh, g->ray[i].first_yh);
				if (!g->ray[i].finaldistance || (g->ray[i].distancevert && g->ray[i].distancevert > g->ray[i].distancehorz))
				{
					g->ray[i].finaldistance = g->ray[i].distancehorz;
				}
				return (0);
			}
			if(ret == -1)
				return (0);
			g->ray[i].first_yh += g->ray[i].y_step;
			g->ray[i].first_xh += g->ray[i].x_step;
		}
		else 
			return (0);
		return (1);	
}

void	cast_ray_horizontal(t_global *g, int i)
{
	int ret;
	int y;

	y = -1;
	ret = 0;
	g->ray[i].y_step = SIZE_PIXEL * g->ray[i].signe_y;
	g->ray[i].x_step = (SIZE_PIXEL / g->ray[i].tan_ray ) * g->ray[i].signe_x;
	while (++y < 500)
	{ 
		if (!cast_ray_horizontal_utils(g, ret, i))
			return ;
	}
}


int	cast_ray_vertical_utils(t_global *g, int ret, int i)
{
		if ((g->ray[i].first_xv < HRES || g->ray[i].first_yv < VRES))
		{
			if (g->ray[i].x_step < 0)
				ret = is_wall(g, g->ray[i].first_xv -32  , g->ray[i].first_yv );
			else
				ret = is_wall(g, g->ray[i].first_xv , g->ray[i].first_yv );
			if (!ret)
			{
				g->ray[i].distancevert = ft_distance(g->player_s.pos[0], g->player_s.pos[1], g->ray[i].first_xv, g->ray[i].first_yv);
				if (!g->ray[i].finaldistance || (g->ray[i].distancehorz && g->ray[i].distancehorz > g->ray[i].distancevert))
				{
					g->ray[i].finaldistance = g->ray[i].distancevert;
				}
				return (0);
			}
			if (ret == -1)
				return (0);
			g->ray[i].first_yv += g->ray[i].y_step;
			g->ray[i].first_xv += g->ray[i].x_step;
		}
		else 
			return (0);
		return (1);
}

void	cast_ray_vertical(t_global *g, int i)
{
	int ret;
	int	y;

	y = -1;
	ret = 0;
	g->ray[i].x_step = SIZE_PIXEL * g->ray[i].signe_xv;
	g->ray[i].y_step = SIZE_PIXEL * g->ray[i].tan_ray * g->ray[i].signe_yv;
	while (++y < 500)
		if (!cast_ray_vertical_utils(g, ret, i))
			return ;
}

void	set_ray_angle(t_global *g,float rayangle, int i)
{
	if (rayangle <= PI2 && rayangle >= 0)
	{
		dda_pi2(g, rayangle, i);
		g->ray[i].direction = 1;
	}
	else if (rayangle <= PI && rayangle >= PI2)
	{
		dda_pi_pi2(g, rayangle, i);
		g->ray[i].direction = 2;
	}
	else if (rayangle >= PI && rayangle <= PI3)
	{
		dda_pi_pi3(g, rayangle, i);
		g->ray[i].direction = 3;
	}
	else if (rayangle >= PI3 && rayangle <= DPI)
	{
		dda_pi3(g, rayangle, i);
		g->ray[i].direction = 4;
	}
	else
	{
		g->ray[i].direction = 1;
		dda_pi3(g, rayangle, i);
	}
}

void	cast_ray(t_global *g, float rayangle, int i)
{
	set_ray_angle(g, rayangle, i);
	cast_ray_horizontal(g, i);
	cast_ray_vertical(g, i);
	if (g->ray[i].finaldistance == g->ray[i].distancehorz)
	{
		if (g->ray[i].direction > 2)
			g->ray[i].direction = 0;
		else
			g->ray[i].direction = 1;
		g->ray[i].finaldistancex = g->ray[i].first_xh;
		g->ray[i].finaldistancey = g->ray[i].first_yh;
		g->ray[i].see = 1; // Si see = 1 cela veut dire que le hit est en horz
	}
	else if (g->ray[i].finaldistance == g->ray[i].distancevert)
	{
		if (g->ray[i].direction == 1 || g->ray[i].direction == 4)
			g->ray[i].direction = 3;
		else
			g->ray[i].direction = 2;
		g->ray[i].finaldistancex = g->ray[i].first_xv;
		g->ray[i].finaldistancey = g->ray[i].first_yv;
		g->ray[i].see = 0; // Si see = 0 cela veut dire que le hit est en vertical
	}
}

float	deg_to_rad(float angle, float degree)
{
	angle += (RAD * degree);
	if (angle < 0)
		angle += 2 * PI;
	if (angle > 2 * PI)
		angle -= 2 * PI;
	return (angle);

}

int	full_cast_ray(t_global *g)
{
	int i;
	float ray;


	i = -1;
	g->ray = malloc(sizeof(t_ray) * (NUM_RAYS));
	ray = g->player_s.rotation_angle -(FOV/2);
	while(++i < NUM_RAYS)
	{
		init_struct_ray(g, i);
		cast_ray(g, ray, i);
		g->ray[i].rayAngle = ray;
		ray = secure_radians(ray ,FOV / NUM_RAYS); //  PB LANGLE PASSE A 7DEGRE PAS NORMAL EN GROS IL FAUT SECURE ICI !
	}
	return (0);
}

