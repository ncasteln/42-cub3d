/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprites.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrubina <mrubina@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/14 19:01:50 by mrubina           #+#    #+#             */
/*   Updated: 2024/01/27 22:07:27 by mrubina          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void put_sprites(t_cub3d *data, double dist_arr[WIN_W])
{
	t_sprite sprite[2];
	t_sprite sorted_sprite[2];
	t_dvect vdist;
	t_dvect tf;
	t_ivect	start;
	t_ivect end;
	int h;
	int w;
	double det;
	int screen_x;
	int i;
	int stripe;
	mlx_texture_t *tex;
	t_ivect texpos;
	int y;
	int d;
	int ind;

	//for test 2 stripes will be used
	//for now sprite coordinates are set manually here
	sprite[0].x = 2;
	sprite[0].y = 2;
	sprite[1].x = 2;
	sprite[1].y = 5;
	sprite[0].dist = sprite_dist_sq(sprite[0], data->p->pos);
	sprite[1].dist = sprite_dist_sq(sprite[1], data->p->pos);
	//printf("dist: %f, %f \n", sprite[0].dist, sprite[1].dist);
	//manual sorting
	if (sprite[0].dist >= sprite[1].dist)
	{
		sorted_sprite[0] = sprite[0];
		sorted_sprite[1] = sprite[1];
	}
	else
	{
		sorted_sprite[0] = sprite[1];
		sorted_sprite[1] = sprite[0];
	}
	i = 0;
	// going through all sprites and drawing them
	while (i < 2)
	{
		tex = data->tex[H];
		set_vect(&vdist, sprite[i].x - data->p->pos.x, sprite[i].y - data->p->pos.y);// relative distance
		det = 1.0/(data->p->plane.x * data->p->dirv.y - data->p->plane.y * data->p->dirv.x);
		tf.x = det * (vdist.x * data->p->dirv.y - vdist.y * data->p->dirv.x); //transformed position
		tf.y = det * (- data->p->plane.y * vdist.x + data->p->plane.x * vdist.y);
		printf("rel: %f, %f \n", vdist.x, vdist.y);
		printf("tf: %f, %f \n", tf.x, tf.y);
		screen_x = (int) ((WIN_W / 2) * (1 + tf.x/tf.y));//pixel x on the screen - middle?
		h = abs((int) (WIN_H / tf.y)); //height
		start.y = -h/2 + WIN_H/2;
		if (start.y < 0)
			start.y = 0;
		end.y = h/2 + WIN_H/2;
		if (end.y >= WIN_H)
			end.y = WIN_H - 1;
		w = abs((int) (WIN_H / tf.y));
		printf("w x: %d, %d \n", w, screen_x);
		start.x = -w/2 + screen_x;
		if (start.x < 0)
			start.x = 0;
		end.x = w/2 + screen_x;
		if (end.x >= WIN_W)
			end.x = WIN_W - 1;
		printf("x interval: %d, %d \n", start.x, end.x);
		printf("y interval: %d, %d \n", start.y, end.y);
		stripe = start.x;
		while (stripe < end.x)
		{
			//texpos.x = (int) (256 * (stripe - (-w/ 2 + screen_x)) *  tex->width / w) / 256;
			texpos.x = (int) ((stripe - (- w/ 2 + screen_x)) *  tex->width / w);
			if (tf.y > 0 && stripe > 0 && stripe < WIN_W && tf.y < dist_arr[stripe])
			{
				//printf("x interval: %d, %d \n", start.x, end.x);
				y = start.y;
				//printf("d arr: %d, %d \n", screen_x, y);
				while (y < end.y)
				{
					d = y * 256 - WIN_H * 128 + h * 128;
					texpos.y = (d * tex->height / h)/ 256;
					ind = (texpos.y * tex->width + texpos.x) * tex->bytes_per_pixel;
					if (readcol(&tex->pixels[ind]) != 0x00000000)
						mlx_put_pixel(data->img, stripe, y, readcol(&tex->pixels[ind]));
					y++;
				}
			}
			stripe++;
		}
		i++;
	}

	//printf("d arr: %f, %f \n", dist_arr[40], dist_arr[200]);
}

