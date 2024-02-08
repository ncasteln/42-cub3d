/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path_validation.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncasteln <ncasteln@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/25 19:17:39 by nico              #+#    #+#             */
/*   Updated: 2024/01/26 09:47:40 by ncasteln         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static char	**cpy_map_without_empty_lines(int i, int j, t_cub3d *data)
{
	char	**trimmed_map;
	int		k;

	data->n_rows = j - i + 1;
	trimmed_map = ft_calloc(data->n_rows + 1, sizeof(char *));
	if (!trimmed_map)
		err_free_exit("trim_empty_lines", data, errno);
	k = 0;
	while (i <= j)
	{
		trimmed_map[k] = ft_strdup(data->map[i]);
		if (!trimmed_map[k])
			err_free_exit("trim_empty_lines", data, errno);
		i++;
		k++;
	}
	return (trimmed_map);
}

static void	trim_empty_lines(t_cub3d *data)
{
	char	**trimmed_map;
	int		i;
	int		j;

	i = 0;
	j = get_n_rows(data->map) - 1;
	while (is_blank_line(data->map[i]))
		i++;
	while (is_blank_line(data->map[j]))
		j--;
	trimmed_map = cpy_map_without_empty_lines(i, j, data);
	free_dptr(data->map);
	data->map = trimmed_map;
}

void	flood_fill(int py, int px, char **map_cpy, t_cub3d *data)
{
	int	y_limit;
	int	x_limit;

	y_limit = (int)data->n_rows - 1;
	x_limit = (int)data->n_col - 1;
	if (map_cpy[py][px] == '1' || map_cpy[py][px] == '.')
		return ;
	if (py <= 0 || px <= 0 || py >= y_limit || px >= x_limit)
	{
		free_dptr(map_cpy);
		err_free_exit("flood_fill", data, E_MAP_OPEN);
	}
	else
		map_cpy[py][px] = '.';
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
		err_free_exit("cpy_map", data, errno);
	i = 0;
	while (i < data->n_rows)
	{
		map_cpy[i] = ft_strdup(data->map[i]);
		if (!map_cpy[i])
			err_free_exit("cpy_map", data, errno);
		i++;
	}
	return (map_cpy);
}

/*
	The map in which the player can walk has to be enclosed by walls (1). It is
	still possible that in this portion of map, there are empty spaces.
	Steps:
	1) Trim empty lines on the top and on the bottom of the map.
	2) Fit the map into a rectangle, to give a common limit.
	3) Use flood_fill to understand if the player meets the limits, which means
	that the map is not enclosed.
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
	free_dptr(map_cpy);
	map_cpy = cpy_map(data);
	if (BONUS)
		check_behind_doors(data, map_cpy);
	free_dptr(map_cpy);
}
