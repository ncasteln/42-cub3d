/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrubina <mrubina@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/14 19:01:50 by mrubina           #+#    #+#             */
/*   Updated: 2024/01/10 15:21:32 by mrubina          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "cub3d.h"
//D
// void move_r(t_cub3d *data)
// {
// 	if (data->rcdata->dir_x = )
// 	data->rcdata->pos_y += 0.1;
// }
//
void move_f(t_cub3d *data, double move)
{
	double abs_cos;
	double abs_sin;
	double tan;
	tan = data->rcdata->dir_y / data->rcdata->dir_x;
	abs_cos = sqrtf(1/(powf(tan, 2) + 1));
	abs_sin =  sqrtf(1 - powf(abs_cos, 2));

	if (data->rcdata->dir_x > 0)
		data->rcdata->pos_x += move * abs_cos;
	else
		data->rcdata->pos_x += move * -abs_cos;
	if (data->rcdata->dir_y > 0)
		data->rcdata->pos_y += move * abs_sin;
	else
		data->rcdata->pos_y += move * -abs_sin;
// 	 printf("dir: %f, %f \n", data->rcdata->dir_x, data->rcdata->dir_y);
// 	 printf("stop: %f, %f \n", data->rcdata->pos_x, data->rcdata->pos_y);
}

void move_b(t_cub3d *data, double move)
{
	double abs_cos;
	double abs_sin;
	double tan;
	tan = data->rcdata->dir_y / data->rcdata->dir_x;
	abs_cos = sqrtf(1/(powf(tan, 2) + 1));
	abs_sin =  sqrtf(1 - powf(abs_cos, 2));

	if (data->rcdata->dir_x > 0)
		data->rcdata->pos_x -= move * abs_cos;
	else
		data->rcdata->pos_x -= move * -abs_cos;
	if (data->rcdata->dir_y > 0)
		data->rcdata->pos_y -= move * abs_sin;
	else
		data->rcdata->pos_y -= move * -abs_sin;
}

// void	key_hook(mlx_key_data_t keydata, void *data)
// {
// 	if (keydata.key == MLX_KEY_ESCAPE)
// 		win_close(((t_cub3d *)data)->mlx);
// 	if (keydata.key == MLX_KEY_A)
// 		((t_cub3d *)data)->rcdata->pos_y -= 0.1;
// 	if (keydata.key == MLX_KEY_D)
// 		((t_cub3d *)data)->rcdata->pos_y += 0.1;
// 	if (keydata.key == MLX_KEY_S)
// 		((t_cub3d *)data)->rcdata->pos_x += 0.1;
// 	if (keydata.key == MLX_KEY_W)
// 		((t_cub3d *)data)->rcdata->pos_x -= 0.1;
// 	if (keydata.key == MLX_KEY_RIGHT)
// 		rotateP((t_cub3d *)data, -0.01);
// 	if (keydata.key == MLX_KEY_LEFT)
// 		rotateP((t_cub3d *)data, 0.01);
// 	mlx_image_to_window(((t_cub3d *)data)-> mlx, ((t_cub3d *)data)->img, 0, 0);
// }
