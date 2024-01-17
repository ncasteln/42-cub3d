/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncasteln <ncasteln@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/18 08:58:26 by ncasteln          #+#    #+#             */
/*   Updated: 2024/01/17 09:50:37 by ncasteln         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	init_cub3d(t_cub3d *data)
{
	data->assets = ft_calloc(1, sizeof(t_assets));
	if (!data->assets)
		err_free_exit("init_cub3d", data, errno);
	data->assets->no = NULL;
	data->assets->ea = NULL;
	data->assets->so = NULL;
	data->assets->we = NULL;
	data->assets->f = 0;
	data->assets->c = 0;
	data->map = NULL;
	data->line = NULL;
	data->p = NULL;
	data->n_rows = 0;
	data->n_col = 0;
}

void init_move(t_cub3d *data)
{
	data->mv->pos.x = data->p->x;
	data->mv->pos.y = data->p->y;
	if (data->p->dir == 'N' || data->p->dir == 'S')
		data->mv->dir.x = 0;
	else if (data->p->dir == 'W' || data->p->dir == 'E')
		data->mv->dir.y = 0;
	if (data->p->dir == 'N')
		data->mv->dir.y = -1;
	else if (data->p->dir == 'S')
		data->mv->dir.y = 1;
	else if (data->p->dir == 'W')
		data->mv->dir.x = -1;
	else if (data->p->dir == 'E')
		data->mv->dir.x = 1;
	data->mv->plane.x = 0.66 * data->mv->dir.x;
	data->mv->plane.y = 0.66 * data->mv->dir.y;
	rotateV(&data->mv->plane.x, &data->mv->plane.y, M_PI / 2);
	//data->mv->hit = 0;
	load_textures(data);
}

int	main(int argc, char **argv)
{
	t_cub3d	data;
	t_move mv;

	// substitute with ftbzero???
	init_cub3d(&data);
	parse(argc, argv, &data);
	print_map(data.map, data.n_col);
	// printf("%x \n", data.assets->c);
	// printf("%x \n", data.assets->f);
	data.mlx = mlx_init(WIN_W, WIN_H, "cub3d", 0);
	data.img = mlx_new_image(data.mlx, WIN_W, WIN_H);
	data.mv = &mv;
	init_move(&data);

	mlx_image_to_window(data.mlx, data.img, 0, 0);
	raycasting(&data);
	mlx_loop_hook(data.mlx, refresh, &data);
	mlx_key_hook(data.mlx, key_hook, &data);
	//mlx_mouse_hook(mv.mlx, mouse_hook, &mv);
	mlx_loop(data.mlx);
	mlx_terminate(data.mlx);
	return (0);
}
