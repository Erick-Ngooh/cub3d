/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_line.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: engooh <engooh@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/30 18:00:10 by sredjini          #+#    #+#             */
/*   Updated: 2022/11/19 15:30:21 by engooh           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

 /*void   line_float()
 {
    int x_origin;
    int y_origin;
    int x_end;
    int y_end;

    float dx= x_end -x_origin;
    float dy = y_end - y_origin;
    float m = dy/dx;
    float e = 0;

    while (x_origin < x_end)
    {
        // putpixel x y
        x_origin++;
        e = e -m;
        if (e < -0.5)
        {
            y_end--;
            e = e + 1;
        }
    }
    
 }

static void    bresenham_1()
{
	int x1;
    int y1; 
    int x2;
    int y2;
    int e; 
    int dx;
    int dy;
    x2 = g->player_s.pos[0] + cos(g->player_s.rotation_angle)  * 30;
	y2 = g->player_s.pos[1] + sin(g->player_s.rotation_angle)  * 30;
	y1 = g->player_s.pos[1];
	x1 = g->player_s.pos[0];
    e = absolute(x2 - x1);
    dx = 2*e;
    dy = 2 * absolute(y2 - y1);
   while (x1 <= x2)
    {
        my_mlx_pixel_put(&g->data, x1, y1, 0X0CC544);
        x1++;
        e -= dy;
        if (e < 0)
        {
            y1++;
            e += dx;
        }
    }
}


static void    bresenham_2()
{
	int x1;
    int y1; 
    int x2;
    int y2;
    int e; 
    int dx;
    int dy;
    x2 = g->player_s.pos[0] + cos(g->player_s.rotation_angle)  * 30;
	y2 = g->player_s.pos[1] + sin(g->player_s.rotation_angle)  * 30;
	y1 = get_g()->player_s.pos[1];
	x1 = get_g()->player_s.pos[0];
    e = absolute(x2 - x1);
    dx = 2*e;
    dy = 2 * absolute(y2 - y1);
   while (x1 >= x2)
    {
    	my_mlx_pixel_put(&get_g()->data, x1, y1, 0X0CC544);
        x1--;
        e -= dy;
        if (e < 0)
        {
            y1++;
            e += dx;
        }
    }
}


static void    bresenham_3()
{

	int x1;
    int y1; 
    int x2;
    int y2;
    int e; 
    int dx;
    int dy;
    x2 = get_g()->player_s.pos[0] + cos(get_g()->player_s.rotation_angle)  * 30;
	y2 = get_g()->player_s.pos[1] + sin(get_g()->player_s.rotation_angle)  * 30;
	y1 = get_g()->player_s.pos[1];
	x1 = get_g()->player_s.pos[0];
    e = absolute(x2 - x1);
    dx = 2*e;
    dy = 2 * absolute(y2 - y1);
    
    while (x1 >= x2)
    {
        my_mlx_pixel_put(&get_g()->data, x1, y1, 0X0CC544);
        x1--;
        e -= dy;
        if (e < 0)
        {
            y1--;
            e += dx;
        }
    }
}

static void    bresenham_4()
{
	int x1;
    int y1; 
    int x2;
    int y2;
    int e; 
    int dx;
    int dy;
    x2 = get_g()->player_s.pos[0] + cos(get_g()->player_s.rotation_angle)  * 30;
	y2 = get_g()->player_s.pos[1] + sin(get_g()->player_s.rotation_angle)  * 30;
	y1 = get_g()->player_s.pos[1];
	x1 = get_g()->player_s.pos[0];
    e = (x2 - x1);
    dx = 2*e;
    dy = 2 * (y2 - y1);
   while (x1 <= x2)
    {
        x1++;
        e -= dy;
        if (e < 0)
        {
            y1--;
            e += dx;
        }
    }
}*/


int absolute(int nbr)
{
	if (nbr < 0)
		return (nbr * -1);
	return (nbr);
}

void    bresenham(t_global *g)
{
    
    int x1; // origin
    int y1; // origin 
    int x2; // end
    int y2; // end
	int	ex;
	int	ey;
	int	dx;
	int	dy;
	int	Dx;
	int	Dy;
	int	i;
	int	Xincr;
	int	Yincr;

   // printf("ICI1\n");
    x2 = g->player_s.pos[0] + cos(g->player_s.rotation_angle)  * 30;
	y2 = g->player_s.pos[1] + sin(g->player_s.rotation_angle)  * 30;
	y1 = g->player_s.pos[1];
	x1 = g->player_s.pos[0];
	ex = absolute(x2 - x1);
	ey = absolute(y2 - y1);
	Xincr = 1;
	Yincr = 1;
	dx = 2 * ex;
	dy = 2 * ey;
	Dx = ex;
	Dy = ey;
	i = 0;

	if (x1>x2)
		Xincr = -1;
	if (y1 > y2)
		Yincr = -1;
	if (Dx > Dy)
	{
		while (i <= Dx)
		{
			my_mlx_pixel_put(&g->data, x1, y1, 0X0CC544);
			i++;
			x1 += Xincr;
			ex -= dy;
			
			if (ex < 0)
			{
				y1 += Yincr;
				ex += dx;
			}
		}	
	}
	if (Dx < Dy)
	{
		while (i <= Dy)
		{
			my_mlx_pixel_put(&g->data, x1, y1, 0X0CC544);
			i++;
			y1 += Yincr;
			ey -= dx;

			if (ey < 0)
			{
				x1 += Xincr;
				ey += dy;
			}
		}
	}

	mlx_put_image_to_window(g->mlx, g->mlx_win, g->data.img, 0, 0);
}   


