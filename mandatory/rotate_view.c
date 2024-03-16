/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotate_view.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebezerra <ebezerra@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/15 00:44:29 by ebezerra          #+#    #+#             */
/*   Updated: 2024/03/15 03:44:18 by ebezerra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	rotate_left(t_map_data *map_data, double rotate_speed)
{
	double	old_dir_x;
	double	old_plane_x;

	old_dir_x = map_data->player.dir_x;
	map_data->player.dir_x = (map_data->player.dir_x * cos(-rotate_speed))
		- (map_data->player.dir_y * sin(-rotate_speed));
	map_data->player.dir_y = (old_dir_x * sin(-rotate_speed))
		+ (map_data->player.dir_y * cos(-rotate_speed));
	old_plane_x = map_data->player.plane_x;
	map_data->player.plane_x = (map_data->player.plane_x * cos(-rotate_speed))
		- (map_data->player.plane_y * sin(-rotate_speed));
	map_data->player.plane_y = (old_plane_x * sin(-rotate_speed))
		+ (map_data->player.plane_y * cos(-rotate_speed));
}

void	rotate_right(t_map_data *map_data, double rotate_speed)
{
	double	old_dir_x;
	double	old_plane_x;

	old_dir_x = map_data->player.dir_x;
	map_data->player.dir_x = (map_data->player.dir_x * cos(rotate_speed))
		- (map_data->player.dir_y * sin(rotate_speed));
	map_data->player.dir_y = (old_dir_x * sin(rotate_speed))
		+ (map_data->player.dir_y * cos(rotate_speed));
	old_plane_x = map_data->player.plane_x;
	map_data->player.plane_x = (map_data->player.plane_x * cos(rotate_speed))
		- (map_data->player.plane_y * sin(rotate_speed));
	map_data->player.plane_y = (old_plane_x * sin(rotate_speed))
		+ (map_data->player.plane_y * cos(rotate_speed));
}
