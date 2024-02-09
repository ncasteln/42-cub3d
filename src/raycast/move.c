/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncasteln <ncasteln@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/14 19:01:50 by mrubina           #+#    #+#             */
/*   Updated: 2024/02/09 08:58:33 by ncasteln         ###   ########.fr       */
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
	set_vect(vector, magnitude * cos, magnitude * sin);
}

/*
given x and the direction we get y or the other way round
 */
static void get_second_dim(t_dvect *vector, t_dvect *dir, int dim)
{
	double tan;

	tan = dir->y / dir->x;
	if (dim == Y)
		vector->y = tan * vector->x;
	else if (dim == X && tan != 0)
		vector->x = vector->y / tan;
}

// static void add_delta(t_cub3d *data, double *delta_x, double *delta_y)
// {
// 	int x;
// 	int y;
// 	t_dvect test;
// 	test.x = data->p->pos.x + *delta_x;
// 	test.y = data->p->pos.y + *delta_y;

// 	x = (int)test.x;
// 	y = (int)test.y;
// 	if (data->map[y][x] != '1' && data->map[y][x] != ' ')
// 	{
// // 		printf("no wall\n");
// 		data->p->pos.x += *delta_x;
// 		data->p->pos.y += *delta_y;
// 		data->p->x = (int) data->p->pos.x;
// 		data->p->y = (int) data->p->pos.y;
// 	}
// 	else
// 	{
// // 		printf("wall\n");
// 		// *delta_x = data->p->pos.x + *delta_x - x;
// 		// *delta_y = data->p->pos.y + *delta_y - y;

// // // printf("de: %f, %f \n", *delta_x, *delta_y);
// // 		if (fabs(*delta_x) < fabs(*delta_y))
// // 			data->p->pos.x += *delta_x;
// // 		else
// // 			data->p->pos.y += *delta_y;
// // 		printf("wall: %i, %i \n", x, y);
// 		data->p->pos.x = x - 0.1 * sign(*delta_x);
// 		data->p->pos.y = y - 0.1 * sign(*delta_y);
// // 		printf("new_pos: %f, %f \n", data->p->pos.x, data->p->pos.y);
// 		data->p->x = (int) data->p->pos.x;
// 		data->p->y = (int) data->p->pos.y;
// // 		printf("de: %f, %f \n", *delta_x, *delta_y);
// 	}
// }

//checks if the movement is possible and the player doesn't go through walls
int check_space(t_cub3d *data, double delta_x, double delta_y)
{
	int x;
	int y;

	x = (int)(data->p->pos.x + delta_x);
	y = (int)(data->p->pos.y + delta_y);
	if (data->map[y][x] != '1' && data->map[y][x] != 'H')
		return (true);
	// if (BONUS && data->map[y][x] != 'D' && data->map[y][x] != '$')
	// 	return (true);
	return (false);
}

static void next_to_wall(t_cub3d *data, t_dvect *new_pos, int dim, t_dvect delta)
{
	double tan;

	// printf("x or y: %i\n", dim);

	tan = delta.y / delta.x;
	// printf("ntw: %f, %f \n", data->p->pos.x, data->p->pos.y);
	if (dim == X)
	{
		if (delta.x > 0)
			new_pos->x = floor(new_pos->x + delta.x) - 0.01;
		else
			new_pos->x = floor(new_pos->x) + 0.01;
		new_pos->y += tan * (new_pos->x - data->p->pos.x);
		// printf("ntw new: %f, %f \n", new_pos->x, new_pos->y);
	}
	else if (dim == Y)
	{
		if (delta.y > 0)
			new_pos->y = floor(new_pos->y + delta.y) - 0.01;
		else
			new_pos->y = floor(new_pos->y) + 0.01;
		if (tan != 0)
			new_pos->x += (new_pos->y - data->p->pos.y)/ tan;
	}
}

