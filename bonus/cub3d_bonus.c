/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebezerra <ebezerra@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/20 22:54:16 by tairribe          #+#    #+#             */
/*   Updated: 2024/03/18 11:33:39 by ebezerra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

int	main(int argc, char *argv[])
{
	t_map_data	map_data;

	if (argc != 2)
	{
		ft_dprintf(STDERR_FILENO, "Usage: ./cub3d map_name\n");
		return (1);
	}
	init_map_data(&map_data);
	read_map_file(argv[1], &map_data);
	print_map(&map_data);
	init_player(&map_data);
	initialize_mlx(&map_data);
	mlx_loop_hook(map_data.mlx_ptr, &render, &map_data);
	mlx_hook(map_data.win_ptr, KEY_RELEASE, KEY_RELEASE_MASK,
		&handle_keyrelease, &map_data);
	mlx_hook(map_data.win_ptr, KEY_PRESS, KEY_PRESS_MASK, &handle_keypress,
		&map_data);
	mlx_hook(map_data.win_ptr, DESTROY_NOTIFY, STRUCTURE_NOTIFY_MASK,
		&handle_mouse, &map_data);
	mlx_loop(map_data.mlx_ptr);
	return (0);
}
