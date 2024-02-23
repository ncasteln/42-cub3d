/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   extract_color_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrubina <mrubina@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/19 09:39:29 by ncasteln          #+#    #+#             */
/*   Updated: 2024/02/23 12:39:36 by mrubina          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/*
	Check if the return of ft_atoi() was caused by a real zero like 0 or 0000,
	and not the return of a non-digit string, like ft_atoi("abc").
*/
static int	is_valid_zero(char *s)
{
	size_t	i;

	i = 0;
	while (s[i] && (s[i] == '0' || s[i] == '+'))
		i++;
	if (i == ft_strlen(s))
		return (1);
	return (0);
}

static int	trim_rgb(char **rgb)
{
	int		i;
	char	*tmp;

	i = 0;
	while (rgb[i])
	{
		tmp = rgb[i];
		rgb[i] = ft_strtrim(rgb[i], " \t");
		if (!rgb[i])
			return (free(tmp), 1);
		free(tmp);
		i++;
	}
	return (0);
}

uint32_t	str_to_rgb(char *color, t_cub3d *data)
{
	char		**rgb;
	uint32_t	rgb_n;
	int			i;

	i = 0;
	rgb = ft_split(color, ',');
	if (!rgb)
		err_free_exit("str_to_rgb()", data, 0, errno);
	if (trim_rgb(rgb))
	{
		while (i < 3)
		{
			if (rgb[i])
				free(rgb[i]);
		}
		free(rgb);
		err_free_exit("str_to_rgb()", data, 0, errno);
	}
	rgb_n = getcol(ft_atoi(rgb[0]), ft_atoi(rgb[1]), ft_atoi(rgb[2]), 255);
	free_dptr(rgb);
	return (rgb_n);
}

/*
	A color is valid when it has 3 positive digits between 0 and 255,
	extremes included separated by commas and multiple possible whitespaces
	and tabs.
*/
int	is_valid_color(char *color)
{
	char	**rgb;
	int		i;
	int		n;

	rgb = ft_split(color, ',');
	if (!rgb)
		return (0);
	i = 0;
	if (trim_rgb(rgb))
		return (free_dptr(rgb), 1);
	while (rgb[i])
	{
		n = ft_atoi(rgb[i]);
		if (n < 0 || n > 255)
			return (free_dptr(rgb), 0);
		if (n == 0 && !is_valid_zero(rgb[i]))
			return (free_dptr(rgb), 0);
		i++;
	}
	if (i != 3)
		return (free_dptr(rgb), 0);
	return (free_dptr(rgb), 1);
}
