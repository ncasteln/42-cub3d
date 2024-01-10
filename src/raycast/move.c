/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrubina <mrubina@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/14 19:01:50 by mrubina           #+#    #+#             */
/*   Updated: 2024/01/11 00:23:51 by mrubina          ###   ########.fr       */
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

	tan = data->rc->dir_y / data->rc->dir_x;
	cos = sign(data->rc->dir_x) * sqrtf(1/(powf(tan, 2) + 1));
	sin = sign(data->rc->dir_y) * sqrtf(1 - powf(cos, 2));
	delta_x = move * cos;
	delta_y = move * sin;
	if (dir == BACK)
	{
		delta_x *= -1;
		delta_y *= -1;
	}
	if (check_space(data, delta_x, delta_y) == true)
	{
		data->rc->pos_x += delta_x;
		data->rc->pos_y += delta_y;
	}
	//  printf("dir: %f, %f \n", data->rc->dir_x, data->rc->dir_y);
	//  printf("stop: %f, %f \n", data->rc->pos_x, data->rc->pos_y);
}

//checks if the movement is possible and the player doesn't go through walls
int check_space(t_cub3d *data, double delta_x, double delta_y)
{
	int x;
	int y;

	x = (int)(data->rc->pos_x + delta_x);
	y = (int)(data->rc->pos_y + delta_y);
	if (data->map[y][x] != '1')
		return (true);
	else
		return (false);
}

void rotateV(double *x, double *y, double angle)
{
	double temp_x;

	temp_x = *x;
	*x = *x * cosf(angle) - *y * sinf(angle);
	*y = temp_x * sinf(angle) + *y * cosf(angle);
}

void rotateP(t_rc *data, double angle)
{
	double tempX;

	tempX = data->dir_x;
	data->dir_x = data->dir_x*cosf(angle) - data->dir_y * sinf(angle);
	data->dir_y = tempX * sinf(angle) + data->dir_y * cosf(angle);
	tempX = data->plane_x;
	data->plane_x = data->plane_x*cosf(angle) - data->plane_y * sinf(angle);
	data->plane_y = tempX * sinf(angle) + data->plane_y * cosf(angle);
}
