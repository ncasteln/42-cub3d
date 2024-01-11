/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrubina <mrubina@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/18 08:58:26 by ncasteln          #+#    #+#             */
/*   Updated: 2024/01/12 00:19:21 by mrubina          ###   ########.fr       */
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

void init_rc(t_cub3d *data)
{
	data->rc->pos_x = data->p->x;
	data->rc->pos_y = data->p->y;
	if (data->p->dir == 'N' || data->p->dir == 'S')
		data->rc->dir_x = 0;
	else if (data->p->dir == 'W' || data->p->dir == 'E')
		data->rc->dir_y = 0;
	if (data->p->dir == 'N')
		data->rc->dir_y = -1;
	else if (data->p->dir == 'S')
		data->rc->dir_y = 1;
	else if (data->p->dir == 'W')
		data->rc->dir_x = -1;
	else if (data->p->dir == 'E')
		data->rc->dir_x = 1;
	data->rc->plane_x = 0.9 * data->rc->dir_x;
	data->rc->plane_y = 0.9 * data->rc->dir_y;
	rotateV(&data->rc->plane_x, &data->rc->plane_y, -M_PI / 2);
	data->rc->hit = 0;
}

int	main(int argc, char **argv)
{
	t_cub3d	data;
	t_rc rc;

	// substitute with ftbzero???
	init_cub3d(&data);
	parse(argc, argv, &data);
	print_map(data.map, data.n_col);
printf("%x \n", data.assets->c);
	printf("%x \n", data.assets->f);
	//exit(0);
	//t_rc	rc;
	data.mlx = mlx_init(WIN_W, WIN_H, "cub3d", 0);
	data.img = mlx_new_image(data.mlx, WIN_W, WIN_H);
	data.rc = &rc;
	init_rc(&data);
	//exit(0);
	mlx_image_to_window(data.mlx, data.img, 0, 0);
	raycasting(&data);
	printf("%i \n", data.p->x);
	printf("%i \n", data.p->y);
	// exit(0);
	mlx_loop_hook(data.mlx, refresh, &data);
	mlx_key_hook(data.mlx, key_hook, &data);
	//mlx_mouse_hook(rc.mlx, mouse_hook, &rc);
	//mlx_loop_hook(rc.mlx, )
	mlx_loop(data.mlx);
	mlx_terminate(data.mlx);
	return (0);
}


