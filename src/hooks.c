/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrubina <mrubina@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/14 19:01:50 by mrubina           #+#    #+#             */
/*   Updated: 2023/12/22 00:48:21 by mrubina          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../include/cub3d.h"

void	win_close(mlx_t* mlx)
{
	mlx_terminate(mlx);
	exit(0);
}

void	key_hook(mlx_key_data_t keydata, void *data)
{
	if (keydata.key == MLX_KEY_ESCAPE)
		win_close(((t_data *)data)->mlx);
	if (keydata.key == MLX_KEY_A)
		((t_data *)data)->posY -= 0.1;
	if (keydata.key == MLX_KEY_D)
		{
			//clearScreen(((t_data *)data));
			((t_data *)data)->posY += 0.1;
			//draw_square(((t_data *)data), 10, 10, 30, ORANGE);
			//rayCasting(((t_data *)data));
		//((t_data *)data)->sx++;
		//printf("%f, ", ((t_data *)data)->posX);
		}
	if (keydata.key == MLX_KEY_S)
		((t_data *)data)->posX += 0.1;
	if (keydata.key == MLX_KEY_W)
		((t_data *)data)->posX -= 0.1;
	mlx_image_to_window(((t_data *)data)->mlx, ((t_data *)data)->img, 0, 0);
}

void	mouse_hook(mlx_key_data_t keydata, int x, int y, void *param)
{
	if (keydata.key == MLX_MOUSE_BUTTON_LEFT)
		mlx_put_pixel(((t_data *)param)->img, x, y, 0xFF0000FF);
}

void renewSquare(void *data)
{
	//((t_data *)data)->img = mlx_new_image(((t_data *)data)->mlx, WIN_W, WIN_H);
	clearScreen(((t_data *)data));
	//vert_line((t_data *)data, ((t_data *)data)->x, 10, 300, RED);
	//printf("%f new frame ", ((t_data *)data)->posX);
	rayCasting(((t_data *)data));
	//mlx_image_to_window(((t_data *)data)->mlx, ((t_data *)data)->img, 0, 0);
	//draw_square(((t_data *)data), 10, 10, 30, WHITE);
}