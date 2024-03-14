/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebezerra <ebezerra@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/01 18:31:38 by ebezerra          #+#    #+#             */
/*   Updated: 2024/03/14 18:45:30 by ebezerra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void kill_mlx(t_map_data *map_data);

static void mlx_exit(t_map_data *map_data)
{
	free(map_data->map);
	map_data->map = NULL;
}

int handle_keyrelease(int keysym, t_map_data *map_data)
{
	if (keysym == XK_ESCAPE)
		kill_mlx(map_data);
	return (0);
}

t_bool can_move_right(t_map_data *map_data, double move_speed)
{
	int next_y;
	int next_x;

	next_y = map_data->player.y + map_data->player.plane_y * move_speed;
	next_x = map_data->player.x + map_data->player.plane_x * move_speed;

	if (next_y >= 0 && next_y < map_data->map_rows && next_x >= 0 &&
		next_x < (int)ft_strlen(map_data->map[(int)map_data->player.y]))
	{
		if ((map_data->map[next_y][(int)map_data->player.x] == '0' &&
			 map_data->map[(int)map_data->player.y][next_x] == '0') ||
			(ft_isalpha(map_data->map[next_y][(int)map_data->player.x]) &&
			 ft_isalpha(map_data->map[(int)map_data->player.y][next_x])))
			return true;
		return false;
	}
	return false;
}

t_bool can_move_left(t_map_data *map_data, double move_speed)
{
	int next_y;
	int next_x;

	next_y = map_data->player.y - map_data->player.plane_y * move_speed;
	next_x = map_data->player.x - map_data->player.plane_x * move_speed;

	if (next_y >= 0 && next_y < map_data->map_rows && next_x >= 0 &&
		next_x < (int)ft_strlen(map_data->map[(int)map_data->player.y]))
	{
		if ((map_data->map[next_y][(int)map_data->player.x] == '0' &&
			 map_data->map[(int)map_data->player.y][next_x] == '0') ||
			(ft_isalpha(map_data->map[next_y][(int)map_data->player.x]) &&
			 ft_isalpha(map_data->map[(int)map_data->player.y][next_x])))
			return true;
		return false;
	}
	return false;
}

void calculate_strafe(t_map_data *map_data, int keysym, double move_speed)
{
	if (keysym == XK_A)
	{
		if (can_move_left(map_data, move_speed))
		{
			map_data->player.x -= map_data->player.plane_x * move_speed;
			map_data->player.y -= map_data->player.plane_y * move_speed;
		}
		else if (can_move_right(map_data, move_speed))
		{
			map_data->player.x += map_data->player.plane_x * move_speed;
			map_data->player.y += map_data->player.plane_y * move_speed;
		}
	}
	if (keysym == XK_D)
	{
		if (can_move_right(map_data, move_speed))
		{
			map_data->player.x += map_data->player.plane_x * move_speed;
			map_data->player.y += map_data->player.plane_y * move_speed;
		}
		else if (can_move_left(map_data, move_speed))
		{
			map_data->player.x -= map_data->player.plane_x * move_speed;
			map_data->player.y -= map_data->player.plane_y * move_speed;
		}
	}
}

void rotate_left(t_map_data *map_data, double rotate_speed)
{
	double old_dir_x;
	double old_plane_x;

	old_dir_x = map_data->player.dir_x;
	map_data->player.dir_x =
			(map_data->player.dir_x * cos(-rotate_speed)) - (map_data->player.dir_y * sin(-rotate_speed));
	map_data->player.dir_y = (old_dir_x * sin(-rotate_speed)) + (map_data->player.dir_y * cos(-rotate_speed));
	old_plane_x = map_data->player.plane_x;
	map_data->player.plane_x =
			(map_data->player.plane_x * cos(-rotate_speed)) - (map_data->player.plane_y * sin(-rotate_speed));
	map_data->player.plane_y = (old_plane_x * sin(-rotate_speed)) + (map_data->player.plane_y * cos(-rotate_speed));
}

void rotate_right(t_map_data *map_data, double rotate_speed)
{
	double old_dir_x;
	double old_plane_x;

	old_dir_x = map_data->player.dir_x;
	map_data->player.dir_x =
			(map_data->player.dir_x * cos(rotate_speed)) - (map_data->player.dir_y * sin(rotate_speed));
	map_data->player.dir_y = (old_dir_x * sin(rotate_speed)) + (map_data->player.dir_y * cos(rotate_speed));
	old_plane_x = map_data->player.plane_x;
	map_data->player.plane_x =
			(map_data->player.plane_x * cos(rotate_speed)) - (map_data->player.plane_y * sin(rotate_speed));
	map_data->player.plane_y = (old_plane_x * sin(rotate_speed)) + (map_data->player.plane_y * cos(rotate_speed));
}


t_bool can_move_y_forward(t_map_data *map_data, double move_speed)
{
	int next_y;

	next_y = (int)(map_data->player.y + map_data->player.dir_y * move_speed);

	if (next_y >= 0 && next_y < map_data->map_rows)
	{
		if (map_data->map[next_y][(int)(map_data->player.x)] == '0' ||
			ft_isalpha(map_data->map[next_y][(int)(map_data->player.x)]))
			return true;
		return false;
	}
	return false;
}

t_bool can_move_y_backwards(t_map_data *map_data, double move_speed)
{
	int next_y;

	next_y = (int)(map_data->player.y - map_data->player.dir_y * move_speed);

	if (next_y >= 0 && next_y < map_data->map_rows)
	{
		if (map_data->map[next_y][(int)(map_data->player.x)] == '0' ||
			ft_isalpha(map_data->map[next_y][(int)(map_data->player.x)]))
			return true;
		return false;
	}
	return false;
}

t_bool can_move_x_forward(t_map_data *map_data, double move_speed)
{
	int next_x;

	next_x = (int)(map_data->player.x + map_data->player.dir_x * move_speed);

	if (next_x >= 0 && next_x < (int)ft_strlen(map_data->map[(int)map_data->player.y]))
	{
		if (map_data->map[(int)map_data->player.y][next_x] == '0' ||
			ft_isalpha(map_data->map[(int)map_data->player.y][next_x]))
			return true;
		return false;
	}
	return false;
}

t_bool can_move_x_backwards(t_map_data *map_data, double move_speed)
{
	int next_x;

	next_x = (int)(map_data->player.x - map_data->player.dir_x * move_speed);

	if (next_x >= 0 && next_x < (int)ft_strlen(map_data->map[(int)map_data->player.y]))
	{
		if (map_data->map[(int)map_data->player.y][next_x] == '0' ||
			ft_isalpha(map_data->map[(int)map_data->player.y][next_x]))
			return true;
		return false;
	}
	return false;
}

int handle_keypress(int keysym, t_map_data *map_data)
{
	double move_speed = 0.03 * 5.0;
	double rotation_speed = 0.03 * 3.0;
	if (keysym == XK_LEFT)
		rotate_left(map_data, rotation_speed);
	if (keysym == XK_RIGHT)
		rotate_right(map_data, rotation_speed);
	if (keysym == XK_W)
	{
		if (can_move_y_forward(map_data, move_speed))
			map_data->player.y += map_data->player.dir_y * move_speed;
		else if (can_move_y_backwards(map_data, move_speed))
			map_data->player.y -= map_data->player.dir_y * move_speed;
		if (can_move_x_forward(map_data, move_speed))
			map_data->player.x += map_data->player.dir_x * move_speed;
		else if (can_move_x_backwards(map_data, move_speed))
			map_data->player.x -= map_data->player.dir_x * move_speed;
	}
	if (keysym == XK_A || keysym == XK_D)
		calculate_strafe(map_data, keysym, move_speed);
	if (keysym == XK_S)
	{
		if (can_move_y_backwards(map_data, move_speed))
			map_data->player.y -= map_data->player.dir_y * move_speed;
		else if (can_move_y_forward(map_data, move_speed))
			map_data->player.y += map_data->player.dir_y * move_speed;
		if (can_move_x_backwards(map_data, move_speed))
			map_data->player.x -= map_data->player.dir_x * move_speed;
		else if (can_move_x_forward(map_data, move_speed))
			map_data->player.x += map_data->player.dir_x * move_speed;
	}
	return (0);
}

static void kill_mlx(t_map_data *map_data)
{
	mlx_exit(map_data);//free map
	if (map_data->img.mlx_img)
		mlx_destroy_image(map_data->mlx_ptr, map_data->img.mlx_img);
	if (map_data->win_ptr)
		mlx_destroy_window(map_data->mlx_ptr, map_data->win_ptr);
	if (map_data->mlx_ptr)
	{
		mlx_destroy_display(map_data->mlx_ptr);
		free(map_data->mlx_ptr);
	}
	exit(0);
}

int handle_mouse(t_map_data *map_data)
{
	kill_mlx(map_data);
	return (0);
}

void initialize_mlx(t_map_data *map_data)
{
	map_data->mlx_ptr = mlx_init();
	if (map_data->mlx_ptr == NULL)
	{
		ft_printf("Error: Mlx initialization error\n");
		exit(MLX_ERROR);
	}
	map_data->win_ptr = mlx_new_window(map_data->mlx_ptr, WINDOW_WIDTH, WINDOW_HEIGHT, "Cub3d");
	if (map_data->win_ptr == NULL)
	{
		free(map_data->win_ptr);
		ft_printf("Error: Mlx window error\n");
		exit(MLX_ERROR);
	}
	map_data->img.mlx_img = mlx_new_image(map_data->mlx_ptr, WINDOW_WIDTH, WINDOW_HEIGHT);
	map_data->img.addr = mlx_get_data_addr(map_data->img.mlx_img, &map_data->img.bpp, &map_data->img.line_len,
										   &map_data->img.endian);
	map_data->tex.texture_north =
			mlx_xpm_file_to_image(map_data->mlx_ptr, map_data->tex.tex_file_north, &map_data->tex.tex_width_north,
								  &map_data->tex.tex_height_north);
	map_data->tex.text_addr_north = mlx_get_data_addr(map_data->tex.texture_north, &map_data->tex.bpp_north,
													  &map_data->tex.line_len_north, &map_data->tex.endian_north);
	map_data->tex.texture_east = mlx_xpm_file_to_image(map_data->mlx_ptr, map_data->tex.tex_file_east,
													   &map_data->tex.tex_width_east, &map_data->tex.tex_height_east);
	map_data->tex.text_addr_east = mlx_get_data_addr(map_data->tex.texture_east, &map_data->tex.bpp_east,
													 &map_data->tex.line_len_east, &map_data->tex.endian_east);
	map_data->tex.texture_south =
			mlx_xpm_file_to_image(map_data->mlx_ptr, map_data->tex.tex_file_south, &map_data->tex.tex_width_south,
								  &map_data->tex.tex_height_south);
	map_data->tex.text_addr_south = mlx_get_data_addr(map_data->tex.texture_south, &map_data->tex.bpp_south,
													  &map_data->tex.line_len_south, &map_data->tex.endian_south);
	map_data->tex.texture_west = mlx_xpm_file_to_image(map_data->mlx_ptr, map_data->tex.tex_file_west,
													   &map_data->tex.tex_width_west, &map_data->tex.tex_height_west);
	map_data->tex.text_addr_west = mlx_get_data_addr(map_data->tex.texture_west, &map_data->tex.bpp_west,
													 &map_data->tex.line_len_west, &map_data->tex.endian_west);
}
