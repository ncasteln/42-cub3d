/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   spritecast.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncasteln <ncasteln@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/14 19:01:50 by mrubina           #+#    #+#             */
/*   Updated: 2024/02/20 10:00:56 by ncasteln         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/*
calculates transform coordinates of a vextor in space
multiplying it with the inverse transform matrix
 */
void	transform_vector(t_dvect *new, t_dvect *old, t_player *p)
{
	double	det;

	det = 1.0 / (p->plane.x * p->dirv.y - p->plane.y * p->dirv.x);
	new->x = det * (old->x * p->dirv.y - old->y * p->dirv.x);
	new->y = det * (-p->plane.y * old->x + p->plane.x * old->y);
}

/*
calculates transform coordinates of a sprite
using the distance from the player to the sprite
for a door two points are used
 */
void	transform(t_player *p, t_spritecast *sc, t_sprite *sprite)
{
	t_dvect	vdist;

	//set_vect(&vdist, sprite->x - p->pos.x, sprite->y - p->pos.y);
	//printf("c %d %f \n", i, data->sprite[i].dist);
	if (sprite->c == 'D')
	{
		set_vect(&vdist, sprite->door_left_edge.x - p->pos.x, sprite->door_left_edge.y - p->pos.y);
		transform_vector(&(sc->transform), &vdist, p);
		set_vect(&vdist, sprite->door_right_edge.x - p->pos.x, sprite->door_right_edge.y - p->pos.y);
		transform_vector(&(sc->transform2), &vdist, p);
		// printf("tr1 %f %f \n", sc->transform.x, sc->transform.y);
		// printf("tr2 %f %f \n", sc->transform2.x, sc->transform2.y);

	}
	else
	{
		set_vect(&vdist, sprite->x - p->pos.x, sprite->y - p->pos.y);
		transform_vector(&(sc->transform), &vdist, p);
	}
}

/*
calculates start and end points for drawing,
height and width of the sprite
uncut x is needed to correctly determine the texture position
because sc->start.x is cut as it is used for drawing and
can't be less than 0
 */
void	set_draw(t_spritecast *sc)
{
	int	screen_x;

	screen_x = (int)((WIN_W / 2) * (1 + sc->transform.x / sc->transform.y));
	sc->h = abs((int)(WIN_H / sc->transform.y));
	sc->start.y = -sc->h / 2 + WIN_H / 2;
	if (sc->start.y < 0)
		sc->start.y = 0;
	sc->end.y = sc->h / 2 + WIN_H / 2;
	if (sc->end.y >= WIN_H)
		sc->end.y = WIN_H - 1;
	sc->w = abs((int)(WIN_H / sc->transform.y));
	sc->uncut_x = -sc->w / 2 + screen_x;
	sc->start.x = sc->uncut_x;
	if (sc->start.x < 0)
		sc->start.x = 0;
	sc->end.x = sc->w / 2 + screen_x;
	if (sc->end.x >= WIN_W)
		sc->end.x = WIN_W - 1;
}

/*
calculates
1. x on the screen where the door starts (left edge)
2. x on the screen where the door ends (right edge)
3. y range of the screen for those edges
4. width
 */
void	set_draw_door(t_spritecast *sc)
{
	double dtemp;

	sc->left_x = (int)((WIN_W / 2) * (1 + sc->transform.x / sc->transform.y));
	sc->right_x = (int)((WIN_W / 2) * (1 + sc->transform2.x / sc->transform2.y));
	sc->uncut_x = sc->left_x;
	if (sc->right_x < sc->left_x)
	{
		sc->uncut_x = sc->right_x;
		sc->right_x = sc->left_x;
		sc->left_x = sc->uncut_x;
		dtemp = sc->transform.x;
		sc->transform.x = sc->transform2.x;
		sc->transform2.x = dtemp;
		dtemp = sc->transform.y;
		sc->transform.y = sc->transform2.y;
		sc->transform2.y = dtemp;
	}
	sc->h = abs((int)(WIN_H / sc->transform.y));
	sc->h2 = abs((int)(WIN_H / sc->transform2.y));
	sc->up_left = -sc->h / 2 + WIN_H / 2;
	sc->lo_left = sc->h / 2 + WIN_H / 2;
	sc->up_right = -sc->h2 / 2 + WIN_H / 2;
	sc->lo_right = sc->h2 / 2 + WIN_H / 2;
	sc->w = sc->right_x - sc->left_x;
	// printf("lx %d \n", sc->left_x);
	// printf("rx %d \n", sc->right_x);
	// printf("t1 %f \n", sc->transform.y);
	// printf("t2 %f \n", sc->transform2.y);
	// printf("dy %f \n", data->p->dirv.y);

}

