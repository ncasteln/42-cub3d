/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrubina <mrubina@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/14 19:01:50 by mrubina           #+#    #+#             */
/*   Updated: 2024/02/18 18:25:50 by mrubina          ###   ########.fr       */
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

	if (dir->x != 0)
	{
		tan = dir->y / dir->x;
		if (dim == Y)
			vector->y = tan * vector->x;
		else if (dim == X && tan != 0)
			vector->x = vector->y / tan;
	}
	else if (dim == X)
		vector->x = 0.0;
}

//returns true if the door is open
//at first we should find the door
int door_open(t_cub3d *data, int x, int y)
{
	int i;

	i = 0;
	while (i < data->n_total_sprites)
	{
		if (data->sprite[i].c == 'D' && (int)(data->sprite[i].x) == x
			&& (int)(data->sprite[i].y) == y && data->sprite[i].isopen == OPEN)
			return (true);
		i++;
	}
	return (false);
}


//checks if a square on the map is free
int check_square(t_cub3d *data, int x, int y)
{
	int isfree;

	//printf("xy: %d, %d \n", x, y);
	isfree = read_map(data, y, x) == '0' || data->map[y][x] == 'N';
	if (BONUS)
		isfree = isfree || (data->map[y][x] == 'D' && door_open(data, x, y));
	return (isfree);
}

// int int_coord(double coord)
// {
// 	if (fabs(coord - round(coord)) <= 0.001) //real coordinate is very close to next
// }
// printf("inc: %f, %f \n", temp.x, temp.y);
//printf("move to: %f, %f \n", data->p->pos.x, data->p->pos.y);

// changes increment vector if an obstacle is encountered
void refine(t_cub3d *data, t_dvect *incr)
{
	t_ivect new_pos;
	t_dvect delta;
	t_dvect temp;
	int isfree;

//finding intersections
// printf("init incr: %f, %f \n", incr->x, incr->y);
new_pos.x = (int)(data->p->pos.x + incr->x);
new_pos.y = (int)(data->p->pos.y + incr->y);
	if (incr->x > 0.01)
		delta.x = ceil(data->p->pos.x) - data->p->pos.x - 0.01;
	else if (incr->x < -0.01)
		delta.x = floor(data->p->pos.x) - data->p->pos.x + 0.01;
	else
		delta.x = 0;
	if (incr->y > 0.01)
		delta.y = ceil(data->p->pos.y) - data->p->pos.y - 0.01;
	else if (incr->y < -0.01)
		delta.y = floor(data->p->pos.y) - data->p->pos.y + 0.01;
	else
		delta.y = 0;
//printf("delta: %f, %f \n", delta.x, delta.y);
// printf("cold - new x: %f, %f \n", data->p->pos.x, data->p->pos.x + incr->x);
// printf("old - new x: %d, %d \n", (int)data->p->pos.x, (int)(data->p->pos.x + incr->x));
// printf("old - new y: %d, %d \n", (int)data->p->pos.y, (int)(data->p->pos.y + incr->y));
//find middle squares
if (new_pos.x == data->p->x && new_pos.y == data->p->y)
{
}//we are in the same square we don't change anything
else if (new_pos.x != data->p->x && new_pos.y != data->p->y) //diagonal movement
{
	//printf("n\n");

	if (fabs(delta.x) < fabs(delta.y)) // it intersects the x shifted square
	{
		if (!check_square(data, new_pos.x, data->p->y)) //we check the x shifted square
		{
			set_vect(&temp, delta.x, 0);
			get_second_dim(&temp, incr, Y);
			set_vect(incr, temp.x, temp.y);
			// printf("x shifted square: %f, %f \n", temp.x, temp.y);
		}
		else if (!check_square(data, new_pos.x, new_pos.y))//we check the diaogonal square
		{
			set_vect(&temp, 0, delta.y);
			get_second_dim(&temp, incr, X);
			set_vect(incr, temp.x, temp.y);
		}
		
	}
	else if (fabs(delta.y) <= fabs(delta.x))
	{
		
	// 	printf("x: %d, %d \n", new_pos.x, data->p->x);
	// printf("y: %d, %d \n", new_pos.y, data->p->y);
		
		if (!check_square(data, data->p->x, new_pos.y)) //we need to stop near the square
		{
			set_vect(&temp, 0, delta.y);
			get_second_dim(&temp, incr, X);
			set_vect(incr, temp.x, temp.y);
			// printf("y shifted square: %f, %f \n", temp.x, temp.y);
		}
		else if (!check_square(data, new_pos.x, new_pos.y))//we need to stop near the square
		{
			set_vect(&temp, delta.x, 0);
			get_second_dim(&temp, incr, Y);
			set_vect(incr, temp.x, temp.y);
		}
		//set_vect(incr, temp.x, temp.y);
	}
}
else if (!check_square(data, new_pos.x, new_pos.y))//we move to adjacent square 
{
	if (new_pos.x == data->p->x) //y is changing
	{
		set_vect(&temp, 0, delta.y);
		get_second_dim(&temp, incr, X);
	}
	else
	{
		
		set_vect(&temp, delta.x, 0);
		get_second_dim(&temp, incr, Y);
		//printf("shift r: %f, %f \n", temp.x, temp.y);
	}
	set_vect(incr, temp.x, temp.y);
}

//if all space is free return true
//if not find the first intersection
//determine the closest position where the player can stand
// put player there

}




// printf("delta: %f, %f \n", incr_vector.x, incr_vector.y);
// 	printf("move to: %f, %f \n", data->p->pos.x, data->p->pos.y);

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
	refine(data, &incr_vector);
	// printf("incr: %f, %f \n", incr_vector.x, incr_vector.y);
	data->p->pos.x += incr_vector.x;
	data->p->pos.y += incr_vector.y;
	data->p->x = (int) data->p->pos.x;
	data->p->y = (int) data->p->pos.y;
	// if ()
	// 	correction(data);
	// printf("new_pos: %f, %f \n", data->p->pos.x, data->p->pos.y);
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
	// printf("x %f \n", p->dirv.x);
	// printf("y %f \n", p->dirv.y);
}


//edit to consider other obstacles!!!
void correction(t_cub3d *data)
{
	t_dvect wtest;
	t_dvect delta;

	set_vect(&wtest, data->p->pos.x, data->p->pos.y + 0.1);
	set_vect(&delta, 0.0, 0.0);
	if (data->map[(int)wtest.y][(int)wtest.x] == '1')
		delta.y += -0.01;
	set_vect(&wtest, data->p->pos.x, data->p->pos.y - 0.1);
	if (data->map[(int)wtest.y][(int)wtest.x] == '1')
		delta.y += 0.01;
	set_vect(&wtest, data->p->pos.x + 0.1, data->p->pos.y);
	if (data->map[(int)wtest.y][(int)wtest.x] == '1')
		delta.x += -0.01;
	set_vect(&wtest, data->p->pos.x - 0.1, data->p->pos.y);
	if (data->map[(int)wtest.y][(int)wtest.x] == '1')
		delta.x += 0.01;
	set_vect(&wtest, data->p->pos.x - 0.1, data->p->pos.y - 0.1);
	if (data->map[(int)wtest.y][(int)wtest.x] == '1')
	{
		delta.x += 0.01;
		delta.y += 0.01;
	}
	data->p->pos.x += delta.x;
	data->p->pos.y += delta.y;
}
