/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_minimap.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncasteln <ncasteln@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/17 10:17:42 by ncasteln          #+#    #+#             */
/*   Updated: 2024/02/08 12:13:33 by ncasteln         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	draw_player(t_cub3d *data)
{
	int y = 0;
	int x = 0;

	while (y < 5)
	{
		x = 0;
		while (x < 5)
		{
			int drawAtX = (data->p->pos.x) * MAP_PIXEL + x;
			int drawAtY = (data->p->pos.y) * MAP_PIXEL + y;
			if (data->p->x <= drawAtX && data->p->y <= drawAtY)
				mlx_put_pixel(data->minimap, drawAtX, drawAtY, 0x000000FF);
			x++;
		}
		y++;
	}
}

/*
	@param startX = (cellX + 2) * MAP_PIXEL, +2 is an offset to give the
	minimap a margin from the edge of the window.
*/
static void	draw_tile(t_cub3d *data, char c, int cellY, int cellX)
{
	int	startX;
	int	startY;
	int	endX;
	int	endY;

	startX = cellX * MAP_PIXEL;
	startY = cellY * MAP_PIXEL;
	endX = startX + MAP_PIXEL;
	endY = startY + MAP_PIXEL;
	while (startY < endY)
	{
		startX = (cellX) * MAP_PIXEL;
		while (startX < endX)
		{
			if (c == '1')
				mlx_put_pixel(data->minimap, startX, startY, BLUE);
			else if (c == ' ')
				mlx_put_pixel(data->minimap, startX, startY, BLACK);
			else if (c == 'H')
				mlx_put_pixel(data->minimap, startX, startY, RED);
			else if (c == 'D')
				mlx_put_pixel(data->minimap, startX, startY, ORANGE);
			else
				mlx_put_pixel(data->minimap, startX, startY, WHITE);
			startX++;
		}
		startY++;
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
	// fix another size if too big
	if (data->minimap)
		mlx_delete_image(data->mlx, data->minimap);
	data->minimap = mlx_new_image(data->mlx, data->n_col * MAP_PIXEL, data->n_rows * MAP_PIXEL);
	draw_minimap(data);
	draw_player(data);
	mlx_image_to_window(data->mlx, data->minimap, 20, 20);
}
