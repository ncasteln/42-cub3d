/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   spritecast.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrubina <mrubina@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/14 19:01:50 by mrubina           #+#    #+#             */
/*   Updated: 2024/02/20 13:34:37 by mrubina          ###   ########.fr       */
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
