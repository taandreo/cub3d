/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_validation_2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebezerra <ebezerra@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/18 11:17:40 by ebezerra          #+#    #+#             */
/*   Updated: 2024/03/18 08:09:15 by ebezerra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

char	*read_empty_lines(char *line, int fd)
{
	while (is_empty(line))
	{
		free(line);
		line = get_next_line(fd);
	}
	return (line);
}

void	*clear_list_return_null(t_list **map_list, char *line)
{
	if (line)
		free(line);
	ft_lstclear(map_list, free);
	return (NULL);
}

t_list	*read_map_list(char *line, int fd)
{
	size_t	i;
	t_list	*map_list;

	map_list = NULL;
	line = read_empty_lines(line, fd);
	while (line)
	{
		i = 0;
		while (line[i] && ft_strchr("01NSEW ", line[i]))
			i++;
		if (!ft_strchr("\n\0", line[i]))
			return (clear_list_return_null(&map_list, line));
		if (line[i] == '\n' && i != 0)
			line[i] = '\0';
		if (line[i] == '\n')
			return (clear_list_return_null(&map_list, line));
		ft_lstadd_back(&map_list, ft_lstnew(line));
		line = get_next_line(fd);
	}
	return (map_list);
}

char	*read_texture(t_map_data *map_data)
{
	char	*line;

	line = get_next_line(map_data->fd);
	while (!check_texture(map_data) && line)
	{
		if (is_texture(line))
		{
			if (is_texture_set(line, map_data))
			{
				free(line);
				free_and_error(map_data, "Texture already set");
			}
			set_texture(line, map_data);
		}
		else if (!is_empty(line))
		{
			free(line);
			free_and_error(map_data, "Reading file");
		}
		free(line);
		line = get_next_line(map_data->fd);
	}
	if (!check_texture(map_data))
		free_and_error(map_data, "Texture or colors misconfiguration");
	return (line);
}
