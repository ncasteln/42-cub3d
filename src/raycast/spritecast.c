/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   spritecast.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrubina <mrubina@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/14 19:01:50 by mrubina           #+#    #+#             */
/*   Updated: 2024/02/22 01:09:07 by mrubina          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/*
calculates transform coordinates of a vextor in space
multiplying it with the inverse transform matrix
 */
static void	transform_vector(t_dvect *new, t_dvect *old, t_player *p)
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
static void	transform(t_player *p, t_spritecast *sc, t_sprite *sprite)
{
	t_dvect	vdist;

	if (sprite->c == 'D')
	{
		vdist.x = sprite->door_left_edge.x - p->pos.x;
		vdist.y = sprite->door_left_edge.y - p->pos.y;
		transform_vector(&(sc->transf), &vdist, p);
		vdist.x = sprite->door_right_edge.x - p->pos.x;
		vdist.y = sprite->door_right_edge.y - p->pos.y;
		transform_vector(&(sc->transf2), &vdist, p);
	}
	else
	{
		set_vect(&vdist, sprite->x - p->pos.x, sprite->y - p->pos.y);
		transform_vector(&(sc->transf), &vdist, p);
	}
}

/*
calculates start and end points for drawing,
height and width of the sprite
ref_x (reference x) is needed to correctly determine the texture position
because sc->start.x is cut as it is used for drawing and
can't be less than 0
 */
static void	set_draw_sprite(t_spritecast *sc)
{
	int	screen_x;

	screen_x = (int)((WIN_W / 2) * (1 + sc->transf.x / sc->transf.y));
	sc->h = abs((int)(WIN_H / sc->transf.y));
	sc->start.y = -sc->h / 2 + WIN_H / 2;
	if (sc->start.y < 0)
		sc->start.y = 0;
	sc->end.y = sc->h / 2 + WIN_H / 2;
	if (sc->end.y >= WIN_H)
		sc->end.y = WIN_H - 1;
	sc->w = abs((int)(WIN_H / sc->transf.y));
	sc->ref_x = -sc->w / 2 + screen_x;
	sc->start.x = sc->ref_x;
	if (sc->start.x < 0)
		sc->start.x = 0;
	sc->end.x = sc->w / 2 + screen_x;
	if (sc->end.x >= WIN_W)
		sc->end.x = WIN_W - 1;
}

static void	draw_sprite(t_cub3d *data, t_spritecast *sc, mlx_texture_t *tex)
{
	int		x;
	t_ivect	texpos;
	int		y;
	int		ind;

	x = sc->start.x;
	while (x < sc->end.x)
	{
		texpos.x = (int)((x - (sc->ref_x)) * tex->width) / sc->w;
		if (sc->transf.y > 0 && x > 0 && x < WIN_W
			&& sc->transf.y < data->dist_arr[x])
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

void	put_sprites(t_cub3d *data)
{
	t_spritecast	sc;
	int				i;

	set_dist(data);
	bubble(data->sprite, data->n_total_sprites);
	i = 0;
	while (i < data->n_total_sprites)
	{
		transform(data->p, &sc, &data->sprite[i]);
		if (data->sprite[i].c == 'H')
		{
			set_draw_sprite(&sc);
			draw_sprite(data, &sc, data->tex[data->sprite[i].tex_i]);
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
