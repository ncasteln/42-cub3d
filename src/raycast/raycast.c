/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrubina <mrubina@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/14 19:01:50 by mrubina           #+#    #+#             */
/*   Updated: 2024/01/10 01:29:03 by mrubina          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "cub3d.h"

/*
functions for raycasting algorithm
 */

/*
Some expanations, for now incomplete:
	We have several spaces and each space has several coordinate systems
	1. map space - this is a space where our player walks
	it has two coordinate systems
	first system is integer and based on squares
	for example we have a map 10x10 squares
	A square can be occupied or not occupied by the wall
	It's easy to say where is the wall on the map using integer coordinates
	for example we can put a column at (6, 7)
	float point coordinates
	A player doesn't occupy the whole square and he can move inside it
	so it makes sense using float point coordinates to show his precise position
	if a player has integer coordinates (1,1) and he moves inside the square (1,1)
	his float coordinates can be (1.24, 1.76) for example
	2. screen space - this is what out player sees and therefore our game screen shows
	it also has two types of coordinates
	first system is integer pixel system
	if for example our game window is 640x480 pixels
	a pixel is going to have integer coordinates like (120,65)
	float coordinates are used to make vector manipulations easier
	we use it only for x-dimension here
	the left side of the window has x = -1, middle x = 0 right side - x = 1
	I call them normalized coordinates because it's similar
	to normalization process in math.
	Raycasting algorithm:
	Input (non-constant): palyer position, player look direction
	Output: the game screen shows what player sees
	for each x of the game screen we find the wall that the player faces,
	calculate the distance to that wall and it's size
	and draw that wall

*/

