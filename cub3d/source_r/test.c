/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: engooh <engooh@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/21 13:35:29 by engooh            #+#    #+#             */
/*   Updated: 2022/11/19 20:59:55 by engooh           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"



void	my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	char	*dst;

	//printf("debug x %d y %d\n", x, y);
	if (x < 0 || y < 0)
		return ;
	if (x + (y * HRES) < (HRES*VRES) && x < HRES && y < VRES)
	{
		dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
		*(unsigned int*)dst = color;
	}
}


void draw_wall(int x_start, int y_start, t_global *g)
{
	int	x_end;
	int	y_end;


	x_end = x_start + SIZE_PIXEL;
	y_end = y_start + SIZE_PIXEL;
	while (y_start < y_end)
	{
		while (x_start < x_end)
		{
			if (x_start >= x_end)
				my_mlx_pixel_put(&g->data, x_start, y_start, 0X000000);
			else
				my_mlx_pixel_put(&g->data, x_start, y_start, 0XFFFFFF);
			x_start++;
		}
		x_start = x_start - (SIZE_PIXEL);
		y_start++;
	}
}

void draw_floor(int x_start, int y_start, t_global *g)
{
	int	x_end;
	int	y_end;

	x_end = x_start + SIZE_PIXEL;
	y_end = y_start + SIZE_PIXEL ;
	while (y_start < y_end)
	{
		while (x_start < x_end)
		{
			if (x_start >= x_end)
				my_mlx_pixel_put(&g->data, x_start, y_start, 0X000000);
			else
				my_mlx_pixel_put(&g->data, x_start, y_start, 0X03A1FC);
			x_start++;
		}
		x_start = x_start - (SIZE_PIXEL);
		y_start++;
	}
}

void	draw_map_move_1(int x, int y, t_global *g)
{
	if (g->map_s.map[y][x])
		draw_floor(x * SIZE_PIXEL, y * SIZE_PIXEL, g);
	if (g->map_s.map[y][x + 1] == '0' || g->map_s.map[y][x + 1] == 'P')
		draw_floor((x + 1) * SIZE_PIXEL, y * SIZE_PIXEL, g);
	else if (g->map_s.map[y][x + 1] == '1')
		draw_wall((x + 1) * SIZE_PIXEL, y * SIZE_PIXEL, g);
	if (g->map_s.map[y][x - 1] == '0' || g->map_s.map[y][x - 1] == 'P') 
		draw_floor((x - 1) * SIZE_PIXEL, y * SIZE_PIXEL, g);
	else if (g->map_s.map[y][x - 1] == '1')
		draw_wall((x - 1) * SIZE_PIXEL, y * SIZE_PIXEL, g);
	if (g->map_s.map[y + 1 ][x] == '0' || g->map_s.map[y + 1][x] == 'P') 
		draw_floor(x * SIZE_PIXEL, (y + 1) * SIZE_PIXEL, g);
	else if (g->map_s.map[y + 1][x] == '1')
		draw_wall(x * SIZE_PIXEL, (y + 1) * SIZE_PIXEL, g);
	if (g->map_s.map[y + 1][x + 1] == '0' || g->map_s.map[y + 1][x + 1] == 'P') 
		draw_floor((x + 1) * SIZE_PIXEL, (y + 1) * SIZE_PIXEL, g);
	else if (g->map_s.map[y + 1][x + 1] == '1')
		draw_wall((x + 1) * SIZE_PIXEL, (y + 1) * SIZE_PIXEL, g);
}

void	draw_map_move_2(int x, int y, t_global *g)
{
	if (g->map_s.map[y + 1][x - 1] == '0' || g->map_s.map[y + 1][x + 1] == 'P') 
		draw_floor((x - 1) * SIZE_PIXEL, (y + 1) * SIZE_PIXEL, g);
	else if (g->map_s.map[y + 1][x - 1] == '1')
		draw_wall((x - 1) * SIZE_PIXEL, (y + 1) * SIZE_PIXEL, g);
	if (g->map_s.map[y - 1][x] == '0' || g->map_s.map[y - 1][x] == 'P') 
		draw_floor(x * SIZE_PIXEL, (y - 1) * SIZE_PIXEL, g);
	else if (g->map_s.map[y - 1][x] == '1')
		draw_wall(x * SIZE_PIXEL, (y - 1) * SIZE_PIXEL, g);
	if (g->map_s.map[y - 1][x + 1] == '0' || g->map_s.map[y - 1][x + 1] == 'P') 
		draw_floor((x + 1) * SIZE_PIXEL, (y - 1) * SIZE_PIXEL, g);
	else if (g->map_s.map[y - 1][x + 1] == '1')
		draw_wall((x + 1) * SIZE_PIXEL, (y - 1) * SIZE_PIXEL, g);
	if (g->map_s.map[y - 1][x - 1] == '0' || g->map_s.map[y - 1][x - 1] == 'P') 
		draw_floor((x - 1) * SIZE_PIXEL, (y - 1) * SIZE_PIXEL, g);
	else if (g->map_s.map[y - 1][x - 1] == '1')
		draw_wall((x - 1) * SIZE_PIXEL, (y - 1) * SIZE_PIXEL, g);
}

void	draw_map_move(int x, int y, t_global *g)
{
	draw_map_move_1(x, y, g);
	draw_map_move_2(x, y, g);
	bresenham(g);
	circle(g->player_s.pos[0], g->player_s.pos[1], 8, g);
	mlx_put_image_to_window(g->mlx, g->mlx_win, g->data.img, 0, 0);
}

void	draw_map_pos(t_global *g, int x, int y)
{
	if (ft_strchr("NSWE", g->map_s.map[y][x]))
	{
		if (!g->player_s.pos[0])
		{
			g->player_s.pos[0] = (x * (float)SIZE_PIXEL) + SIZE_PIXEL / 2;
			g->player_s.pos[1] = (y * (float)SIZE_PIXEL) + SIZE_PIXEL / 2;
		}
		//draw_floor(x * SIZE_PIXEL, y * SIZE_PIXEL, g);
		//circle(g->player_s.pos[0], g->player_s.pos[1] , 8, g);
		//bresenham(g);
	}
}

void	draw_map(t_global *g)
{
	int		x;
	int		y;
	char	**map;

	y = -1;
	map = g->map_s.map;
	if (!map )
		return ;
	while (map[++y])
	{
		x = -1;
		while (g->map_s.map[y][++x])
		{
			//if (g->map_s.map[y][x] == '1')
			//	draw_wall(x * SIZE_PIXEL, y * SIZE_PIXEL, g);
			//else if (g->map_s.map[y][x] == '0')
		//		draw_floor(x * SIZE_PIXEL, y * SIZE_PIXEL, g);
			if(ft_strchr("NSWE", g->map_s.map[y][x]))
				draw_map_pos(g, x, y);
		}
	}
}

float secure_radians(float angle, float add)
{
	float new_angle;

	new_angle = angle + add;
	if (new_angle <= 0 )
	{
		new_angle += DPI;
	}
	else if (new_angle > DPI)
		new_angle -= DPI;
	return (new_angle);
}

void	move_player_utils(int x_new, int y_new, t_global *g)
{
	float	x;
	float	y;

	x = (x_new / SIZE_PIXEL);
	y = (y_new / SIZE_PIXEL);
	if (g->map_s.map[(int)y][(int)x] && g->map_s.map[(int)y][(int)x] != '1')
	{
		g->player_s.pos[0] = x_new;
		g->player_s.pos[1] = y_new;
		g->map_s.update = 1;
		//draw_map_move(x, y, g);
	}
}

void move_player(float x_new, float y_new, int dir, t_global *g)
{
	g->player_s.move_step = g->player_s.walkdirection * g->player_s.move_speed;
	if (dir == -1)
	{
		x_new = x_new + cos(g->player_s.rotation_angle) * g->player_s.move_step;
		y_new = y_new + sin(g->player_s.rotation_angle) * g->player_s.move_step;
	}
	else if (!dir)
	{
		x_new = x_new + cos(secure_radians(g->player_s.rotation_angle, -PI2)) * g->player_s.move_step;
		y_new = y_new + sin(secure_radians(g->player_s.rotation_angle, -PI2)) * g->player_s.move_step;
	}
	else if (dir == 1)
	{
		x_new = x_new + cos(secure_radians(g->player_s.rotation_angle, PI2)) * g->player_s.move_step;
		y_new = y_new + sin(secure_radians(g->player_s.rotation_angle, PI2)) * g->player_s.move_step;
	}
	move_player_utils(x_new, y_new, g);
}

int	draw_update(t_global *g)
{
	g->player_s.rotation_angle += g->player_s.turndirection * g->player_s.rotation_speed;
	if (g->player_s.rotation_angle >= TWO_PI)
		g->player_s.rotation_angle -= TWO_PI;
	else if (g->player_s.rotation_angle < 0)
		g->player_s.rotation_angle += TWO_PI;
	//draw_map_move(g->player_s.pos[0] / SIZE_PIXEL, g->player_s.pos[1] / SIZE_PIXEL, g);
	return (0);
}

void	keycode_direction(int key_code, t_global *g)
{
	if (key_code == UP)
	{
		g->player_s.walkdirection = 1;
		move_player(g->player_s.pos[0], g->player_s.pos[1], -1, g);
	}
	if (key_code == DOWN)
	{
		g->player_s.walkdirection = -1;
		move_player(g->player_s.pos[0], g->player_s.pos[1], -1, g);
	}
	if (key_code == LEFT)
	{
		g->player_s.walkdirection = 1;
		move_player(g->player_s.pos[0], g->player_s.pos[1], 0, g);
	}
	if (key_code == RIGHT)
	{	
		g->player_s.walkdirection = 1;
		move_player(g->player_s.pos[0], g->player_s.pos[1], 1, g);
	}	
}

void	keycode_angle(int key_code, t_global *g)
{
	if (key_code == ARROW_LEFT)
	{
		g->player_s.turndirection = -1;
		draw_update(g);
	}
	if (key_code == ARROW_RIGTH)
	{
		g->player_s.turndirection = 1;
		draw_update(g);
	}
	if (key_code == 112)
	{
		for (int y = 0; y < 7; y++)
			printf("%s\n", g->map_s.map[y]);
	}
}

void keycode_excute(int key_code,  t_global *g)
{
	//draw_map(g);
	keycode_direction(key_code, g);
	keycode_angle(key_code, g);
}

int	catch_keycode(int key_code, t_global *g)
{
	if (!g->player_s.touch_status)
		g->player_s.touch_status = key_code;
	if (g->player_s.touch_status && (key_code != g->player_s.touch_status))
		keycode_excute(g->player_s.touch_status, g);
	keycode_excute(key_code, g);
	return (0);
}

int release_keycode(int key_code, t_global *g)
{
	if (key_code == g->player_s.touch_status)
		g->player_s.touch_status = 0;
	return (0);
}

int	init_value(t_global *g)
{
	g->map_s.update = 1;
	g->player_s.pos[0] = 0;
	g->player_s.pos[1] = 0;
	g->player_s.touch_status = 0;
	g->player_s.rotation_angle = PI2;
	g->player_s.turndirection = 0;
	g->player_s.walkdirection = 0;
	g->player_s.move_speed = 4;
	g->player_s.rotation_speed =  2 * (PI / 180);	
	return (1);
}

int	game(t_global *g)
{
	full_cast_ray(g);
	put_ray(g, 0, 0, 0);
	return (1);
}

void	ft_cub2d(t_global *g)
{
	init_value(g);
	g->map_s.map = g->map.map;
	g->mlx = mlx_init();
	g->mlx_win = mlx_new_window(g->mlx, HRES, VRES, "Hello world!");
	g->txt[0].img = mlx_xpm_file_to_image(g->mlx, "/mnt/nfs/homes/engooh/Documents/cub3d/texture/grass.xpm", &g->txt[0].width, &g->txt[0].heigt);
	g->txt[1].img = mlx_xpm_file_to_image(g->mlx, PATH_NORD, &g->txt[1].width, &g->txt[1].heigt);
	g->txt[2].img = mlx_xpm_file_to_image(g->mlx, PATH_EAST, &g->txt[2].width, &g->txt[2].heigt);
	g->txt[3].img = mlx_xpm_file_to_image(g->mlx, PATH_WEST, &g->txt[3].width, &g->txt[3].heigt);
	g->data.img = mlx_new_image(g->mlx, HRES, VRES);
	g->data.addr = mlx_get_data_addr(g->data.img, &g->data.bits_per_pixel, &g->data.line_length, &g->data.endian);
	draw_map(g);
	mlx_put_image_to_window(g->mlx, g->mlx_win, g->data.img, 0, 0);
	mlx_loop_hook(g->mlx, game, g);
	mlx_hook(g->mlx_win, 2, 1L << 0, catch_keycode, g);
	mlx_hook(g->mlx_win, 3, 1L << 1, release_keycode, g); //draw_map();
	mlx_loop(g->mlx);
}