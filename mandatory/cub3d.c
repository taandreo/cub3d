/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tairribe <tairribe@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/20 22:54:16 by tairribe          #+#    #+#             */
/*   Updated: 2024/02/20 23:28:20 by tairribe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

char	*map_sample(void)
{
	char *map;
	map = ft_strdup("111111\n100101\n101001\n1100N1\n111111");
	return (map);
}

char	*read_map(void)
{
	return (map_sample());
}

int main(void)
{
	char *map = read_map();
	return(0);
}
