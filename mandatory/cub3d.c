/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tairribe <tairribe@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/20 22:54:16 by tairribe          #+#    #+#             */
/*   Updated: 2024/03/16 20:58:40 by tairribe         ###   ########.fr       */
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

void	set_texture(char *line, t_map_data *map_data)
{
	int	rgb;

	if (ft_startswith(line, "SO "))
		map_data->tex.tex_file_south = ft_strtrim(line + 3, " ");
	else if (ft_startswith(line, "NO "))
		map_data->tex.tex_file_north = ft_strtrim(line + 3, " ");
	else if (ft_startswith(line, "WE "))
		map_data->tex.tex_file_west = ft_strtrim(line + 3, " ");
	else if (ft_startswith(line, "EA "))
		map_data->tex.tex_file_east = ft_strtrim(line + 3, " ");
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

void	read_map_file(char *filename, t_map_data *map_data)
{
	int	fd;
	char *line;

	fd = open_file(filename);
	line = get_next_line(fd);
	(void) map_data;
	while(line)
	{
		if (is_texture(line))
			set_texture(line, map_data);
		else if (!is_empty(line))
		{
			free(line);
			ft_dprintf(STDERR_FILENO, "Error\nReading file\n");
			exit(1);
		}
		free(line);
		line = get_next_line(fd);
	}
	// read_map(line)
	ft_printf("NO: %s\n", map_data->tex.tex_file_north);
	ft_printf("SO: %s\n", map_data->tex.tex_file_south);
	ft_printf("WE: %s\n", map_data->tex.tex_file_west);
	ft_printf("EA: %s\n", map_data->tex.tex_file_east);
	ft_printf("C: %d\n", map_data->tex.ceiling_color);
	ft_printf("F: %d\n", map_data->tex.floor_color);
	if (!check_texture(map_data))
	{
		ft_dprintf(STDERR_FILENO, "Error\nReading file\n");
		exit(1);
	}

}

// void	map_sample(char *filename, t_map_data *map_data)
// {
// 	int fd;
// 	char *gnl;
// 	int map_rows;
// 	int i;
// 	int max_column;

// 	fd = open_file(filename);
// 	map_data->max_columns = 0;
// 	gnl = get_next_line(fd);
// 	map_rows = 0;
// 	while (gnl)
// 	{
// 		map_rows++;
// 		max_column = ft_strlen(ft_strtrim(gnl, "\n"));
// 		if (max_column > map_data->max_columns)
// 			map_data->max_columns = max_column;
// 		gnl = get_next_line(fd);
// 	}
// 	close(fd);
// 	map_data->map = malloc((map_rows + 1) * sizeof(char *));
// 	map_data->map[map_rows] = NULL;
// 	fd = open("test.cub", O_RDONLY);
// 	gnl = get_next_line(fd);
// 	i = 0;
// 	while (gnl)
// 	{
// 		map_data->map[i] = ft_strdup(ft_strtrim(gnl, "\n"));
// 		i++;
// 		gnl = get_next_line(fd);
// 	}
// 	map_data->map_rows = map_rows;
// 	if (map_data->map_rows >= map_data->max_columns)
// 		map_data->scale_factor = WINDOW_HEIGHT / map_data->map_rows;
// 	else
// 		map_data->scale_factor = WINDOW_WIDTH / map_data->max_columns;
// 	close(fd);
// 	map_data->tex.tex_file_east = ft_strdup("./img/greystone.xpm");
// 	map_data->tex.tex_file_west = ft_strdup("./img/mossy.xpm");
// 	map_data->tex.tex_file_north = ft_strdup("./img/redbrick.xpm");
// 	map_data->tex.tex_file_south = ft_strdup("./img/colorstone.xpm");
// }

void	init_map_data(t_map_data *map_data)
{
	map_data->tex.ceiling_color = -1;
	map_data->tex.floor_color   = -1;
	map_data->tex.tex_file_east = NULL;
	map_data->tex.tex_file_west = NULL;
	map_data->tex.tex_file_north = NULL;
	map_data->tex.tex_file_south = NULL;
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
	// for (int i = 0; i < map_data.map_rows; i++)
	// {
	// 	ft_printf("%s\n", map_data.map[i]);
	// }
	// init_player(&map_data);
	// initialize_mlx(&map_data);
	// mlx_loop_hook(map_data.mlx_ptr, &render, &map_data);
	// mlx_hook(map_data.win_ptr, KEY_RELEASE, KEY_RELEASE_MASK, &handle_keyrelease, &map_data);
	// mlx_hook(map_data.win_ptr, KEY_PRESS, KEY_PRESS_MASK, &handle_keypress, &map_data);
	// mlx_hook(map_data.win_ptr, DESTROY_NOTIFY, STRUCTURE_NOTIFY_MASK, &handle_mouse, &map_data);
	// mlx_loop(map_data.mlx_ptr);
	return (0);
}
