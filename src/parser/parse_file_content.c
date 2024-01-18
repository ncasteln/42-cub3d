/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_file_content.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncasteln <ncasteln@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/20 08:59:11 by nico              #+#    #+#             */
/*   Updated: 2024/01/18 16:31:36 by ncasteln         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static char	*is_valid_type_id(char *line)
{
	int	i;

	i = 0;
	while (line[i] == ' ' || line[i] == '\t') //|| line[i] == '\n
		i++;
	if (!ft_strncmp(line + i, "NO", 2))
		return ("NO");
	if (!ft_strncmp(line + i, "EA", 2))
		return ("EA");
	if (!ft_strncmp(line + i, "SO", 2))
		return ("SO");
	if (!ft_strncmp(line + i, "WE", 2))
		return ("WE");
	if (!ft_strncmp(line + i, "F", 1))
		return ("F");
	if (!ft_strncmp(line + i, "C", 1))
		return ("C");
	if (BONUS && !ft_strncmp(line + i, "DO", 2))
		return ("DO");
	return (NULL);
}

static void	parse_line(char *line, int *is_map_parsing, t_cub3d *data)
{
	char	*type_id;
	int		line_already_parsed;

	type_id = NULL;
	line_already_parsed = 0;
	while (line) // maybe not work if last line
	{
		type_id = is_valid_type_id(line);
		if (is_empty_line(line) && !(*is_map_parsing))
			break ;
		if (type_id && !(*is_map_parsing)) // problem with empty lines -- here need to jump, but map need to save
		{
			jump_whitspaces(&line);
			parse_type_id(&line, type_id, data);
			line_already_parsed = 1;
			if (is_empty_line(line))
				break ;
		}
		else
		{
			if (is_missing_asset(data->assets))
				err_free_exit("parse_line", data, E_MISS_ASSET);
			if (line_already_parsed)
				err_free_exit("parse_line", data, E_INV_FORMAT);
			*is_map_parsing = 1;
			store_map_line(line, data);
			break ; // need to break ???
		}
	}
}

void	parse_file_content(char *f_name, t_cub3d *data)
{
	int		fd;
	int		is_map_parsing;

	is_map_parsing = 0;
	fd = open(f_name, O_RDONLY);
	if (fd == -1)
		err_free_exit("parse_assets", data, errno);
	while (1)
	{
		data->line = get_next_line(fd); // how get errno from here ?
		if (!data->line)
			break ;
		parse_line(data->line, &is_map_parsing, data);
		free(data->line); // right ???
	}
	if (data->assets && !data->map)
		err_free_exit("parse_line", data, E_NO_MAP);
	if (!data->assets && !data->map)
		err_free_exit("parse_line", data, E_EMPTY_FILE);
	close(fd);
}