void	draw(t_cub3d *data, t_spritecast *sc, mlx_texture_t *tex)
{
	int		x;
	t_ivect	texpos;
	int		y;
	int		ind;

	x = sc->start.x;
	while (x < sc->end.x)
	{
		texpos.x = (int)((x - (sc->uncut_x)) * tex->width) / sc->w;
		if (sc->transform.y > 0 && x > 0 && x < WIN_W
			&& sc->transform.y < data->dist_arr[x])
		{
			y = sc->start.y;
			while (y < sc->end.y)
			{
				texpos.y = ((y - WIN_H / 2 + sc->h / 2) * tex->height) / sc->h;
				ind = (texpos.y * tex->width + texpos.x) * tex->bytes_per_pixel;
				if (readcol(&tex->pixels[ind]) != 0x000000FF)
					mlx_put_pixel(data->img, x, y, readcol(&tex->pixels[ind]));
				y++;
			}
		}
		x++;
	}
}

void	draw_door(t_cub3d *data, t_spritecast *sc, mlx_texture_t *tex, int i)
{
	int		x;
	t_ivect	texpos;
	int		y;
	int		ind;
	int	start_y;
	int	end_y;
	double diff;

	// printf("p %p \n", sc);
	// printf("p %p \n", tex);
	// printf("dx %f \n", data->p->dirv.x);
	// printf("dy %f \n", data->p->dirv.y);

//  || (data->dir_arr[x] != dir)

	x = sc->left_x;
	if (data->sprite[i].isopen == OPENING)
	{
		x += (mlx_get_time() - data->sprite[i].open_time) * sc->w;
		if (x >= sc->right_x)
			data->sprite[i].isopen = OPEN;
	}
	if (data->sprite[i].isopen == CLOSING)
	{
		x += sc->right_x - (mlx_get_time() - data->sprite[i].open_time) * sc->w;
		if (x <= sc->left_x)
			{
				x = sc->left_x;
				data->sprite[i].isopen = CLOSED;}
	}
	while (x < sc->right_x && x < WIN_W)
	{

		//printf("w %d \n", sc->w);
		diff = fabs(data->sprite[i].dist - pow(data->dist_arr[x], 2));
		texpos.x = (int)((x - (sc->uncut_x)) * tex->width) / sc->w;
		if (sc->transform.y > 0 && sc->transform2.y > 0 && x > 0 && x < WIN_W
			&& ((sc->transform.y < data->dist_arr[x]) || (data->dir_arr[x] != data->sprite[i].dir && diff < 5)))
		{
			start_y = sc->up_left + (sc->up_right - sc->up_left) * (x - sc->left_x)/ sc->w;
			if (start_y < 0)
				start_y = 0;
			end_y = sc->lo_left + (sc->lo_right - sc->lo_left) * (x - sc->left_x)/ sc->w;
			if (end_y >= WIN_H)
				end_y = WIN_H - 1;
			y = start_y;
			while (y < end_y)
			{
				//printf("while start 1 p\n");
				sc->h = end_y - start_y;
				texpos.y = ((y - WIN_H / 2 + sc->h / 2) * tex->height * 800) / (sc->h * 800);
				texpos.y = (int)texpos.y & (tex->height - 1);
				// printf("y %i \n", y);
				// printf("tex y %i \n", texpos.y);
				// printf("h %i \n", sc->h);
				// printf("h %i \n", tex->width);
				ind = (texpos.y * tex->width + texpos.x) * tex->bytes_per_pixel;
				//printf("tex y %i \n", sc->h);
				//printf("i %d \n", ind);
				mlx_put_pixel(data->img, x, y, readcol(&tex->pixels[ind]));
				y++;
				//printf("while end 1 \n");
			}
			//printf("draw end 1 p\n");
		}
		x++;

	}
}

void	put_sprites(t_cub3d *data)
{
	t_spritecast	sc;
	int				i;

	set_dist(data);
	bubble(data->sprite, data->n_total_sprites);
	i = 0;
	while (i < data->n_total_sprites)
	{
		if (data->sprite[i].c == 'H') // modifed by nico
			data->sprite[i].tex_i = H;
		else if (data->sprite[i].c == 'D') // modified by nico
			data->sprite[i].tex_i = D;
		transform(data->p, &sc, &data->sprite[i]);
		if (data->sprite[i].c != 'D')
		{
			set_draw(&sc);
			draw(data, &sc, data->tex[data->sprite[i].tex_i]);
		}
		else if (data->sprite[i].c == 'D' && data->sprite[i].isopen != OPEN)
		{
			set_draw_door(&sc);
			if (sc.left_x > -1.5 * WIN_W && sc.right_x < 2.5 * WIN_W)
				draw_door(data, &sc, data->tex[data->sprite[i].tex_i], i);
		}
		i++;
	}
}


