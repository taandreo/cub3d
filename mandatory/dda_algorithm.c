/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dda_algorithm.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebezerra <ebezerra@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/15 07:29:31 by ebezerra          #+#    #+#             */
/*   Updated: 2024/03/15 07:43:12 by ebezerra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	calculate_side_dist(t_rays *rays)
{
	if (rays->side_dist_x < rays->side_dist_y)
	{
		rays->side_dist_x += rays->delta_dist_x;
		rays->map_x += rays->step_x;
		rays->side = 0;
	}
	else
	{
		rays->side_dist_y += rays->delta_dist_y;
		rays->map_y += rays->step_y;
		rays->side = 1;
	}
}

void	dda_line_algorithm(t_map_data *map_data, t_rays *rays)
{
	rays->hit = 0;
	while (!rays->hit)
	{
		calculate_side_dist(rays);
		if (rays->map_y < 0)
			rays->map_y = 0;
		else if (rays->map_y >= map_data->map_rows)
			rays->map_y = map_data->map_rows - 1;
		if (rays->map_x < 0)
			rays->map_x = 0;
		else if (rays->map_x >= (int)ft_strlen(map_data->map[rays->map_y]))
			rays->map_x = (int)ft_strlen(map_data->map[rays->map_y]) - 1;
		if (map_data->map[rays->map_y][rays->map_x] == '1')
			rays->hit = 1;
	}
}
