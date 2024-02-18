/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncasteln <ncasteln@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/14 19:01:50 by mrubina           #+#    #+#             */
/*   Updated: 2024/02/15 15:57:39 by ncasteln         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int facing_door(t_cub3d *data, int i)
{
	double delta;

	if (data->sprite[i].dir == NORTH_SOUTH)
	{
		delta = data->sprite[i].y - data->p->pos.y;
		return (sign(data->p->dirv.y) == sign(delta)
			&& fabs(data->p->dirv.x) < 0.77);
	}
	else
	{
		delta = data->sprite[i].x - data->p->pos.x;
		return (fabs(data->p->dirv.y) < 0.77
			&& sign(data->p->dirv.x) == sign(delta));
	}
}

static void open_door(t_cub3d *data)
{
	int i;
	i = 0;
	while (i < data->n_total_sprites)
	{
		if (data->sprite[i].c == 'D'
		&& sprite_dist_sq(data->sprite[i], data->p->pos) <= 5
		&& facing_door(data, i))
		{
			if (data->sprite[i].isopen == OPEN
			&& ((data->sprite[i].x != data->p->x)
			|| (data->sprite[i].y != data->p->y)))
			{
				data->sprite[i].isopen = CLOSING;
				data->sprite[i].open_time = mlx_get_time();
			}
			else if (data->sprite[i].isopen == CLOSED)
			{
				data->sprite[i].isopen = OPENING;
				data->sprite[i].open_time = mlx_get_time();
			}
		}
		i++;
	}
}

void	key_hook(mlx_key_data_t keydata, void *param)
{
	t_cub3d	*data;

	data = (t_cub3d *)param;
	if (keydata.key == MLX_KEY_ESCAPE)
		err_free_exit(NULL, data, 1, EXIT_SUCCESS);
	if (keydata.action == MLX_PRESS || keydata.action == MLX_REPEAT)
	{
		if (keydata.key == MLX_KEY_A)
			move(data, 0.2, LEFT);
		if (keydata.key == MLX_KEY_D)
			move(data, 0.2, RIGHT);
		if (keydata.key == MLX_KEY_S)
			move(data, 0.2, BACK);
		if (keydata.key == MLX_KEY_W)
			move(data, 0.2, FORWARD);
		if (keydata.key == MLX_KEY_RIGHT)
			rotate_player((data)->p, 0.1);
		if (keydata.key == MLX_KEY_LEFT)
			rotate_player((data)->p, -0.1);
		if (BONUS && keydata.key == MLX_KEY_SPACE)
			open_door(data);
	}
	if (mlx_image_to_window((data)->mlx, (data)->img, 0, 0) == -1)
		err_free_exit("key_hook()", data, 1, E_MLX);
}

// trainign function
// void draw_square(t_cub3d *data, int xStart, int yStart, int side, int color)
// {
// 	int x;
// 	int y;

// 	x = xStart;
// 	while (x < xStart + side)
// 	{
// 		y = yStart;
// 		while (y < yStart + side)
// 		{
// 			mlx_put_pixel(data->img1, x, y, color);
// 			y++;
// 		}
// 		x++;
// 	}
// }

void refresh(void *param)
{
	double	time_dif;
	t_cub3d	*data;

	data = (t_cub3d *)param;
	raycasting((data));
	if (BONUS)
		minimap(data);
	if ((data)->n_total_sprites)
		put_sprites(data);
}
