/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrubina <mrubina@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/14 19:01:50 by mrubina           #+#    #+#             */
/*   Updated: 2024/01/05 20:31:39 by mrubina          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "cub3d.h"
//D
void move_r(t_cub3d *data)
{
	if (data->rcdata->dir_x = )
	data->rcdata->pos_y += 0.1;
}

void	key_hook(mlx_key_data_t keydata, void *data)
{
	if (keydata.key == MLX_KEY_ESCAPE)
		win_close(((t_cub3d *)data)->mlx);
	if (keydata.key == MLX_KEY_A)
		((t_cub3d *)data)->rcdata->pos_y -= 0.1;
	if (keydata.key == MLX_KEY_D)
		((t_cub3d *)data)->rcdata->pos_y += 0.1;
	if (keydata.key == MLX_KEY_S)
		((t_cub3d *)data)->rcdata->pos_x += 0.1;
	if (keydata.key == MLX_KEY_W)
		((t_cub3d *)data)->rcdata->pos_x -= 0.1;
	if (keydata.key == MLX_KEY_RIGHT)
		rotateP((t_cub3d *)data, -0.01);
	if (keydata.key == MLX_KEY_LEFT)
		rotateP((t_cub3d *)data, 0.01);
	mlx_image_to_window(((t_cub3d *)data)-> mlx, ((t_cub3d *)data)->img, 0, 0);
}
