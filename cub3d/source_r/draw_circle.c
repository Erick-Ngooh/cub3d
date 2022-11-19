/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_circle.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: engooh <engooh@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/30 20:19:53 by sredjini          #+#    #+#             */
/*   Updated: 2022/11/19 17:48:53 by engooh           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

void    circle(int cx, int cy, int r, t_global *g)
{
    // cx centre du rayon cy hauteur et r rayon en pixel
    
    int x;
    int e;
    int y;

    y = r;
    x = 0;
    e = 5 - 4*r;
    
    if (cx > HRES || cy > VRES)
        return ;
    if (cx <= 0 || cy <= 0)
        return ;
    while (x <= y)
    {
        my_mlx_pixel_put(&g->data, x + cx, y + cy, 0X00FF00);
        my_mlx_pixel_put(&g->data, -x + cx, y + cy, 0X00FF00);
        my_mlx_pixel_put(&g->data, -x + cx, -y + cy, 0X00FF00);
        my_mlx_pixel_put(&g->data, (x + cx), (-y + cy), 0X00FF00);
        //pixel x + cx , y + cy
        // pixel -x + cx, y +cy
        // pixel -x + cx, -y +cy
        // //pixel x + cx , y + -cy
        my_mlx_pixel_put(&g->data, -y + cx, x + cy, 0X00FF00);
        my_mlx_pixel_put(&g->data, -y + cx, -x + cy, 0X00FF00);
        my_mlx_pixel_put(&g->data, y + cx, x + cy, 0X00FF00);
        my_mlx_pixel_put(&g->data, y + cx, -x + cy, 0X00FF00);
        // pixel -y + cx , x + cy
        //pixel -y + cx , -x + cy
        // pixel y + cx , x +cy
        // pixel y + cx -x + cy
        e += 8*x + 4;
        x++;
        if (e > 0)
        {
            y--;
            e -= 8 * y;
        }
    }
   // bresenham();
   // update();
}

void    circle2(int cx, int cy, int r, t_global *g)
{
    // cx centre du rayon cy hauteur et r rayon en pixel
    
    int x;
    int e;
    int y;

    y = r;
    x = 0;
    e = 5 - 4*r;
   // printf("ICI cx; %d cy; %d\n", cx, cy);
    if (cx > HRES || cy > VRES)
        return ;
    if (cx <= 0 || cy <= 0)
        return ;
    while (x <= y)
    {
		int col = 0xFF00FF;

        my_mlx_pixel_put(&g->data, x + cx, y + cy, col);
        my_mlx_pixel_put(&g->data, -x + cx, y + cy, col);
        my_mlx_pixel_put(&g->data, -x + cx, -y + cy, col);
        my_mlx_pixel_put(&g->data, (x + cx), (-y + cy), col);
        //pixel x + cx , y + cy
        // pixel -x + cx, y +cy
        // pixel -x + cx, -y +cy
        // //pixel x + cx , y + -cy
        my_mlx_pixel_put(&g->data, -y + cx, x + cy, col);
        my_mlx_pixel_put(&g->data, -y + cx, -x + cy, col);
        my_mlx_pixel_put(&g->data, y + cx, x + cy, col);
        my_mlx_pixel_put(&g->data, y + cx, -x + cy, col);
        // pixel -y + cx , x + cy
        //pixel -y + cx , -x + cy
        // pixel y + cx , x +cy
        // pixel y + cx -x + cy
        e += 8*x + 4;
        x++;
        if (e > 0)
        {
            y--;
            e -= 8 * y;
        }
		(void)col;
    }
   // bresenham();
   // update();
}

void    circle3(int cx, int cy, int r, int col, t_global *g)
{
    // cx centre du rayon cy hauteur et r rayon en pixel 
    int x;
    int e;
    int y;

    y = r;
    x = 0;
    e = 5 - 4*r;
   // printf("ICI cx; %d cy; %d\n", cx, cy);
    if (cx > HRES || cy > VRES)
        return ;
    if (cx <= 0 || cy <= 0)
        return ;
    while (x <= y)
    {
        my_mlx_pixel_put(&g->data, x + cx, y + cy, col);
        my_mlx_pixel_put(&g->data, -x + cx, y + cy, col);
        my_mlx_pixel_put(&g->data, -x + cx, -y + cy, col);
        my_mlx_pixel_put(&g->data, (x + cx), (-y + cy), col);
        //pixel x + cx , y + cy
        // pixel -x + cx, y +cy
        // pixel -x + cx, -y +cy
        // //pixel x + cx , y + -cy
        my_mlx_pixel_put(&g->data, -y + cx, x + cy, col);
        my_mlx_pixel_put(&g->data, -y + cx, -x + cy, col);
        my_mlx_pixel_put(&g->data, y + cx, x + cy, col);
        my_mlx_pixel_put(&g->data, y + cx, -x + cy, col);
        // pixel -y + cx , x + cy
        //pixel -y + cx , -x + cy
        // pixel y + cx , x +cy
        // pixel y + cx -x + cy
        e += 8*x + 4;
        x++;
        if (e > 0)
        {
            y--;
            e -= 8 * y;
        }
		(void)col;
    }
   // bresenham();
   // update();
}


