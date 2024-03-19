/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_validation_utils.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebezerra <ebezerra@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/18 11:21:27 by ebezerra          #+#    #+#             */
/*   Updated: 2024/03/18 11:34:08 by ebezerra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

t_bool	is_empty(char *line)
{
	while (*line)
	{
		if (!ft_is_space(*line))
			return (false);
		line++;
	}
	return (true);
}

void	free_list(t_list *list)
{
	t_list	*next;

	while (list)
	{
		next = list->next;
		free(list);
		list = next;
	}
}

void	list_to_array(t_map_data *map_data, t_list *map_list)
{
	int		i;
	t_list	*current_map_list;

	i = 0;
	map_data->map_rows = ft_lstsize(map_list);
	map_data->map = ft_calloc(map_data->map_rows + 1, sizeof(char *));
	map_data->line_size = ft_calloc(map_data->map_rows, sizeof(int));
	current_map_list = map_list;
	while (current_map_list)
	{
		map_data->map[i] = current_map_list->content;
		map_data->line_size[i] = (int)ft_strlen(current_map_list->content);
		current_map_list = current_map_list->next;
		i++;
	}
	free_list(map_list);
}

void	print_map(t_map_data *map_data)
{
	int	i;

	i = 0;
	while (i < map_data->map_rows)
	{
		ft_printf("%s\n", map_data->map[i]);
		i++;
	}
}

void	init_map_data(t_map_data *map_data)
{
	map_data->tex.ceiling_color = -1;
	map_data->tex.floor_color = -1;
	map_data->tex.tex_file_east = NULL;
	map_data->tex.tex_file_west = NULL;
	map_data->tex.tex_file_north = NULL;
	map_data->tex.tex_file_south = NULL;
	map_data->tex.texture_north = NULL;
	map_data->tex.texture_east = NULL;
	map_data->tex.texture_south = NULL;
	map_data->tex.texture_west = NULL;
	map_data->tex.text_addr_north = NULL;
	map_data->tex.text_addr_east = NULL;
	map_data->tex.text_addr_south = NULL;
	map_data->tex.text_addr_west = NULL;
	map_data->mlx_ptr = NULL;
	map_data->win_ptr = NULL;
	map_data->img.mlx_img = NULL;
	map_data->img.addr = NULL;
	map_data->img.line_len = 0;
	map_data->img.bpp = 0;
	map_data->img.endian = 0;
	map_data->start_x = -1;
	map_data->start_y = -1;
	map_data->map = NULL;
	map_data->start = '\0';
	ft_memset(map_data->keysym_states, 0, sizeof(map_data->keysym_states));
}
