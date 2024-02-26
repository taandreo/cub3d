/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tairribe <tairribe@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/20 22:54:16 by tairribe          #+#    #+#             */
/*   Updated: 2024/02/26 00:35:58 by ebezerra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include <fcntl.h>

void map_sample(t_map_data *map_data)
{
	int fd;
	char *gnl;
	int map_rows;
	int i;

	fd = open("test.cub", O_RDONLY);
	gnl = get_next_line(fd);
	map_rows = 0;
	while (gnl)
	{
		map_rows++;
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
		gnl = get_next_line(fd);
	}
	map_data->map_rows = map_rows;
}

int main(void)
{
	t_map_data map_data;

	map_sample(&map_data);
	for (int i = 0; i < map_data.map_rows; i++)
	{
		ft_printf("%s\n", map_data.map[i]);
	}
	init_player(&map_data);
	initialize_mlx(&map_data);
	mlx_loop_hook(map_data.mlx_ptr, &render, &map_data);
	mlx_hook(map_data.win_ptr, KEY_RELEASE, KEY_RELEASE_MASK, &handle_keyrelease, &map_data);
	mlx_hook(map_data.win_ptr, KEY_PRESS, KEY_PRESS_MASK, &handle_keypress, &map_data);
	mlx_hook(map_data.win_ptr, DESTROY_NOTIFY, STRUCTURE_NOTIFY_MASK, &handle_mouse, &map_data);
	mlx_loop(map_data.mlx_ptr);
	return (0);
}
