/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrubina <mrubina@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/14 19:01:50 by mrubina           #+#    #+#             */
/*   Updated: 2023/12/18 20:13:04 by mrubina          ###   ########.fr       */
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
}

void	mouse_hook(mlx_key_data_t keydata, int x, int y, void *param)
{
	if (keydata.key == MLX_MOUSE_BUTTON_LEFT)
		mlx_put_pixel(((t_data *)param)->img, x, y, 0xFF0000FF);
}