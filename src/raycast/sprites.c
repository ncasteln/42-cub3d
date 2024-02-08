/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprites.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrubina <mrubina@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/24 14:30:48 by ncasteln          #+#    #+#             */
/*   Updated: 2024/02/08 23:07:32 by mrubina          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/* sets some door parameters 
	position of the door left and right edges
	as seen when the player stands facing the door
	direction // sides the door is facing
	sets the door as closed
*/
void set_door(int n, int y, int x, t_cub3d *data)
{
	 //printf("int xy %d %d \n", x, y);
	if (data->map[y][x - 1] == '1' && data->map[y][x + 1] == '1')
	{
		// printf("door start before %f %f \n", data->sprite[n].door_left_edge.x, data->sprite[n].door_left_edge.y);
		// printf("door end before %f %f \n", data->sprite[n].door_right_edge.x, data->sprite[n].door_right_edge.y);
		data->sprite[n].door_left_edge.x = x; //6 +
		data->sprite[n].door_right_edge.x = x + 0.999; //6.99
		data->sprite[n].door_left_edge.y = y + 0.5;  //2.5
		data->sprite[n].door_right_edge.y = y + 0.5;
		data->sprite[n].dir = NORTH_SOUTH;
	}
	else if (data->map[y - 1][x] == '1' && data->map[y + 1][x] == '1')
	{
		data->sprite[n].door_left_edge.y = y;
		data->sprite[n].door_right_edge.y = y + 0.999;
		data->sprite[n].door_left_edge.x = x + 0.5;
		data->sprite[n].door_right_edge.x = x + 0.5;
		data->sprite[n].dir = WEST_EAST;
	}
	data->sprite[n].isopen = CLOSED;
	// printf("st %f %f \n", data->sprite[n].door_left_edge.x, data->sprite[n].door_left_edge.y);
	// printf("end %f %f \n", data->sprite[n].door_right_edge.x, data->sprite[n].door_right_edge.y);
}


void	set_sprite(int n, int y, int x, t_cub3d *data)
{
	data->sprite[n].c = data->map[y][x];
	data->sprite[n].y = y;
	data->sprite[n].x = x;
	data->sprite[n].dist = -1;
	if (data->sprite[n].c == 'D')
		set_door(n, y, x, data);
	// data->sprite[n].dist = rand(); // remove, addedto test the bubblesort
}

/* sets squared distance
from the sprite to the current position of the player */
static void	set_dist(t_cub3d *data)
{
	int	n;
	n = 0;
	while (n < data->n_total_sprites)
	{
		data->sprite[n].dist = sprite_dist_sq(data->sprite[n], data->p->pos);
		n++;
	}
}

//creates sprites at the start
void	create_sprite_list(t_cub3d *data)
{
	int	y;
	int	x;
	int	n;

	y = 0;
	n = 0;
	while (data->map[y])
	{
		x = 0;
		while (data->map[y][x])
		{
			if (data->map[y][x] == 'H' || data->map[y][x] == '$' || data->map[y][x] == 'D')
			{
				set_sprite(n, y, x, data);
				n++;
			}
			x++;
		}
		y++;
	}
}

static void	bubble(t_sprite *sprite, int n)
{
	t_sprite	temp;
	int			swapped;
	int			i;

	swapped = 1;
	while (swapped)
	{
		swapped = 0;
		i = 1;
		while (i <= n - 1)
		{
			if (sprite[i - 1].dist < sprite[i].dist)
			{
				temp = sprite[i - 1];
				sprite[i - 1] = sprite[i];
				sprite[i] = temp;
				swapped = 1;
			}
			i++;
		}
	}
}

/*
	Holes and are considered SPRITES! So in an case the function runs, and it'll
	add eventually other BONUS sprites (included doors) in case the bonus
	version of the program is compiled.

	) Create sprite list
	) Calculate the dist of each sprite
	) Sort by distance
	) Projection of the sprite (2x2 matrix)
	) Calculate the size on the screen
	) Draws
*/

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
calculates start and end points for drawing
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

