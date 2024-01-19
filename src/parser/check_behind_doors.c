/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_behind_doors.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncasteln <ncasteln@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/19 10:24:34 by ncasteln          #+#    #+#             */
/*   Updated: 2024/01/19 10:41:41 by ncasteln         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

// static int	is_walkable(char c, int *p_found)
// {
// 	if (c == 'N' || c == 'E' || c == 'S' || c == 'W')
// 	{
// 		*p_found = 1;
// 		return (0);
// 	}
// 	if (c == '1' || c == 'D' || c == 'x')
// 		return (0);
// 	return (1);
// }

// static void	door_look_for_player(int y, int x, char **map_cpy, int *p_found, t_cub3d *data)
// {
// 	int	y_limit;
// 	int	x_limit;

// 	y_limit = (int)data->n_rows - 1;
// 	x_limit = (int)data->n_col - 1;
// 	if (*p_found == 0 && (y - 1 > 0) && is_walkable(map_cpy[y - 1][x], p_found))
// 	{
// 		map_cpy[y - 1][x] = 'x';
// 		door_look_for_player(y - 1, x, map_cpy, p_found, data);
// 	}
// 	if (*p_found == 0 && (x + 1 < x_limit) && is_walkable(map_cpy[y][x + 1], p_found))
// 	{
// 		map_cpy[y][x + 1] = 'x';
// 		door_look_for_player(y, x + 1, map_cpy, p_found, data);
// 	}
// 	if (*p_found == 0 && (y + 1 < y_limit) && is_walkable(map_cpy[y + 1][x], p_found))
// 	{
// 		map_cpy[y + 1][x] = 'x';
// 		door_look_for_player(y + 1, x, map_cpy, p_found, data);
// 	}
// 	if (*p_found == 0 && (x - 1 > 0) && is_walkable(map_cpy[y][x - 1], p_found))
// 	{
// 		map_cpy[y][x - 1] = 'x';
// 		door_look_for_player(y, x - 1, map_cpy, p_found, data);
// 	}
// }

// /*
// 	In case of BONUS version, the flood fill has to be improved: since the
// 	player can open doors, behind them there could be a room without a wall
// 	which can be reached.
// 	The unreachable doors which lead to unenclosed piece of maps, are
// 	considered valid.
// */
// void	check_behind_doors(t_cub3d *data, char **map_cpy) // move to bonus stuff
// {
// 	int	y;
// 	int	x;
// 	int	p_found;

// 	y = 0;
// 	while (map_cpy[y])
// 	{
// 		x = 0;
// 		while (map_cpy[y][x])
// 		{
// 			if (map_cpy[y][x] == 'D')
// 			{
// 				p_found = 0;
// 				door_look_for_player(y, x, map_cpy, &p_found, data);
// 				if (p_found)
// 					flood_fill(y, x, map_cpy, data);
// 			}
// 			x++;
// 		}
// 		y++;
// 	}
// }


// /* ************************************************************************** */
// /*                                                                            */
// /*                                                        :::      ::::::::   */
// /*   check_behind_doors.c                               :+:      :+:    :+:   */
// /*                                                    +:+ +:+         +:+     */
// /*   By: ncasteln <ncasteln@student.42.fr>          +#+  +:+       +#+        */
// /*                                                +#+#+#+#+#+   +#+           */
// /*   Created: 2024/01/19 10:24:34 by ncasteln          #+#    #+#             */
// /*   Updated: 2024/01/19 10:35:43 by ncasteln         ###   ########.fr       */
// /*                                                                            */
// /* ************************************************************************** */

// #include "cub3d.h"

// static int	get_row_len(char *row)
// {
// 	int	i;

// 	i = 0;
// 	while (row[i])
// 		i++;
// 	return (i);
// }

// static int	can_walk(char c, int *p_found)
// {
// 	if (c == 'N' || c == 'E' || c == 'S' || c == 'W')
// 	{
// 		*p_found = 1;
// 		return (0);
// 	}
// 	if (c == '1' || c == 'D' || c == 'x')
// 		return (0);
// 	return (1);
// }

// static void	door_look_for_player(int y, int x, char **map, int *p_found)
// {
// 	int	y_limit;
// 	int	x_limit;

// 	y_limit = get_n_rows(map);
// 	x_limit = get_row_len(map[0]);
// 	if (*p_found == 0 && (y - 1 > 0) && can_walk(map[y - 1][x], p_found))
// 	{
// 		map[y - 1][x] = 'x';
// 		door_look_for_player(y - 1, x, map, p_found);
// 	}
// 	if (*p_found == 0 && (x + 1 < x_limit) && can_walk(map[y][x + 1], p_found))
// 	{
// 		map[y][x + 1] = 'x';
// 		door_look_for_player(y, x + 1, map, p_found);
// 	}
// 	if (*p_found == 0 && (y + 1 < y_limit) && can_walk(map[y + 1][x], p_found))
// 	{
// 		map[y + 1][x] = 'x';
// 		door_look_for_player(y + 1, x, map, p_found);
// 	}
// 	if (*p_found == 0 && (x - 1 > 0) && can_walk(map[y][x - 1], p_found))
// 	{
// 		map[y][x - 1] = 'x';
// 		door_look_for_player(y, x - 1, map, p_found);
// 	}
// }

// /*
// 	In case of BONUS version, the flood fill has to be improved: since the
// 	player can open doors, behind them there could be a room without a wall
// 	which can be reached.
// 	The unreachable doors which lead to unenclosed piece of maps, are
// 	considered valid.
// */
// void	check_behind_doors(t_cub3d *data, char **map)
// {
// 	int	y;
// 	int	x;
// 	int	p_found;

// 	y = 0;
// 	while (map[y])
// 	{
// 		x = 0;
// 		while (map[y][x])
// 		{
// 			if (map[y][x] == 'D')
// 			{
// 				p_found = 0;
// 				door_look_for_player(y, x, map, &p_found);
// 				if (p_found)
// 					flood_fill(y, x, map, data);
// 			}
// 			x++;
// 		}
// 		y++;
// 	}
// }
