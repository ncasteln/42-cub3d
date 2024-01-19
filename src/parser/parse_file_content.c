/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_file_content.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncasteln <ncasteln@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/20 08:59:11 by nico              #+#    #+#             */
/*   Updated: 2024/01/19 15:22:34 by ncasteln         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	jump_whitespaces(char **line)
{
	while (**line == ' ' || **line == '\t')
		(*line)++;
}

static int	asset_line(char **line, char *asset_id, t_cub3d *data)
{
	jump_whitespaces(line);
	parse_assets(line, asset_id, data);
	if (is_blank_line(*line))
		return (1);
	return (0);
}

static void	map_line(char *line, int is_line_parsed, t_cub3d *data)
{
	if (is_missing_asset(data->assets))
		err_free_exit("parse_line", data, E_MISS_ASSET);
	if (is_line_parsed)
		err_free_exit("parse_line", data, E_INV_FORMAT);
	store_map_line(line, data);
}

/*
	@param is_line_parsed: means, that the line is already in part parsed. It
	is required to parse map with assets written on the same line (see 
	./tests/valid/ass_02.cub and ass_12.cub).
	Note: assets on same line are valid, but if the id of the asset and its
	path are on different lines, they are considered invalid (see
	./tests/invalid/ass_id_path_different_lines.cub).
*/
static void	parse_line(char *line, int *is_map_parsing, t_cub3d *data)
{
	char	*asset_id;
	int		is_line_parsed;

	asset_id = NULL;
	is_line_parsed = 0;
	while (line)
	{
		asset_id = is_valid_asset_id(line);
		if (is_blank_line(line) && !(*is_map_parsing))
			break ;
		if (asset_id && !(*is_map_parsing))
		{
			is_line_parsed = 1;
			if (asset_line(&line, asset_id, data))
				break ;
		}
		else
		{
			*is_map_parsing = 1;
			map_line(line, is_line_parsed, data);
			break ;
		}
	}
}

/*
	@param is_map_parsing: turned to 1 when it starts to parse the map, and
	remain to 1 until the end of the file (if there is something after the
	map, it is invalid).
*/
void	parse_file_content(char *f_name, t_cub3d *data)
{
	int		is_map_parsing;

	is_map_parsing = 0;
	data->fd = open(f_name, O_RDONLY);
	if (data->fd == -1)
		err_free_exit("parse_assets", data, errno);
	while (1)
	{
		data->line = get_next_line(data->fd);
		if (!data->line)
			break ;
		parse_line(data->line, &is_map_parsing, data);
		free(data->line);
	}
	if (data->assets && !data->map)
		err_free_exit("parse_line", data, E_NO_MAP);
	if (!data->assets && !data->map)
		err_free_exit("parse_line", data, E_EMPTY_FILE);
	close(data->fd);
	data->fd = -1;
}
