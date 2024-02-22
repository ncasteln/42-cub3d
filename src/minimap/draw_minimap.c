/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_minimap.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrubina <mrubina@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/17 10:17:42 by ncasteln          #+#    #+#             */
/*   Updated: 2024/02/21 23:11:38 by mrubina          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	draw_player(t_cub3d *data)
{
	int	x;
	int	y;
	int	draw_x;
	int	draw_y;

	y = 0;
	while (y < 5)
	{
		x = 0;
		while (x < 5)
		{
			draw_x = (data->p->pos.x) * data->minimap_pixel + x;
			draw_y = (data->p->pos.y) * data->minimap_pixel + y;
			if (data->p->x <= draw_x && data->p->y <= draw_y)
				mlx_put_pixel(data->minimap, draw_x, draw_y, 0x000000FF);
			x++;
		}
		y++;
	}
}

static void	put_map_pixels(mlx_image_t *map, int start_x, int start_y, char c)
{
	if (c == '1')
		mlx_put_pixel(map, start_x, start_y, BLUE);
	else if (c == ' ')
		mlx_put_pixel(map, start_x, start_y, BLACK);
	else if (c == 'H')
		mlx_put_pixel(map, start_x, start_y, RED);
	else if (c == 'D')
		mlx_put_pixel(map, start_x, start_y, ORANGE);
	else
		mlx_put_pixel(map, start_x, start_y, WHITE);
}

/*
	@param start_x = (cellX + 2) * data->minimap_pixel, +2 is an offset to give the
	minimap a margin from the edge of the window.
*/
static void	draw_tile(t_cub3d *data, char c, int cellY, int cellX)
{
	int	start_x;
	int	start_y;
	int	end_x;
	int	end_y;

	start_x = cellX * data->minimap_pixel;
	start_y = cellY * data->minimap_pixel;
	end_x = start_x + data->minimap_pixel;
	end_y = start_y + data->minimap_pixel;
	while (start_y < end_y)
	{
		start_x = (cellX) * data->minimap_pixel;
		while (start_x < end_x)
		{
			put_map_pixels(data->minimap, start_x, start_y, c);
			start_x++;
		}
		start_y++;
	}
}

static void	draw_minimap(t_cub3d *data)
{
	uint32_t	y;
	uint32_t	x;

	y = 0;
	while (data->map[y])
	{
		x = 0;
		while (data->map[y][x])
		{
			draw_tile(data, data->map[y][x], y, x);
			x++;
		}
		y++;
	}
}

void	minimap(t_cub3d *data)
{
	uint32_t	width;
	uint32_t	height;

	width = data->n_col * data->minimap_pixel;
	height = data->n_rows * data->minimap_pixel;
	if (data->minimap)
		mlx_delete_image(data->mlx, data->minimap);
	data->minimap = mlx_new_image(data->mlx, width, height);
	if (!data->minimap)
		err_free_exit("minimap()", data, 1, E_MLX);
	draw_minimap(data);
	draw_player(data);
	if (mlx_image_to_window(data->mlx, data->minimap, 20, 20) == -1)
		err_free_exit("minimap()", data, 1, E_MLX);
}