void    rayon(float angle, t_global *g)
{
    
    int x1; // origin
    int y1; // origin 
    int x2; // end
    int y2; // end
	int	ex;
	int	ey;
	int	dx;
	int	dy;
	int	Dx;
	int	Dy;
	int	i;
	int	Xincr;
	int	Yincr;

   // printf("ICI1\n");
    x2 = g->player_s.pos[0] + cos(angle)  * 70;
	y2 = g->player_s.pos[1] + sin(angle)  * 70;
	y1 = g->player_s.pos[1];
	x1 = g->player_s.pos[0];
	ex = absolute(x2 - x1);
	ey = absolute(y2 - y1);
	Xincr = 1;
	Yincr = 1;
	dx = 2 * ex;
	dy = 2 * ey;
	Dx = ex;
	Dy = ey;
	i = 0;

	if (x1>x2)
		Xincr = -1;
	if (y1 > y2)
		Yincr = -1;
	if (Dx > Dy)
	{
		while (i <= Dx)
		{
			my_mlx_pixel_put(&g->data, x1, y1, 0X0CC544);
			i++;
			x1 += Xincr;
			ex -= dy;
			
			if (ex < 0)
			{
				y1 += Yincr;
				ex += dx;
			}
		}	
	}
	if (Dx < Dy)
	{
		while (i <= Dy)
		{
			my_mlx_pixel_put(&g->data, x1, y1, 0X0CC544);
			i++;
			y1 += Yincr;
			ey -= dx;

			if (ey < 0)
			{
				x1 += Xincr;
				ey += dy;
			}
		}
	}

	mlx_put_image_to_window(g->mlx, g->mlx_win, g->data.img, 0, 0);
}   

void    bresenham2(float x2, float y2, t_global *g)
{
    
    float x1; // origin
    float y1; // origin 
    //float x2; // end
    //float y2; // end
	float	ex;
	float	ey;
	float	dx;
	float	dy;
	float	Dx;
	float	Dy;
	int	i;
	int	Xincr;
	int	Yincr;

   // printf("ICI1\n");
    //x2 = g->player_s.pos[0] + cos(g->player_s.rotation_angle)  * 30;
	//y2 = g->player_s.pos[1] + sin(g->player_s.rotation_angle)  * 30;
	y1 = g->player_s.pos[1];
	x1 = g->player_s.pos[0];
	ex = absolute(x2 - x1);
	ey = absolute(y2 - y1);
	Xincr = 1;
	Yincr = 1;
	dx = 2 * ex;
	dy = 2 * ey;
	Dx = ex;
	Dy = ey;
	i = 0;

	if (x1>x2)
		Xincr = -1;
	if (y1 > y2)
		Yincr = -1;
	if (Dx > Dy)
	{
		while (i <= Dx)
		{
			my_mlx_pixel_put(&g->data, x1, y1, 0X0CC544);
			i++;
			x1 += Xincr;
			ex -= dy;
			
			if (ex < 0)
			{
				y1 += Yincr;
				ex += dx;
			}
		}	
	}
	if (Dx < Dy)
	{
		while (i <= Dy)
		{
			my_mlx_pixel_put(&g->data, x1, y1, 0X0CC544);
			i++;
			y1 += Yincr;
			ey -= dx;

			if (ey < 0)
			{
				x1 += Xincr;
				ey += dy;
			}
		}
	}
	mlx_put_image_to_window(g->mlx, g->mlx_win, g->data.img, 0, 0);
}   

int	circle_check(t_global *g, int cx, int cy, int r)
{

    int x;
    int e;
    int y;

    y = r;
    x = 0;
    e = 5 - 4*r;
    if (cx > HRES || cy > VRES)
        return (0);
    if (cx <= 0 || cy <= 0)
        return (0);
    while (x <= y)
    {
        if (g->map_s.map[(y + cy) / SIZE_PIXEL][(x + cx) / SIZE_PIXEL] == '1')
			 return (0);
		else if (g->map_s.map[(y + cy) / SIZE_PIXEL][(x + cx) / SIZE_PIXEL]  == '1')
			 return (0);
        else if (g->map_s.map[(y + cy) / SIZE_PIXEL][(x + cx) / SIZE_PIXEL]  == '1')    
			 return (0);
        else if (g->map_s.map[(y + cy) / SIZE_PIXEL][(x + cx) / SIZE_PIXEL]  == '1')
			 return (0);
        else if ( g->map_s.map[(y + cx) / SIZE_PIXEL][(x + cy) / SIZE_PIXEL]  == '1')
			 return (0);
    	else if ( g->map_s.map[(y + cx) / SIZE_PIXEL][(x + cy) / SIZE_PIXEL] == '1')
			 return (0);
        else if ( g->map_s.map[(y + cx) / SIZE_PIXEL][(x + cy) / SIZE_PIXEL] == '1')
			 return (0);
        else if ( g->map_s.map[(y + cx) / SIZE_PIXEL][(x + cy) / SIZE_PIXEL] == '1')
			 return (0);
        e += 8*x + 4;
        x++;
        if (e > 0)
        {
            y--;
            e -= 8 * y;
        }
    }
	return (1);
   }