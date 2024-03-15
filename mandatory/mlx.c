/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebezerra <ebezerra@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/01 18:31:38 by ebezerra          #+#    #+#             */
/*   Updated: 2024/03/15 01:59:14 by ebezerra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void mlx_exit(t_map_data *map_data)
{
	free(map_data->map);
	map_data->map = NULL;
}

void kill_mlx(t_map_data *map_data)
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
