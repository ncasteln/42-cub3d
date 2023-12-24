/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nico <nico@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/24 18:27:13 by nico              #+#    #+#             */
/*   Updated: 2023/12/24 20:40:01 by nico             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	init_map(char *line, t_cub3d *data)
{
	data->map = ft_calloc(2, sizeof(char *));
	if (!data->map)
		err_free_exit("init_map", data, errno);
	data->map[0] = ft_strdup(line);
	if (!data->map[0])
		err_free_exit("init_map", data, errno);
}

static int	count_map_lines(char **map)
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

static void	cpy_and_add_line(char *line, t_cub3d *data, int new_len)
{
	char	**tmp;
	int		i;

	tmp = data->map;
	data->map = ft_calloc(new_len + 1, sizeof(char *));
	if (!data->map)
		err_free_exit("cpy_and_add_line", data, errno);
	i = 0;
	while (tmp[i])
	{
		data->map[i] = tmp[i];
		i++;
	}
	data->map[i] = ft_strdup(line);
	if (!data->map[i])
		err_free_exit("cpy_and_add_line", data, errno);
}

void	store_map_line(char *line, t_cub3d *data)
{
	int		new_len;

	if (!is_valid_map_line(line))
		err_free_exit("store_map_line", data, E_INV_CHAR);
	if (!data->map)
		return (init_map(line, data));
	new_len = count_map_lines(data->map) + 1;
	cpy_and_add_line(line, data, new_len);
}
