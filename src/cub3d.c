/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrubina <mrubina@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/14 19:01:50 by mrubina           #+#    #+#             */
/*   Updated: 2023/12/18 20:12:20 by mrubina          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../include/cub3d.h"

void find_leaks()
{
	system("leaks cub3d");
}

//int	main(int argc, char *argv[])

//function draws a line
void draw_line(t_data *data, int a, int b)
{
	int x;
	int y;
	x = 0;
	y = a*x + b;
	while (x < WIN_W)
	{
		if ( y > 0 && y < WIN_W)
			mlx_put_pixel(data->img, x, y, 0xFF00FFAA);
		x++;
		y = a*x + b;
	}
}

int	main()
{
	//atexit(find_leaks);
	t_data	data;
	ft_putchar_fd('t', 2);
	data.mlx = mlx_init(WIN_W, WIN_H, "cub3d", 0);
	data.img = mlx_new_image(data.mlx, WIN_W, WIN_H);
	mlx_image_to_window(data.mlx, data.img, 0, 0);
	mlx_put_pixel(data.img, 20, 20, 0xFF0000FF);
	draw_line(&data, -2, 1100);
	mlx_key_hook(data.mlx, key_hook, &data);
	//mlx_mouse_hook(data.mlx, mouse_hook, &data);
	mlx_loop(data.mlx);
	mlx_terminate(data.mlx);
	return (0);
}