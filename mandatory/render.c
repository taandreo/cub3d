#include "cub3d.h"
#include <mlx.h>
#include <stdio.h>

void render_player(t_map_data *map_data);
void render_map(t_map_data *map_data);
void render_background(t_map_data *map_data);
void render_player_view(t_map_data *map_data);
void render_rays_3d(t_map_data *map_data);

int render(t_map_data *map_data)
{
	render_background(map_data);
	render_map(map_data);
	render_player(map_data);
	render_player_view(map_data);
	render_rays_3d(map_data);
	mlx_put_image_to_window(map_data->mlx_ptr, map_data->win_ptr, map_data->img.mlx_img, 0, 0);
	return 0;
}

//int is_parallel_to_x_axis(double angle)
//{
//	angle = fmod(angle, 2 * PI);
//	if (angle < 0)
//	{
//		angle += 2 * PI;
//	}
//
//	return (fabs(angle - PI) < EPSILON || fabs(angle) < EPSILON || fabs(angle - 2 * PI) < EPSILON);
//}

//double distance(t_map_data *map_data, int a, int b)
//{
//	return (sqrt((a - map_data->player.x) * (a - map_data->player.x) +
//				 (b - map_data->player.y) * (b - map_data->player.y)));
//}

//float deg_to_rad(int x) {
//	return ((float)(x * PI/180.0));
//}

//void render_rays_3d(t_map_data *map_data)
//{
//	t_rays rays;
////	double distH;
////	double distV;
//	double a_tan;
////	double v_tan;
//	size_t row_len;
//	int dof_len;
//
//	rays.ra = map_data->player.pa;
//	rays.r = 0;
//	while (rays.r < 1)
//	{
//		// Draw Horizontal Ray
////		distH = 1000000;
//		rays.dof = 0;
//		rays.hx = map_data->player.x;
//		rays.hy = map_data->player.y;
//		if (fabs(tan(rays.ra)) < MY_DBL_EPSILON)
//			a_tan = 0;
//		else
//			a_tan = -1 / tan(rays.ra);
//		if (sin(rays.ra) > 0.001)
//		{
//			rays.ry = (int)(floor(map_data->player.y / map_data->scale_factor) * map_data->scale_factor);
//			rays.rx = (map_data->player.y - rays.ry) * a_tan + map_data->player.x;
//			rays.yo = map_data->scale_factor;
//			rays.xo = -rays.yo * a_tan;
//		}
//		else if (sin(rays.ra) < -0.001)
//		{
//			rays.ry = (floor(map_data->player.y / map_data->scale_factor) * map_data->scale_factor) +
//					map_data->scale_factor;
//			rays.rx = (map_data->player.y - rays.ry) * a_tan + map_data->player.x;
//			rays.yo = -map_data->scale_factor;
//			rays.xo = -rays.yo * a_tan;
//		}
//		else
//		{
//			rays.rx = map_data->player.x;
//			rays.ry = map_data->player.y;
//			if (map_data->map_rows > map_data->max_columns)
//				rays.dof = map_data->map_rows;
//			else
//				rays.dof = map_data->max_columns;
//		}
//
//		if (map_data->map_rows > map_data->max_columns)
//			dof_len = map_data->map_rows;
//		else
//			dof_len = map_data->max_columns;
//		while (rays.dof < dof_len)
//		{
//			rays.mx = (int)((int)rays.rx / map_data->scale_factor);
//			rays.my = (int)((int)rays.ry / map_data->scale_factor);
//			if (rays.my >= 0 && rays.my < map_data->map_rows)
//			{
//				row_len = ft_strlen(map_data->map[rays.my]);
//				if (rays.mx >= 0 && rays.mx < (int)row_len && map_data->map[rays.my][rays.mx] == '1')
//				{
//					rays.hx = rays.rx;
//					rays.hy = rays.ry;
////					distH = distance(map_data, rays.hx, rays.hy);
//					if (map_data->map_rows > map_data->max_columns)
//						rays.dof = map_data->map_rows;
//					else
//						rays.dof = map_data->max_columns;
//				}
//				else
//				{
//					rays.rx -= rays.xo;
//					rays.ry -= rays.yo;
//					rays.dof++;
//				}
//			}
//		}
//
//
//		// Draw Vertical Ray
////		rays.dof = 0;
////		distV = 100000;
////		rays.vx = map_data->player.x;
////		rays.vy = map_data->player.y;
////		v_tan = -tan(rays.ra);
////		if (cos(rays.ra) < -0.001)
////		{
////			rays.rx = (int)(floor(map_data->player.x / map_data->scale_factor) * map_data->scale_factor);
////			rays.ry = (map_data->player.x - rays.rx) * v_tan + map_data->player.y;
////			rays.xo = map_data->scale_factor;
////			rays.yo = -rays.xo * v_tan;
////		}
////		else if (cos(rays.ra) > 0.001)
////		{
////			rays.rx = (int)(floor(map_data->player.x / map_data->scale_factor) * map_data->scale_factor) +
////					map_data->scale_factor;
////			rays.ry = (map_data->player.x - rays.rx) * v_tan + map_data->player.y;
////			rays.xo = -map_data->scale_factor;
////			rays.yo = -rays.xo * v_tan;
////		}
////		else
////		{
////			rays.rx = map_data->player.x;
////			rays.ry = map_data->player.y;
////			if (map_data->map_rows > map_data->max_columns)
////				rays.dof = map_data->map_rows;
////			else
////				rays.dof = map_data->max_columns;
////		}
////
////		if (map_data->map_rows > map_data->max_columns)
////			dof_len = map_data->map_rows;
////		else
////			dof_len = map_data->max_columns;
////		while (rays.dof < dof_len)
////		{
////			rays.mx = (int)((int)rays.rx / map_data->scale_factor);
////			rays.my = (int)((int)rays.ry / map_data->scale_factor);
////			if (rays.my >= 0 && rays.my < map_data->map_rows)
////			{
////				row_len = ft_strlen(map_data->map[rays.my]);
////				if (rays.mx >= 0 && rays.mx < (int)row_len && map_data->map[rays.my][rays.mx] == '1')
////				{
////					rays.vx = rays.rx;
////					rays.vy = rays.ry;
////					distV = distance(map_data, rays.vx, rays.vy);
////					if (map_data->map_rows > map_data->max_columns)
////						rays.dof = map_data->map_rows;
////					else
////						rays.dof = map_data->max_columns;
////				}
////				else
////				{
////					rays.rx -= rays.xo;
////					rays.ry -= rays.yo;
////					rays.dof++;
////				}
////			}
////		}
////		if (distH > distV)
////		{
////			rays.rx = rays.vx;
////			rays.ry = rays.vy;
////		}
////		else
////		{
////			rays.rx = rays.hx;
////			rays.ry = rays.hy;
////		}
//		draw_line(map_data, rays.rx, rays.ry, GREEN_PIXEL);
//		rays.r++;
//	}
//}

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
				map_data->player.y = (i * map_data->scale_factor) + (map_data->scale_factor / 2);
				map_data->player.x = (j * map_data->scale_factor) + (map_data->scale_factor / 2);
				map_data->player.height = 5;
				map_data->player.width = 5;
				map_data->player.pa = M_PI;
				map_data->player.pdx = cos(map_data->player.pa) * 5;
				map_data->player.pdy = sin(map_data->player.pa) * 5;
				return;
			}
			j++;
		}
		i++;
	}
}

