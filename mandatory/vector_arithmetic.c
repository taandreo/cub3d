/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector_arithmetic.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebezerra <ebezerra@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/15 07:32:54 by ebezerra          #+#    #+#             */
/*   Updated: 2024/03/15 07:33:33 by ebezerra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	calculate_perp_distance_on_camera_direction(t_rays *rays)
{
	if (rays->side == 0)
		rays->perp_wall_dist = (rays->side_dist_x - rays->delta_dist_x);
	else
		rays->perp_wall_dist = (rays->side_dist_y - rays->delta_dist_y);
}

void	calculate_line_height_to_be_drawn(t_rays *rays)
{
	if (rays->perp_wall_dist == 0)
		rays->line_height = WINDOW_WIDTH - 1;
	else
		rays->line_height = (int)(WINDOW_HEIGHT / rays->perp_wall_dist);
}

void	calculate_lowest_highest_pixel(t_rays *rays)
{
	rays->draw_end = (-rays->line_height / 2) + (WINDOW_HEIGHT / 2);
	if (rays->draw_end < 0)
		rays->draw_end = 0;
	rays->draw_start = (rays->line_height / 2) + (WINDOW_HEIGHT / 2);
	if (rays->draw_start >= WINDOW_HEIGHT)
		rays->draw_start = WINDOW_HEIGHT - 1;
}

void	calculate_where_wall_was_hit(t_map_data *map_data, t_rays *rays)
{
	if (rays->side == 0)
		map_data->tex.wall_x = map_data->player.y
			+ rays->perp_wall_dist * rays->ray_dir_y;
	else
		map_data->tex.wall_x = map_data->player.x
			+ rays->perp_wall_dist * rays->ray_dir_x;
	map_data->tex.wall_x -= floor(map_data->tex.wall_x);
}
