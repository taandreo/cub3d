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

char	*free_then_gnl(char *line, int fd)
{
	free(line);
	return (get_next_line(fd));
}

void	*clear_list_return_null(t_list **map_list)
{
	ft_lstclear(map_list, free);
	return (NULL);
}

t_list	*read_map_list(char *line, int fd)
{
	size_t	i;
	t_list	*map_list;

	map_list = NULL;
	if (line == NULL)
		return (NULL);
	while (is_empty(line))
		line = free_then_gnl(line, fd);
	while (line)
	{
		i = 0;
		while (line[i] && ft_strchr("01NSEW ", line[i]))
			i++;
		if (!ft_strchr("\n\0", line[i]))
			clear_list_return_null(&map_list);
		if (line[i] == '\n' && i != 0)
			line[i] = '\0';
		if (line[i] == '\n')
			clear_list_return_null(&map_list);
		ft_lstadd_back(&map_list, ft_lstnew(line));
		line = free_then_gnl(line, fd);
	}
	return (map_list);
}

char	*read_texture(t_map_data *map_data, int fd)
{
	char	*line;

	line = get_next_line(fd);
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
		line = get_next_line(fd);
	}
	if (!check_texture(map_data))
		free_and_error(map_data, "Texture or colors misconfiguration");
	return (line);
}