// void put_sprites(t_cub3d *data, double dist_arr[WIN_W])
// {
// 	t_sprite sprite[2];
// 	t_sprite sorted_sprite[2];
// 	t_dvect vdist;
// 	t_dvect tf;
// 	t_ivect	start;
// 	t_ivect end;
// 	int h;
// 	int w;
// 	double det;
// 	int screen_x;
// 	int i;
// 	int stripe;
// 	mlx_texture_t *tex;
// 	t_ivect texpos;
// 	int y;
// 	int d;
// 	int ind;

// 	//for test 2 stripes will be used
// 	//for now sprite coordinates are set manually here
// 	sprite[0].x = 2;
// 	sprite[0].y = 2;
// 	sprite[1].x = 2;
// 	sprite[1].y = 5;
// 	sprite[0].dist = sprite_dist_sq(sprite[0], data->p->pos);
// 	sprite[1].dist = sprite_dist_sq(sprite[1], data->p->pos);
// 	//printf("dist: %f, %f \n", sprite[0].dist, sprite[1].dist);
// 	//manual sorting
// 	if (sprite[0].dist >= sprite[1].dist)
// 	{
// 		sorted_sprite[0] = sprite[0];
// 		sorted_sprite[1] = sprite[1];
// 	}
// 	else
// 	{
// 		sorted_sprite[0] = sprite[1];
// 		sorted_sprite[1] = sprite[0];
// 	}
// 	i = 0;
// 	printf("n: %f \n", data->sprite->x);
// 	// going through all sprites and drawing them
// 	while (i < data->n_s)
// 	{
// 		tex = data->tex[H];
// 		set_vect(&vdist, data->sprite[i].x - data->p->pos.x, data->sprite[i].y - data->p->pos.y);// relative distance
// 		det = 1.0/(data->p->plane.x * data->p->dirv.y - data->p->plane.y * data->p->dirv.x);
// 		tf.x = det * (vdist.x * data->p->dirv.y - vdist.y * data->p->dirv.x); //transformed position
// 		tf.y = det * (- data->p->plane.y * vdist.x + data->p->plane.x * vdist.y);
// 		//printf("rel: %f, %f \n", vdist.x, vdist.y);
// 		//printf("tf: %f, %f \n", tf.x, tf.y);
// 		screen_x = (int) ((WIN_W / 2) * (1 + tf.x/tf.y));//pixel x on the screen - middle?
// 		h = abs((int) (WIN_H / tf.y)); //height
// 		start.y = -h/2 + WIN_H/2;
// 		if (start.y < 0)
// 			start.y = 0;
// 		end.y = h/2 + WIN_H/2;
// 		if (end.y >= WIN_H)
// 			end.y = WIN_H - 1;
// 		w = abs((int) (WIN_H / tf.y));
// 		printf("w x: %d, %d \n", w, screen_x);
// 		start.x = -w/2 + screen_x;
// 		if (start.x < 0)
// 			start.x = 0;
// 		end.x = w/2 + screen_x;
// 		if (end.x >= WIN_W)
// 			end.x = WIN_W - 1;
// 		//printf("x interval: %d, %d \n", start.x, end.x);
// 		//printf("y interval: %d, %d \n", start.y, end.y);
// 		stripe = start.x;
// 		while (stripe < end.x)
// 		{
// 			//texpos.x = (int) (256 * (stripe - (-w/ 2 + screen_x)) *  tex->width / w) / 256;
// 			texpos.x = (int) ((stripe - (- w/ 2 + screen_x)) *  tex->width / w);
// 			if (tf.y > 0 && stripe > 0 && stripe < WIN_W && tf.y < dist_arr[stripe])
// 			{
// 				//printf("x interval: %d, %d \n", start.x, end.x);
// 				y = start.y;
// 				//printf("d arr: %d, %d \n", screen_x, y);
// 				while (y < end.y)
// 				{
// 					d = y * 256 - WIN_H * 128 + h * 128;
// 					texpos.y = (d * tex->height / h)/ 256;
// 					ind = (texpos.y * tex->width + texpos.x) * tex->bytes_per_pixel;
// 					if (readcol(&tex->pixels[ind]) != 0x00000000)
// 						mlx_put_pixel(data->img, stripe, y, readcol(&tex->pixels[ind]));
// 					y++;
// 				}
// 			}
// 			stripe++;
// 		}
// 		i++;
// 	}

// 	//printf("d arr: %f, %f \n", dist_arr[40], dist_arr[200]);
// }
