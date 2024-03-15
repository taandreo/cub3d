/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   calculate_strafe.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebezerra <ebezerra@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/15 00:39:22 by ebezerra          #+#    #+#             */
/*   Updated: 2024/03/15 03:36:33 by ebezerra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

t_bool	can_move_right(t_map_data *map_data, double move_speed)
{
	int	next_y;
	int	next_x;

	next_y = map_data->player.y + map_data->player.plane_y * move_speed;
	next_x = map_data->player.x + map_data->player.plane_x * move_speed;
	if (next_y >= 0 && next_y < map_data->map_rows && next_x >= 0
		&& next_x < (int)ft_strlen(map_data->map[(int)map_data->player.y]))
	{
		if ((map_data->map[next_y][(int)map_data->player.x] == '0'
			&& map_data->map[(int)map_data->player.y][next_x] == '0')
			|| (ft_isalpha(map_data->map[next_y][(int)map_data->player.x])
			&& ft_isalpha(map_data->map[(int)map_data->player.y][next_x])))
			return (true);
		return (false);
	}
	return (false);
}

t_bool	can_move_left(t_map_data *map_data, double move_speed)
{
	int	next_y;
	int	next_x;

	next_y = map_data->player.y - map_data->player.plane_y * move_speed;
	next_x = map_data->player.x - map_data->player.plane_x * move_speed;
	if (next_y >= 0 && next_y < map_data->map_rows && next_x >= 0
		&& next_x < (int)ft_strlen(map_data->map[(int)map_data->player.y]))
	{
		if ((map_data->map[next_y][(int)map_data->player.x] == '0'
			&& map_data->map[(int)map_data->player.y][next_x] == '0')
			|| (ft_isalpha(map_data->map[next_y][(int)map_data->player.x])
			&& ft_isalpha(map_data->map[(int)map_data->player.y][next_x])))
			return (true);
		return (false);
	}
	return (false);
}

void	subtract_x_y(t_map_data *map_data, double move_speed)
{
	map_data->player.x -= map_data->player.plane_x * move_speed;
	map_data->player.y -= map_data->player.plane_y * move_speed;
}

void	add_x_y(t_map_data *map_data, double move_speed)
{
	map_data->player.x += map_data->player.plane_x * move_speed;
	map_data->player.y += map_data->player.plane_y * move_speed;
}

void	calculate_strafe(t_map_data *map_data, double move_speed)
{
	if (map_data->keysym_states[KEY_A])
	{
		if (can_move_left(map_data, move_speed))
			subtract_x_y(map_data, move_speed);
		else if (can_move_right(map_data, move_speed))
			add_x_y(map_data, move_speed);
	}
	else if (map_data->keysym_states[KEY_D])
	{
		if (can_move_right(map_data, move_speed))
			add_x_y(map_data, move_speed);
		else if (can_move_left(map_data, move_speed))
			subtract_x_y(map_data, move_speed);
	}
}
