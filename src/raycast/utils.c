/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncasteln <ncasteln@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/14 19:01:50 by mrubina           #+#    #+#             */
/*   Updated: 2024/01/24 08:17:01 by ncasteln         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "cub3d.h"

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

/*
reads rgba values from a pixel and returns its color
p points to the r value of a pixel followed by the others
*/
uint32_t readcol(uint8_t *p)
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

//takes separate rgba values and returns color
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
	data->tex[NO] = mlx_load_png(data->assets->no);
	data->tex[WE] = mlx_load_png(data->assets->we);
	data->tex[SO] = mlx_load_png(data->assets->so);
	data->tex[EA] = mlx_load_png(data->assets->ea);
	data->tex[4] = mlx_load_png("src/textures/lava.png");
}

// t_ftile *revert_buff(t_dvect *buff, int size)
// {
// 	t_dvect *new_buff;
// 	int i;

// 	if (size == 0)
// 		return(NULL);
// 	i = 0;
// 	new_buff = malloc(sizeof(t_dvect) * size);
// 	while (i < size)
// 	{
// 		new_buff[i].x = buff[i + size - 1].x;
// 		new_buff[i].y = buff[i + size - 1].y;
// 		i++;
// 	}
// 	printf("%s \n", "free");
// 	free(buff);
// 	buff = NULL;
// 	return (new_buff);
// }
