/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   trim_empty_lines.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncasteln <ncasteln@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/20 09:02:04 by ncasteln          #+#    #+#             */
/*   Updated: 2024/02/20 09:03:38 by ncasteln         ###   ########.fr       */
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
		err_free_exit("trim_empty_lines", data, 0, errno);
	k = 0;
	while (i <= j)
	{
		trimmed_map[k] = ft_strdup(data->map[i]);
		if (!trimmed_map[k])
			err_free_exit("trim_empty_lines", data, 0, errno);
		i++;
		k++;
	}
	return (trimmed_map);
}

/*
	Trim empty lines on the exteremities of the map, means on the top
	and on the bottom (not in the middle).
*/
void	trim_empty_lines(t_cub3d *data)
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