/*
if the player is about to collide with the wall
we calculate the nearest position to the wall in intended direction
and put the player in this position
1) we check in what direction we have the closest wall
2) in that direction we calculate the intersection
and the closest possible coordinate to the wall
3)we calculate the second coordinate
both coordinates should correspond to the moving direction
4)we place the player to the new position

 */
void minimove(t_cub3d *data, t_dvect delta)
{
	t_dvect new_pos;

	set_vect(&new_pos, data->p->pos.x, data->p->pos.y);
	if (fabs(delta.x) < fabs(delta.y))
	{
		if (!check_space(data, delta.x, 0)) //intersection while x
			next_to_wall(data, &new_pos, X, delta);
		else if (!check_space(data, 0, delta.y))
			next_to_wall(data, &new_pos, Y, delta);
		//else
	}
	else
	{
		if (!check_space(data, 0, delta.y))
			next_to_wall(data, &new_pos, Y, delta);
		else if (!check_space(data, delta.x, 0)) //intersection while x
			next_to_wall(data, &new_pos, X, delta);
		//else
	}
		data->p->pos.x = new_pos.x;
		data->p->pos.y = new_pos.y;
}

/*
we have the magnitude of the increment vector
we need to calculate the increment vector in order to add it
to player position vector
we create the increment vector with the same direction as player direction
then we rotate it according to the movement direction
 */
void move(t_cub3d *data, double incr, int dir)
{
	t_dvect incr_vector;

	get_vector(&incr_vector, &data->p->dirv, incr);
	if (dir == RIGHT)
		rotate_vector(&incr_vector, M_PI / 2);
	else if (dir == LEFT)
		rotate_vector(&incr_vector, -M_PI / 2);
	if (dir == BACK)
		rotate_vector(&incr_vector, M_PI);
	// //printf("delta: %f, %f \n", incr_vector.x, incr_vector.y);
	if (check_space(data, incr_vector.x, incr_vector.y) == true)
	{
		data->p->pos.x += incr_vector.x;
		data->p->pos.y += incr_vector.y;
		data->p->x = (int) data->p->pos.x;
		data->p->y = (int) data->p->pos.y;
	}
	else
		minimove(data, incr_vector);
}

//rotates any vector by a given angle (radians)
void rotate_vector(t_dvect *v, double angle)
{
	double temp_x;

	temp_x = v->x;
	v->x = v->x * cosf(angle) - v->y * sinf(angle);
	v->y = temp_x * sinf(angle) + v->y * cosf(angle);
}

//rotates direction vector and plane vector
void rotate_player(t_player *p, double angle)
{
	rotate_vector(&p->dirv, angle);
	rotate_vector(&p->plane, angle);
}

void correction(t_cub3d *data)
{
	t_dvect wtest;
	t_dvect delta;

	set_vect(&wtest, data->p->pos.x, data->p->pos.y + 0.1);
	set_vect(&delta, 0.0, 0.0);
	if (data->map[(int)wtest.y][(int)wtest.x] == '1')
		{
			delta.y += -0.01;
			// printf("pos: %f, %f \n", wtest.x, wtest.y);
			// printf("c%c \n", data->map[(int)wtest.y][(int)wtest.x]);

		}
	set_vect(&wtest, data->p->pos.x, data->p->pos.y - 0.1);
	if (data->map[(int)wtest.y][(int)wtest.x] == '1')
		{
			// printf("-%f \n", data->p->pos.y - 0.1);
			delta.y += 0.01;}
	set_vect(&wtest, data->p->pos.x + 0.1, data->p->pos.y);
	if (data->map[(int)wtest.y][(int)wtest.x] == '1')
		delta.x += -0.01;
	set_vect(&wtest, data->p->pos.x - 0.1, data->p->pos.y);
	if (data->map[(int)wtest.y][(int)wtest.x] == '1')
		delta.x += 0.01;
	data->p->pos.x += delta.x;
	// printf("d%f \n", delta.y);
	data->p->pos.y += delta.y;
	// printf("%f \n", data->p->pos.y);
}
