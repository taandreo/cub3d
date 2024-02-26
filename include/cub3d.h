/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tairribe <tairribe@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/19 21:12:53 by tairribe          #+#    #+#             */
/*   Updated: 2024/02/26 01:23:02 by ebezerra         ###   ########.fr       */
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
// Mlx Events
#define KEY_RELEASE 3
#define KEY_PRESS 2
#define KEY_PRESS_MASK 1
#define KEY_RELEASE_MASK 2
#define DESTROY_NOTIFY 17
#define STRUCTURE_NOTIFY_MASK 131072
// Player Color
#define RED_PIXEL 0xFF0000

typedef struct t_player
{
	int x;
	int y;
	int height;
	int width;
} t_player;

typedef struct s_img
{
	void *mlx_img;
	char *addr;
	int bpp;
	int line_len;
	int endian;
} t_img;

typedef struct s_map_data
{
	void *mlx_ptr;
	void *win_ptr;
	t_player player;
	t_img img;
	char **map;
	int map_rows;
} t_map_data;

void initialize_mlx(t_map_data *map_data);
int handle_mouse(t_map_data *map_data);
int handle_keyrelease(int keysym, t_map_data *map_data);
int render(t_map_data *map_data);
void init_player(t_map_data *map_data);
int handle_keypress(int keysym, t_map_data *map_data);

#endif
