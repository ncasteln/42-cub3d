/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncasteln <ncasteln@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/18 08:58:26 by ncasteln          #+#    #+#             */
/*   Updated: 2024/01/25 16:51:48 by ncasteln         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/*
	THINGS TO DO TO FINISH:
	1) Handle the whitespaces inside the map:	------------------------> MARIA
		- color the floor differently?
		- use a different wall, maybe half transparent?
	2) Handle doors
	3) Handle mouse
	3) Add animation to the door
	4) Check for the leaks
	5) Clean everyhting
		- remove traingin and its functions
		- Remove unuseful stuff
		- Norm
	6) Understand the mate's code

	DOUBTS:
	- should compile with math lib ?

	QUESTION:
	- t_player which is the diff between x, y and pos.x, pos.y ?
	- The pixel are written top-down left-right, right?
	- What is line_start and _end in putline() ?

	NOTES:
	- Doors and other sprites can be placed anywhere, but sure to let the user
	change the texture?
	- Error map_06 something works not properly
	- Modfy fllod_fill() for bonus sprites
	- Remember to move out sprites.c because is not bonus anymore
*/

int	main(int argc, char **argv)
{
	t_cub3d	data;

	init_cub3d(&data);
	parse(argc, argv, &data);

	// print_map(data.map, data.n_col);
	// printf("%i \n", (int) 5.7);
	// printf("%x \n", data.assets->c);
	// printf("%x \n", data.assets->f);

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
	mlx_terminate(data.mlx); // ----- Necessary ?????
	return (0);
}
