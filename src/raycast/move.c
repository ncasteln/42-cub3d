/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrubina <mrubina@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/14 19:01:50 by mrubina           #+#    #+#             */
/*   Updated: 2024/01/12 16:29:53 by mrubina          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "cub3d.h"

/*
given the magnitude and the direction of the vector
the vector is calculated
input: direction, magnitude
output: corresponding vector
 */
static void get_vector(t_dvect *vector, t_dvect *dir, double magnitude)
{
	double cos;
	double sin;
	double tan;

	tan = dir->y / dir->x;
	cos = sign(dir->x) * sqrtf(1/(powf(tan, 2) + 1));
	sin = sign(dir->y) * sqrtf(1 - powf(cos, 2));
	init_vect(vector, magnitude * cos, magnitude * sin);
}

/*
player moves forward - along the look direction
 */
void move(t_cub3d *data, double incr, int dir)
{
	t_dvect incr_vector;
	t_dvect dir_vector;

	init_vect(&dir_vector, data->rc->dir_x, data->rc->dir_y);
	if (dir == RIGHT)
		rotateV(&(dir_vector.x), &(dir_vector.y), M_PI / 2);
	else if (dir == LEFT)
		rotateV(&(dir_vector.x), &(dir_vector.y), -M_PI / 2);
	get_vector(&incr_vector, &dir_vector, incr);
	if (dir == BACK)
	{
		incr_vector.x *= -1;
		incr_vector.y *= -1;
	}
	if (check_space(data, incr_vector.x, incr_vector.y) == true)
	{
		data->rc->pos_x += incr_vector.x;
		data->rc->pos_y += incr_vector.y;
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
//rotates any vector by a given angle (radians)
void rotateV(double *x, double *y, double angle)
{
	double temp_x;

	temp_x = *x;
	*x = *x * cosf(angle) - *y * sinf(angle);
	*y = temp_x * sinf(angle) + *y * cosf(angle);
}

//rotates direction vector and plane vector
void rotateP(t_rc *data, double angle)
{
	rotateV(&data->dir_x, &data->dir_y, angle);
	rotateV(&data->plane_x, &data->plane_y, angle);
}
