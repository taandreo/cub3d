/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_validation.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebezerra <ebezerra@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/18 11:14:39 by ebezerra          #+#    #+#             */
/*   Updated: 2024/03/18 11:36:18 by ebezerra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

void	set_player_position(t_map_data *map_data)
{
	int	y;
	int	x;

	y = -1;
	while (map_data->map[++y])
	{
		x = -1;
		while (map_data->map[y][++x])
		{
			if (ft_strchr("NSEW", map_data->map[y][x]))
			{
				if (map_data->start_x != -1)
					free_and_error(map_data,
						"More then one player start position");
				map_data->start = map_data->map[y][x];
				map_data->start_x = x;
				map_data->start_y = y;
			}
		}
	}
}

t_bool	flood_fill(t_map_data *map_data, int x, int y)
{
	if (x < 0 || x >= map_data->line_size[y]
		|| y < 0 || y >= map_data->map_rows)
		return (false);
	if (map_data->map[y][x] == '1' || map_data->map[y][x] == 'x')
		return (true);
	if (map_data->map[y][x] == ' ')
		return (false);
	map_data->map[y][x] = 'x';
	if (!flood_fill(map_data, x, y + 1))
		return (false);
	if (!flood_fill(map_data, x + 1, y))
		return (false);
	if (!flood_fill(map_data, x, y - 1))
		return (false);
	if (!flood_fill(map_data, x - 1, y))
		return (false);
	return (true);
}

void	recreate_map(t_map_data *map_data)
{
	int	x;
	int	y;

	y = -1;
	while (map_data->map[++y])
	{
		x = -1;
		while (map_data->map[y][++x])
		{
			if (map_data->map[y][x] == 'x')
				map_data->map[y][x] = '0';
		}
	}
	map_data->map[map_data->start_y][map_data->start_x] = map_data->start;
}

t_bool	is_a_valid_map(t_map_data *map_data)
{
	t_bool	valid_map;

	set_player_position(map_data);
	if (map_data->start_x == -1)
		free_and_error(map_data, "No player start position");
	valid_map = flood_fill(map_data, map_data->start_x, map_data->start_y);
	recreate_map(map_data);
	return (valid_map);
}

void	read_map_file(char *filename, t_map_data *map_data)
{
	char	*line;
	t_list	*map_list;

	if (!ft_endswith(filename, ".cub"))
		free_and_error(map_data, "Invalid file extension");
	map_data->fd = open_file(filename);
	line = read_texture(map_data);
	if (!line)
		free_and_error(map_data, "Missing Map");
	map_list = read_map_list(line, map_data->fd);
	if (map_list == NULL)
		free_and_error(map_data, "Parsing map file");
	list_to_array(map_data, map_list);
	if (!is_a_valid_map(map_data))
		free_and_error(map_data, "Map is invalid");
}
