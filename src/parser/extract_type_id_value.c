/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   extract_type_id_value.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncasteln <ncasteln@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/24 10:31:41 by nico              #+#    #+#             */
/*   Updated: 2024/01/18 09:48:34 by ncasteln         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

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

static char	*rgb_to_hex_string(char *color)
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
	Check if the return of ft_atoi() was caused by a real zero like 0 or 0000,
	and not the return of a non-digit string, like ft_atoi("abc").
*/
static int	is_valid_zero(char *s)
{
	size_t	i;

	i = 0;
	if (s[i] == '+')
		i++;
	while (s[i] && s[i] == '0') // add +
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
		rgb[i] = ft_strtrim(rgb[i], " \t"); // new line??
		if (!rgb[i])
			return (free(tmp), 1);
		free(tmp);
		i++;
	}
	return (0);
}

/*
	A color is valid when it has 3 positive digits between 0 and 255,
	separated by commas and multiple possible whitespaces and tabs.
*/
static int	is_valid_color(char *color)
{
	char	**rgb;
	int		i;
	int		n;

	rgb = ft_split(color, ','); // remember to freeee!!!!
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

static int	is_valid_path(char *path)
{
	int	fd;

	fd = open(path, O_RDONLY);
	if (fd == -1)
		return (0);
	close(fd);
	return (1);
}

static char	*extract_color(char **line, t_cub3d *data)
{
	int			i;
	char		*color;
	char		*hex;

	i = 0;
	while ((*line)[i] && (ft_isdigit((*line)[i]) || (*line)[i] == ' ' || (*line)[i] == ',' || (*line)[i] == '+'))
		i++;
	color = ft_calloc(i + 1, sizeof(char));
	if (!color)
		return (NULL);
	ft_strlcpy(color, *line, i + 1);
	(*line) += i;
	if (!is_valid_color(color))
	{
		free(color);
		err_free_exit("extract_color", data, E_INV_ASSET);
	}
	hex = rgb_to_hex_string(color);
	return (hex);
}

static char	*extract_texture_path(char **line, t_cub3d *data)
{
	int		i;
	char	*path;

	i = 0;
	// go until it finds a space !!!
	while ((*line)[i] && ((*line)[i] != ' ' && (*line)[i] != '\t' && (*line)[i] != '\n'))
		i++;
	path = ft_calloc(i + 1, sizeof(char));
	if (!path)
		return (NULL);
	ft_strlcpy(path, *line, i + 1);
	(*line) += i;
	if (!is_valid_path(path))
	{
		free(path);
		err_free_exit("extract_texture_path", data, errno);
	}
	return (path);
}

char	*extract_type_id_value(char **line, char *id, t_cub3d *data)
{
	jump_whitspaces(line);
	if (is_texture(id))
		return (extract_texture_path(line, data));
	else
		return (extract_color(line, data));
	return (NULL);
}