void put_color_pixel(t_map_data *map_data, int x, int y, int color)
{
	int i;
	int j;

	i = y + 1;
	while (i < y + map_data->scale_factor - 1)
	{
		j = x + 1;
		while (j < x + map_data->scale_factor - 1)
			img_pixel_put(&map_data->img, j++, i, color);
		i++;
	}
}

void render_square_map(t_map_data *map_data, int x, int y, char *value)
{
	if (!value)
		put_color_pixel(map_data, x, y, BLACK_PIXEL);
	else if (ft_strcmp(value, "1") == 0)
		put_color_pixel(map_data, x, y, WHITE_PIXEL);
	else if (ft_strcmp(value, "0") == 0)
		put_color_pixel(map_data, x, y, BLACK_PIXEL);
	else if (ft_strcmp(value, " ") == 0)
		put_color_pixel(map_data, x, y, GRAY_PIXEL);
}
void render_map(t_map_data *map_data)
{
	int x;
	int y;
	int x0;
	int y0;

	y = 0;
	while (map_data->map[y])
	{
		x = 0;
		while (map_data->map[y][x])
		{
			y0 = y * map_data->scale_factor;
			x0 = x * map_data->scale_factor;
			if (map_data->map[y][x] == '1')
				render_square_map(map_data, x0, y0, "1");
			else if (map_data->map[y][x] == '0')
				render_square_map(map_data, x0, y0, "0");
			else if (map_data->map[y][x] == ' ')
				render_square_map(map_data, x0, y0, " ");
			else if (ft_isalpha(map_data->map[y][x]))
				render_square_map(map_data, x0, y0, NULL);
			x++;
		}
		y++;
	}
}

void render_player(t_map_data *map_data)
{
	int i;
	int j;

	i = map_data->player.y;
	while (i < map_data->player.y + map_data->player.height)
	{
		j = map_data->player.x;
		while (j < map_data->player.x + map_data->player.width)
			img_pixel_put(&map_data->img, j++, i, RED_PIXEL);
		i++;
	}
}

void render_background(t_map_data *map_data)
{
	int i;
	int j;

	i = 0;
	while (i < WINDOW_HEIGHT)
	{
		j = 0;
		while (j < WINDOW_WIDTH)
		{
			img_pixel_put(&map_data->img, j++, i, GRAY_PIXEL);
		}
		i++;
	}
}

void render_player_view(t_map_data *map_data)
{
	double x_end;
	double y_end;

	x_end = map_data->player.x + (cos(map_data->player.pa) * 15);
	y_end = map_data->player.y + (sin(map_data->player.pa) * 15);
	draw_line(map_data, x_end, y_end, RED_PIXEL);
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
