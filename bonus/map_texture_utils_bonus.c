/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_texture_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebezerra <ebezerra@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/18 11:19:25 by ebezerra          #+#    #+#             */
/*   Updated: 2024/03/18 11:32:12 by ebezerra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

t_bool	is_texture_set(char *line, t_map_data *map_data)
{
	if (ft_startswith(line, "NO "))
		return (map_data->tex.tex_file_north != NULL);
	if (ft_startswith(line, "SO "))
		return (map_data->tex.tex_file_south != NULL);
	if (ft_startswith(line, "WE "))
		return (map_data->tex.tex_file_west != NULL);
	if (ft_startswith(line, "EA "))
		return (map_data->tex.tex_file_east != NULL);
	if (ft_startswith(line, "C "))
		return (map_data->tex.ceiling_color != -1);
	return (map_data->tex.floor_color != -1);
}

void	set_texture(char *line, t_map_data *map_data)
{
	int	rgb;

	if (ft_startswith(line, "SO "))
		map_data->tex.tex_file_south = ft_strtrim(line + 3, " \n");
	else if (ft_startswith(line, "NO "))
		map_data->tex.tex_file_north = ft_strtrim(line + 3, " \n");
	else if (ft_startswith(line, "WE "))
		map_data->tex.tex_file_west = ft_strtrim(line + 3, " \n");
	else if (ft_startswith(line, "EA "))
		map_data->tex.tex_file_east = ft_strtrim(line + 3, " \n");
	else if (ft_startswith(line, "C ") || ft_startswith(line, "F "))
	{
		rgb = to_rgb(line + 2);
		if (rgb == -1)
			free_and_error(map_data, "Colors misconfiguration");
		if (ft_startswith(line, "F "))
			map_data->tex.floor_color = rgb;
		else
			map_data->tex.ceiling_color = rgb;
	}
}

t_bool	check_texture(t_map_data *map_data)
{
	if (!map_data->tex.tex_file_south
		|| !map_data->tex.tex_file_north
		|| !map_data->tex.tex_file_west
		|| !map_data->tex.tex_file_east
		|| map_data->tex.ceiling_color == -1
		|| map_data->tex.floor_color == -1)
		return (false);
	return (true);
}
