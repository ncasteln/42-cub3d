/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncasteln <ncasteln@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/24 18:27:13 by nico              #+#    #+#             */
/*   Updated: 2024/01/19 10:55:37 by ncasteln         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	init_map(char *line, t_cub3d *data)
{
	data->map = ft_calloc(2, sizeof(char *));
	if (!data->map)
		err_free_exit("init_map", data, errno);
	data->map[0] = ft_substr(line, 0, ft_strlen(line) - 1); // ft_strdup(line);
	if (!data->map[0])
		err_free_exit("init_map", data, errno);
}

static int	count_map_rows(char **map)
{
	int	i;

	i = 0;
	if (map)
	{
		while (map[i])
			i++;
	}
	return (i);
}

static void	cpy_and_add_line(char *line, t_cub3d *data)
{
	char	**tmp;
	int		i;

	tmp = data->map;
	data->map = ft_calloc(data->n_rows + 1, sizeof(char *));
	if (!data->map)
		err_free_exit("cpy_and_add_line", data, errno);
	i = 0;
	while (tmp[i])
	{
		data->map[i] = ft_strdup(tmp[i]);
		if (!data->map[i])
			err_free_exit("cpy_and_add_line", data, errno);
		i++;
	}
	data->map[i] = ft_substr(line, 0, ft_strlen(line) - 1); //ft_strdup(line);
	if (!data->map[i])
		err_free_exit("cpy_and_add_line", data, errno);
	free_dptr(tmp);
}

static int	is_valid_map_char(char c)
{
	if (c == '0' || c == '1' || c == ' ' || c == '\n')
		return (1);
	if (c == 'N' || c == 'E' || c == 'S' || c == 'W')
		return (1);
	if (BONUS && c == 'D')
		return (1);
	return (0);
}

int	is_valid_map_line(char *s)
{
	size_t	i;

	i = 0;
	if (is_blank_line(s))
		return (1);
	while (s[i])
	{
		if (!is_valid_map_char(s[i]))
			return (0);
		i++;
	}
	return (1);
}

/*
	From this point, is assumed that the rest of the file content is just the
	map. If a line contains characters which are not valid for the map, the
	program throws an error.
	IMPORTANT: If an assets is written after the map, it is considered invalid.
*/
void	store_map_line(char *line, t_cub3d *data)
{
	if (!is_valid_map_line(line))
		err_free_exit("store_map_line", data, E_INV_CHAR);
	if (!data->map)
		return (init_map(line, data));
	data->n_rows = count_map_rows(data->map) + 1;
	cpy_and_add_line(line, data);
}
