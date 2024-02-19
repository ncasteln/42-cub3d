/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrubina <mrubina@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/14 19:01:50 by mrubina           #+#    #+#             */
/*   Updated: 2024/02/20 00:48:11 by mrubina          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"


//returns true if the door is open
//at first we should find the door
int	door_open(t_cub3d *data, int x, int y)
{
	int	i;

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

/*
we have the magnitude of the increment vector
we need to calculate the increment vector in order to add it
to player position vector
we create the increment vector with the same direction as player direction
then we rotate it according to the movement direction
 */
void	move(t_cub3d *data, double incr, int dir)
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
	data->p->pos.x += incr_vector.x;
	data->p->pos.y += incr_vector.y;
	data->p->x = (int) data->p->pos.x;
	data->p->y = (int) data->p->pos.y;
}

//rotates direction vector and plane vector
void	rotate_player(t_player *p, double angle)
{
	rotate_vector(&p->dirv, angle);
	rotate_vector(&p->plane, angle);
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
