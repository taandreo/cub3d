/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move_forward_backward.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebezerra <ebezerra@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/15 00:42:17 by ebezerra          #+#    #+#             */
/*   Updated: 2024/03/15 02:10:03 by ebezerra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

t_bool can_move_y_forward(t_map_data *map_data, double move_speed)
{
	int next_y;

	next_y = (int)(map_data->player.y + map_data->player.dir_y * move_speed);

	if (next_y >= 0 && next_y < map_data->map_rows)
	{
		if (map_data->map[next_y][(int)(map_data->player.x)] == '0' ||
			ft_isalpha(map_data->map[next_y][(int)(map_data->player.x)]))
			return true;
		return false;
	}
	return false;
}

t_bool can_move_y_backwards(t_map_data *map_data, double move_speed)
{
	int next_y;

	next_y = (int)(map_data->player.y - map_data->player.dir_y * move_speed);

	if (next_y >= 0 && next_y < map_data->map_rows)
	{
		if (map_data->map[next_y][(int)(map_data->player.x)] == '0' ||
			ft_isalpha(map_data->map[next_y][(int)(map_data->player.x)]))
			return true;
		return false;
	}
	return false;
}

t_bool can_move_x_forward(t_map_data *map_data, double move_speed)
{
	int next_x;

	next_x = (int)(map_data->player.x + map_data->player.dir_x * move_speed);

	if (next_x >= 0 && next_x < (int)ft_strlen(map_data->map[(int)map_data->player.y]))
	{
		if (map_data->map[(int)map_data->player.y][next_x] == '0' ||
			ft_isalpha(map_data->map[(int)map_data->player.y][next_x]))
			return true;
		return false;
	}
	return false;
}

t_bool can_move_x_backwards(t_map_data *map_data, double move_speed)
{
	int next_x;

	next_x = (int)(map_data->player.x - map_data->player.dir_x * move_speed);

	if (next_x >= 0 && next_x < (int)ft_strlen(map_data->map[(int)map_data->player.y]))
	{
		if (map_data->map[(int)map_data->player.y][next_x] == '0' ||
			ft_isalpha(map_data->map[(int)map_data->player.y][next_x]))
			return true;
		return false;
	}
	return false;
}

void calculate_forward_and_backward_movement(t_map_data *map_data, double move_speed)
{
	if (map_data->keysym_states[KEY_W])
	{
		if (can_move_y_forward(map_data, move_speed))
			map_data->player.y += map_data->player.dir_y * move_speed;
		else if (can_move_y_backwards(map_data, move_speed))
			map_data->player.y -= map_data->player.dir_y * move_speed;
		if (can_move_x_forward(map_data, move_speed))
			map_data->player.x += map_data->player.dir_x * move_speed;
		else if (can_move_x_backwards(map_data, move_speed))
			map_data->player.x -= map_data->player.dir_x * move_speed;
	}
	else if (map_data->keysym_states[KEY_S])
	{
		if (can_move_y_backwards(map_data, move_speed))
			map_data->player.y -= map_data->player.dir_y * move_speed;
		else if (can_move_y_forward(map_data, move_speed))
			map_data->player.y += map_data->player.dir_y * move_speed;
		if (can_move_x_backwards(map_data, move_speed))
			map_data->player.x -= map_data->player.dir_x * move_speed;
		else if (can_move_x_forward(map_data, move_speed))
			map_data->player.x += map_data->player.dir_x * move_speed;
	}
}
