/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   extract_color_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncasteln <ncasteln@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/19 09:39:29 by ncasteln          #+#    #+#             */
/*   Updated: 2024/02/22 11:53:56 by ncasteln         ###   ########.fr       */
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

static void	build_hex(int n, char **hex, int i)
{
	char	*base16;
	char	a;
	char	b;

	base16 = "0123456789ABCDEF";
	a = base16[n / 16];
	b = base16[n % 16];
	(*hex)[i + i + 2] = a;
	(*hex)[i + i + 3] = b;
}

char	*rgb_to_hex_string(char *color)
{
	int		n;
	char	**rgb;
	char	*hex;
	int		i;

	hex = ft_calloc(11, sizeof(char));
	if (!hex)
		return (NULL);
	hex[0] = '0';
	hex[1] = 'x';
	rgb = ft_split(color, ',');
	if (!rgb)
		return (free(hex), NULL);
	i = 0;
	while (rgb[i])
	{
		n = ft_atoi(rgb[i]);
		build_hex(n, &hex, i);
		i++;
	}
	hex[8] = 'F';
	hex[9] = 'F';
	return (free_dptr(rgb), hex);
}

/*
	A color is valid when it has 3 positive digits between 0 and 255,
	separated by commas and multiple possible whitespaces and tabs.
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
