/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_assets.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nico <nico@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/20 08:59:11 by nico              #+#    #+#             */
/*   Updated: 2023/12/23 13:09:38 by nico             ###   ########.fr       */
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
	if (!is_texture(line))
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

static char	*is_valid_id(char *line)
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

static void	jump_whitspaces(char **line)
{
	while (**line == ' ' || **line == '\t')
		(*line)++;
}

/*
	Example.
	"   NO./path  SO./path" ---> valid
	"   NO path  SO path"   ---> valid
	"   NOpath  SOpath"     ---> invalid
*/
static int	value_is_separated(char *line)
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

static char	*get_id_value(char **line, char *id)
{
	int		fd;
	int		i;
	char	*path;

	jump_whitspaces(line);
	if (is_texture(id))
	{
		// now i have "./path         SO ./path" OR "./path\n" OR "./path    \n"
		i = 0;
		while ((*line)[i] && ((*line)[i] != ' ' && (*line)[i] != '\t' && (*line)[i] != '\n'))
			i++;
		path = ft_calloc(i + 1, sizeof(char));
		if (!path)
			return (NULL); // catch return
		ft_strlcpy(path, *line, i + 1);
		ft_printf("PATH = [%s]\n", path);
		ft_printf("jump to [%c]\n", (*line + i)[0]);
		(*line) += i;  // jump to next index
		ft_printf("line ---> %s", *line);
		return (path);
	}
	else
	{
		// extract the number
	}
}

static void	store_asset_value(char *path, char *id, t_cub3d *data)
{
	if (!ft_strncmp(id, "NO", 2))
		data->assets->no = path;
	if (!ft_strncmp(id, "EA", 2))
		data->assets->ea = path;
	if (!ft_strncmp(id, "SO", 2))
		data->assets->so = path;
	if (!ft_strncmp(id, "WE", 2))
		data->assets->we = path;
	if (!ft_strncmp(id, "F", 1))
		data->assets->f = path;
	if (!ft_strncmp(id, "C", 1))
		data->assets->c = path;
}

static void	parse_line(char *line, t_cub3d *data)
{
	char	*tmp;
	char	*id;
	char	*value;

	while (line && line[0] != '\n')
	{
		ft_printf("line ---> %s", line);
		jump_whitspaces(&line);
		id = is_valid_id(line);
		if (id)
		{
			line += ft_strlen(id);
			if (value_is_separated(line))
			{
				if (!is_duplicate_asset(id, data))
				{
					value = get_id_value(&line, id); // check return value
					if (!value)
						err_free_exit("parse_line", data, errno);
					store_asset_value(value, id, data);
				}
				else
					err_free_exit("parse_line", data, E_DUP_ASSET);
			}
			else
				err_free_exit("parse_line", data, E_INV_ASSET);
		}
		else
		{
			if (is_valid_edge(line))
			{
				ft_printf("Start parsing the map from [%s]\n", line);
				exit(0);
			}
			else
				err_free_exit("parse_line", data, E_INV_ASSET);
		}
	}
}

void	parse_assets(char *f_name, t_cub3d *data)
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
}





	// char	*tmp;
	// char	*type;

	// // instead of this, jump spaces and tabs until find a char
	// tmp = line;
	// line = ft_strtrim(line, " \t");
	// free(tmp);
	// if (!line)
	// 	err_free_exit("parse_line", data, errno);

	// // now take the first portion of the string
	// 	// iterate until ' ' or '\t' or ./
	// 	// ftsubstr and strcmp to understand if it is a correct type
	// 		// OR
	// 	// strcmp directly with all types -----> [[[ easier way ]]]
	// 	// check what after:
	// 		// if ' ' \t or ./ or ../ is a good path
	// 			// check the path - can be a // ./maps/v/0.cub
	// 										 // ../maps
	// 										 // maps/v/0.cub --- valid ??
	// 		// if not there some shit, err_exit()


	// // parse_texture(line, data);
	// // parse_color(line, data);
	// if (is_texture(line, data))
	// {
	// 	if (is_duplicate_asset(line, data))
	// 		err_free_exit("parse_line", data, E_DUP_ASSET);
	// 	if (store_texture_path(line, data))
	// 		err_free_exit("parse_line", data, errno);
	// }
	// else if (is_color(line))
	// {
	// 	if (is_duplicate_asset(line, data))
	// 		err_free_exit("parse_line", data, E_DUP_ASSET);
	// 	if (store_color(line, data))
	// 		err_free_exit("parse_line", data, errno);
	// }
	// else
	// {
	// 	if (is_valid_edge(line))
	// 	{
	// 		// is just the beginning of the map
	// 		// check if assets are all set
	// 		// start parse the map
	// 		exit (0);
	// 	}
	// 	else
	// 	{
	// 		err_free_exit(line, data, E_INV_ASSET);
	// 	}
	// }
