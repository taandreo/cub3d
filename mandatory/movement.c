/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebezerra <ebezerra@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/15 02:04:34 by ebezerra          #+#    #+#             */
/*   Updated: 2024/03/15 02:21:30 by ebezerra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void handle_movement(t_map_data *map_data)
{
	double move_speed = 0.025 * 5.0;
	double rotation_speed = 0.02 * 5.0;

	if (map_data->keysym_states[KEY_LEFT])
		rotate_left(map_data, rotation_speed);
	if (map_data->keysym_states[KEY_RIGHT])
		rotate_right(map_data, rotation_speed);
	if (map_data->keysym_states[KEY_W] || map_data->keysym_states[KEY_S])
		calculate_forward_and_backward_movement(map_data, move_speed);
	if (map_data->keysym_states[KEY_A] || map_data->keysym_states[KEY_D])
		calculate_strafe(map_data, move_speed);
}
