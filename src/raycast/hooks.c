/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrubina <mrubina@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/14 19:01:50 by mrubina           #+#    #+#             */
/*   Updated: 2024/02/12 00:18:44 by mrubina          ###   ########.fr       */
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

void	key_hook(mlx_key_data_t keydata, void *data)
{
	if (keydata.key == MLX_KEY_ESCAPE) {
		mlx_terminate(((t_cub3d *)data)->mlx);
		err_free_exit(NULL, data, 0);
	}
	if (keydata.key == MLX_KEY_A)
		move((t_cub3d *)data, 0.2, LEFT);
	if (keydata.key == MLX_KEY_D)
		move((t_cub3d *)data, 0.2, RIGHT);
	if (keydata.key == MLX_KEY_S)
		move((t_cub3d *)data, 0.2, BACK);
	if (keydata.key == MLX_KEY_W)
		move((t_cub3d *)data, 0.2, FORWARD);
	if (keydata.key == MLX_KEY_RIGHT)
		rotate_player(((t_cub3d *)data)->p, 0.05);
	if (keydata.key == MLX_KEY_LEFT)
		rotate_player(((t_cub3d *)data)->p, -0.05);
	if (BONUS && keydata.key == MLX_KEY_SPACE && keydata.action == MLX_PRESS)
		open_door((t_cub3d *)data);
	mlx_image_to_window(((t_cub3d *)data)->mlx, ((t_cub3d *)data)->img, 0, 0);
}



// void	mouse_hook(mlx_key_data_t keydata, int x, int y, void *param)
// {
// 	// t_cub3d	*data;

// 	// data = (t_cub3d *)param;
// 	// mlx_get_mouse_pos(data->mlx, data->mouseX, data->mouseY);
// 	// ft_printf("MOUSE [%d, %d]\n", data->mouseX, data->mouseY);
// }

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


// void refresh(void *data)
// {
// 	raycasting(((t_cub3d *)data));
// 	if (BONUS)
// 		minimap(data);
// 	if (((t_cub3d *)data)->n_total_sprites) // moved outside the if(BONUS) because otherwise barrels are not rendered
// 		put_sprites(data);
// }

void refresh(void *data)
{
	double time_dif;

	raycasting(((t_cub3d *)data));
	if (BONUS)
		minimap(data);
	if (((t_cub3d *)data)->n_total_sprites) // moved outside the if(BONUS) because otherwise barrels are not rendered
		put_sprites(data);
}
