/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_minimap_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncasteln <ncasteln@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/17 10:17:42 by ncasteln          #+#    #+#             */
/*   Updated: 2024/01/17 14:02:21 by ncasteln         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	clear_map_tile(t_cub3d *data, char c, int cellY, int cellX)
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
			mlx_put_pixel(data->img, startX, startY, 0x00000000);
			startX++;
		}
		startY++;
	}
}

void clear_minimap(t_cub3d *data)
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
			clear_map_tile(data, data->map[y][x], y, x);
			x++;
		}
		y++;
	}
}

static void	draw_map_tile(t_cub3d *data, char c, int cellY, int cellX)
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
			if (c == '1')
				mlx_put_pixel(data->img, startX, startY, 0xF5F0F0FF);
			else if (c == '0')
				mlx_put_pixel(data->img, startX, startY, 0x74ba56FF);
			else if (c == ' ')
				mlx_put_pixel(data->img, startX, startY, 0x2ab567FF);
			else
				mlx_put_pixel(data->img, startX, startY, 0x000000FF);
			startX++;
		}
		startY++;
	}
}

void	draw_minimap(t_cub3d *data)
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
			draw_map_tile(data, data->map[y][x], y, x);
			x++;
		}
		y++;
	}
}
