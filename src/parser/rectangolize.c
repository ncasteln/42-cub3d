/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rectangolize.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncasteln <ncasteln@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/19 10:19:23 by ncasteln          #+#    #+#             */
/*   Updated: 2024/02/23 08:25:51 by ncasteln         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	get_n_rows(char **map)
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

static int	get_longest_row_size(char **map)
{
	size_t	longest_row;
	int		i;

	longest_row = 0;
	i = 0;
	while (map[i])
	{
		if (ft_strlen(map[i]) > longest_row && !(is_blank_line(map[i])))
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

static char	**cpy_rectangolized_map(t_cub3d *data, size_t row_len, int n_rows)
{
	char	**map_cpy;
	int		i;

	map_cpy = ft_calloc(n_rows + 1, sizeof(char *));
	if (!map_cpy)
		err_free_exit("rectangolize", data, 0, errno);
	i = 0;
	while (i < n_rows)
	{
		map_cpy[i] = ft_calloc(row_len + 1, sizeof(char));
		if (!map_cpy[i])
			err_free_exit("rectangolize", data, 0, errno);
		fill_row(map_cpy[i], data->map[i], row_len);
		i++;
	}
	return (map_cpy);
}

char	**rectangolize(t_cub3d *data)
{
	int		n_rows;
	char	**rectangolized_map;

	data->n_col = get_longest_row_size(data->map);
	n_rows = get_n_rows(data->map);
	rectangolized_map = cpy_rectangolized_map(data, data->n_col, n_rows);
	return (rectangolized_map);
}
