/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path_validation.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncasteln <ncasteln@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/25 19:17:39 by nico              #+#    #+#             */
/*   Updated: 2024/02/22 08:56:00 by ncasteln         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	flood_fill(int py, int px, char **map_cpy, t_cub3d *data)
{
	int	y_limit;
	int	x_limit;

	y_limit = (int)data->n_rows - 1;
	x_limit = (int)data->n_col - 1;
	if (map_cpy[py][px] == '1'
	|| map_cpy[py][px] == '.'
	|| map_cpy[py][px] == 'H')
		return ;
	if (py <= 0 || px <= 0 || py >= y_limit || px >= x_limit)
	{
		free_dptr(map_cpy);
		err_free_exit("flood_fill", data, 0, E_MAP_OPEN);
	}
	else
	{
		if (map_cpy[py][px] == ' ')
			map_cpy[py][px] = 'H';
		else
			map_cpy[py][px] = '.';
	}
	flood_fill(py - 1, px, map_cpy, data);
	flood_fill(py, px + 1, map_cpy, data);
	flood_fill(py + 1, px, map_cpy, data);
	flood_fill(py, px - 1, map_cpy, data);
}

static char	**cpy_map(t_cub3d *data)
{
	char	**map_cpy;
	size_t	i;

	map_cpy = ft_calloc(data->n_rows + 1, sizeof(char *));
	if (!map_cpy)
		err_free_exit("cpy_map", data, 0, errno);
	i = 0;
	while (i < data->n_rows)
	{
		map_cpy[i] = ft_strdup(data->map[i]);
		if (!map_cpy[i])
			err_free_exit("cpy_map", data, 0, errno);
		i++;
	}
	return (map_cpy);
}

static void	refill_items(t_cub3d *data, char **map)
{
	int	i;
	int	j;

	i = 0;
	while (map[i])
	{
		j = 0;
		while (map[i][j])
		{
			if (data->map[i][j] != ' ')
				map[i][j] = data->map[i][j];
			j++;
		}
		i++;
	}
}

/*
	The map in which the player can walk has to be enclosed by walls (1). It is
	still possible that in this portion of map, there are empty spaces.
	Steps:
	1) Trim empty lines on the top and on the bottom of the map.
	2) Fit the map into a rectangle, to give a common limit.
	3) Use flood_fill to understand if the player meets the limits, which means
	that the map is not enclosed.
	4) The empty spaces in the map are considered valid, but not walkable. To
	differentiate them from the outside spaces, they are filled with 'H' to
	sign them as 'holes'.
*/
void	path_validation(t_cub3d *data)
{
	char	**map_rect;
	char	**map_cpy;

	trim_empty_lines(data);
	map_rect = rectangolize(data);
	free_dptr(data->map);
	data->map = map_rect;
	map_cpy = cpy_map(data);
	flood_fill(data->p->y, data->p->x, map_cpy, data);
	refill_items(data, map_cpy);
	free_dptr(data->map);
	data->map = map_cpy;
}
