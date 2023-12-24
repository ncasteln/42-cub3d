/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   extract_type_id_value.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nico <nico@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/24 10:31:41 by nico              #+#    #+#             */
/*   Updated: 2023/12/24 11:52:13 by nico             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/*
	Check if the return of ft_atoi() was caused by a real zero like 0 or 0000,
	and not the return of a non-digit string, like ft_atoi("abc").
*/
static int	is_valid_zero(char *s)
{
	int	i;

	i = 0;
	while (s[i] && s[i] == '0')
		i++;
	if (i == ft_strlen(s))
		return (1);
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
	while (rgb[i])
	{
		n = ft_atoi(rgb[i]);
		if (n < 0 || n > 255)
			return (0);
		if (n == 0 && !is_valid_zero(rgb[i]))
			return (0);
		i++;
	}
	if (i != 3)
		return (0);
	return (1);
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
	int		i;
	char	*color;

	i = 0;
	// modify this rgb validator
	while ((*line)[i] && (ft_isdigit((*line)[i]) || (*line)[i] == ' ' || (*line)[i] == ','))
		i++;
	color = ft_calloc(i + 1, sizeof(char));
	if (!color)
		return (NULL);
	ft_strlcpy(color, *line, i + 1);
	(*line) += i;
	ft_printf("color ---> [%s]\n", color);
	if (!is_valid_color(color))
	{
		free(color);
		err_free_exit("extract_color", data, errno);
	}
	return (color);
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
	ft_printf("path ---> [%s]\n", path);
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
