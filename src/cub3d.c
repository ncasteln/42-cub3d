/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrubina <mrubina@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/18 08:58:26 by ncasteln          #+#    #+#             */
/*   Updated: 2024/01/22 15:16:41 by mrubina          ###   ########.fr       */
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

void init_move(t_player *p)
{
	p->pos.x = p->x;
	p->pos.y = p->y;
	if (p->dir == 'N' || p->dir == 'S')
		p->dirv.x = 0;
	else if (p->dir == 'W' || p->dir == 'E')
		p->dirv.y = 0;
	if (p->dir == 'N')
		p->dirv.y = -1;
	else if (p->dir == 'S')
		p->dirv.y = 1;
	else if (p->dir == 'W')
		p->dirv.x = -1;
	else if (p->dir == 'E')
		p->dirv.x = 1;
	p->plane.x = 0.66 * p->dirv.x;
	p->plane.y = 0.66 * p->dirv.y;
	rotateV(&p->plane.x, &p->plane.y, M_PI / 2);
}

int	main(int argc, char **argv)
{
	t_cub3d	data;

	// substitute with ftbzero???
	init_cub3d(&data);
	parse(argc, argv, &data);
	print_map(data.map, data.n_col);
	 printf("%i \n", (int) 5.7);
	// printf("%x \n", data.assets->c);
	// printf("%x \n", data.assets->f);
	data.mlx = mlx_init(WIN_W, WIN_H, "cub3d", 0);
	data.img = mlx_new_image(data.mlx, WIN_W, WIN_H);
	init_move(data.p);
	correction(&data);
	load_textures(&data);
	mlx_image_to_window(data.mlx, data.img, 0, 0);
	raycasting(&data);
	mlx_loop_hook(data.mlx, refresh, &data);
	mlx_key_hook(data.mlx, key_hook, &data);
	//mlx_mouse_hook(mv.mlx, mouse_hook, &mv);
	mlx_loop(data.mlx);
	mlx_terminate(data.mlx);
	return (0);
}