void rayCasting(t_cub3d *data)
{
	data->rcdata->pixel_x = 0;//we start at first pixel
	while (data->rcdata->pixel_x < WIN_W)
	{
		data->rcdata->cam_x = 2 * data->rcdata->pixel_x / ((double) WIN_W) - 1;
		data->rcdata->raydir_x = data->rcdata->dir_x - data->rcdata->plane_x * data->rcdata->cam_x;
		data->rcdata->raydir_y = data->rcdata->dir_y - data->rcdata->plane_y * data->rcdata->cam_x;
		
		// printf("raydir(%f, %f) \n", data->rcdata->raydir_x, data->rcdata->raydir_y);
		// printf("lookdir(%f, %f) \n", data->rcdata->dir_x, data->rcdata->dir_y);
		// printf("camx %f \n", data->rcdata->cam_x);
		// printf("pix %i \n", data->rcdata->pixel_x);
		data->rcdata->map_x = (int) data->rcdata->pos_x;
		data->rcdata->map_y = (int) data->rcdata->pos_y;
		//printf("%d ", data->rcdata->map_y);
	
		//printf("(%i, %i) ", data->rcdata->map_x, data->rcdata->map_y);
		data->rcdata->delta_dist_x = fabs(1/data->rcdata->raydir_x);
		data->rcdata->delta_dist_y = fabs(1/data->rcdata->raydir_y);
		//printf("(%f, %f) ", data->rcdata->delta_dist_x, data->rcdata->delta_dist_y);
		if (data->rcdata->raydir_x < 0)
		{
			data->rcdata->step_x = -1;
			data->rcdata->side_dist_x = (data->rcdata->pos_x - data->rcdata->map_x) * data->rcdata->delta_dist_x;
			//printf("less %f ", data->rcdata->side_dist_x);
		}
		else
		{

			data->rcdata->step_x = 1;
			data->rcdata->side_dist_x = (data->rcdata->map_x + 1.0 - data->rcdata->pos_x) * data->rcdata->delta_dist_x;
			//printf("greater %f ", data->rcdata->side_dist_x);
		}
		if (data->rcdata->raydir_y < 0)
		{
			data->rcdata->step_y = -1;
			data->rcdata->side_dist_y = (data->rcdata->pos_y - data->rcdata->map_y) * data->rcdata->delta_dist_y;
			//printf("less %f ", data->rcdata->side_dist_y);
		}
		else
		{
			data->rcdata->step_y = 1;
			data->rcdata->side_dist_y = (data->rcdata->map_y + 1.0 - data->rcdata->pos_y) * data->rcdata->delta_dist_y;
			//printf("greater  %f ", data->rcdata->side_dist_y);
		}
		//algorithm before hit
		while (data->rcdata->hit == 0)
		{
			//printf("%i, ", data->rcdata->hit);
			// printf("%f ", data->rcdata->side_dist_x);
			// printf("%f ", data->rcdata->side_dist_y);
			//exit(0);
			if (data->rcdata->side_dist_x < data->rcdata->side_dist_y)
			{
				data->rcdata->side_dist_x += data->rcdata->delta_dist_x;
				data->rcdata->map_x += data->rcdata->step_x;
				data->rcdata->side = 0;
			}
			else
			{
				data->rcdata->side_dist_y += data->rcdata->delta_dist_y;
				data->rcdata->map_y += data->rcdata->step_y;
				// printf("%d ", data->rcdata->map_y);
				// exit(0);
				data->rcdata->side = 1;
			}
			
			//if (data->rcdata->map[data->rcdata->map_x][data->rcdata->map_y] > 0)
			// printf("%d ", data->map[data->rcdata->map_y][data->rcdata->map_x]);
			// printf("%d ", data->rcdata->map_y);
			// exit(0);
			if (data->map[data->rcdata->map_y][data->rcdata->map_x] == 49)
				data->rcdata->hit = 1;
			//exit(0);
			//printf("%i ", data->rcdata->hit);
		}
		data->rcdata->hit = 0;
		if (data->rcdata->side == 0)
			data->rcdata->wall_dist = data->rcdata->side_dist_x - data->rcdata->delta_dist_x;
		else
			data->rcdata->wall_dist = data->rcdata->side_dist_y - data->rcdata->delta_dist_y;
		data->rcdata->line_h = (int)(data->rcdata->h / data->rcdata->wall_dist);
		data->rcdata->draw_start = - data->rcdata->line_h / 2 + data->rcdata->h / 2;
		if (data->rcdata->draw_start < 0)
			data->rcdata->draw_start = 0;
		data->rcdata->draw_end = data->rcdata->line_h / 2 + data->rcdata->h / 2;
		if (data->rcdata->draw_start >= data->rcdata->h)
			data->rcdata->draw_start = data->rcdata->h - 1;
		//printf("%i, ", data->rcdata->draw_end);
		//int color;

	//color = RED;
	// if (data->map[data->rcdata->map_y][data->rcdata->map_x] == 49)
	// 	color = RED;//red
	// else if (data->map[data->rcdata->map_y][data->rcdata->map_x] == 2)
	// 	color = GREEN;//green
	// else if (data->map[data->rcdata->map_y][data->rcdata->map_x] == 3)
	// 	color = BLUE;//blue
	// else if (data->map[data->rcdata->map_y][data->rcdata->map_x] == 4)
	// 	color = ORANGE;
	// else
	// 	color = WHITE;
	data->rcdata->w_color = WALLC;
	if (data->rcdata->side == 0)
		data->rcdata->w_color = dim(WALLC, 10);
	else
		data->rcdata->w_color = WALLC;
	//printf("drawing %i, x %i", data->rcdata->draw_start, data->rcdata->pixel_x);
	vert_line(data, data->rcdata->pixel_x, data->rcdata->draw_start, data->rcdata->draw_end);
		data->rcdata->pixel_x++;
	}
	// printf("x: %f \n", data->rcdata->dir_x);
	// printf("y: %f \n", data->rcdata->dir_y);
	// printf("px: %f \n", data->rcdata->plane_x);
	// printf("py: %f \n", data->rcdata->plane_y);
	//printf("built for %f, x %f", data->rcdata->dir_x, data->rcdata->dir_y);
}


void rotateV(double *x, double *y, double angle)
{
	double temp_x;

	temp_x = *x;
	*x = *x * cosf(angle) - *y * sinf(angle);
	*y = temp_x * sinf(angle) + *y * cosf(angle);
}

void rotateP(t_rcdata *data, double angle)
{
	double tempX;

	tempX = data->dir_x;
	data->dir_x = data->dir_x*cosf(angle) - data->dir_y * sinf(angle);
	data->dir_y = tempX * sinf(angle) + data->dir_y * cosf(angle);
	tempX = data->plane_x;
	data->plane_x = data->plane_x*cosf(angle) - data->plane_y * sinf(angle);
	data->plane_y = tempX * sinf(angle) + data->plane_y * cosf(angle);
	// double alpha = atan(data->dir_y / data->dir_x);
	// printf("angle: %f \n", alpha);
	// printf("%f, %f \n", data->dir_x, data->dir_y);
}

