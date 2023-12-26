/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path_validation.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nico <nico@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/25 19:17:39 by nico              #+#    #+#             */
/*   Updated: 2023/12/26 12:24:20 by nico             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	is_empty_line(char *s)
{
	int	i;

	i = 0;
	while (s[i] && (s[i] == ' ' || s[i] == '\n')) // tab??
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
	int	i;
	
	i = 0;
	ft_printf("OLD %s\n", old_row);
	while (i < new_row_len)
	{
		if (i < ft_strlen(old_row))
			new_row[i] = old_row[i];
		else
			new_row[i] = '-';
		i++;
	}
	ft_printf("NEW %s\n\n", new_row);
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
	size_t	longest_row;
	int		n_rows;
	char	**map_cpy;

	longest_row = get_longest_row_size(data->map);
	n_rows = get_n_rows(data->map);
	map_cpy = cpy_rectangolized_map(data, longest_row, n_rows);
	return (map_cpy);
}

static void	trim_empty_lines(t_cub3d *data)
{
	char	**trimmed_map;
	int		i;
	int		j;
	int		new_n_rows;

	i = 0;
	j = get_n_rows(data->map) - 1;
	while (is_empty_line(data->map[i]))
		i++;
	while (is_empty_line(data->map[j]))
		j--;
	new_n_rows = j - i;
	ft_printf("NEW N ROWS [%d]\n", new_n_rows);
	exit (99);
}

/*
	The map in which the player can walk has to be enclosed by walls (1). It is
	still possible that in this portion of map, there are empty spaces.

	Valid map.		Valid map.		Invalid map.
	111111111111	111111111111	111111111111
	1N0000000001	1N0000000001	1N000000000
	100      001	100      001	100      00
	100000000001	100000000001	10000000000
	111111111111	111111111111	111111111111
	  00000000
	    0000
*/
void	path_validation(t_cub3d *data)
{
	char	**map_rect;

	trim_empty_lines(data);
	map_rect = rectangolize(data);
}
