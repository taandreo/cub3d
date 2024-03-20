/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   calculate_rays_position.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebezerra <ebezerra@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/15 07:36:11 by ebezerra          #+#    #+#             */
/*   Updated: 2024/03/15 09:24:01 by ebezerra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

void	calculate_rays_initial_position(t_map_data *map_data, t_rays *rays,
			int x)
{
	rays->camera_x = 2 * x / (double)WINDOW_WIDTH - 1;
	rays->ray_dir_x = map_data->player.dir_x + map_data->player.plane_x
		* rays->camera_x;
	rays->ray_dir_y = map_data->player.dir_y + map_data->player.plane_y
		* rays->camera_x;
	rays->map_x = (int)map_data->player.x;
	rays->map_y = (int)map_data->player.y;
	if (rays->ray_dir_x == 0)
		rays->delta_dist_x = 1e30;
	else
		rays->delta_dist_x = fabs(1 / rays->ray_dir_x);
	if (rays->ray_dir_y == 0)
		rays->delta_dist_y = 1e30;
	else
		rays->delta_dist_y = fabs(1 / rays->ray_dir_y);
}

void	calculate_step_direction(t_map_data *map_data, t_rays *rays)
{
	if (rays->ray_dir_x < 0)
	{
		rays->step_x = -1;
		rays->side_dist_x = (map_data->player.x - rays->map_x)
			* rays->delta_dist_x;
	}
	else
	{
		rays->step_x = 1;
		rays->side_dist_x = (rays->map_x + 1.0 - map_data->player.x)
			* rays->delta_dist_x;
	}
	if (rays->ray_dir_y < 0)
	{
		rays->step_y = -1;
		rays->side_dist_y = (map_data->player.y - rays->map_y)
			* rays->delta_dist_y;
	}
	else
	{
		rays->step_y = 1;
		rays->side_dist_y = (rays->map_y + 1.0 - map_data->player.y)
			* rays->delta_dist_y;
	}
}
