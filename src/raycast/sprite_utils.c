/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprite_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrubina <mrubina@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/14 19:01:50 by mrubina           #+#    #+#             */
/*   Updated: 2024/02/21 21:56:29 by mrubina          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

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

/* sets squared distance
from the sprite to the current position of the player */
void	set_dist(t_cub3d *data)
{
	int	n;

	n = 0;
	while (n < data->n_total_sprites)
	{
		data->sprite[n].dist = sprite_dist_sq(data->sprite[n], data->p->pos);
		n++;
	}
}

void	bubble(t_sprite *sprite, int n)
{
	t_sprite	temp;
	int			swapped;
	int			i;

	swapped = 1;
	while (swapped)
	{
		swapped = 0;
		i = 1;
		while (i <= n - 1)
		{
			if (sprite[i - 1].dist < sprite[i].dist)
			{
				temp = sprite[i - 1];
				sprite[i - 1] = sprite[i];
				sprite[i] = temp;
				swapped = 1;
			}
			i++;
		}
	}
}
