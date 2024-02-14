/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_valid_doors.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncasteln <ncasteln@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/19 10:24:34 by ncasteln          #+#    #+#             */
/*   Updated: 2024/02/14 16:33:10 by ncasteln         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/*
	111111
	100001
	10D001
	100001
	100001
	111111
 */

static void	check_nesw(t_cub3d *data, size_t y, size_t x)
{
	if (y - 1 >= 0 && data->map[y - 1][x] == '1')
	{
		if (y + 1 <= data->n_rows && data->map[y + 1][x] == '1')
			return ;
	}
	if (x - 1 >= 0 && data->map[y][x - 1] == '1')
	{
		if (x - 1 <= data->n_col && data->map[y][x + 1] == '1')
			return ;
	}
	err_free_exit("check_nesw()", data, E_INV_DOOR);
}

/*
	Doors which are not enclosed between two walls are not considered as valid.
	Something like 00D00 is invalid, as opposite as 01D10.
*/
void	check_valid_doors(t_cub3d *data)
{
	int	i;
	int	j;

	i = 0;
	while (data->map[i])
	{
		j = 0;
		while (data->map[i][j])
		{
			if (data->map[i][j] == 'D')
				check_nesw(data, i, j);
			j++;
		}
		i++;
	}
}
