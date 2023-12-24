/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_file_content.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nico <nico@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/20 08:59:11 by nico              #+#    #+#             */
/*   Updated: 2023/12/24 12:06:42 by nico             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static char	*is_valid_type_id(char *line)
{
	if (!ft_strncmp(line, "NO", 2))
		return ("NO");
	if (!ft_strncmp(line, "EA", 2))
		return ("EA");
	if (!ft_strncmp(line, "SO", 2))
		return ("SO");
	if (!ft_strncmp(line, "WE", 2))
		return ("WE");
	if (!ft_strncmp(line, "F", 1))
		return ("F");
	if (!ft_strncmp(line, "C", 1))
		return ("C");
	return (NULL);
}

static void	parse_line(char *line, t_cub3d *data)
{
	char	*type_id;

	while (line) // maybe not work if last line
	{
		jump_whitspaces(&line);
		if (!line || line[0] == '\n')
			break ;
		type_id = is_valid_type_id(line);
		if (type_id)
			parse_type_id(&line, type_id, data);
		else
		{
			if (!are_assets_complete(data->assets))
				err_free_exit("parse_line", data, E_MISS_ASSET);
			if (!is_valid_map_line(line))
				err_free_exit("parse_line", data, E_INV_ASSET);
			ft_printf("Map ---> [%s]\n", line);
			exit(0);
		}
	}
}

void	parse_file_content(char *f_name, t_cub3d *data)
{
	int		fd;

	fd = open(f_name, O_RDONLY);
	if (fd == -1)
		err_free_exit("parse_assets", data, errno);
	while (1)
	{
		data->line = get_next_line(fd);
		if (errno)
			err_free_exit("get_next_line", data, errno);
		if (!data->line)
			break ;
		parse_line(data->line, data);
		free(data->line); // right ???
	}
	close(fd);
	ft_printf("---Parsing finished---\n");
}
