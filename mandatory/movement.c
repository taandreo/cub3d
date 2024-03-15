/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebezerra <ebezerra@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/15 02:04:34 by ebezerra          #+#    #+#             */
/*   Updated: 2024/03/15 07:58:22 by ebezerra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	handle_movement(t_map_data *map_data)
{
	double	move_speed;
	double	rotation_speed;

	move_speed = 0.03 * 5.0;
	rotation_speed = 0.03 * 3.0;
	if (map_data->keysym_states[KEY_LEFT])
		rotate_left(map_data, rotation_speed);
	if (map_data->keysym_states[KEY_RIGHT])
		rotate_right(map_data, rotation_speed);
	if (map_data->keysym_states[KEY_W] || map_data->keysym_states[KEY_S])
		calculate_forward_and_backward_movement(map_data, move_speed);
	if (map_data->keysym_states[KEY_A] || map_data->keysym_states[KEY_D])
		calculate_strafe(map_data, move_speed);
}