void	set_draw_door(t_spritecast *sc)
{
	int	screen_x1;
	int	screen_x2;
	int temp;
	double dtemp;
	screen_x1 = (int)((WIN_W / 2) * (1 + sc->transform.x / sc->transform.y));
	temp = (int)((WIN_W / 2) * (1 + sc->transform2.x / sc->transform2.y));
	if (temp < screen_x1)
	{
		screen_x1 = temp;
		dtemp = sc->transform.x;
		sc->transform.x = sc->transform2.x;
		sc->transform2.x = dtemp;
		dtemp = sc->transform.y;
		sc->transform.y = sc->transform2.y;
		sc->transform2.y = dtemp;
	}
	screen_x2 = (int)((WIN_W / 2) * (1 + sc->transform2.x / sc->transform2.y));
	sc->h = abs((int)(WIN_H / sc->transform.y));
	sc->h2 = abs((int)(WIN_H / sc->transform2.y));
	sc->up_left = -sc->h / 2 + WIN_H / 2;
	sc->lo_left = sc->h / 2 + WIN_H / 2;
	sc->up_right = -sc->h2 / 2 + WIN_H / 2;
	sc->lo_right = sc->h2 / 2 + WIN_H / 2;
	if (sc->transform.y != 0)
		sc->w = abs((int)(WIN_H / sc->transform.y));
	sc->uncut_x = screen_x1; //seems to be right!!!!
	sc->left_x = sc->uncut_x;
	if (sc->transform2.y != 0)
		sc->w2 = abs((int)(WIN_H / sc->transform2.y));
	sc->right_x = screen_x2; //?
	sc->w = sc->right_x - sc->left_x;

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

//  || (data->dir_arr[x] != dir)
	x = sc->left_x;
	while (x < sc->right_x)
	{
		//printf("w %d \n", sc->w);
		diff = fabs(data->sprite[i].dist - pow(data->dist_arr[x], 2));
		texpos.x = (int)((x - (sc->uncut_x)) * tex->width) / sc->w;
		if (sc->transform.y > 0 && x > 0 && x < WIN_W
			&& ((sc->transform.y < data->dist_arr[x]) || (data->dir_arr[x] != data->sprite[i].dir && diff < 5)))
		{
			//diff = fabs(data->sprite[i].dist - pow(data->dist_arr[x], 2));
			// if (diff < 5)
			// {printf("i %i \n", i);
			// printf("i %f \n", data->sprite[i].dist);
			// printf("diff %f \n", diff);}
			start_y = sc->up_left + (sc->up_right - sc->up_left) * (x - sc->left_x)/ sc->w;
			if (start_y < 0)
				start_y = 0;
			end_y = sc->lo_left + (sc->lo_right - sc->lo_left) * (x - sc->left_x)/ sc->w;
			if (end_y >= WIN_H)
				end_y = WIN_H - 1;
			y = start_y;
			while (y < end_y)
			{
				sc->h = end_y - start_y;
				texpos.y = ((y - WIN_H / 2 + sc->h / 2) * tex->height) / sc->h;
				ind = (texpos.y * tex->width + texpos.x) * tex->bytes_per_pixel;
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
		if (data->sprite[i].c == 'H') // modifed by nico
			data->sprite[i].tex_i = H;
		else if (data->sprite[i].c == 'D')
			data->sprite[i].tex_i = D;
		else if (data->sprite[i].c == '$')
			data->sprite[i].tex_i = S;
		transform(data->p, &sc, &data->sprite[i]);
		if (data->sprite[i].c != 'D')
		{
			set_draw(&sc);
			draw(data, &sc, data->tex[data->sprite[i].tex_i]);
		}
		else if (data->sprite[i].c == 'D' && data->sprite[i].isopen == CLOSED)
		{
			set_draw_door(&sc);
			draw_door(data, &sc, data->tex[data->sprite[i].tex_i], i);
		}
		i++;
	}
}
