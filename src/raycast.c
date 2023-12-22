/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrubina <mrubina@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/14 19:01:50 by mrubina           #+#    #+#             */
/*   Updated: 2023/12/22 20:39:43 by mrubina          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../include/cub3d.h"

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

void rayCasting(t_data *data)
{
	// int map[MAP_W][MAP_H]=
	// {
	//   {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
	//   {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	//   {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	//   {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	//   {1,0,0,0,0,0,2,2,2,2,2,0,0,0,0,3,0,3,0,3,0,0,0,1},
	//   {1,0,0,0,0,0,2,0,0,0,2,0,0,0,0,0,0,0,0,0,0,0,0,1},
	//   {1,0,0,0,0,0,2,0,0,0,2,0,0,0,0,3,0,0,0,3,0,0,0,1},
	//   {1,0,0,0,0,0,2,0,0,0,2,0,0,0,0,0,0,0,0,0,0,0,0,1},
	//   {1,0,0,0,0,0,2,2,0,2,2,0,0,0,0,3,0,3,0,3,0,0,0,1},
	//   {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	//   {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	//   {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	//   {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	//   {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	//   {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	//   {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	//   {1,4,4,4,4,4,4,4,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	//   {1,4,0,4,0,0,0,0,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	//   {1,4,0,0,0,0,5,0,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	//   {1,4,0,4,0,0,0,0,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	//   {1,4,0,4,4,4,4,4,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	//   {1,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	//   {1,4,4,4,4,4,4,4,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	//   {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1}
	// };

	// 	int map[MAP_W][MAP_H]=
	// {
	//   {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
	//   {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	//   {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	//   {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	//   {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	//   {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	//   {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	//   {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	//   {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	//   {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	//   {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	//   {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	//   {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	//   {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	//   {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	//   {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	//   {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	//   {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	//   {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	//   {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	//   {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	//   {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	//   {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	//   {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1}
	// };

		int map[MAP_H][MAP_W]=
{
	{3,3,3,3,3,3,3,3,3,3,3,3,3},
	{4,0,0,0,0,0,0,0,0,0,0,0,2},
	{4,0,0,0,0,0,0,0,0,0,0,0,2},
	{4,0,0,0,0,0,0,0,0,0,0,0,2},
	{4,0,0,0,0,0,0,0,0,0,0,0,2},
	{4,0,0,0,0,0,0,0,0,0,0,0,2},
	{4,0,0,0,0,0,0,0,0,0,0,0,2},
	{4,0,0,0,0,0,0,0,0,0,0,0,2},
	{4,0,0,0,0,0,0,0,0,0,0,0,2},
	{4,0,0,0,0,0,0,0,0,0,0,0,2},
	{4,0,0,0,0,0,0,0,0,0,0,0,2},
	{4,0,0,0,0,0,0,0,0,0,0,0,2},
	{4,0,0,0,0,0,0,0,0,0,0,0,2},
	{4,0,0,0,4,4,0,0,0,0,0,0,2},
	{4,0,0,0,0,0,2,2,0,0,0,0,2},
	{4,0,0,0,0,0,0,0,0,0,0,0,2},
	{4,0,0,0,0,0,0,0,0,0,0,0,2},
	{4,0,0,0,0,0,0,0,0,0,0,0,2},
	{4,0,0,0,0,0,0,0,0,0,0,0,2},
	{4,0,0,0,0,0,0,0,0,0,0,0,2},
	{4,0,0,0,0,0,0,0,0,0,0,0,2},
	{4,0,0,0,0,0,0,0,0,0,0,0,2},
	{4,0,0,0,0,0,0,0,0,0,0,0,2},
	{1,1,1,1,1,1,1,1,1,1,1,1,1}
};


	data->pixelX = 0;//we start at first pixel
	//printf("start %f, ", ((t_data *)data)->posX);
	//printf("%d, ", n);
	//printf("%d, ", map[22][12]);
	while (data->pixelX < WIN_W)
	{
		
		data->camX = 2 * data->pixelX / ((double) WIN_W) - 1;
		data->rayDirX = data->dirX + data->planeX * data->camX;
		data->rayDirY = data->dirY + data->planeY * data->camX;
		
		//printf("(%f, %f) ", data->rayDirX, data->rayDirY);
		data->mapX = (int) data->posX;
		data->mapY = (int) data->posY;
	
		//printf("(%i, %i) ", data->mapX, data->mapY);
		data->deltaDistX = fabs(1/data->rayDirX);
		data->deltaDistY = fabs(1/data->rayDirY);
		//printf("(%f, %f) ", data->deltaDistX, data->deltaDistY);
		if (data->rayDirX < 0)
		{
			data->stepX = -1;
			data->sideDistX = (data->posX - data->mapX) * data->deltaDistX;
			//printf("less %f ", data->sideDistX);
		}
		else
		{

			data->stepX = 1;
			data->sideDistX = (data->mapX + 1.0 - data->posX) * data->deltaDistX;
			//printf("greater %f ", data->sideDistX);
		}
		if (data->rayDirY < 0)
		{
			data->stepY = -1;
			data->sideDistY = (data->posY - data->mapY) * data->deltaDistY;
			//printf("less %f ", data->sideDistY);
		}
		else
		{
			data->stepY = 1;
			data->sideDistY = (data->mapY + 1.0 - data->posY) * data->deltaDistY;
			//printf("greater  %f ", data->sideDistY);
		}
	
		//algorithm before hit
		while (data->hit == 0)
		{
			//printf("%i, ", data->hit);
			if (data->sideDistX < data->sideDistY)
			{
				data->sideDistX += data->deltaDistX;
				data->mapX += data->stepX;
				data->side = 0;
			}
			else
			{
				data->sideDistY += data->deltaDistY;
				data->mapY += data->stepY;
				data->side = 1;
			}
			//if (data->map[data->mapX][data->mapY] > 0)
			if (map[data->mapX][data->mapY] > 0)
				data->hit = 1;
			//printf("%i ", data->hit);
		}
	
		data->hit = 0;
		if (data->side == 0)
			data->wallDist = data->sideDistX - data->deltaDistX;
		else
			data->wallDist = data->sideDistY - data->deltaDistY;
		data->lineHeight = (int)(data->h / data->wallDist);
		data->drawStart = - data->lineHeight / 2 + data->h / 2;
		if (data->drawStart < 0)
			data->drawStart = 0;
		data->drawEnd = data->lineHeight / 2 + data->h / 2;
		if (data->drawStart >= data->h)
			data->drawStart = data->h - 1;
		//printf("%i, ", data->drawEnd);
		int color;

	if (map[data->mapX][data->mapY] == 1)
		color = RED;//red
	else if (map[data->mapX][data->mapY] == 2)
		color = GREEN;//green
	else if (map[data->mapX][data->mapY] == 3)
		color = BLUE;//blue
	else if (map[data->mapX][data->mapY] == 4)
		color = ORANGE;
	else
		color = WHITE;
	if (data->side == 1)
		color = color / 2;
	//printf("drawing %i, x %i", data->drawStart, data->pixelX);
	vert_line(data, data->pixelX, data->drawStart, data->drawEnd, color);
		data->pixelX++;
	}
	//printf("built for %f, x %f", data->posX, data->posY);
}

void rotateP(t_data *data, double angle)
{
	double tempX;

	tempX = data->dirX;
	data->dirX = data->dirX*cosf(angle) - data->dirY * sinf(angle);
	data->dirY = tempX * sinf(angle) + data->dirY * cosf(angle);
	tempX = data->planeX;
	data->planeX = data->planeX*cosf(angle) - data->planeY * sinf(angle);
	data->planeY = tempX * sinf(angle) + data->planeY * cosf(angle);
}