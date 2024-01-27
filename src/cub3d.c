/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncasteln <ncasteln@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/18 08:58:26 by ncasteln          #+#    #+#             */
/*   Updated: 2024/01/26 09:52:47 by ncasteln         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/*
	THINGS TO DO TO FINISH:
	1) Handle sprite (whitespaces, doors, others)
	2) Add animation to the door
	3) Handle mouse
	4) Check for the leaks
	5) Clean everyhting
		- remove traingin and its functions
		- Remove unuseful stuff
		- Norm
	6) Understand the mate's code

	DOUBTS:
	- should compile with math lib?
	- bonus_vali/sprites_01.cub is not enclosed by 1, but by $, I think it should
	be fine like that, and allow only maps which are enclosed by 1

	QUESTION:

	NOTES:
	- Doors and other sprites can be placed anywhere, but sure to let the user
	change the texture in the prsing? Think when done
	- Error map_06 something works not properly
*/

int	main(int argc, char **argv)
{
	t_cub3d	data;

	init_cub3d(&data);
	parse(argc, argv, &data);

	data.mlx = mlx_init(WIN_W, WIN_H, "cub3d", 0);
	data.img = mlx_new_image(data.mlx, WIN_W, WIN_H);
	init_move(data.p);
	correction(&data);
	load_textures(&data);
	mlx_image_to_window(data.mlx, data.img, 0, 0);

	raycasting(&data); // ----- Necessary? if removed nothing changes
	sprites(&data);
	mlx_loop_hook(data.mlx, refresh, &data);
	mlx_key_hook(data.mlx, key_hook, &data);

	// mlx_mouse_hook(data.mlx, mouse_hook, &data);

	mlx_loop(data.mlx);
	mlx_terminate(data.mlx);
	free_data(&data);
	return (0);
}
