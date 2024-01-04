/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrubina <mrubina@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/14 19:01:50 by mrubina           #+#    #+#             */
/*   Updated: 2024/01/05 00:45:39 by mrubina          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "cub3d.h"

// this function clears the image - makes it black
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
			mlx_put_pixel(data->img, x, y, 0x00000000);
			y++;
		}
		x++;
	}
}

void vert_line(t_data *data, int x, int drawStart, int drawEnd, int color)
{
	int y;

	y = 0;
	while (y >=0 && y < WIN_H)
	{
		if (y > drawStart && y < drawEnd)
			mlx_put_pixel(data->img, x, y, color);
		y++;
	}
}

void set_map(int map[MAP_W][MAP_H])
{
	int x;
	int y;
	x = 0;
	y = 0;
	while (x < MAP_W)
	{
		while (y < MAP_H)
		{
			if ((x == 0 || x == MAP_W - 1) || (y == 0 || y == MAP_H - 1))
				map[x][y] = 1;
			else
				map[x][y] = 0;
			y++;
		}
		x++;
	}
	// map[1][1] = 1;
	// map[3][1] = 1;
	// 1111111111
	// 1000000001
	// 1000000001
	// 1000000001
	// 1000000001
	// 1000000001
	// 1000000001
	// 1000000001
	// 1000p00001
	// 1111111111
}