/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrubina <mrubina@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/14 19:01:50 by mrubina           #+#    #+#             */
/*   Updated: 2024/01/04 15:13:02 by mrubina          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../include/cub3d.h"

void find_leaks()
{
	system("leaks cub3d");
}

//int	main(int argc, char *argv[])

void init_data(t_data *data)
{
	data->posX = 22;
	data->posY = 1.2;
	data->dirX = -1;
	data->dirY = 0;
	data->planeX = 0;
	data->planeY = 0.66;
	data->time = 0;
	data->oldTime = 0;
	data->hit = 0;
	data->h = 700;
	//set_map(data->map);
	// printf("%i ", data->map[0][0]);
	// printf("%i ", data->map[0][1]);
	// printf("%i ", data->map[1][0]);
	// printf("%i ", data->map[1][1]);
}

int	main()
{
	//atexit(find_leaks);
	t_data	data;
	data.mlx = mlx_init(WIN_W, WIN_H, "cub3d", 0);
	data.img = mlx_new_image(data.mlx, WIN_W, WIN_H);
	//data.mlx->delta_time = 1;
	init_data(&data);
	//mlx_image_to_window(data.mlx, data.img, 0, 0);
	//teture test
	// mlx_texture_t* texture;
	// mlx_image_t *img = mlx_new_image(data.mlx, 10, 10);
	//texture = mlx_load_png("src/colorstone.png");
	//texture->height = texture->height/2;
	//texture->width = texture->width/2;
	//img = mlx_texture_to_image(data.mlx, texture);
	

	mlx_image_to_window(data.mlx, data.img, 0, 0);
	//data.mlx->delta_time = 1;
	//rayCasting(&data);
	//data.map = &map;
	//raycasting calculation for each pixel in the game window
	
	//vert_line(&data, 100, 5, 600);
	//data.sx = 0;
	//draw_square(&data, 10, 10, 100, WHITE);
	//mlx_put_pixel(data.img, 20, 20, 0xFF00FFFF);
	//draw_line(&data, -2, 1100);
	//printf("%f, ", data.mlx->delta_time);
	//vert_line(&data, (&data)->pixelX, 10, 300, RED);
	mlx_loop_hook(data.mlx, refresh, &data);
	mlx_key_hook(data.mlx, key_hook, &data);
	//mlx_mouse_hook(data.mlx, mouse_hook, &data);
	//mlx_loop_hook(data.mlx, )
	mlx_loop(data.mlx);
	mlx_terminate(data.mlx);
	return (0);
}