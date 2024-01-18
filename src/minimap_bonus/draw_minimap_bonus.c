/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_minimap_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncasteln <ncasteln@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/17 10:17:42 by ncasteln          #+#    #+#             */
/*   Updated: 2024/01/18 08:37:00 by ncasteln         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	minimap_clear_tile(t_cub3d *data, int cellY, int cellX)
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
		startX = cellX * MAP_PIXEL;
		while (startX < endX)
		{
			// mlx_put_pixel(data->img, startX, startY, 0x00000000);
			startX++;
		}
		startY++;
	}
}

void minimap_clear(t_cub3d *data)
{
	int	y;
	int	x;
	int	startY;
	int	startX;

	y = 0;
	startY = 0;
	startX = 0;
	while (data->map[y])
	{
		x = 0;
		while (data->map[y][x])
		{
			minimap_clear_tile(data, y, x);
			x++;
		}
		y++;
	}
}

void	minimap_draw_player(t_cub3d *data)
{
	int y = 0;
	int x = 0;

	while (y < 5)
	{
		x = 0;
		while (x < 5)
		{
			int drawAtX = (data->mv->pos.x + 2) * MAP_PIXEL + x;
			int drawAtY = (data->mv->pos.y + 2) * MAP_PIXEL + y;
			if (data->mv->map.y <= drawAtX && data->mv->map.y <= drawAtY)
				mlx_put_pixel(data->img, drawAtX, drawAtY, 0x000000FF);
			x++;
		}
		y++;
	}
}

/*
	@param startX = (cellX + 2) * MAP_PIXEL, +2 is an offset to give the
	minimap a margin from the edge of the window.
*/
static void	minimap_draw_tile(t_cub3d *data, char c, int cellY, int cellX)
{
	int	startX;
	int	startY;
	int	endX;
	int	endY;

	startX = (cellX + 2) * MAP_PIXEL;
	startY = (cellY + 2) * MAP_PIXEL;
	endX = startX + MAP_PIXEL;
	endY = startY + MAP_PIXEL;
	while (startY < endY)
	{
		startX = (cellX + 2) * MAP_PIXEL;
		while (startX < endX)
		{
			if (c == '1')
				mlx_put_pixel(data->img, startX, startY, 0xF5F0F0FF);
			else if (c == ' ')
				mlx_put_pixel(data->img, startX, startY, 0x2ab567FF);
			else if (c == 'D')
				mlx_put_pixel(data->img, startX, startY, 0x000000FF);
			else
				mlx_put_pixel(data->img, startX, startY, 0x74ba56FF);
			startX++;
		}
		startY++;
	}
}

void	minimap_draw_ambient(t_cub3d *data)
{
	int	y;
	int	x;

	y = 0;
	while (data->map[y])
	{
		x = 0;
		while (data->map[y][x])
		{
			minimap_draw_tile(data, data->map[y][x], y, x);
			x++;
		}
		y++;
	}
}
