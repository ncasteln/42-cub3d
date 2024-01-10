/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrubina <mrubina@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/14 19:01:50 by mrubina           #+#    #+#             */
/*   Updated: 2024/01/08 16:16:04 by mrubina          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "cub3d.h"

// this function clears the image - makes it black
void clearScreen(t_cub3d *data)
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

// void vert_line(t_cub3d *data, int x, int draw_start, int draw_end, int color)
// {
// 	int y;

// 	y = 0;
// 	while (y >=0 && y < WIN_H)
// 	{
// 		if (y > draw_start && y < draw_end)
// 			mlx_put_pixel(data->img, x, y, color);
// 		y++;
// 	}
// }

void vert_line(t_cub3d *data, int x, int draw_start, int draw_end)
{
	int y;

	y = 0;
	while (y >=0 && y < WIN_H)
	{
		if (y >= draw_start && y <= draw_end)
			mlx_put_pixel(data->img, x, y, data->rcdata->w_color);
		else if (y < draw_start)
			///mlx_put_pixel(data->img, x, y, data->assets->f);
			mlx_put_pixel(data->img, x, y, 0xFF0000FF);
		else if (y > draw_end)
			//mlx_put_pixel(data->img, x, y, data->assets->c);
			mlx_put_pixel(data->img, x, y, 0xC80808FF);
		y++;
	}
}

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

double x_move(double dir_x, double dir_y, double move)
{
	double alpha;
	double x_move;
	
	alpha = atan(dir_y/dir_x);
	x_move = move * cosf(alpha);
	return(x_move);
}