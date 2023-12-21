/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_assets.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nico <nico@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/20 08:59:11 by nico              #+#    #+#             */
/*   Updated: 2023/12/21 18:24:42 by nico             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/*
	get rid of

	"NONO ./path" -----> will store the path as "NO ./path"
	"NO ./texture name with spaces"
	"NO./texture_path_not_separated_from_type"
*/

static void	parse_texture(char *line, t_cub3d *data)
{
	if (!is_texture(line, data))
		return ;
	if (is_duplicate_asset(line, data))
	{
		free(line);
		err_free_exit("parse_line", data, E_DUP_ASSET);
	}
	if (store_texture_path(line, data))
	{
		// need to check what kind of file ???
		// for example need to trim space
		// but FF ./path should try open("F ./path"), or is it an invalid identifier?
		// I would say, that in case of FFFF or somethign else should return error
		free(line);
		err_free_exit("parse_line", data, errno);
	}
}

static void	parse_color(char *line, t_cub3d *data)
{
	if (!is_color(line))
		return ;
	if (is_duplicate_asset(line, data))
	{
		free(line);
		err_free_exit("parse_line", data, E_DUP_ASSET);
	}
	if (store_color(line, data))
	{
		free(line);
		err_free_exit("parse_line", data, errno);
	}
}

static void	parse_line(char *line, t_cub3d *data)
{
	char	*tmp;
	char	*type;

	// instead of this, jump spaces and tabs until find a char
	tmp = line;
	line = ft_strtrim(line, " \t");
	free(tmp);
	if (!line)
		err_free_exit("parse_line", data, errno);

	// now take the first portion of the string
		// iterate until ' ' or '\t' or ./
		// ftsubstr and strcmp to understand if it is a correct type
			// OR
		// strcmp directly with all types -----> [[[ easier way ]]]
		// check what after:
			// if ' ' \t or ./ or ../ is a good path
				// check the path - can be a // ./maps/v/0.cub
											 // ../maps
											 // maps/v/0.cub --- valid ??
			// if not there some shit, err_exit()


	// parse_texture(line, data);
	// parse_color(line, data);
	if (is_texture(line, data))
	{
		if (is_duplicate_asset(line, data))
			err_free_exit("parse_line", data, E_DUP_ASSET);
		if (store_texture_path(line, data))
			err_free_exit("parse_line", data, errno);
	}
	else if (is_color(line))
	{
		if (is_duplicate_asset(line, data))
			err_free_exit("parse_line", data, E_DUP_ASSET);
		if (store_color(line, data))
			err_free_exit("parse_line", data, errno);
	}
	else
	{
		if (is_valid_edge(line))
		{
			// is just the beginning of the map
			// check if assets are all set
			// start parse the map
			exit (0);
		}
		else
		{
			err_free_exit(line, data, E_INV_ASSET);
		}
	}
}

void	parse_assets(char *f_name, t_cub3d *data)
{
	char	*line;
	int		fd;

	line = NULL;
	fd = open(f_name, O_RDONLY);
	exit (0);
	if (fd == -1)
		err_free_exit("parse_assets", data, errno);
	while (1)
	{
		line = get_next_line(fd);
		if (errno)
			err_free_exit("get_next_line", data, errno);
		if (!line)
			break ;
		parse_line(line, data);
	}
}
