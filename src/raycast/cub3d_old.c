/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d_old.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrubina <mrubina@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/14 19:01:50 by mrubina           #+#    #+#             */
/*   Updated: 2024/01/11 00:26:38 by mrubina          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../include/cub3d.h"

void find_leaks()
{
	system("leaks cub3d");
}

//int	main(int argc, char *argv[])

void init_rc(t_rc *data)
{
	data->pos_x = 22;
	data->pos_y = 1.2;
	data->dir_x = -1;
	data->dir_y = 0;
	data->plane_x = 0;
	data->plane_y = 0.66;
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
	t_rc	rc;
	rc.mlx = mlx_init(WIN_W, WIN_H, "cub3d", 0);
	rc.img = mlx_new_image(rc.mlx, WIN_W, WIN_H);
	//rc.mlx->delta_time = 1;
	init_rc(&rc);
	//mlx_image_to_window(rc.mlx, rc.img, 0, 0);
	//teture test
	// mlx_texture_t* texture;
	// mlx_image_t *img = mlx_new_image(rc.mlx, 10, 10);
	//texture = mlx_load_png("src/colorstone.png");
	//texture->height = texture->height/2;
	//texture->width = texture->width/2;
	//img = mlx_texture_to_image(rc.mlx, texture);
	

	mlx_image_to_window(rc.mlx, rc.img, 0, 0);
	//rc.mlx->delta_time = 1;
	raycasting(&rc);
	//rc.map = &map;
	//raycasting calculation for each pixel in the game window
	
	//vert_line(&rc, 100, 5, 600);
	//rc.sx = 0;
	//draw_square(&rc, 10, 10, 100, WHITE);
	//mlx_put_pixel(rc.img, 20, 20, 0xFF00FFFF);
	//draw_line(&rc, -2, 1100);
	//printf("%f, ", rc.mlx->delta_time);
	//vert_line(&rc, (&rc)->pixel_x, 10, 300, RED);
	mlx_loop_hook(rc.mlx, refresh, &rc);
	mlx_key_hook(rc.mlx, key_hook, &rc);
	//mlx_mouse_hook(rc.mlx, mouse_hook, &rc);
	//mlx_loop_hook(rc.mlx, )
	mlx_loop(rc.mlx);
	mlx_terminate(rc.mlx);
	return (0);
}