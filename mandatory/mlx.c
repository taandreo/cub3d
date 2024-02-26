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

int handle_keypress(int keysym, t_map_data *map_data)
{
	if (keysym == XK_LEFT)
	{
		map_data->player.pa -= 0.1;
		if (map_data->player.pa < 0)
		{
			map_data->player.pa += 2 * PI;
		}
		map_data->player.pdx = cos(map_data->player.pa) * 5;
		map_data->player.pdy = sin(map_data->player.pa) * 5;
	}
	if (keysym == XK_RIGHT)
	{
		map_data->player.pa += 0.1;
		if (map_data->player.pa > 2 * PI)
		{
			map_data->player.pa -= 2 * PI;
		}
		map_data->player.pdx = cos(map_data->player.pa) * 5;
		map_data->player.pdy = sin(map_data->player.pa) * 5;
	}
	if (keysym == XK_W)
	{
		map_data->player.y += map_data->player.pdy;
		map_data->player.x += map_data->player.pdx;
	}
	if (keysym == XK_A)
	{
		if (!map_data->player.pdx)
			map_data->player.x -= 5;
		else
			map_data->player.x -= map_data->player.pdx;
	}
	if (keysym == XK_S)
	{
		map_data->player.x -= map_data->player.pdx;
		map_data->player.y -= map_data->player.pdy;
	}
	if (keysym == XK_D)
	{
		if (!map_data->player.pdx)
			map_data->player.x += 5;
		else
			map_data->player.x += map_data->player.pdx;
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
	map_data->win_ptr = mlx_new_window(map_data->mlx_ptr, WINDOW_WIDTH, WINDOW_HEIGHT, "FdF");
	if (map_data->win_ptr == NULL)
	{
		free(map_data->win_ptr);
		ft_printf("Error: Mlx window error\n");
		exit(MLX_ERROR);
	}
	map_data->img.mlx_img = mlx_new_image(map_data->mlx_ptr, WINDOW_WIDTH, WINDOW_HEIGHT);
	map_data->img.addr = mlx_get_data_addr(map_data->img.mlx_img, &map_data->img.bpp, &map_data->img.line_len,
										   &map_data->img.endian);
}
