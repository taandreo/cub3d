/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tairribe <tairribe@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/29 18:47:40 by tairribe          #+#    #+#             */
/*   Updated: 2024/03/18 07:54:26 by ebezerra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

char	*ft_strchr(const char *str, int ch)
{
	unsigned char	c0;
	unsigned char	c1;
	int				i;

	i = 0;
	c0 = (unsigned char) ch;
	while (str[i])
	{
		c1 = (unsigned char) str[i];
		if (c1 == c0)
			return ((char *)&str[i]);
		i++;
	}
	c1 = (unsigned char) str[i];
	if (c1 == c0)
		return ((char *)&str[i]);
	return (0);
}
