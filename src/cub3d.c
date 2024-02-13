/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrubina <mrubina@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/18 08:58:26 by ncasteln          #+#    #+#             */
/*   Updated: 2024/02/13 02:51:48 by mrubina          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/*
	STEPS TO DO TO FINISH:
	1) Handle sprite (whitespaces, doors, others)
	2) Add animation to the door
	3) Handle mouse
	4) Check for the leaks
	5) Clean everyhting
		- remove traingin and its functions
		- Remove unuseful stuff
		- Remove function about floodfill of doors
		- Norm
	6) Understand the mate's code

	DOUBTS:
	- should compile with math lib?

	NOTES:
	- Doors and other sprites can be placed anywhere, but sure to let the user
	change the texture in the prsing? Think when done
*/

int	main(int argc, char **argv)
{
	t_cub3d	data;

	init_cub3d(&data);
	parse(argc, argv, &data);
	sprites(&data);
	// printf("total %d \n", data.n_total_sprites);
	// printf("sprites %d \n", data.n_s);
	// printf("holes %d \n", data.n_h);
	data.mlx = mlx_init(WIN_W, WIN_H, "cub3d", 0); //error handling to be added
	data.img = mlx_new_image(data.mlx, WIN_W, WIN_H);//error handling to be added
	init_move(data.p);
	// printf("x %f \n", data.p->pos.x);
	// printf("x %f \n", data.p->pos.y);
	correction(&data);
	// printf("x %f \n", data.p->pos.x);
	// printf("x %f \n", data.p->pos.y);
	load_textures(&data);
	mlx_image_to_window(data.mlx, data.img, 0, 0);//error handling to be added
	//sprites(&data);
	mlx_loop_hook(data.mlx, refresh, &data);
	mlx_key_hook(data.mlx, key_hook, &data);

	// mlx_mouse_hook(data.mlx, mouse_hook, &data);

	mlx_loop(data.mlx);
	mlx_terminate(data.mlx);
	mlx_delete_image(data.mlx, data.img);
	//delete textures
	free_data(&data);
	return (0);
}
