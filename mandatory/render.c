/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebezerra <ebezerra@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/01 18:32:09 by ebezerra          #+#    #+#             */
/*   Updated: 2024/03/17 23:29:57 by ebezerra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	render_vectors(t_map_data *map_data);

int	render(t_map_data *map_data)
{
	handle_movement(map_data);
	render_vectors(map_data);
	mlx_put_image_to_window(map_data->mlx_ptr, map_data->win_ptr,
		map_data->img.mlx_img, 0, 0);
	return (0);
}

void	render_vectors(t_map_data *map_data)
{
	t_rays	rays;
	int		x;

	x = 0;
	while (x < WINDOW_WIDTH)
	{
		calculate_rays_initial_position(map_data, &rays, x);
		calculate_step_direction(map_data, &rays);
		dda_line_algorithm(map_data, &rays);
		calculate_perp_distance_on_camera_direction(&rays);
		calculate_line_height_to_be_drawn(&rays);
		calculate_lowest_highest_pixel(&rays);
		calculate_where_wall_was_hit(map_data, &rays);
		set_texture_width_and_height(map_data, rays);
		calculate_texture_x(map_data, &rays);
		calculate_texture_y(map_data, &rays, x);
		map_data->x = x;
		vert_line_img(map_data, 0, rays.draw_end - 1, map_data->tex.ceiling_color);
		vert_line_img(map_data, rays.draw_start + 1, WINDOW_HEIGHT - 1,
			map_data->tex.floor_color);
		x++;
	}
}
