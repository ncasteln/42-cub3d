/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrubina <mrubina@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/14 19:01:50 by mrubina           #+#    #+#             */
/*   Updated: 2023/12/22 00:44:07 by mrubina          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../include/cub3d.h"

void draw_square(t_data *data, int xStart, int yStart, int side, int color)
{
	int x;
	int y;

	x = data->sx;
	while (x < data->sx + side)
	{
		y = yStart;
		while (y < yStart + side)
		{
			//printf("(%i, %i) ", x, y);
			mlx_put_pixel(data->img, x, y, color);
			y++;
		}
		x++;
	}
}

void clearScreen(t_data *data)
{
	int x;
	int y;

	x = 0;
	while (x < WIN_W)
	{
		y = 0;
		while (y < WIN_H)
		{
			//printf("(%i, %i) ", x, y);
			mlx_put_pixel(data->img, x, y, 0x00000000);
			y++;
		}
		x++;
	}
}

void rayCasting(t_data *data)
{
	int map[MAP_W][MAP_H]=
{
  {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,2,2,2,2,2,0,0,0,0,3,0,3,0,3,0,0,0,1},
  {1,0,0,0,0,0,2,0,0,0,2,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,2,0,0,0,2,0,0,0,0,3,0,0,0,3,0,0,0,1},
  {1,0,0,0,0,0,2,0,0,0,2,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,2,2,0,2,2,0,0,0,0,3,0,3,0,3,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,4,4,4,4,4,4,4,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,4,0,4,0,0,0,0,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,4,0,0,0,0,5,0,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,4,0,4,0,0,0,0,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,4,0,4,4,4,4,4,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,4,4,4,4,4,4,4,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1}
};
	data->x = 0;
	//printf("start %f, ", ((t_data *)data)->posX);
	//printf("%d, ", n);
	while (data->x < WIN_W)
	{
	
		// if (data->x == 639)
		// 	printf("dgssgdg ");
		data->camX = 2 * data->x / ((double) WIN_W) - 1;
		//printf("%f ", data->camX);
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
	//printf("drawing %i, x %i", data->drawStart, data->x);
	vert_line(data, data->x, data->drawStart, data->drawEnd, color);
		data->x++;
	}
	//printf("built for %f, x %f", data->posX, data->posY);
}