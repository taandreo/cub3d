/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_player_data.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebezerra <ebezerra@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/15 04:30:52 by ebezerra          #+#    #+#             */
/*   Updated: 2024/03/15 04:33:20 by ebezerra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	init_north_south_directions(t_map_data *map_data, char direction)
{
	if (direction == 'N')
	{
		map_data->player.dir_x = 0;
		map_data->player.dir_y = -1;
		map_data->player.plane_x = 0.66;
		map_data->player.plane_y = 0;
	}
	else if (direction == 'S')
	{
		map_data->player.dir_x = 0;
		map_data->player.dir_y = 1;
		map_data->player.plane_x = -0.66;
		map_data->player.plane_y = 0;
	}
}

static void	init_west_east_directions(t_map_data *map_data, char direction)
{
	if (direction == 'W')
	{
		map_data->player.dir_x = -1;
		map_data->player.dir_y = 0;
		map_data->player.plane_x = 0;
		map_data->player.plane_y = -0.66;
	}
	else if (direction == 'E')
	{
		map_data->player.dir_x = 1;
		map_data->player.dir_y = 0;
		map_data->player.plane_x = 0;
		map_data->player.plane_y = 0.66;
	}
}

static void	init_vectors(t_map_data *map_data, char direction)
{
	if (direction == 'N' || direction == 'S')
		init_north_south_directions(map_data, direction);
	else if (direction == 'W' || direction == 'E')
		init_west_east_directions(map_data, direction);
}

void	init_player(t_map_data *map_data)
{
	int	i;
	int	j;

	i = 0;
	while (map_data->map[i])
	{
		j = 0;
		while (map_data->map[i][j])
		{
			if (ft_isalpha(map_data->map[i][j]))
			{
				map_data->player.y = i;
				map_data->player.x = j;
				init_vectors(map_data, map_data->map[i][j]);
				return ;
			}
			j++;
		}
		i++;
	}
}
