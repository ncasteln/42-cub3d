/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d_old.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrubina <mrubina@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/14 19:01:50 by mrubina           #+#    #+#             */
/*   Updated: 2024/01/05 18:19:58 by mrubina          ###   ########.fr       */
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
	t_data	rcdata;
	rcdata.mlx = mlx_init(WIN_W, WIN_H, "cub3d", 0);
	rcdata.img = mlx_new_image(rcdata.mlx, WIN_W, WIN_H);
	//rcdata.mlx->delta_time = 1;
	init_data(&rcdata);
	//mlx_image_to_window(rcdata.mlx, rcdata.img, 0, 0);
	//teture test
	// mlx_texture_t* texture;
	// mlx_image_t *img = mlx_new_image(rcdata.mlx, 10, 10);
	//texture = mlx_load_png("src/colorstone.png");
	//texture->height = texture->height/2;
	//texture->width = texture->width/2;
	//img = mlx_texture_to_image(rcdata.mlx, texture);
	

	mlx_image_to_window(rcdata.mlx, rcdata.img, 0, 0);
	//rcdata.mlx->delta_time = 1;
	rayCasting(&rcdata);
	//rcdata.map = &map;
	//raycasting calculation for each pixel in the game window
	
	//vert_line(&rcdata, 100, 5, 600);
	//rcdata.sx = 0;
	//draw_square(&rcdata, 10, 10, 100, WHITE);
	//mlx_put_pixel(rcdata.img, 20, 20, 0xFF00FFFF);
	//draw_line(&rcdata, -2, 1100);
	//printf("%f, ", rcdata.mlx->delta_time);
	//vert_line(&rcdata, (&rcdata)->pixelX, 10, 300, RED);
	mlx_loop_hook(rcdata.mlx, refresh, &rcdata);
	mlx_key_hook(rcdata.mlx, key_hook, &rcdata);
	//mlx_mouse_hook(rcdata.mlx, mouse_hook, &rcdata);
	//mlx_loop_hook(rcdata.mlx, )
	mlx_loop(rcdata.mlx);
	mlx_terminate(rcdata.mlx);
	return (0);
}