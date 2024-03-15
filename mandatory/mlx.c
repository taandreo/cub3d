/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebezerra <ebezerra@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/01 18:31:38 by ebezerra          #+#    #+#             */
/*   Updated: 2024/03/15 03:23:48 by ebezerra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	mlx_exit(t_map_data *map_data)
{
	int	y;

	y = 0;
	while (map_data->map[y])
	{
		free(map_data->map[y]);
		y++;
	}
	free(map_data->map);
	free(map_data->tex.tex_file_north);
	free(map_data->tex.tex_file_south);
	free(map_data->tex.tex_file_east);
	free(map_data->tex.tex_file_west);
	map_data->map = NULL;
}

void	kill_mlx(t_map_data *map_data)
{
	mlx_exit(map_data);
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

int	handle_mouse(t_map_data *map_data)
{
	kill_mlx(map_data);
	return (0);
}

void	initialize_mlx(t_map_data *map_data)
{
	map_data->mlx_ptr = mlx_init();
	if (map_data->mlx_ptr == NULL)
	{
		ft_printf("Error: Mlx initialization error\n");
		exit(MLX_ERROR);
	}
	map_data->win_ptr = mlx_new_window(map_data->mlx_ptr, WINDOW_WIDTH,
			WINDOW_HEIGHT, "Cub3d");
	if (map_data->win_ptr == NULL)
	{
		free(map_data->win_ptr);
		ft_printf("Error: Mlx window error\n");
		exit(MLX_ERROR);
	}
	map_data->img.mlx_img = mlx_new_image(map_data->mlx_ptr, WINDOW_WIDTH,
			WINDOW_HEIGHT);
	map_data->img.addr = mlx_get_data_addr(map_data->img.mlx_img,
			&map_data->img.bpp, &map_data->img.line_len, &map_data->img.endian);
	init_textures(map_data);
}
