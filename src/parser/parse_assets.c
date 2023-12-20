/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_assets.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nico <nico@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/20 08:59:11 by nico              #+#    #+#             */
/*   Updated: 2023/12/20 12:37:14 by nico             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	is_valid_map_char(char c)
{
	if (c == '1' || c == '0' || c == ' '
	|| c == 'N' || c == 'S' || c == 'W' || c == 'E')
		return (1);
	return(0);
}

static int	is_map_line(char *s)
{
	int	i;

	i = 0;
	while (s[i] && is_valid_map_char(s[i]))
		i++;
	if (i == ft_strlen(s) - 1) // because of the new line
		return (1);
	return (0);
}

static int	is_blank_string(char *s)
{
	int	i;

	i = 0;
	while (s[i] && (s[i] == ' ' || s[i] == '\t'))
		i++;
	if (s[i] == '\n')
		return (1);
	return (0);
}

static int	store_color(char *line, t_cub3d *data)
{
	char	*color;

	color = ft_strdup(line + 1);
	if (!color)
		return (1);
	if (!ft_strncmp(line, "F", 1))
		data->assets->f = color;
	if (!ft_strncmp(line, "C", 1))
		data->assets->c = color;
	return (0);
}

static int	store_texture_path(char *line, t_cub3d *data)
{
	char	*path;

	path = ft_strdup(line + 2);
	if (!path)
		return (1);
	if (!ft_strncmp(line, "NO", 2))
		data->assets->no = path;
	if (!ft_strncmp(line, "EA", 2))
		data->assets->ea = path;
	if (!ft_strncmp(line, "SO", 2))
		data->assets->so = path;
	if (!ft_strncmp(line, "WE", 2))
		data->assets->we = path;
	return (0);
}

static int is_color(char *line)
{
	if (!ft_strncmp(line, "F", 1))
		return (1);
	if (!ft_strncmp(line, "C", 1))
		return (1);
	return (0);
}

static int is_texture(char *line, t_cub3d *data)
{
	if (!ft_strncmp(line, "NO", 2))
		return (1);
	if (!ft_strncmp(line, "EA", 2))
		return (1);
	if (!ft_strncmp(line, "SO", 2))
		return (1);
	if (!ft_strncmp(line, "WE", 2))
		return (1);
	return (NULL);
}

static int is_duplicate_asset(char *line, t_cub3d *data)
{
	if (!ft_strncmp(line, "NO", 2))
		if (data->assets->no)
			err_free_exit("NO", data, CE_DUPASS);
	if (!ft_strncmp(line, "EA", 2))
		if (data->assets->ea)
			err_free_exit("EA", data, CE_DUPASS);
	if (!ft_strncmp(line, "SO", 2))
		if (data->assets->so)
			err_free_exit("SO", data, CE_DUPASS);
	if (!ft_strncmp(line, "WE", 2))
		if (data->assets->we)
			err_free_exit("WE", data, CE_DUPASS);
	if (!ft_strncmp(line, "F", 1))
		if (data->assets->f)
			err_free_exit("F", data, CE_DUPASS);
	if (!ft_strncmp(line, "C", 1))
		if (data->assets->c)
			err_free_exit("C", data, CE_DUPASS);
	return (0);
}


/*
	get rid of

	"NONO ./path" -----> will store the path as "NO ./path"
	"NO ./texture name with spaces"
	"NO./texture_path_not_separated_from_type"
*/

static int	parse_line(char *line, t_cub3d *data)
{
	char	*tmp;
	char	*type;

	// tmp = line;
	line = ft_strtrim(line, " \t");
	// free(tmp);
	if (!line)
		return (1);
	if (is_texture(line, data))
	{
		if (is_duplicate_asset(line, data) || store_texture_path(line, data))
			return (1);
	}
	else if (is_color(line))
	{
		if (is_duplicate_asset(line, data) || store_color(line, data))
			return (1);
	}
	else
	{
		// if (!all asset are present) ----> should catch extraneous lines
		// error
		// else
		// parse map
		if (!is_map_line(line))
		{
			ft_printf("POrcodio, non è la mapppa!\n");
			return (1);
		}
	}
	return (0);
}

void	parse_assets(char *f_name, t_cub3d *data)
{
	char	*line;
	int		fd;

	line = NULL;
	fd = open(f_name, O_RDONLY);
	if (fd == -1)
		err_free_exit("parse_assets", data, errno);
	while (1)
	{
		if (line)
			free(line);
		line = get_next_line(fd);
		if (errno)
			err_free_exit("get_next_line", data, errno);
		if (!line)
			break ;
		ft_printf("Checking ---> %s", line);
		if (!is_blank_string(line))
		{
			if (parse_line(line, data))
				err_free_exit("parse_assets", data, CE_PARSEASSETS);
		}
	}
	ft_printf("asset NO [%s]\n", data->assets->no);
	ft_printf("asset EA [%s]\n", data->assets->ea);
	ft_printf("asset SO [%s]\n", data->assets->so);
	ft_printf("asset WE [%s]\n", data->assets->we);
}
