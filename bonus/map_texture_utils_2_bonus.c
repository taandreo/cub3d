/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_texture_utils_2.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebezerra <ebezerra@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/18 11:22:10 by ebezerra          #+#    #+#             */
/*   Updated: 2024/03/18 11:34:51 by ebezerra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

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

int	rgb_to_int(int r, int g, int b)
{
	return ((r << 16) | (g << 8) | b);
}

t_bool	trim_rgb_spaces(char **rgb)
{
	char	*value;
	int		i;
	int		size;

	i = 0;
	size = ft_lenmt((void *)rgb);
	while (i < size)
	{
		value = ft_strtrim(rgb[i], " ");
		if (!value)
			return (false);
		free(rgb[i]);
		rgb[i] = value;
		i++;
	}
	return (true);
}

int	to_rgb(char *line)
{
	char	*rgbstr;
	char	**rgb;
	t_bool	is_rgb;
	int		rgb_int;

	is_rgb = true;
	rgbstr = ft_strtrim(line, " \n");
	rgb = ft_split(rgbstr, ',');
	free(rgbstr);
	if (ft_lenmt((void **) rgb) != 3 || !trim_rgb_spaces(rgb))
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
