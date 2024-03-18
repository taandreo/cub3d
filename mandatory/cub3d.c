/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tairribe <tairribe@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/20 22:54:16 by tairribe          #+#    #+#             */
/*   Updated: 2024/03/17 23:53:11 by ebezerra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

t_bool	is_texture(char *texture)
{
	if (ft_startswith(texture, "NO "))
		return (true);
	if (ft_startswith(texture, "SO "))
		return (true);
	if (ft_startswith(texture, "WE "))
		return (true);
	if (ft_startswith(texture, "EA "))
		return (true);
	if (ft_startswith(texture, "C "))
		return (true);
	if (ft_startswith(texture, "F "))
		return (true);
	return (false);
}

int rgb_to_int(int r, int g, int b) {
    return (r << 16) | (g << 8) | b;
}

int to_rgb(char *line)
{
	char	*rgbstr;
	char	**rgb;
	t_bool 	is_rgb;
	int		rgb_int;

	is_rgb = true;
	rgbstr = ft_strtrim(line, " \n");
	rgb = ft_split(rgbstr, ',');
	free(rgbstr);
	if (ft_lenmt((void **) rgb) != 3)
	{
		ft_freemt((void **) rgb);
		return (-1);
	}
	if (!ft_is_number(rgb[0]) || ft_atoi(rgb[0]) < 0 || ft_atoi(rgb[0]) > 255)
		is_rgb = false;
	if (!ft_is_number(rgb[1]) || ft_atoi(rgb[1]) < 0 || ft_atoi(rgb[1]) > 255)
		is_rgb = false;
	if (!ft_is_number(rgb[2]) || ft_atoi(rgb[2]) < 0 || ft_atoi(rgb[2]) > 255)
		is_rgb = false;
	rgb_int = rgb_to_int(ft_atoi(rgb[0]), ft_atoi(rgb[1]), ft_atoi(rgb[2]));
	ft_freemt((void **) rgb);
	if (is_rgb)
		return (rgb_int);
	return (-1);	
}

t_bool is_empty(char *line)
{
	while (*line)
	{
		if (!ft_is_space(*line))
			return (false);
		line++;
	}
	return (true);
}

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
		{
			ft_dprintf(STDERR_FILENO, "Error\nReading file\n");
			exit(1);
		}
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

void	free_list(t_list *list)
{
	t_list *next;

	while (list)
	{
		next = list->next;
		free(list);
		list = next;
	}
}

void	list_to_array(t_map_data *map_data, t_list *map_list)
{
	int i;

	i = 0;
	map_data->map_rows = ft_lstsize(map_list);
	map_data->map = ft_calloc(map_data->map_rows + 1, sizeof(char *));
	map_data->line_size = ft_calloc(map_data->map_rows, sizeof(int));
	while(map_list)
	{
		map_data->map[i] = map_list->content;
		map_data->line_size[i] = ft_strlen(map_list->content);
		map_list = map_list->next;
		i++;
	}
	map_data->map[i] = NULL;
	free_list(map_list);
}

void	print_map(t_map_data *map_data)
{
	int i;

	i = 0;
	while (i < map_data->map_rows)
	{
		ft_printf("%s\n", map_data->map[i]);
		i++;
	}
}

t_list	*read_map_list(char *line, int fd)
{
	size_t	i;
	t_list	*map_list;

	i = 0;
	map_list = NULL;
	if (line == NULL)
		return (NULL);
	while(is_empty(line))
	{
		free(line);
		line = get_next_line(fd);
	}
	while(line)
	{
		while (ft_strchr("01NSEW ", line[i]))
			i++;
		if (!ft_strchr("\n\0", line[i]) && line[i] != 33)
		{
			ft_lstclear(&map_list, free);
			return(NULL);
		}
		if (line[i] == '\n')
			line[i] = '\0';
		i = 0;
		ft_lstadd_back(&map_list, ft_lstnew(line));
		line = get_next_line(fd);
	}
	return(map_list);
}

char	*read_texture(t_map_data *map_data, int fd)
{
	char *line;

	line = get_next_line(fd);
	while(!check_texture(map_data) && line)
	{
		if (is_texture(line))
		{
			if (is_texture_set(line, map_data))
				free_and_error(map_data, "Texture already set");
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
		free_and_error(map_data, "Reading file");
	return (line);
}

void	set_player_position(t_map_data *map_data)
{
	int y;
	int x;
	
	y = -1;
	while (map_data->map[++y])
	{
		x = -1;
		while(map_data->map[y][++x])
		{
			if (ft_strchr("NSEW", map_data->map[y][x]))
			{
				if (map_data->start_x != -1)
					free_and_error(map_data, "More then one player start position");
				map_data->start = map_data->map[y][x];
				map_data->start_x = x;
				map_data->start_y = y;
			}
		}
	}
}

t_bool	flood_fill(t_map_data *map_data, int x, int y)
{
	if (x < 0 || x >= map_data->line_size[y] || y < 0 || y >= map_data->map_rows)
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
	int x;
	int y;

	y = -1;
	while(map_data->map[++y])
	{
		x = -1;
		while(map_data->map[y][++x])
		{
			if (map_data->map[y][x] == 'x')
				map_data->map[y][x] = '0';
		}
	}
	map_data->map[map_data->start_y][map_data->start_x] = map_data->start;
}

t_bool	is_a_valid_map(t_map_data *map_data)
{
	t_bool valid_map;

	set_player_position(map_data);
	if (map_data->start_x == -1)
		free_and_error(map_data, "No player start position");
	valid_map = flood_fill(map_data, map_data->start_x, map_data->start_y);
	recreate_map(map_data);
	return(valid_map);
}


void	read_map_file(char *filename, t_map_data *map_data)
{
	int	fd;
	char *line;
	t_list *map_list;

	if (!ft_endswith(filename, ".cub"))
		free_and_error(map_data, "Invalid file extension");
	fd = open_file(filename);
	line = read_texture(map_data, fd);
	map_list = read_map_list(line, fd);
	if (map_list == NULL)
		free_and_error(map_data, "Reading map data");
	list_to_array(map_data, map_list);
	// print_map(map_data);
	// ft_printf("\n");
	if (is_a_valid_map(map_data))
		ft_printf("Map is valid\n");
	else
		ft_printf("Map is not valid\n");	
	// print_map(map_data);
	// ft_printf("\n");
	// recreate_map(map_data);
	// print_map(map_data);
}

void	init_map_data(t_map_data *map_data)
{
	map_data->tex.ceiling_color = -1;
	map_data->tex.floor_color   = -1;
	map_data->tex.tex_file_east = NULL;
	map_data->tex.tex_file_west = NULL;
	map_data->tex.tex_file_north = NULL;
	map_data->tex.tex_file_south = NULL;
	map_data->start_x = -1;
	map_data->start_y = -1;
	map_data->map = NULL;
	map_data->start = '\0';
}

int main(int argc, char *argv[])
{
	t_map_data	map_data;

	if (argc != 2)
	{
		ft_dprintf(STDERR_FILENO, "Usage: ./cub3d map_name\n");
		return(1);
	}
	init_map_data(&map_data);
	read_map_file(argv[1], &map_data);
	init_player(&map_data);
	initialize_mlx(&map_data);
	mlx_loop_hook(map_data.mlx_ptr, &render, &map_data);
	mlx_hook(map_data.win_ptr, KEY_RELEASE, KEY_RELEASE_MASK, &handle_keyrelease, &map_data);
	mlx_hook(map_data.win_ptr, KEY_PRESS, KEY_PRESS_MASK, &handle_keypress, &map_data);
	mlx_hook(map_data.win_ptr, DESTROY_NOTIFY, STRUCTURE_NOTIFY_MASK, &handle_mouse, &map_data);
	mlx_loop(map_data.mlx_ptr);
	return (0);
}
