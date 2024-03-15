/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   img_pixel_put.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebezerra <ebezerra@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/15 07:16:13 by ebezerra          #+#    #+#             */
/*   Updated: 2024/03/15 09:21:34 by ebezerra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	convert_color_data_west_east(t_map_data *map_data, t_rays *rays)
{
	int				tex_offset;
	unsigned char	*pixel_ptr;

	if (rays->side == 0 && rays->ray_dir_x > 0)
	{
		tex_offset = map_data->tex.line_len_east * map_data->tex.tex_y
			+ map_data->tex.tex_x * (map_data->tex.bpp_east / 8);
		pixel_ptr = (unsigned char *)(map_data->tex.text_addr_east
				+ tex_offset);
		if (map_data->tex.endian_east == 0)
			return ((pixel_ptr[2] << 16) | (pixel_ptr[1] << 8) | pixel_ptr[0]);
		return ((pixel_ptr[0] << 16) | (pixel_ptr[1] << 8) | pixel_ptr[2]);
	}
	else if (rays->side == 0 && rays->ray_dir_x < 0)
	{
		tex_offset = map_data->tex.line_len_west * map_data->tex.tex_y
			+ map_data->tex.tex_x * (map_data->tex.bpp_west / 8);
		pixel_ptr = (unsigned char *)(map_data->tex.text_addr_west
				+ tex_offset);
		if (map_data->tex.endian_west == 0)
			return ((pixel_ptr[2] << 16) | (pixel_ptr[1] << 8) | pixel_ptr[0]);
		return ((pixel_ptr[0] << 16) | (pixel_ptr[1] << 8) | pixel_ptr[2]);
	}
	return (0);
}

static int	convert_color_data_north_south(t_map_data *map_data, t_rays *rays)
{
	int				tex_offset;
	unsigned char	*pixel_ptr;

	if (rays->side == 1 && rays->ray_dir_y > 0)
	{
		tex_offset = map_data->tex.line_len_south * map_data->tex.tex_y
			+ map_data->tex.tex_x * (map_data->tex.bpp_south / 8);
		pixel_ptr = (unsigned char *)(map_data->tex.text_addr_south
				+ tex_offset);
		if (map_data->tex.endian_south == 0)
			return ((pixel_ptr[2] << 16) | (pixel_ptr[1] << 8) | pixel_ptr[0]);
		return ((pixel_ptr[0] << 16) | (pixel_ptr[1] << 8) | pixel_ptr[2]);
	}
	else if (rays->side == 1 && rays->ray_dir_y < 0)
	{
		tex_offset = map_data->tex.line_len_north * map_data->tex.tex_y
			+ map_data->tex.tex_x * (map_data->tex.bpp_north / 8);
		pixel_ptr = (unsigned char *)(map_data->tex.text_addr_north
				+ tex_offset);
		if (map_data->tex.endian_north == 0)
			return ((pixel_ptr[2] << 16) | (pixel_ptr[1] << 8) | pixel_ptr[0]);
		return ((pixel_ptr[0] << 16) | (pixel_ptr[1] << 8) | pixel_ptr[2]);
	}
	return (0);
}

int	get_color(t_map_data *map_data, t_rays *rays)
{
	int	color;

	color = 0;
	if ((rays->side == 0 && rays->ray_dir_x > 0)
		|| (rays->side == 0 && rays->ray_dir_x < 0))
		color = convert_color_data_west_east(map_data, rays);
	else if ((rays->side == 1 && rays->ray_dir_y > 0)
		|| (rays->side == 1 && rays->ray_dir_y < 0))
		color = convert_color_data_north_south(map_data, rays);
	return (color);
}

void	vert_line_img(t_map_data *map_data, int y1, int y2, int color)
{
	int	y;
	int	temp;

	if (y2 < y1)
	{
		temp = y1;
		y1 = y2;
		y2 = temp;
	}
	if (map_data->x < 0 || map_data->x >= WINDOW_WIDTH || y2 < 0
		|| y1 >= WINDOW_HEIGHT)
		return ;
	if (y1 < 0)
		y1 = 0;
	if (y2 >= WINDOW_HEIGHT)
		y2 = WINDOW_HEIGHT - 1;
	y = y1;
	while (y <= y2)
	{
		img_pixel_put(&map_data->img, map_data->x, y, color);
		y++;
	}
}

void	img_pixel_put(t_img *img, int x, int y, int color)
{
	char	*pixel;
	int		i;

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
