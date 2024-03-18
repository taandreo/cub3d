/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_textures.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tairribe <tairribe@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/15 02:50:06 by ebezerra          #+#    #+#             */
/*   Updated: 2024/03/17 23:39:57 by ebezerra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	init_north_east(t_map_data *map_data)
{
	ft_printf("%s", map_data->tex.tex_file_north);
	map_data->tex.texture_north = mlx_xpm_file_to_image(map_data->mlx_ptr,
			map_data->tex.tex_file_north, &map_data->tex.tex_width_north,
			&map_data->tex.tex_height_north);
	if (!map_data->tex.texture_north)
		free_and_error(map_data, "North texture file error");
	map_data->tex.text_addr_north = mlx_get_data_addr(
			map_data->tex.texture_north, &map_data->tex.bpp_north,
			&map_data->tex.line_len_north, &map_data->tex.endian_north);
	map_data->tex.texture_east = mlx_xpm_file_to_image(map_data->mlx_ptr,
			map_data->tex.tex_file_east,
			&map_data->tex.tex_width_east, &map_data->tex.tex_height_east);
	if (!map_data->tex.texture_east)
		free_and_error(map_data, "East texture file error");
	map_data->tex.text_addr_east = mlx_get_data_addr(map_data->tex.texture_east,
			&map_data->tex.bpp_east, &map_data->tex.line_len_east,
			&map_data->tex.endian_east);
}

void	init_south_west(t_map_data *map_data)
{
	map_data->tex.texture_south = mlx_xpm_file_to_image(map_data->mlx_ptr,
			map_data->tex.tex_file_south, &map_data->tex.tex_width_south,
			&map_data->tex.tex_height_south);
	if (!map_data->tex.texture_south)
		free_and_error(map_data, "South texture file error");
	map_data->tex.text_addr_south = mlx_get_data_addr(
			map_data->tex.texture_south, &map_data->tex.bpp_south,
			&map_data->tex.line_len_south, &map_data->tex.endian_south);
	map_data->tex.texture_west = mlx_xpm_file_to_image(map_data->mlx_ptr,
			map_data->tex.tex_file_west, &map_data->tex.tex_width_west,
			&map_data->tex.tex_height_west);
	if (!map_data->tex.texture_west)
		free_and_error(map_data, "West texture file error");
	map_data->tex.text_addr_west = mlx_get_data_addr(map_data->tex.texture_west,
			&map_data->tex.bpp_west, &map_data->tex.line_len_west,
			&map_data->tex.endian_west);
}

void	init_textures(t_map_data *map_data)
{
	init_north_east(map_data);
	init_south_west(map_data);
}
