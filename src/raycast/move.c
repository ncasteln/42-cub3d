/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrubina <mrubina@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/14 19:01:50 by mrubina           #+#    #+#             */
/*   Updated: 2024/01/10 17:08:09 by mrubina          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "cub3d.h"


/*
player moves forward - along the look direction
 */
void move(t_cub3d *data, double move, int dir)
{
	double abs_cos;
	double abs_sin;
	double tan;
	double delta_x;
	double delta_y;

	tan = data->rcdata->dir_y / data->rcdata->dir_x;
	abs_cos = sqrtf(1/(powf(tan, 2) + 1));
	abs_sin = sqrtf(1 - powf(abs_cos, 2));
	delta_x = move * sign(data->rcdata->dir_x) * abs_cos;
	delta_y = move * sign(data->rcdata->dir_y) * abs_sin;
	if (dir == BACK)
	{
		delta_x *= -1;
		delta_y *= -1;
	}
	if (check_space(data, delta_x, delta_y) == true)
	{
		data->rcdata->pos_x += delta_x;
		data->rcdata->pos_y += delta_y;
	}
	//  printf("dir: %f, %f \n", data->rcdata->dir_x, data->rcdata->dir_y);
	//  printf("stop: %f, %f \n", data->rcdata->pos_x, data->rcdata->pos_y);
}

//checks if the movement is possible and the player doesn't go through walls
int check_space(t_cub3d *data, double delta_x, double delta_y)
{
	int x;
	int y;

	x = (int)(data->rcdata->pos_x + delta_x);
	y = (int)(data->rcdata->pos_y + delta_y);
	if (data->map[y][x] != '1')
		return (true);
	else
		return (false);
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
