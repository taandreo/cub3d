/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tairribe <tairribe@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/19 21:12:53 by tairribe          #+#    #+#             */
/*   Updated: 2024/03/16 20:55:46 by tairribe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "ft_printf.h"
# include "libft.h"
# include <fcntl.h>
# include <math.h>
# include <mlx.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>

// Window Params
# define WINDOW_WIDTH 1200
# define WINDOW_HEIGHT 900
# define MAP_OFFSET 36
// Mlx Error
# define MLX_ERROR 1
// Mlx Key Symbol
# define XK_ESCAPE 0xff1b
# define XK_W 0x77
# define XK_A 0x61
# define XK_S 0x73
# define XK_D 0x64
# define XK_RIGHT 0xff53
# define XK_LEFT 0xff51
// Mlx Events
# define KEY_RELEASE 3
# define KEY_PRESS 2
# define KEY_PRESS_MASK 1
# define KEY_RELEASE_MASK 2
# define DESTROY_NOTIFY 17
# define STRUCTURE_NOTIFY_MASK 131072
// Player Color
# define RED_PIXEL 0xFF0000
# define GREEN_PIXEL 0x00FF00
# define BLACK_PIXEL 0x000000
# define WHITE_PIXEL 0xFFFFFF
# define GRAY_PIXEL 0x777777
# define CEILING_COLOR 0xC6FCFF
# define FLOOR_COLOR 0x5C7554
# define STDERR_FILENO 2

typedef enum e_keys_index
{
	KEY_W,
	KEY_A,
	KEY_S,
	KEY_D,
	KEY_RIGHT,
	KEY_LEFT,
	MAX_KEYS
}	t_keys_index;

typedef struct t_player
{
	double	x;
	double	y;
	double	dir_x;
	double	dir_y;
	double	plane_x;
	double	plane_y;
	double	height;
	double	width;
}	t_player;

typedef struct s_img
{
	void	*mlx_img;
	char	*addr;
	int		bpp;
	int		line_len;
	int		endian;
}	t_img;

typedef struct s_texture
{
	void *texture_north;
	void *texture_south;
	void *texture_east;
	void *texture_west;
	int ceiling_color;
	int floor_color;
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
	char *tex_file_north;
	char *tex_file_south;
	char *tex_file_east;
	char *tex_file_west;
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
	void		*mlx_ptr;
	void		*win_ptr;
	t_player	player;
	t_img		img;
	t_texture	tex;
	char		**map;
	int			map_rows;
	t_bool		keysym_states[MAX_KEYS];
	int			max_columns;
	double		scale_factor;
	int			x;
}	t_map_data;

typedef struct s_rays
{
	double	camera_x;
	double	ray_dir_x;
	double	ray_dir_y;
	double	delta_dist_x;
	double	delta_dist_y;
	double	side_dist_x;
	double	side_dist_y;
	double	perp_wall_dist;
	int		map_x;
	int		map_y;
	int		step_x;
	int		step_y;
	int		hit;
	int		side;
	int		line_height;
	int		draw_start;
	int		draw_end;

}	t_rays;

void	initialize_mlx(t_map_data *map_data);
int		handle_mouse(t_map_data *map_data);
int		render(t_map_data *map_data);
void	init_player(t_map_data *map_data);
int		handle_keypress(int keysym, t_map_data *map_data);
int		handle_keyrelease(int keysym, t_map_data *map_data);
void	handle_movement(t_map_data *map_data);
int		keysym_to_index(int keysym);
void	img_pixel_put(t_img *img, int x, int y, int color);
void	rotate_left(t_map_data *map_data, double rotate_speed);
void	rotate_right(t_map_data *map_data, double rotate_speed);
void	calculate_strafe(t_map_data *map_data, double move_speed);
void	calculate_forward_and_backward_movement(t_map_data *map_data,
			double move_speed);
void	kill_mlx(t_map_data *map_data);
void	init_textures(t_map_data *map_data);
void	calculate_rays_initial_position(t_map_data *map_data, t_rays *rays,
			int x);
void	calculate_step_direction(t_map_data *map_data, t_rays *rays);
void	dda_line_algorithm(t_map_data *map_data, t_rays *rays);
void	calculate_perp_distance_on_camera_direction(t_rays *rays);
void	calculate_line_height_to_be_drawn(t_rays *rays);
void	calculate_lowest_highest_pixel(t_rays *rays);
void	calculate_where_wall_was_hit(t_map_data *map_data, t_rays *rays);
void	calculate_texture_x(t_map_data *map_data, t_rays *rays);
void	calculate_texture_y(t_map_data *map_data, t_rays *rays, int x);
void	set_texture_width_and_height(t_map_data *map_data, t_rays rays);
int		get_color(t_map_data *map_data, t_rays *rays);
void	vert_line_img(t_map_data *map_data, int y1, int y2, int color);
void	img_pixel_put(t_img *img, int x, int y, int color);
void	free_map_data(t_map_data *map_data);
void	free_and_error(t_map_data *map_data, char *msg);
int		open_file(char *filename);


#endif
