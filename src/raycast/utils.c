/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrubina <mrubina@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/14 19:01:50 by mrubina           #+#    #+#             */
/*   Updated: 2024/02/03 18:44:57 by mrubina          ###   ########.fr       */
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

//	takes separate rgba values and returns color
uint32_t getcol(uint32_t r, uint32_t g, uint32_t b, uint32_t a)
{
	return ((r << 24) + (g << 16) + (b << 8) + a);
}


//	sign() adds or substracts 1 to the ray vector x or y.
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

/*
	Loads the textures for the library. 5 mandatory, 2 optional.
	@param [H] - represents the whitespaces of the map (we called them holes).
*/
void load_textures(t_cub3d *data)
{
	data->tex[NO] = mlx_load_png(data->assets->no);
	data->tex[WE] = mlx_load_png(data->assets->we);
	data->tex[SO] = mlx_load_png(data->assets->so);
	data->tex[EA] = mlx_load_png(data->assets->ea);
	data->tex[H] = mlx_load_png("assets/barrel.png"); // check if needed at the end  ?????
	if (BONUS && data->n_d)
		//data->tex[D] = mlx_load_png(data->assets->d); // check if needed at the end  ?????
		data->tex[D] = mlx_load_png("assets/Tile_17.png"); // check if needed at the end  ?????
	if (BONUS && data->n_s)
		data->tex[S] = mlx_load_png("assets/barrel.png"); // check if needed at the end  ?????
}

/*
	The sprites are counted both in mandatory and BONUS version, because the
	empty spaces are part of the mandatory. The empty spaces are handled as
	they are sprites.
*/
void	count_sprites(t_cub3d *data)
{
	int	i;
	int	j;

	i = 0;
	while (data->map[i])
	{
		j = 0;
		while (data->map[i][j])
		{
			if (data->map[i][j] == ' ')
				data->n_h += 1;
			if (BONUS)
			{
				if (data->map[i][j] == '$')
					data->n_s += 1;
				if (data->map[i][j] == 'D')
					data->n_d += 1;
			}
			j++;
		}
		i++;
	}
}

// double vect_dist_sq(t_dvect v1, t_dvect v2)
// {
// 	return (pow((v2.x - v1.x), 2) + pow((v2.y - v1.y), 2));
// }

double sprite_dist_sq(t_sprite s, t_dvect p)
{
	return (pow((s.x - p.x), 2) + pow((s.y - p.y), 2));
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
