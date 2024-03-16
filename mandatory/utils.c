/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tairribe <tairribe@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/16 20:10:51 by ebezerra          #+#    #+#             */
/*   Updated: 2024/03/16 20:54:36 by tairribe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	open_file(char *filename)
{
    int	fd;

    fd = open(filename, O_RDONLY);
    if (fd < 0)
    {
        ft_dprintf(STDERR_FILENO, "Error reading file %s", filename);
        exit(1);
    }
    return (fd);
}

void   error_and_exit(char *msg)
{
	ft_dprintf(STDERR_FILENO, "Error\n%s\n", msg);
	exit(1);
}

void	free_and_error(t_map_data *map_data, char *msg)
{
	free_map_data(map_data);
	error_and_exit(msg);
}

void	free_map_data(t_map_data *map_data)
{
	int	y;

	y = 0;
	while (map_data->map[y])
	{
		free(map_data->map[y]);
		y++;
	}
	if (map_data->map)
		free(map_data->map);
	if (map_data->tex.tex_file_north)
		free(map_data->tex.tex_file_north);
	if (map_data->tex.tex_file_south)
		free(map_data->tex.tex_file_south);
	if (map_data->tex.tex_file_east)
		free(map_data->tex.tex_file_east);
	if (map_data->tex.tex_file_west)
		free(map_data->tex.tex_file_west);
	map_data->map = NULL;
}

