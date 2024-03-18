/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebezerra <ebezerra@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/01 18:31:38 by ebezerra          #+#    #+#             */
/*   Updated: 2024/03/16 20:13:13 by ebezerra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	kill_mlx(t_map_data *map_data)
{
	free_map_data(map_data);
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
		free_and_error(map_data, "Mlx initialization error");
	map_data->win_ptr = mlx_new_window(map_data->mlx_ptr, WINDOW_WIDTH,
			WINDOW_HEIGHT, "Cub3d");
	if (map_data->win_ptr == NULL)
		free_and_error(map_data, "Mlx window error");
	map_data->img.mlx_img = mlx_new_image(map_data->mlx_ptr, WINDOW_WIDTH,
			WINDOW_HEIGHT);
	map_data->img.addr = mlx_get_data_addr(map_data->img.mlx_img,
			&map_data->img.bpp, &map_data->img.line_len, &map_data->img.endian);
	init_textures(map_data);
}
