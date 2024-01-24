/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bonus_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncasteln <ncasteln@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/24 15:11:12 by ncasteln          #+#    #+#             */
/*   Updated: 2024/01/24 16:40:34 by ncasteln         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

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
			if (data->map[i][j] == ' ')
				data->n_h += 1;
			if (BONUS)
			{
				if (data->map[i][j] == '$')
					data->n_s += 1;
				if (data->map[i][j] == 'D')
					data->n_d += 1;
			}
			j++;
		}
		i++;
	}
}
