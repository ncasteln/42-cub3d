/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_type_id.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nico <nico@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/24 10:04:41 by nico              #+#    #+#             */
/*   Updated: 2023/12/24 11:25:09 by nico             ###   ########.fr       */
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

static void	store_asset_value(char *value, char *type_id, t_cub3d *data)
{
	if (!ft_strncmp(type_id, "NO", 2))
		data->assets->no = value;
	if (!ft_strncmp(type_id, "EA", 2))
		data->assets->ea = value;
	if (!ft_strncmp(type_id, "SO", 2))
		data->assets->so = value;
	if (!ft_strncmp(type_id, "WE", 2))
		data->assets->we = value;
	if (!ft_strncmp(type_id, "F", 1))
		data->assets->f = value;
	if (!ft_strncmp(type_id, "C", 1))
		data->assets->c = value;
}

void	parse_type_id(char **line, char *type_id, t_cub3d *data)
{
	char	*value;

	value = NULL;
	(*line) += ft_strlen(type_id);
	if (!value_is_well_separated(*line))
		err_free_exit("parse_line", data, E_INV_ASSET);
	if (is_duplicate_asset(type_id, data))
		err_free_exit("parse_line", data, E_DUP_ASSET);
	value = extract_type_id_value(line, type_id, data);
	store_asset_value(value, type_id, data);
}
