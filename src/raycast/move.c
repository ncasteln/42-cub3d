/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrubina <mrubina@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/14 19:01:50 by mrubina           #+#    #+#             */
/*   Updated: 2024/01/10 17:21:17 by mrubina          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "cub3d.h"


/*
player moves forward - along the look direction
 */
void move(t_cub3d *data, double move, int dir)
{
	double cos;
	double sin;
	double tan;
	double delta_x;
	double delta_y;

	tan = data->rcdata->dir_y / data->rcdata->dir_x;
	cos = sign(data->rcdata->dir_x) * sqrtf(1/(powf(tan, 2) + 1));
	sin = sign(data->rcdata->dir_y) * sqrtf(1 - powf(cos, 2));
	delta_x = move * cos;
	delta_y = move * sin;
	if (dir == BACK)
	{
		delta_x *= -1;
		delta_y *= -1;
	}
	if (check_space(data, delta_x, delta_y) == true)
	{
		data->rcdata->pos_x += delta_x;
		data->rcdata->pos_y += delta_y;
	}
	//  printf("dir: %f, %f \n", data->rcdata->dir_x, data->rcdata->dir_y);
	//  printf("stop: %f, %f \n", data->rcdata->pos_x, data->rcdata->pos_y);
}

//checks if the movement is possible and the player doesn't go through walls
int check_space(t_cub3d *data, double delta_x, double delta_y)
{
	int x;
	int y;

	x = (int)(data->rcdata->pos_x + delta_x);
	y = (int)(data->rcdata->pos_y + delta_y);
	if (data->map[y][x] != '1')
		return (true);
	else
		return (false);
}
