/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncasteln <ncasteln@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/14 19:01:50 by mrubina           #+#    #+#             */
/*   Updated: 2024/01/17 17:03:11 by ncasteln         ###   ########.fr       */
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

// void vert_line(t_cub3d *data, int x, int draw_start, int draw_end)
// {
// 	int y;

// 	y = 0;
// 	while (y >=0 && y < WIN_H)
// 	{
// 		if (y >= draw_start && y <= draw_end)
// 			mlx_put_pixel(data->img, x, y, data->mv->w_color);
// 		else if (y < draw_start)
// 			mlx_put_pixel(data->img, x, y, data->assets->c);
// 		else if (y > draw_end)
// 			mlx_put_pixel(data->img, x, y, data->assets->f);
// 		y++;
// 	}
// }

uint32_t getpixcol(uint8_t *p)
{
	uint32_t b;
	uint32_t g;
	uint32_t r;
	uint32_t a;

	r = (uint32_t) *p;
	g = (uint32_t) *(p + 1);
	b = (uint32_t) *(p + 2);
	a = (uint32_t) *(p + 3);
	return (getcol(r, g, b, a));
}

uint32_t getcol(uint32_t r, uint32_t g, uint32_t b, uint32_t a)
{
	return ((r << 24) + (g << 16) + (b << 8) + a);
}

int sign(double x)
{
	if (x > 0)
		return (1);
	if (x < 0)
		return (-1);
	else
		return (0);
}

t_dvect *set_vect(t_dvect *v, double x, double y)
{
	v->x = x;
	v->y = y;
	return (v);
}

//loads 4 texures from files
//change to add mlx files
void load_textures(t_cub3d *data)
{
	data->mv->tex[0] = mlx_load_png(data->assets->no);
	data->mv->tex[1] = mlx_load_png(data->assets->we);
	data->mv->tex[2] = mlx_load_png(data->assets->so);
	data->mv->tex[3] = mlx_load_png(data->assets->ea);
}
