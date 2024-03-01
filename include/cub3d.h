/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tairribe <tairribe@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/19 21:12:53 by tairribe          #+#    #+#             */
/*   Updated: 2024/03/01 00:20:06 by ebezerra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
#define CUB3D_H

#include "ft_printf.h"
#include "libft.h"
#include <fcntl.h>
#include <math.h>
#include <mlx.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

// Window Params
#define WINDOW_WIDTH 1200
#define WINDOW_HEIGHT 900
#define MAP_OFFSET 36
// Mlx Error
#define MLX_ERROR 1
// Mlx Key Symbol
#define XK_ESCAPE 0xff1b
#define XK_W 0x77
#define XK_A 0x61
#define XK_S 0x73
#define XK_D 0x64
#define XK_RIGHT 0xff53
#define XK_LEFT 0xff51
// Mlx Events
#define KEY_RELEASE 3
#define KEY_PRESS 2
#define KEY_PRESS_MASK 1
#define KEY_RELEASE_MASK 2
#define DESTROY_NOTIFY 17
#define STRUCTURE_NOTIFY_MASK 131072
// Player Color
#define RED_PIXEL 0xFF0000
#define GREEN_PIXEL 0x00FF00
#define BLACK_PIXEL 0x000000
#define WHITE_PIXEL 0xFFFFFF
#define GRAY_PIXEL 0x777777
#define CEILING_COLOR 0xAAAAAA
#define FLOOR_COLOR 0x555555
// Value of PI
#define PI 3.14159265
#define EPSILON 0.00001
#define MY_DBL_EPSILON 1e-9
#define PI270 (3 * PI) / 2
#define PI90 PI / 2

typedef struct t_player
{
	double x;
	double y;
	double dir_x;
	double dir_y;
	double plane_x;
	double plane_y;
	double height;
	double width;
} t_player;

typedef struct s_img
{
	void *mlx_img;
	char *addr;
	int bpp;
	int line_len;
	int endian;
} t_img;


typedef struct s_texture
{
	void *texture_north;
	void *texture_south;
	void *texture_east;
	void *texture_west;
	int tex_x;
	int tex_y;
	double wall_x;
	double step;
	double tex_pos;
	int tex_width;
	int tex_height;
	int tex_width_north;
	int tex_width_south;
	int tex_width_east;
	int tex_width_west;
	int tex_height_north;
	int tex_height_south;
	int tex_height_east;
	int tex_height_west;
	char *text_addr_north;
	char *text_addr_east;
	char *text_addr_south;
	char *text_addr_west;
	int bpp_north;
	int bpp_east;
	int bpp_south;
	int bpp_west;
	int line_len_north;
	int line_len_east;
	int line_len_south;
	int line_len_west;
	int endian_north;
	int endian_east;
	int endian_south;
	int endian_west;
} t_texture;

typedef struct s_map_data
{
	void *mlx_ptr;
	void *win_ptr;
	t_player player;
	t_img img;
	t_texture tex;
	char **map;
	int map_rows;
	int max_columns;
	double scale_factor;
} t_map_data;

typedef struct s_bresenham
{
	int x0;
	int y0;
	int x;
	int y;
	int inc_x;
	int inc_y;
	int dx;
	int dy;
	int abs_dx;
	int abs_dy;
	int pk;
} t_bresenham;

typedef struct s_rays
{
	double camera_x;
	double ray_dir_x;
	double ray_dir_y;
	double delta_dist_x;
	double delta_dist_y;
	double side_dist_x;
	double side_dist_y;
	double perp_wall_dist;
	int map_x;
	int map_y;
	int step_x;
	int step_y;
	int hit;
	int side;
	int line_height;
	int draw_start;
	int draw_end;

} t_rays;

void initialize_mlx(t_map_data *map_data);
int handle_mouse(t_map_data *map_data);
int handle_keyrelease(int keysym, t_map_data *map_data);
int render(t_map_data *map_data);
void init_player(t_map_data *map_data);
int handle_keypress(int keysym, t_map_data *map_data);
float ft_abs(float value);
void draw_line(t_map_data *map_data, double x_end, double y_end, int color);
void img_pixel_put(t_img *img, int x, int y, int color);
int is_parallel_to_x_axis(double angle);

#endif
