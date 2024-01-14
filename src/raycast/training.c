/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   training.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrubina <mrubina@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/14 19:01:50 by mrubina           #+#    #+#             */
/*   Updated: 2024/01/12 21:27:39 by mrubina          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "cub3d.h"
/*
functions in this file were used for training
and are saved just in case
 */

void draw_square(t_cub3d *data, int xStart, int yStart, int side, int color)
{
	int x;
	int y;

	x = 0;
	while (x < 0 + side)
	{
		y = yStart;
		while (y < yStart + side)
		{
			mlx_put_pixel(data->img, x, y, color);
			y++;
		}
		x++;
	}
}

//function draws a line
void draw_line(t_cub3d *data, int a, int b)
{
	int x;
	int y;
	x = 0;
	y = a*x + b;
	while (x < WIN_W)
	{
		if ( y > 0 && y < WIN_W)
			mlx_put_pixel(data->img, x, y, 0xFF00FFAA);
		x++;
		y = a*x + b;
	}
}