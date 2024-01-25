/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrubina <mrubina@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/14 19:01:50 by mrubina           #+#    #+#             */
/*   Updated: 2024/01/25 15:17:59 by mrubina          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "cub3d.h"

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
		rotate_player(((t_cub3d *)data)->p, 0.2);
	if (keydata.key == MLX_KEY_LEFT)
		rotate_player(((t_cub3d *)data)->p, -0.2);
	mlx_image_to_window(((t_cub3d *)data)->mlx, ((t_cub3d *)data)->img, 0, 0);
}

void	mouse_hook(mlx_key_data_t keydata, int x, int y, void *param)
{
	// t_cub3d	*data;

	// data = (t_cub3d *)param;
	// mlx_get_mouse_pos(data->mlx, data->mouseX, data->mouseY);
	// ft_printf("MOUSE [%d, %d]\n", data->mouseX, data->mouseY);
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

void refresh(void *data)
{
	raycasting(((t_cub3d *)data));
	if (BONUS)
	{
		minimap(data);
		// refresh sprites?
	}
}
