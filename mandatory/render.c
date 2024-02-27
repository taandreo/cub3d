#include "cub3d.h"
#include <mlx.h>
#include <stdio.h>

void render_background(t_map_data *map_data);
void render_vectors(t_map_data *map_data);
void verLine_img(t_img *img, int x, int y1, int y2, int color);

int render(t_map_data *map_data)
{
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
					map_data->player.plane_y = 0.66;
				}
				else if (map_data->map[i][j] == 'E')
				{
					map_data->player.dir_x = 1;
					map_data->player.dir_y = 0;
					map_data->player.plane_x = 0;
					map_data->player.plane_y = -0.66;
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
	int color;

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
			if (rays.map_x >= 0 && rays.map_x < map_data->max_columns && rays.map_y >= 0 &&
				rays.map_y < map_data->map_rows)
			{
				if (map_data->map[rays.map_y][rays.map_x] == '1')
				{
					rays.hit = 1;
				}
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
		rays.draw_start = (-rays.line_height / 2) + (WINDOW_HEIGHT / 2);
		if (rays.draw_start < 0)
			rays.draw_start = 0;
		rays.draw_end = (rays.line_height / 2) + (WINDOW_HEIGHT / 2);
		if (rays.draw_end >= WINDOW_HEIGHT)
			rays.draw_end = WINDOW_HEIGHT - 1;
		if (rays.side)
			color = RED_PIXEL;
		else
			color = 0x990000;
		verLine_img(&map_data->img, x, rays.draw_start, rays.draw_end, color);
		// Ceiling from top of the screen to the start of the wall
		verLine_img(&map_data->img, x, 0, rays.draw_start - 1, CEILING_COLOR);
		// Floor from the end of the wall to the bottom of the screen
		verLine_img(&map_data->img, x, rays.draw_end + 1, WINDOW_HEIGHT - 1, FLOOR_COLOR);
		x++;
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
	if (y2 >= WINDOW_WIDTH)
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
	while (i >= 0)
	{
		if (img->endian != 0)
			*pixel++ = (color >> i) & 0xFF;
		else
			*pixel++ = (color >> (img->bpp - 8 - i)) & 0xFF;
		i -= 8;
	}
}
