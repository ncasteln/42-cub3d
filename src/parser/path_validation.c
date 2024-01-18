/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path_validation.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncasteln <ncasteln@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/25 19:17:39 by nico              #+#    #+#             */
/*   Updated: 2024/01/18 10:03:28 by ncasteln         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	is_empty_line(char *s) // move into utils
{
	size_t	i;

	i = 0;
	while (s[i] && (s[i] == ' ' || s[i] == '\t' || s[i] == '\n'))
		i++;
	if (ft_strlen(s) == i)
		return (1);
	return (0);
}

static int	get_n_rows(char **map)
{
	int	i;

	i = 0;
	while (map[i])
		i++;
	return (i);
}

static int	get_longest_row_size(char **map)
{
	size_t	longest_row;
	int		i;

	longest_row = 0;
	i = 0;
	while (map[i])
	{
		if (ft_strlen(map[i]) > longest_row && !(is_empty_line(map[i])))
			longest_row = ft_strlen(map[i]);
		i++;
	}
	return (longest_row);
}

/*
	fill_row() need to copy the content of the old_row into the new one,
	filling everything not set with white spaces.
*/
static void	fill_row(char *new_row, char *old_row, size_t new_row_len)
{
	size_t	i;

	i = 0;
	while (i < new_row_len)
	{
		if (i < ft_strlen(old_row))
			new_row[i] = old_row[i];
		else
			new_row[i] = ' ';
		i++;
	}
}

static char	**cpy_rectangolized_map(t_cub3d *data, size_t new_row_len, int n_rows)
{
	char	**map_cpy;
	int		i;

	map_cpy = ft_calloc(n_rows + 1, sizeof(char *));
	if (!map_cpy)
		err_free_exit("rectangolize", data, errno);
	i = 0;
	while (i < n_rows)
	{
		map_cpy[i] = ft_calloc(new_row_len + 1, sizeof(char));
		if (!map_cpy[i])
			err_free_exit("rectangolize", data, errno);
		fill_row(map_cpy[i], data->map[i], new_row_len);
		i++;
	}
	return (map_cpy);
}

static char	**rectangolize(t_cub3d *data)
{
	int		n_rows;
	char	**map_cpy;

	data->n_col = get_longest_row_size(data->map);
	n_rows = get_n_rows(data->map);
	map_cpy = cpy_rectangolized_map(data, data->n_col, n_rows);
	return (map_cpy);
}

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
	while (is_empty_line(data->map[i]))
		i++;
	while (is_empty_line(data->map[j]))
		j--;
	trimmed_map = cpy_map_without_empty_lines(i, j, data);
	free_dptr(data->map);
	data->map = trimmed_map;
}

static void	flood_fill(int py, int px, char **map_cpy, t_cub3d *data)
{
	int	y_limit;
	int	x_limit;

	y_limit = (int)data->n_rows - 1;
	x_limit = (int)data->n_col - 1;
	if (map_cpy[py][px] == '1' || map_cpy[py][px] == 'x')
		return ;
	if (py <= 0 || px <= 0 || py >= y_limit || px >= x_limit)
	{
		// print_map(map_cpy, data->n_col); // remove
		free_dptr(map_cpy);
		err_free_exit("flood_fill", data, E_MAP_OPEN);
	}
	else
		map_cpy[py][px] = 'x';
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

static int	door_need_to_continue(char c, int *player_reached)
{
	if (c == 'N' || c == 'E' || c == 'S' || c == 'W')
	{
		*player_reached = 1;
		return (0);
	}
	if (c == '1' || c == 'D' || c == 'x')
		return (0);
	return (1);
}

static void	door_look_for_player(int y, int x, char **map_cpy, int *player_reached, t_cub3d *data)
{
	int	y_limit;
	int	x_limit;

	y_limit = (int)data->n_rows - 1;
	x_limit = (int)data->n_col - 1;
	if (*player_reached == 0 && (y - 1 > 0) && door_need_to_continue(map_cpy[y - 1][x], player_reached))
	{
		map_cpy[y - 1][x] = 'x';
		door_look_for_player(y - 1, x, map_cpy, player_reached, data);
	}
	if (*player_reached == 0 && (x + 1 < x_limit) && door_need_to_continue(map_cpy[y][x + 1], player_reached))
	{
		map_cpy[y][x + 1] = 'x';
		door_look_for_player(y, x + 1, map_cpy, player_reached, data);
	}
	if (*player_reached == 0 && (y + 1 < y_limit) && door_need_to_continue(map_cpy[y + 1][x], player_reached))
	{
		map_cpy[y + 1][x] = 'x';
		door_look_for_player(y + 1, x, map_cpy, player_reached, data);
	}
	if (*player_reached == 0 && (x - 1 > 0) && door_need_to_continue(map_cpy[y][x - 1], player_reached))
	{
		map_cpy[y][x - 1] = 'x';
		door_look_for_player(y, x - 1, map_cpy, player_reached, data);
	}
}

static int	is_reachable_by_player(int y, int x, char **map_cpy, t_cub3d *data)
{
	int	player_reached;

	player_reached = 0;
	door_look_for_player(y, x, map_cpy, &player_reached, data);
	ft_printf("DOOR [%d][%d] - ", y, x);
	if (player_reached == 1)
		ft_printf("REACH PLAYER!\n");
	else
		ft_printf("DOES NOT REACH PLAYER!\n");
	return (player_reached);
	// free mapcpy
}

/*
	In case of BONUS version, the flood fill has to be improved: since the
	player can open doors, behind them there could be a room without a wall
	which can be reached.
	The unreachable doors which lead to unenclosed piece of maps, are
	considered valid.
*/
static void	check_behind_doors(t_cub3d *data, char **map_cpy) // move to bonus stuff
{
	int	y;
	int	x;

	y = 0;
	while (map_cpy[y])
	{
		x = 0;
		while (map_cpy[y][x])
		{
			if (map_cpy[y][x] == 'D')
			{
				if (is_reachable_by_player(y, x, map_cpy, data))
					flood_fill(y, x, map_cpy, data);
			}
			x++;
		}
		y++;
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
