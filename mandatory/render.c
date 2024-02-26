#include "cub3d.h"
#include <mlx.h>

void img_pixel_put(t_img *img, int x, int y, int color);
void render_player(t_map_data *map_data);
void render_map(t_map_data *map_data);

int render(t_map_data *map_data)
{
	render_map(map_data);
	render_player(map_data);
	mlx_put_image_to_window(map_data->mlx_ptr, map_data->win_ptr, map_data->img.mlx_img, 0, 0);
	return 0;
}

void init_player(t_map_data *map_data)
{
	map_data->player.x = (WINDOW_WIDTH / 2);
	map_data->player.y = (WINDOW_HEIGHT / 2);
	map_data->player.height = 5;
	map_data->player.width = 5;
}

void render_map(t_map_data *map_data)
{
	//char *mapRow;
	int i;
	int j;

	i = 0;
	while (i < WINDOW_HEIGHT)
	{
		j = 0;
		while (j < WINDOW_WIDTH)
		{
			img_pixel_put(&map_data->img, j++, i, 0x000000);
		}
		i++;
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
		{
			img_pixel_put(&map_data->img, j++, i, RED_PIXEL);
		}
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
