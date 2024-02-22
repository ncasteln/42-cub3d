/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   refine.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrubina <mrubina@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/14 19:01:50 by mrubina           #+#    #+#             */
/*   Updated: 2024/02/21 22:36:07 by mrubina          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

//checks if a square on the map is free
static int	check_square(t_cub3d *data, int x, int y)
{
	int	isfree;

	isfree = read_map(data, y, x) == '0' || read_map(data, y, x) == 'N'
		|| read_map(data, y, x) == 'S' || read_map(data, y, x) == 'E'
		|| read_map(data, y, x) == 'W';
	if (BONUS)
		isfree = isfree || (read_map(data, y, x) == 'D'
				&& door_open(data, x, y));
	return (isfree);
}

/*
given one dimension of an increment vector we calculate the other
and set the vector accordingly
dim is the dimension we have to calculate
 */
static void	set_incr(t_dvect *incr, t_dvect *delta, int dim)
{
	t_dvect	temp;

	if (dim == X)
	{
		set_vect(&temp, 0, delta->y);
		get_second_dim(&temp, incr, X);
		set_vect(incr, temp.x, temp.y);
	}
	else
	{
		set_vect(&temp, delta->x, 0);
		get_second_dim(&temp, incr, Y);
		set_vect(incr, temp.x, temp.y);
	}
}

/*
The function changes the increment vector in case of diagonal movement
The function handles the case when a player moves to the diagonal square.
In this example from square A to square C.
During the movement he might cross square B, square D, or none of them
therefore we handle 3 cases.
___________________
|B       |C       |
|        |/       |
|_______/|________|
 A     / |D       |
		 |		  |
		 |________|
1. The player crosses the x shifted square(D)
At first we check if the adjacent square(B) contains an obstacle
If it does the player should stop at its border
and we change the increment vector accordingly.
If not, we check the diagonal square(C).
2. The player crosses the y shifted square(B)
3. The player moves directly to the diagonal square (C)
*/
void	dg_check(t_cub3d *data, t_dvect *incr, t_dvect *delta, t_ivect *new_pos)
{
	if (fabs(delta->x) < fabs(delta->y))
	{
		if (!check_square(data, new_pos->x, data->p->y))
			set_incr(incr, delta, Y);
		else if (!check_square(data, new_pos->x, new_pos->y))
			set_incr(incr, delta, X);
	}
	else if (fabs(delta->y) < fabs(delta->x))
	{
		if (!check_square(data, data->p->x, new_pos->y))
			set_incr(incr, delta, X);
		else if (!check_square(data, new_pos->x, new_pos->y))
			set_incr(incr, delta, Y);
	}
	else if (fabs(delta->y) == fabs(delta->x))
	{
		if (!check_square(data, new_pos->x, new_pos->y))
			set_vect(incr, delta->x, delta->y);
	}
}

/* 
delta is not a real vector
delta.x is a distance from the player to the border of the next square
 - the square he is moving towards according to the increment x
delta.y is a distance from the player to the border of the next square
 - the square he is moving towards according to the increment y
 */
static void	set_delta(t_cub3d *data, t_dvect *delta, t_dvect *incr)
{
	if (incr->x > 0.01)
		delta->x = ceil(data->p->pos.x) - data->p->pos.x - 0.01;
	else if (incr->x < -0.01)
		delta->x = floor(data->p->pos.x) - data->p->pos.x + 0.01;
	else
		delta->x = 0;
	if (incr->y > 0.01)
		delta->y = ceil(data->p->pos.y) - data->p->pos.y - 0.01;
	else if (incr->y < -0.01)
		delta->y = floor(data->p->pos.y) - data->p->pos.y + 0.01;
	else
		delta->y = 0;
}

/*
The function changes the increment vector if an obstacle is encountered
Suppose the player is in square A.
After the movement in case of no obstacles
the player can stop in same square(A),
in an adjacent square(B or D) or diagonal square (C)
In the latter case he is likely to cross either square B or square C
___________________
|B       |C       |
|        |/       |
|_______/|________|
 A     / |D       |
		 |		  |
		 |________|
Considering the above we have the following algorithm
1. Calculating coordinates of the square where we stop in case of no obstacles
2. Calculating distances to adjacent squares
3. Handling diagonal movement
4. Handling moving to one of the adjacent squares
If the player doesn't cross a square with the obstacles
we don't change the increment vector!
*/
void	refine(t_cub3d *data, t_dvect *incr)
{
	t_ivect	new_pos;
	t_dvect	delta;

	if (incr->x > -0.000001 && incr->x < 0.000001)
		incr->x = 0.000000;
	if (incr->y > -0.000001 && incr->y < 0.000001)
		incr->y = 0.000000;
	new_pos.x = (int)(data->p->pos.x + incr->x);
	new_pos.y = (int)(data->p->pos.y + incr->y);
	set_delta(data, &delta, incr);
	if (new_pos.x != data->p->x && new_pos.y != data->p->y)
		dg_check(data, incr, &delta, &new_pos);
	else if ((new_pos.x != data->p->x || new_pos.y != data->p->y)
		&& !check_square(data, new_pos.x, new_pos.y))
	{
		if (new_pos.x == data->p->x)
			set_incr(incr, &delta, X);
		else
			set_incr(incr, &delta, Y);
	}
}
