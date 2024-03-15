/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tairribe <tairribe@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/20 22:54:16 by tairribe          #+#    #+#             */
/*   Updated: 2024/03/15 02:41:39 by ebezerra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void map_sample(t_map_data *map_data)
{
	int fd;
	char *gnl;
	int map_rows;
	int i;
	int max_column;

	fd = open("test.cub", O_RDONLY);
	map_data->max_columns = 0;
	gnl = get_next_line(fd);
	map_rows = 0;
	while (gnl)
	{
		map_rows++;
		max_column = ft_strlen(ft_strtrim(gnl, "\n"));
		if (max_column > map_data->max_columns)
			map_data->max_columns = max_column;
		free(gnl);
		gnl = get_next_line(fd);
	}
	close(fd);
	map_data->map = malloc((map_rows + 1) * sizeof(char *));
	map_data->map[map_rows] = NULL;
	fd = open("test.cub", O_RDONLY);
	gnl = get_next_line(fd);
	i = 0;
	while (gnl)
	{
		map_data->map[i] = ft_strdup(ft_strtrim(gnl, "\n"));
		i++;
		free(gnl);
		gnl = get_next_line(fd);
	}
	map_data->map_rows = map_rows;
	if (map_data->map_rows >= map_data->max_columns)
		map_data->scale_factor = WINDOW_HEIGHT / map_data->map_rows;
	else
		map_data->scale_factor = WINDOW_WIDTH / map_data->max_columns;
	close(fd);
	map_data->tex.tex_file_east = ft_strdup("./img/greystone.xpm");
	map_data->tex.tex_file_west = ft_strdup("./img/mossy.xpm");
	map_data->tex.tex_file_north = ft_strdup("./img/redbrick.xpm");
	map_data->tex.tex_file_south = ft_strdup("./img/colorstone.xpm");
}

int main(void)
{
	t_map_data map_data;

	map_sample(&map_data);
	for (int i = 0; i < map_data.map_rows; i++)
	{
		ft_printf("%s\n", map_data.map[i]);
	}
	ft_memset(map_data.keysym_states, 0, sizeof(map_data.keysym_states));
	init_player(&map_data);
	initialize_mlx(&map_data);
	mlx_loop_hook(map_data.mlx_ptr, &render, &map_data);
	mlx_hook(map_data.win_ptr, KEY_RELEASE, KEY_RELEASE_MASK, &handle_keyrelease, &map_data);
	mlx_hook(map_data.win_ptr, KEY_PRESS, KEY_PRESS_MASK, &handle_keypress, &map_data);
	mlx_hook(map_data.win_ptr, DESTROY_NOTIFY, STRUCTURE_NOTIFY_MASK, &handle_mouse, &map_data);
	mlx_loop(map_data.mlx_ptr);
	return (0);
}
