/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture_calculations.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebezerra <ebezerra@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/15 07:37:25 by ebezerra          #+#    #+#             */
/*   Updated: 2024/03/15 09:22:58 by ebezerra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	calculate_texture_x(t_map_data *map_data, t_rays *rays)
{
	map_data->tex.tex_x = (int)(map_data->tex.wall_x
			* (double)map_data->tex.tex_width);
	if (rays->side == 0 && rays->ray_dir_x < 0)
		map_data->tex.tex_x = map_data->tex.tex_width - map_data->tex.tex_x - 1;
	if (rays->side == 1 && rays->ray_dir_y > 0)
		map_data->tex.tex_x = map_data->tex.tex_width - map_data->tex.tex_x - 1;
	map_data->tex.step = 1.0 * map_data->tex.tex_height / rays->line_height;
	map_data->tex.tex_pos = (rays->draw_end - WINDOW_HEIGHT
			/ 2.0 + rays->line_height / 2.0) * map_data->tex.step;
}

void	calculate_texture_y(t_map_data *map_data, t_rays *rays, int x)
{
	int	y;
	int	color;
	int	y2;
	int	temp;

	y = rays->draw_end;
	y2 = rays->draw_start;
	if (y > y2)
	{
		temp = y;
		y = y2;
		y2 = temp;
	}
	while (y <= y2)
	{
		map_data->tex.tex_y = (int)map_data->tex.tex_pos
			& (map_data->tex.tex_height - 1);
		map_data->tex.tex_pos += map_data->tex.step;
		color = get_color(map_data, rays);
		if (rays->side == 0)
			color = (color >> 1) & 8355711;
		img_pixel_put(&map_data->img, x, y, color);
		y++;
	}
}

void	set_texture_width_and_height(t_map_data *map_data, t_rays rays)
{
	if (rays.side == 0 && rays.ray_dir_x > 0)
	{
		map_data->tex.tex_width = map_data->tex.tex_width_south;
		map_data->tex.tex_height = map_data->tex.tex_height_south;
	}
	else if (rays.side == 0 && rays.ray_dir_x < 0)
	{
		map_data->tex.tex_width = map_data->tex.tex_width_north;
		map_data->tex.tex_height = map_data->tex.tex_height_north;
	}
	else if (rays.side == 1 && rays.ray_dir_y > 0)
	{
		map_data->tex.tex_width = map_data->tex.tex_width_east;
		map_data->tex.tex_height = map_data->tex.tex_height_east;
	}
	else if (rays.side == 1 && rays.ray_dir_y < 0)
	{
		map_data->tex.tex_width = map_data->tex.tex_width_west;
		map_data->tex.tex_height = map_data->tex.tex_height_west;
	}
}
