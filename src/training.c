/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   training.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrubina <mrubina@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/14 19:01:50 by mrubina           #+#    #+#             */
/*   Updated: 2023/12/22 18:10:15 by mrubina          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../include/cub3d.h"
/*
functions in this file were used for training
and are saved just in case
 */

/* void draw_square(t_data *data, int xStart, int yStart, int side, int color)
{
	int x;
	int y;

	x = data->sx;
	while (x < data->sx + side)
	{
		y = yStart;
		while (y < yStart + side)
		{
			mlx_put_pixel(data->img, x, y, color);
			y++;
		}
		x++;
	}
} */

//function draws a line
void draw_line(t_data *data, int a, int b)
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