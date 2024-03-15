/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebezerra <ebezerra@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/01 18:32:09 by ebezerra          #+#    #+#             */
/*   Updated: 2024/03/15 02:14:13 by ebezerra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void render_background(t_map_data *map_data);
void render_vectors(t_map_data *map_data);
void verLine_img(t_img *img, int x, int y1, int y2, int color);
void set_texture_w_and_h(t_map_data *map_data, t_rays rays);
void texture_loop(t_map_data *map_data, t_rays *rays, int x);

int render(t_map_data *map_data)
{
	// Render movements direct on the game loop so we can have Keys Rollover.
	handle_movement(map_data);
	render_vectors(map_data);
	mlx_put_image_to_window(map_data->mlx_ptr, map_data->win_ptr, map_data->img.mlx_img, 0, 0);
	return 0;
}

void init_player(t_map_data *map_data)
{
	int i;
	int j;

	i = 0;
	while (map_data->map[i])
	{
		j = 0;
		while (map_data->map[i][j])
		{
			if (ft_isalpha(map_data->map[i][j]))
			{
				map_data->player.y = i;
				map_data->player.x = j;
				if (map_data->map[i][j] == 'N')
				{
					map_data->player.dir_x = 0;
					map_data->player.dir_y = -1;
					map_data->player.plane_x = 0.66;
					map_data->player.plane_y = 0;
				}
				else if (map_data->map[i][j] == 'S')
				{
					map_data->player.dir_x = 0;
					map_data->player.dir_y = 1;
					map_data->player.plane_x = -0.66;
					map_data->player.plane_y = 0;
				}
				else if (map_data->map[i][j] == 'W')
				{
					map_data->player.dir_x = -1;
					map_data->player.dir_y = 0;
					map_data->player.plane_x = 0;
					map_data->player.plane_y = -0.66;
				}
				else if (map_data->map[i][j] == 'E')
				{
					map_data->player.dir_x = 1;
					map_data->player.dir_y = 0;
					map_data->player.plane_x = 0;
					map_data->player.plane_y = 0.66;
				}
				return;
			}
			j++;
		}
		i++;
	}
}

void render_vectors(t_map_data *map_data)
{
	t_rays rays;
	int x;

	x = 0;
	while (x < WINDOW_WIDTH)
	{
		// calculate ray position and direction normatizing for x 1 and -1
		rays.camera_x = 2 * x / (double)WINDOW_WIDTH - 1;
		rays.ray_dir_x = map_data->player.dir_x + map_data->player.plane_x * rays.camera_x;
		rays.ray_dir_y = map_data->player.dir_y + map_data->player.plane_y * rays.camera_x;
		rays.map_x = (int)map_data->player.x;
		rays.map_y = (int)map_data->player.y;
		// Prevent division by 0
		if (rays.ray_dir_x == 0)
			rays.delta_dist_x = 1e30;
		else
			rays.delta_dist_x = fabs(1 / rays.ray_dir_x);
		if (rays.ray_dir_y == 0)
			rays.delta_dist_y = 1e30;
		else
			rays.delta_dist_y = fabs(1 / rays.ray_dir_y);
		// step direction
		if (rays.ray_dir_x < 0)
		{
			rays.step_x = -1;
			rays.side_dist_x = (map_data->player.x - rays.map_x) * rays.delta_dist_x;
		}
		else
		{
			rays.step_x = 1;
			rays.side_dist_x = (rays.map_x + 1.0 - map_data->player.x) * rays.delta_dist_x;
		}
		if (rays.ray_dir_y < 0)
		{
			rays.step_y = -1;
			rays.side_dist_y = (map_data->player.y - rays.map_y) * rays.delta_dist_y;
		}
		else
		{
			rays.step_y = 1;
			rays.side_dist_y = (rays.map_y + 1.0 - map_data->player.y) * rays.delta_dist_y;
		}
		rays.hit = 0;
		// DDA Line Algorithm
		while (!rays.hit)
		{
			if (rays.side_dist_x < rays.side_dist_y)
			{
				rays.side_dist_x += rays.delta_dist_x;
				rays.map_x += rays.step_x;
				rays.side = 0;
			}
			else
			{
				rays.side_dist_y += rays.delta_dist_y;
				rays.map_y += rays.step_y;
				rays.side = 1;
			}
			if (rays.map_y >= 0 && rays.map_y < map_data->map_rows && rays.map_x >= 0 &&
				rays.map_x < (int)ft_strlen(map_data->map[rays.map_y]))
			{
				if (map_data->map[rays.map_y][rays.map_x] == '1')
					rays.hit = 1;
			}
			else
			{
				if (rays.map_y < 0)
					rays.map_y = 0;
				else if (rays.map_y >= map_data->map_rows)
					rays.map_y = map_data->map_rows - 1;
				if (rays.map_x < 0)
					rays.map_x = 0;
				else if (rays.map_x >= (int)ft_strlen(map_data->map[rays.map_y]))
					rays.map_x = (int)ft_strlen(map_data->map[rays.map_y]) - 1;
				if (map_data->map[rays.map_y][rays.map_x] == '1')
					rays.hit = 1;
			}
		}
		// Distance projected on camera direction
		if (rays.side == 0)
			rays.perp_wall_dist = (rays.side_dist_x - rays.delta_dist_x);
		else
			rays.perp_wall_dist = (rays.side_dist_y - rays.delta_dist_y);
		// Height of Line to be drawn
		if (rays.perp_wall_dist == 0)
			rays.line_height = WINDOW_WIDTH - 1;
		else
			rays.line_height = (int)(WINDOW_HEIGHT / rays.perp_wall_dist);
		// calculate lowest and highest pixel to fill in current stripe
		rays.draw_end = (-rays.line_height / 2) + (WINDOW_HEIGHT / 2);
		if (rays.draw_end < 0)
			rays.draw_end = 0;
		rays.draw_start = (rays.line_height / 2) + (WINDOW_HEIGHT / 2);
		if (rays.draw_start >= WINDOW_HEIGHT)
			rays.draw_start = WINDOW_HEIGHT - 1;
		if (rays.side == 0)
			map_data->tex.wall_x = map_data->player.y + rays.perp_wall_dist * rays.ray_dir_y;
		else
			map_data->tex.wall_x = map_data->player.x + rays.perp_wall_dist * rays.ray_dir_x;
		map_data->tex.wall_x -= floor(map_data->tex.wall_x);
		set_texture_w_and_h(map_data, rays);
		map_data->tex.tex_x = (int)(map_data->tex.wall_x * (double)map_data->tex.tex_width);
		if (rays.side == 0 && rays.ray_dir_x < 0)
			map_data->tex.tex_x = map_data->tex.tex_width - map_data->tex.tex_x - 1;
		if (rays.side == 1 && rays.ray_dir_y > 0)
			map_data->tex.tex_x = map_data->tex.tex_width - map_data->tex.tex_x - 1;
		map_data->tex.step = 1.0 * map_data->tex.tex_height / rays.line_height;
		map_data->tex.tex_pos = (rays.draw_end - WINDOW_HEIGHT / 2 + rays.line_height / 2) * map_data->tex.step;
		texture_loop(map_data, &rays, x);
		//		verLine_img(&map_data->img, x, rays.draw_end, rays.draw_start, color);
		//// Ceiling from top of the screen to the start of the wall
		verLine_img(&map_data->img, x, 0, rays.draw_end - 1, CEILING_COLOR);
		//// Floor from the end of the wall to the bottom of the screen
		verLine_img(&map_data->img, x, rays.draw_start + 1, WINDOW_HEIGHT - 1, FLOOR_COLOR);
		x++;
	}
}

int get_color(t_map_data *map_data, t_rays *rays)
{
	int color;


	// Combine the color channels into one integer value
	if (rays->side == 0 && rays->ray_dir_x > 0)//south
	{
		int tex_offset =
				map_data->tex.line_len_east * map_data->tex.tex_y + map_data->tex.tex_x * (map_data->tex.bpp_east / 8);
		unsigned char *pixel_ptr = (unsigned char *)(map_data->tex.text_addr_east + tex_offset);
		if (map_data->tex.endian_east == 0)
		{
			// BGR format
			color = (pixel_ptr[2] << 16) | (pixel_ptr[1] << 8) | pixel_ptr[0];
		}
		else
		{
			// RGB format
			color = (pixel_ptr[0] << 16) | (pixel_ptr[1] << 8) | pixel_ptr[2];
		}
	}
	else if (rays->side == 0 && rays->ray_dir_x < 0)//north
	{
		int tex_offset =
				map_data->tex.line_len_west * map_data->tex.tex_y + map_data->tex.tex_x * (map_data->tex.bpp_west / 8);
		unsigned char *pixel_ptr = (unsigned char *)(map_data->tex.text_addr_west + tex_offset);
		if (map_data->tex.endian_west == 0)
		{
			// BGR format
			color = (pixel_ptr[2] << 16) | (pixel_ptr[1] << 8) | pixel_ptr[0];
		}
		else
		{
			// RGB format
			color = (pixel_ptr[0] << 16) | (pixel_ptr[1] << 8) | pixel_ptr[2];
		}
	}
	else if (rays->side == 1 && rays->ray_dir_y > 0)//east
	{
		int tex_offset = map_data->tex.line_len_south * map_data->tex.tex_y +
				map_data->tex.tex_x * (map_data->tex.bpp_south / 8);
		unsigned char *pixel_ptr = (unsigned char *)(map_data->tex.text_addr_south + tex_offset);
		if (map_data->tex.endian_south == 0)
		{
			// BGR format
			color = (pixel_ptr[2] << 16) | (pixel_ptr[1] << 8) | pixel_ptr[0];
		}
		else
		{
			// RGB format
			color = (pixel_ptr[0] << 16) | (pixel_ptr[1] << 8) | pixel_ptr[2];
		}
	}
	else//west
	{
		int tex_offset = map_data->tex.line_len_north * map_data->tex.tex_y +
				map_data->tex.tex_x * (map_data->tex.bpp_north / 8);
		unsigned char *pixel_ptr = (unsigned char *)(map_data->tex.text_addr_north + tex_offset);
		if (map_data->tex.endian_north == 0)
		{
			// BGR format
			color = (pixel_ptr[2] << 16) | (pixel_ptr[1] << 8) | pixel_ptr[0];
		}
		else
		{
			// RGB format
			color = (pixel_ptr[0] << 16) | (pixel_ptr[1] << 8) | pixel_ptr[2];
		}
	}
	return (color);
}

void texture_loop(t_map_data *map_data, t_rays *rays, int x)
{
	int y;
	int color;
	int y2;
	int temp;

	y = rays->draw_end;
	y2 = rays->draw_start;
	if (y > y2)
	{
		temp = y;
		y = y2;
		y2 = temp;
	}
	while (y <= y2)
	{
		map_data->tex.tex_y = (int)map_data->tex.tex_pos & (map_data->tex.tex_height - 1);
		map_data->tex.tex_pos += map_data->tex.step;
		color = get_color(map_data, rays);
		if (rays->side == 0)
			color = (color >> 1) & 8355711;
		img_pixel_put(&map_data->img, x, y, color);
		y++;
	}
}
void set_texture_w_and_h(t_map_data *map_data, t_rays rays)
{

	if (rays.side == 0 && rays.ray_dir_x > 0)//south
	{
		map_data->tex.tex_width = map_data->tex.tex_width_south;
		map_data->tex.tex_height = map_data->tex.tex_height_south;
	}
	else if (rays.side == 0 && rays.ray_dir_x < 0)//north
	{
		map_data->tex.tex_width = map_data->tex.tex_width_north;
		map_data->tex.tex_height = map_data->tex.tex_height_north;
	}
	else if (rays.side == 1 && rays.ray_dir_y > 0)//east
	{
		map_data->tex.tex_width = map_data->tex.tex_width_east;
		map_data->tex.tex_height = map_data->tex.tex_height_east;
	}
	else if (rays.side == 1 && rays.ray_dir_y < 0)//west
	{
		map_data->tex.tex_width = map_data->tex.tex_width_west;
		map_data->tex.tex_height = map_data->tex.tex_height_west;
	}
}

void verLine_img(t_img *img, int x, int y1, int y2, int color)
{
	// Ensure y1 is less than y2
	if (y2 < y1)
	{
		int temp = y1;
		y1 = y2;
		y2 = temp;
	}

	// Clip the coordinates to the bounds of the image
	if (x < 0 || x >= WINDOW_WIDTH || y2 < 0 || y1 >= WINDOW_HEIGHT)
		return;// Line is out of bounds
	if (y1 < 0)
		y1 = 0;
	if (y2 >= WINDOW_HEIGHT)
		y2 = WINDOW_HEIGHT - 1;
	int y;

	y = y1;
	// Draw the vertical line
	while (y <= y2)
	{
		img_pixel_put(img, x, y, color);
		y++;
	}
}

void img_pixel_put(t_img *img, int x, int y, int color)
{
	char *pixel;
	int i;

	i = img->bpp - 8;
	pixel = img->addr + (y * img->line_len + x * (img->bpp / 8));
	//	*(unsigned int *)pixel = color;
	while (i >= 0)
	{
		if (img->endian != 0)
			*pixel++ = (color >> i) & 0xFF;
		else
			*pixel++ = (color >> (img->bpp - 8 - i)) & 0xFF;
		i -= 8;
	}
}
