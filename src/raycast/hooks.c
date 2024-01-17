/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrubina <mrubina@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/14 19:01:50 by mrubina           #+#    #+#             */
/*   Updated: 2024/01/17 20:52:30 by mrubina          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "cub3d.h"

void	win_close(mlx_t* mlx)
{
	mlx_terminate(mlx);
	exit(0);
}

void	key_hook(mlx_key_data_t keydata, void *data)
{
	if (keydata.key == MLX_KEY_ESCAPE)
		win_close(((t_cub3d *)data)->mlx);
	if (keydata.key == MLX_KEY_A)
		move((t_cub3d *)data, 0.5, LEFT);
	if (keydata.key == MLX_KEY_D)
		move((t_cub3d *)data, 0.5, RIGHT);
	if (keydata.key == MLX_KEY_S)
		move((t_cub3d *)data, 0.5, BACK);
	if (keydata.key == MLX_KEY_W)
		move((t_cub3d *)data, 0.5, FORWARD);
	if (keydata.key == MLX_KEY_RIGHT)
		rotateP(((t_cub3d *)data)->p, 0.1);
	if (keydata.key == MLX_KEY_LEFT)
		rotateP(((t_cub3d *)data)->p, -0.1);
	mlx_image_to_window(((t_cub3d *)data)->mlx, ((t_cub3d *)data)->img, 0, 0);
	//mlx_image_to_window(((t_cub3d *)data)->mlx, ((t_cub3d *)data)->img1, 0, 0);
}

void	mouse_hook(mlx_key_data_t keydata, int x, int y, void *param)
{
	if (keydata.key == MLX_MOUSE_BUTTON_LEFT)
		mlx_put_pixel(((t_cub3d *)param)->img, x, y, 0xFF0000FF);
}

void draw_square(t_cub3d *data, int xStart, int yStart, int side, int color)
{
	int x;
	int y;

	x = xStart;
	while (x < xStart + side)
	{
		y = yStart;
		while (y < yStart + side)
		{
			mlx_put_pixel(data->img1, x, y, color);
			y++;
		}
		x++;
	}
}

void refresh(void *data)
{
	clearScreen(((t_cub3d *)data));
	raycasting(((t_cub3d *)data));
}
