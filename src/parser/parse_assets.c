/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_assets.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncasteln <ncasteln@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/24 10:04:41 by nico              #+#    #+#             */
/*   Updated: 2024/02/22 16:02:34 by ncasteln         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/*
	Example.
	"   NO./path  SO./path" ---> valid
	"   NO path  SO path"   ---> valid
	"   NOpath  SOpath"     ---> invalid
*/
static int	value_is_well_separated(char *line)
{
	if (line[0] == ' ' || line[0] == '\t')
		return (1);
	if (line[0] == '.')
	{
		if (line[1] == '/')
			return (1);
		if (line[1] == '.' && line[2] == '/')
			return (1);
	}
	return (0);
}

static void	store_texture_path(char *value, char *type_id, t_cub3d *data)
{
	if (!ft_strncmp(type_id, "NO", 2))
		data->assets->no = value;
	else if (!ft_strncmp(type_id, "EA", 2))
		data->assets->ea = value;
	else if (!ft_strncmp(type_id, "SO", 2))
		data->assets->so = value;
	else if (!ft_strncmp(type_id, "WE", 2))
		data->assets->we = value;
	else if (BONUS && !ft_strncmp(type_id, "DO", 2))
		data->assets->d = value;
}

static void	store_color(uint32_t rgb, char *type_id, t_cub3d *data)
{
	if (!ft_strncmp(type_id, "F", 1))
		data->assets->f = rgb;
	else if (!ft_strncmp(type_id, "C", 1))
		data->assets->c = rgb;
}

void	parse_assets(char **line, char *type_id, t_cub3d *data)
{
	char		*value;
	uint32_t	rgb;

	value = NULL;
	rgb = 0;
	(*line) += ft_strlen(type_id);
	if (!value_is_well_separated(*line))
		err_free_exit("parse_line", data, 0, E_INV_ASSET);
	if (is_duplicate_asset(type_id, data))
		err_free_exit("parse_line", data, 0, E_DUP_ASSET);
	jump_whitespaces(line);
	if (is_texture(type_id))
	{
		value = extract_texture_path(line, data);
		if (value[ft_strlen(value) - 1] == '/')
			err_free_exit("parse_asset", data, 0, E_INV_ASSET);
		store_texture_path(value, type_id, data);
	}
	else
	{
		rgb = extract_color(line, data);
		store_color(rgb, type_id, data);
	}
}
