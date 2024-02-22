/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_wall.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrubina <mrubina@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/14 19:01:50 by mrubina           #+#    #+#             */
/*   Updated: 2024/02/21 21:12:29 by mrubina          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/*
	Calculates some parameters of the vertical line that we are going to draw.
	line_start, _end and _h refers to the vertical one.
*/
void	set_draw_wall(t_raycast *rc)
{
	if (rc->wall_dist < 0.0001)
		rc->wall_dist = 0.1;
	rc->line_h = (int)(WIN_H / rc->wall_dist);
	rc->line_start = WIN_H / 2 - rc->line_h / 2;
	if (rc->line_start < 0)
		rc->line_start = 0;
	rc->line_end = WIN_H / 2 + rc->line_h / 2;
	if (rc->line_end >= WIN_H)
		rc->line_end = WIN_H;
}

/*
	Draws a vertical line pixel by pixel according to the texture.

	We iterate the texture pixels, so that its color is read and put onto
	the screen.
*/
void	putline(t_cub3d *data, int x, mlx_texture_t	*tex, t_raycast *rc)
{
	int		y;
	int		tex_y;
	double	step;
	double	tex_pos;
	int		ind;

	step = 1.0 * tex->height / rc->line_h;
	tex_pos = (rc->line_start - WIN_H / 2 + rc->line_h / 2) * step;
	y = 0;
	while (y >= 0 && y < WIN_H)
	{
		if ((y >= rc->line_start && y <= rc->line_end)
			|| rc->line_start > WIN_H)
		{
			tex_y = (int) tex_pos & (tex->height - 1);
			tex_pos += step;
			ind = (tex_y * tex->width + rc->tex_x) * tex->bytes_per_pixel;
			mlx_put_pixel(data->img, x, y, readcol(&tex->pixels[ind]));
		}
		else if (y < rc->line_start)
			mlx_put_pixel(data->img, x, y, data->assets->c);
		else if (y > rc->line_end)
			mlx_put_pixel(data->img, x, y, data->assets->f);
		y++;
	}
}
