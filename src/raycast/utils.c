/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrubina <mrubina@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/14 19:01:50 by mrubina           #+#    #+#             */
/*   Updated: 2024/02/21 00:43:33 by mrubina          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

//	sign() adds or substracts 1 to the ray vector x or y.
int	sign(double x)
{
	if (x > 0)
		return (1);
	if (x < 0)
		return (-1);
	else
		return (0);
}

char	read_map(t_cub3d *data, size_t y, size_t x)
{
	if (y >= data->n_rows || x >= data->n_col)
	{
		exit(0); // to edit
	}
	return (data->map[y][x]);
}

/*
	The sprites are counted both in mandatory and BONUS version, because the
	empty spaces are part of the mandatory. The empty spaces are handled as
	they are sprites.
*/
void	count_sprites(t_cub3d *data)
{
	int	i;
	int	j;

	i = 0;
	while (data->map[i])
	{
		j = 0;
		while (data->map[i][j])
		{
			if (data->map[i][j] == 'H')
				data->n_h += 1;
			if (BONUS && data->map[i][j] == 'D')
				data->n_d += 1;
			j++;
		}
		i++;
	}
}

double	sprite_dist_sq(t_sprite s, t_dvect p)
{
	return (pow((s.x - p.x), 2) + pow((s.y - p.y), 2));
}
