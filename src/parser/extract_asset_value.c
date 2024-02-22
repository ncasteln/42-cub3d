/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   extract_asset_value.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncasteln <ncasteln@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/24 10:31:41 by nico              #+#    #+#             */
/*   Updated: 2024/02/15 15:49:19 by ncasteln         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	is_valid_path(char *path)
{
	int	fd;

	fd = open(path, O_RDONLY);
	if (fd == -1)
		return (0);
	close(fd);
	return (1);
}

static char	*extract_texture_path(char **line, t_cub3d *data)
{
	int		i;
	char	*path;

	i = 0;
	while ((*line)[i])
	{
		if ((*line)[i] == ' ' || (*line)[i] == '\t' || (*line)[i] == '\n')
			break ;
		i++;
	}
	path = ft_calloc(i + 1, sizeof(char));
	if (!path)
		return (NULL);
	ft_strlcpy(path, *line, i + 1);
	(*line) += i;
	if (!is_valid_path(path))
	{
		free(path);
		err_free_exit("extract_texture_path", data, 0, errno);
	}
	return (path);
}

static char	*extract_color(char **line, t_cub3d *data)
{
	int		i;
	char	*color;
	char	*hex;
	char	c;

	i = 0;
	while ((*line)[i])
	{
		c = (*line)[i];
		if (!ft_isdigit(c) && c != ' ' && c != ',' && c != '+')
			break ;
		i++;
	}
	color = ft_calloc(i + 1, sizeof(char));
	if (!color)
		return (NULL);
	ft_strlcpy(color, *line, i + 1);
	(*line) += i;
	if (!is_valid_color(color))
	{
		free(color);
		err_free_exit("extract_color", data, 0, E_INV_ASSET);
	}
	hex = rgb_to_hex_string(color);
	return (free(color), hex);
}

char	*extract_asset_value(char **line, char *id, t_cub3d *data)
{
	jump_whitespaces(line);
	if (is_texture(id))
		return (extract_texture_path(line, data));
	else
		return (extract_color(line, data));
	return (NULL);
}
