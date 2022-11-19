
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycating.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: engooh <engooh@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/19 00:43:19 by engooh            #+#    #+#             */
/*   Updated: 2022/11/19 00:43:32 by engooh           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

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

void move_player_utils(float x_new, float y_new, t_global *g)
{
	float	x;
	float	y;

	x = (x_new / SIZE_PIXEL);
	y = (y_new / SIZE_PIXEL);
	if (g->map_s.map[(int)y][(int)x] && g->map_s.map[(int)y][(int)x] != '1')
	{
        g->map_s.update = 1;
		g->player_s.pos[0] = x_new;
		g->player_s.pos[1] = y_new;
		//draw_map_move(x, y, g);
	}
}

void move_player(float x_new, float y_new, int dir, t_global *g)
{
	//float	x;
	//float	y;

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

void    keycode_excute_angle(int key_code, t_global *g)
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

void    keycode_excute_direction(int key_code, t_global *g)
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

void    keycode_excute(int key_code,  t_global *g)
{
	//draw_map(g);
    keycode_excute_direction(key_code, g);
    keycode_excute_angle(key_code, g);
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

int    game(t_global *g)
{
	full_cast_ray(g);
	put_ray(g);
    return (1);
}

void	ft_cub3d(t_global *g)
{
	g->map_s.map = g->map.map;
    init_value(g);
	g->mlx = mlx_init();
	g->mlx_win = mlx_new_window(g->mlx, HRES, VRES, "Hello world!");
	g->txt[0].img = mlx_xpm_file_to_image(g->mlx, "/mnt/nfs/homes/engooh/Documents/cub3d/texture/grass.xpm", &g->txt[0].width, &g->txt[0].heigt);
	g->txt[1].img = mlx_xpm_file_to_image(g->mlx, PATH_NORD, &g->txt[1].width, &g->txt[1].heigt);
	g->txt[2].img = mlx_xpm_file_to_image(g->mlx, PATH_EAST, &g->txt[2].width, &g->txt[2].heigt);
	g->txt[3].img = mlx_xpm_file_to_image(g->mlx, PATH_WEST, &g->txt[3].width, &g->txt[3].heigt);
	g->data.img = mlx_new_image(g->mlx, HRES, VRES);
	g->data.addr = mlx_get_data_addr(g->data.img, &g->data.bits_per_pixel, &g->data.line_length, &g->data.endian);
	mlx_put_image_to_window(g->mlx, g->mlx_win, g->data.img, 0, 0);
	mlx_loop_hook(g->mlx, game, g);
	mlx_hook(g->mlx_win, 2, 1L << 0, catch_keycode, g);
	mlx_hook(g->mlx_win, 3, 1L << 1, release_keycode, g);
	mlx_loop(g->mlx);
}