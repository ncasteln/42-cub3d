/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_door.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrubina <mrubina@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/14 19:01:50 by mrubina           #+#    #+#             */
/*   Updated: 2024/02/21 00:12:47 by mrubina          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/*
calculates
1. x on the screen where the door starts (left edge)
2. x on the screen where the door ends (right edge)
3. y range of the screen for those edges
4. width
 */
void	set_draw_door(t_spritecast *sc)
{
	double	dtemp;
	int		h2;

	sc->left_x = (int)((WIN_W / 2) * (1 + sc->transf.x / sc->transf.y));
	sc->right_x = (int)((WIN_W / 2) * (1 + sc->transf2.x / sc->transf2.y));
	sc->uncut_x = sc->left_x;
	if (sc->right_x < sc->left_x)
	{
		sc->uncut_x = sc->right_x;
		sc->right_x = sc->left_x;
		sc->left_x = sc->uncut_x;
		dtemp = sc->transf.x;
		sc->transf.x = sc->transf2.x;
		sc->transf2.x = dtemp;
		dtemp = sc->transf.y;
		sc->transf.y = sc->transf2.y;
		sc->transf2.y = dtemp;
	}
	sc->h = abs((int)(WIN_H / sc->transf.y));
	h2 = abs((int)(WIN_H / sc->transf2.y));
	sc->up_left = -sc->h / 2 + WIN_H / 2;
	sc->lo_left = sc->h / 2 + WIN_H / 2;
	sc->up_right = -h2 / 2 + WIN_H / 2;
	sc->lo_right = h2 / 2 + WIN_H / 2;
	sc->w = sc->right_x - sc->left_x;
}

/*
We handle opening and closing of the doors
starting screen x changes with time
 */
static int	get_start_x(t_cub3d *data, t_spritecast *sc, int i)
{
	int	x;

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
			data->sprite[i].isopen = CLOSED;
		}
	}
	return (x);
}

// Before drawing a vertical line for each x we calculate start and end y
static int	set_y(t_spritecast *sc, int x, int *end_y)
{
	int	start_y;

	start_y = sc->up_left + (sc->up_right - sc->up_left)
		* (x - sc->left_x) / sc->w;
	if (start_y < 0)
		start_y = 0;
	*end_y = sc->lo_left + (sc->lo_right - sc->lo_left)
		* (x - sc->left_x) / sc->w;
	if (*end_y >= WIN_H)
		*end_y = WIN_H - 1;
	sc->h = *end_y - start_y;
	return (start_y);
}

/*
checking if this vertical line of the door is visible
 */
static int	is_visible(t_cub3d *data, t_spritecast *sc, int i, int x)
{
	double	diff;

	diff = fabs(data->sprite[i].dist - pow(data->dist_arr[x], 2));
	if (sc->transf.y > 0 && sc->transf2.y > 0 && x > 0 && x < WIN_W
		&& ((sc->transf.y < data->dist_arr[x]
				&& sc->transf2.y < data->dist_arr[x])
			|| (data->dir_arr[x] != data->sprite[i].dir && diff < 5)))
		return (true);
	else
		return (false);
}

/*
1. We set the starting x
2. We start scanning through x and draw if the door is visible
3. Before drawing a vertical line for each x we calculate start and end y
4. We draw the line based on the texture
 */
void	draw_door(t_cub3d *data, t_spritecast *sc, mlx_texture_t *tex, int i)
{
	int		x;
	t_ivect	texpos;
	int		y;
	int		ind;
	int		end_y;

	x = get_start_x(data, sc, i);
	while (x < sc->right_x && x < WIN_W)
	{
		texpos.x = (int)((x - (sc->uncut_x)) * tex->width) / sc->w;
		if (is_visible(data, sc, i, x))
		{
			y = set_y(sc, x, &end_y);
			while (y < end_y)
			{
				texpos.y = ((y - WIN_H / 2 + sc->h / 2) * tex->height * 800)
					/ (sc->h * 800);
				texpos.y = (int)texpos.y & (tex->height - 1);
				ind = (texpos.y * tex->width + texpos.x) * tex->bytes_per_pixel;
				mlx_put_pixel(data->img, x, y, readcol(&tex->pixels[ind]));
				y++;
			}
		}
		x++;
	}
}
