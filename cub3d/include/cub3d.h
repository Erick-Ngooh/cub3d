
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: engooh <engooh@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/15 01:24:29 by engooh            #+#    #+#             */
/*   Updated: 2022/11/19 01:21:40 by engooh           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include <sys/stat.h>
# include <sys/types.h>
# include "libft.h"
# include "define.h"
# include "mlx.h"
# include "mlx_int.h"
# include <math.h>
# include <stdbool.h>
# include <linux/stat.h>
# include <sys/types.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <sys/stat.h>
# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include <stdio.h>
# include <aio.h>
# include "libft.h"

# define BUFFER_SIZE 64000

typedef struct s_xpm
{
	void	*img;
	int	heigt;
	int	width;
}	t_xpm;

typedef struct s_data
{
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}	t_data;

typedef struct s_ray
{
	int	iter;
	float	curr;
	float	next;
	int	slice;
	int	offset;
	int	modulo_pixel;
	int	direction;
	double	tan_ray;
	float	first_xh;
	float	first_yh;
	float	first_xv;
	float	first_yv;
	int		mx;
	int		my;
	float	hx;
	float	hy;
	float	vx;
	float	vy;
	float	vdist;
	float	hdist;
	float	dist;
	float	hray;
	float	x_step;
	float	y_step;
	int		map_x;
	int		map_y;
	int		signe_x;
	int		signe_y;
	int		signe_xv;
	int		signe_yv;
	int		east;
	float	distancehorz;
	float	distancevert;
	float	finaldistance;
	float	finaldistancex;
	float	finaldistancey;
	int		see;  // See est une variable  qui permet de savoir si on regarde en vert ou horz

	float	rayAngle;
	float	wallHitX;
	float	wallHitY;
	float	distance;
	int		wasHitVertical;
	int		isRayfacingUp;
	int		isRayfacingDown;
	int		isRayfacingLeft;
	int		isRayfacingRight;
	int		wallHitContent;
	float	offpx;
} t_ray;

typedef	struct s_fov
{
	float	size;
	float	angle;
} t_fov;

typedef struct s_player
{
	float	pos[2];
	int		touch_status;
	float	rotation_angle;
	float	move_step;
	float	move_speed;
	float	rotation_speed;
	int		turndirection;
	int		walkdirection;
} t_player;

typedef struct s_parse
{
	int		fd;
	char	**map;
	int		len_map;
	int		len_line;
	char	*map_parse;
	char	buf[BUFFER_SIZE];
}	t_parse;

typedef struct s_map
{
	int		fd;
	t_gc	*gc;
	char	**map;
	int		len_map;
	int     update;
}	t_map;

typedef struct s_elem
{
	char	*north_texture;
	char	*south_texture;
	char	*west_texture;
	char	*east_texture;
	int		rgb_sol[3];
	int		rgb_plafond[3];
}	t_elem;

typedef struct s_global
{
	t_map			map;
	t_elem			elem;
	t_parse			*pars;
	//char			**map;
	void			*mlx;
	void			*mlx_win;
	t_player		player_s;
	t_map			map_s;
	t_data			tmp;
	t_data			data;
	t_ray			*ray;
	t_xpm			txt[4];
	float			mult;
}	t_global;

// PARSING //
void	print_map(char **map);
int	set_pos(t_global *g, int x, int y);
void	ft_test_cub2d(t_global *g);

//char	*get_next_line(int fd);
char	**tab_join(char **tab, char *str, int size);
int		open_file(char	*file);
int		check_line_empty(char *line);
int		init_struct_map(t_global *g, t_map *map);
int		init_struct_element(t_elem *elem, t_map *map);

// GARBANGE COLLECTOR // 
char	*get_next_line(int fd);
void	*ft_malloc(size_t size, size_t nbr);
char	*ft_get_line(char *cache);
char	*ft_get_cache(char *cache);

// Raycasting //
void		ft_cub2d(t_global *g);
void	my_mlx_pixel_put(t_data *data, int x, int y, int color);
void draw_wall(int x_start, int y_start, t_global *g);
void draw_floor(int x_start, int y_start, t_global *g);
void	draw_map_move(int x, int y, t_global *g);
void	draw_map(t_global *g);
float secure_radians(float angle, float add);
void move_player(float x_new, float y_new, int dir, t_global *g);
int	draw_update(t_global *g);
void keycode_excute(int key_code,  t_global *g);
int	catch_keycode(int key_code, t_global *g);
int release_keycode(int key_code, t_global *g);
int	init_value(t_global *g);
int	game(t_global *g);
void	ft_test_cub3d(void);
void	ft_test_cub2d(t_global *g);
int	size_x(t_global *g, int x, int y);
int size_y(t_global *g, int y);
int	is_wall(t_global *g, int x_pixel, int y_pixel);
double	ft_distance(float x1, float y1, float x2, float y2);
void	init_struct_ray(t_global *g, int i);
void	dda_pi3(t_global *g, float rayangle, int i);
void	dda_pi2(t_global *g, float rayangle, int i);
void	dda_pi_pi2(t_global *g, float rayangle, int i);
void	dda_pi_pi3(t_global *g, float rayangle, int i);
bool	compare_double(float a, float b);
void	cast_ray_horizontal(t_global *g, int i);
void	cast_ray_vertical(t_global *g, int i);
void	cast_ray(t_global *g, float rayangle, int i);
float	deg_to_rad(float angle, float degree);
int	full_cast_ray(t_global *g);
unsigned int get_color_pixel(t_global *g, void *img, int x, int y);
int	get_horizontal_pixel(int direction, int x, int y);
float	get_math_ray(t_global *g, int i);
int	get_color(int color, float mult);
int	put_ray(t_global *g, int i, int x, int color);
int absolute(int nbr);
void    bresenham(t_global *g);
void    rayon(float angle, t_global *g);
void    bresenham2(float x2, float y2, t_global *g);
int	circle_check(t_global *g, int cx, int cy, int r);
void    circle(int cx, int cy, int r, t_global *g);
void    circle2(int cx, int cy, int r, t_global *g);
void    circle3(int cx, int cy, int r, int col, t_global *g);
#endif
