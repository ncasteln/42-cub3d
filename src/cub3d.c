/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncasteln <ncasteln@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/18 08:58:26 by ncasteln          #+#    #+#             */
/*   Updated: 2024/02/15 15:58:41 by ncasteln         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/*
	STEPS TO DO TO FINISH:
	• Check for the leaks
	• Clean everyhting
		- remove traingin and its functions
		- Remove unuseful stuff
		- Remove function about floodfill of doors (check_behind_doors)
		- Norm
*/
int	main(int argc, char **argv)
{
	t_cub3d	data;

	init_cub3d(&data);
	parse(argc, argv, &data);
	sprites(&data);

	////////////////////////////////////////////////////////////////////////////////
	data.mlx = mlx_init(WIN_W, WIN_H, "cub3d", 0);
	if (!data.mlx)
		err_free_exit("main()", &data, 1, E_MLX);
	data.img = mlx_new_image(data.mlx, WIN_W, WIN_H);
	if (!data.img)
		err_free_exit("main()", &data, 1, E_MLX);

	////////////////////////////////////////////////////////////////////////////////

	init_move(data.p);
	// printf("x %f \n", data.p->pos.x);
	// printf("x %f \n", data.p->pos.y);
	correction(&data);
	// printf("x %f \n", data.p->pos.x);
	// printf("x %f \n", data.p->pos.y);
	load_textures(&data);
	if (mlx_image_to_window(data.mlx, data.img, 0, 0) == -1)
		err_free_exit("main()", &data, 1, E_MLX);
	////////////////////////////////////////////////////////////////////////////////

	if (!mlx_loop_hook(data.mlx, refresh, &data))
		err_free_exit("main()", &data, 1, E_MLX);
	mlx_key_hook(data.mlx, key_hook, &data);

	////////////////////////////////////////////////////////////////////////////////

	mlx_loop(data.mlx);
	mlx_terminate(data.mlx);
	free_data(&data);
	return (0);
}
