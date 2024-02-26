#include "cub3d.h"
#include <mlx.h>

void img_pixel_put(t_img *img, int x, int y, int color);
void render_player(t_map_data *map_data);
void render_map(t_map_data *map_data);
void render_player_view(t_map_data *map_data);

int render(t_map_data *map_data)
{
	render_map(map_data);
	render_player(map_data);
	render_player_view(map_data);
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
				map_data->player.y = (i * map_data->scale_factor) + (map_data->scale_factor / 2);
				map_data->player.x = (j * map_data->scale_factor) + (map_data->scale_factor / 2);
				map_data->player.height = 5;
				map_data->player.width = 5;
				map_data->player.pa = (3 * PI) / 2;
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

	i = y;
	while (i < y + map_data->scale_factor)
	{
		j = x;
		while (j < x + map_data->scale_factor)
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

void render_player_view(t_map_data *map_data)
{
	int i;
	int j;

	i = map_data->player.y;
	while (i < map_data->player.y + 10)
	{
		j = map_data->player.x;
		while (j < map_data->player.x + 5)
			img_pixel_put(&map_data->img, j++ + map_data->player.pdx, i + map_data->player.pdy, RED_PIXEL);
		i++;
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