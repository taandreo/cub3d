/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebezerra <ebezerra@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/16 20:10:51 by ebezerra          #+#    #+#             */
/*   Updated: 2024/03/16 20:13:10 by ebezerra         ###   ########.fr       */
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

void	free_and_error(char *msg)
{
	ft_dprintf(STDERR_FILENO, "Error\n%s\n", msg);
	exit(1);
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
	free(map_data->map);
	free(map_data->tex.tex_file_north);
	free(map_data->tex.tex_file_south);
	free(map_data->tex.tex_file_east);
	free(map_data->tex.tex_file_west);
	map_data->map = NULL;
}

