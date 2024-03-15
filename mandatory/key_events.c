/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_events.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebezerra <ebezerra@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/15 00:36:51 by ebezerra          #+#    #+#             */
/*   Updated: 2024/03/15 02:00:44 by ebezerra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int keysym_to_index(int keysym)
{
	if (keysym == XK_W)
		return (KEY_W);
	if (keysym == XK_A)
		return (KEY_A);
	if (keysym == XK_S)
		return (KEY_S);
	if (keysym == XK_D)
		return (KEY_D);
	if (keysym == XK_RIGHT)
		return (KEY_RIGHT);
	if (keysym == XK_LEFT)
		return (KEY_LEFT);
	return (-1);
}

int handle_keypress(int keysym, t_map_data *map_data)
{
	int index;

	index = keysym_to_index(keysym);
	if (index >= 0)
		map_data->keysym_states[index] = true;
	return (0);
}

int handle_keyrelease(int keysym, t_map_data *map_data)
{
	int index;

	index = keysym_to_index(keysym);
	if (keysym == XK_ESCAPE)
	{
		kill_mlx(map_data);
		return (0);
	}
	if (index >= 0)
		map_data->keysym_states[index] = false;
	return (0);
}
