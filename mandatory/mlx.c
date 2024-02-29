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

void calculate_strafe(t_map_data *map_data, int keysym, double move_speed)
{
	double new_x;
	double new_y;
	double new_x_d;
	double new_y_d;

	if (keysym == XK_A)
	{
		new_x = map_data->player.x - map_data->player.plane_x * move_speed;
		new_y = map_data->player.y - map_data->player.plane_y * move_speed;
		if ((map_data->map[(int)new_y][(int)map_data->player.x] == '0' &&
			 map_data->map[(int)map_data->player.y][(int)new_x] == '0') ||
			(ft_isalpha(map_data->map[(int)new_y][(int)map_data->player.x]) &&
			 ft_isalpha(map_data->map[(int)map_data->player.y][(int)new_x])))
		{
			map_data->player.x = new_x;
			map_data->player.y = new_y;
		}
	}
	if (keysym == XK_D)
	{
		new_x_d = map_data->player.x + map_data->player.plane_x * move_speed;
		new_y_d = map_data->player.y + map_data->player.plane_y * move_speed;
		if ((map_data->map[(int)new_y_d][(int)map_data->player.x] == '0' &&
			 map_data->map[(int)map_data->player.y][(int)new_x_d] == '0') ||
			(ft_isalpha(map_data->map[(int)new_y_d][(int)map_data->player.x]) &&
			 ft_isalpha(map_data->map[(int)map_data->player.y][(int)new_x_d])))
		{
			map_data->player.x = new_x_d;
			map_data->player.y = new_y_d;
		}
	}
}

void rotate_right(t_map_data *map_data, double rotate_speed)
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

void rotate_left(t_map_data *map_data, double rotate_speed)
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

int handle_keypress(int keysym, t_map_data *map_data)
{
	double move_speed = 0.02 * 5.0;
	double rotation_speed = 0.02 * 3.0;
	if (keysym == XK_LEFT)
		rotate_left(map_data, rotation_speed);
	if (keysym == XK_RIGHT)
		rotate_right(map_data, rotation_speed);
	if (keysym == XK_W)
	{
		if (map_data->map[(int)(map_data->player.y + map_data->player.dir_y * move_speed)][(int)(map_data->player.x)] ==
					'0' ||
			ft_isalpha(map_data->map[(int)(map_data->player.y + map_data->player.dir_y * move_speed)]
									[(int)(map_data->player.x)]))
			map_data->player.x += map_data->player.dir_x * move_speed;
		if (map_data->map[(int)(map_data->player.y)][(int)(map_data->player.x + map_data->player.dir_x * move_speed)] ==
					'0' ||
			ft_isalpha(map_data->map[(int)(map_data->player.y)]
									[(int)(map_data->player.x + map_data->player.dir_x * move_speed)]))
			map_data->player.y += map_data->player.dir_y * move_speed;
	}
	if (keysym == XK_A || keysym == XK_D)
		calculate_strafe(map_data, keysym, move_speed);
	if (keysym == XK_S)
	{
		if (map_data->map[(int)(map_data->player.y - map_data->player.dir_y * move_speed)][(int)(map_data->player.x)] ==
					'0' ||
			ft_isalpha(map_data->map[(int)(map_data->player.y - map_data->player.dir_y * move_speed)]
									[(int)(map_data->player.x)]))
			map_data->player.x -= map_data->player.dir_x * move_speed;
		if (map_data->map[(int)(map_data->player.y)][(int)(map_data->player.x - map_data->player.dir_x * move_speed)] ==
					'0' ||
			ft_isalpha(map_data->map[(int)(map_data->player.y)]
									[(int)(map_data->player.x - map_data->player.dir_x * move_speed)]))
			map_data->player.y -= map_data->player.dir_y * move_speed;
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
