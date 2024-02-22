/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrubina <mrubina@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/14 19:01:50 by mrubina           #+#    #+#             */
/*   Updated: 2024/02/21 22:55:36 by mrubina          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

//	takes separate rgba values and returns a color
static uint32_t	getcol(uint32_t r, uint32_t g, uint32_t b, uint32_t a)
{
	return ((r << 24) + (g << 16) + (b << 8) + a);
}

/*
reads rgba values from a pixel and returns its color
p points to the r value of a pixel followed by the others
*/
uint32_t	readcol(uint8_t *p)
{
	uint32_t	b;
	uint32_t	g;
	uint32_t	r;
	uint32_t	a;

	r = (uint32_t) *(p);
	g = (uint32_t) *(p + 1);
	b = (uint32_t) *(p + 2);
	a = (uint32_t) *(p + 3);
	return (getcol(r, g, b, a));
}

/*
	Loads the textures for the library. 5 mandatory, 2 optional.
	@param [H] - represents the whitespaces of the map (we called them holes).
*/
void	load_textures(t_cub3d *data)
{
	int	i;
	int	n_tex;

	i = 0;
	n_tex = 5;
	if (BONUS && data->n_d)
		n_tex = 6;
	data->tex[NO] = mlx_load_png(data->assets->no);
	data->tex[WE] = mlx_load_png(data->assets->we);
	data->tex[SO] = mlx_load_png(data->assets->so);
	data->tex[EA] = mlx_load_png(data->assets->ea);
	data->tex[H] = mlx_load_png("./assets/hole_2.png");
	if (BONUS && data->n_d)
		data->tex[D] = mlx_load_png(data->assets->d);
	while (i < n_tex)
	{
		if (!data->tex[i])
			err_free_exit("load_textures()", data, 1, E_MLX);
		i++;
	}
}

/*
	If a ray with positive y (ray direction vector) hits a horizontal wall
	it means that the wall faces North and we use the  "North texture"
	\    /
	 \  /
	__\/_________
	similarly for other cases
 */
int	select_texture(t_raycast *rc)
{
	if (rc->raydir.y >= 0 && rc->wall_dir == NORTH_SOUTH)
		return (NO);
	else if (rc->raydir.y < 0 && rc->wall_dir == NORTH_SOUTH)
		return (SO);
	else if (rc->raydir.x >= 0 && rc->wall_dir == WEST_EAST)
		return (WE);
	else if (rc->raydir.x < 0 && rc->wall_dir == WEST_EAST)
		return (EA);
	return (-1);
}
