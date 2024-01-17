/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   training.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrubina <mrubina@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/14 19:01:50 by mrubina           #+#    #+#             */
/*   Updated: 2024/01/17 00:37:43 by mrubina          ###   ########.fr       */
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

/*
calculates line start and end and sets color
 */
// static void set_draw(t_move *mv)
// {
// 	mv->line_h = (int)(WIN_H / rc->wall_dist);
// 		mv->draw_start = WIN_H / 2 - mv->line_h / 2;
// 		if (mv->draw_start < 0)
// 			mv->draw_start = 0;
// 		mv->draw_end = WIN_H / 2 + mv->line_h / 2;
// 		if (mv->draw_end >= WIN_H)
// 			mv->draw_end = WIN_H;
// 		mv->w_color = WALLC;
// 		if (mv->side == 0)
// 			mv->w_color = dim(WALLC, 10);
// 		else
// 			mv->w_color = WALLC;
// }

uint32_t dim(uint32_t color, uint32_t shift)
{
	uint32_t b;
	uint32_t g;
	uint32_t r;

	b = (color << 16 >> 24);
	g = (color << 8 >> 24);
	r = (color >> 24);
	if (b >= shift)
		b = b - shift;
	if (g >= shift)
		g = g - shift;
	if (r >= shift)
		r = r - shift;
	return ((r << 24) + (g << 16) + (b << 8) + 0xFF);
}